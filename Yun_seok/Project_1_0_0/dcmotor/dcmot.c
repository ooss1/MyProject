#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/major.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/pwm.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>

#include "dcmot.h"
#define DRV_NAME		"dc motor"

static int dcmot_open(struct inode *inode, struct file *filp);
static int dcmot_release(struct inode *inode, struct file *filp);
static int dcmot_register_cdev(void);
static int he_dcMotonoff(struct file *filp, unsigned int cmd, unsigned long arg);
static int __init dcmot_init(void);
static void __exit dcmot_exit(void);

struct pwm_device {
	struct list_head     list;
	struct platform_device  *pdev;

	struct clk      *clk_div;
	struct clk      *clk;
	const char      *label;

	unsigned int         period_ns;
	unsigned int         duty_ns;

	unsigned char        tcon_base;
	unsigned char        running;
	unsigned char        use_count;
	unsigned char        pwm_id;
};

static struct pwm_device *dc_pwm;
struct pwm_duty_t pwm_duty;

struct file_operations dcmot_fops = { 
	.owner	= THIS_MODULE,
    	.open      	= dcmot_open,
    	.release   	= dcmot_release,
	.unlocked_ioctl	= he_dcMotonoff,
};

static int dcmot_major = 0, dcmot_minor = 0;
static int result;
static dev_t dcmot_dev;
struct cdev dcmot_cdev;

static int dcmot_open(struct inode *inode, struct file *filp)
{	printk("dcmot_open...\n");
	s3c_gpio_cfgpin(S3C2410_GPG(2), S3C_GPIO_SFN(1)); 	//output - in1, 3
	s3c_gpio_cfgpin(S3C2410_GPG(3), S3C_GPIO_SFN(1));	//output - in2, 4

	s3c_gpio_cfgpin(S3C2410_GPB(2), S3C_GPIO_SFN(2));	//pwm - enable A, B
	dc_pwm = pwm_request(2, "dc_pwm");
	if( NULL == dc_pwm )
	{
		printk("dc_pwm Fail!!\n");
		return -1;
	}
	pwm_duty.pulse_width = 150000;
	pwm_duty.period = 200000;
	pwm_config(dc_pwm, pwm_duty.pulse_width, pwm_duty.period);
	 return 0;
}

static int dcmot_release(struct inode *inode, struct file *filp)
{
   	printk("Device has been closed...\n");
	pwm_free( dc_pwm );
   	return 0;
}

static int dcmot_register_cdev(void)
{
	printk("dcmot_register_cdev...\n");
	int error;
	if(dcmot_major) {
		dcmot_dev = MKDEV(dcmot_major, dcmot_minor);
		error = register_chrdev_region(dcmot_dev, 1, "dcmot");
	} else {
		error = alloc_chrdev_region(&dcmot_dev, dcmot_minor, 1, "dcmot");
		dcmot_major = MAJOR(dcmot_dev);
	}
	if(error < 0) {
		printk(KERN_WARNING "can't get major %d\n", dcmot_major);
		return result;
	}
	printk("major number=%d\n", dcmot_major);

	cdev_init(&dcmot_cdev, &dcmot_fops);
	dcmot_cdev.owner = THIS_MODULE;
	dcmot_cdev.ops = &dcmot_fops;
	error = cdev_add(&dcmot_cdev, dcmot_dev, 1);

	if(error)
		printk(KERN_NOTICE "Register Error %d\n", error);

	return 0;

}
static int he_dcMotonoff(struct file *filp, unsigned int cmd, unsigned long arg)
{
	  switch(cmd) {

		case DC_GO : {gpio_set_value(S3C2410_GPG(2), 1);	// 1 : DCMOTER GO
						gpio_set_value(S3C2410_GPG(3), 0);
						pwm_enable(dc_pwm); break;}		

		case DC_BACK : {gpio_set_value(S3C2410_GPG(2),  0);	// 2 : DCMOTER BACK
						gpio_set_value(S3C2410_GPG(3), 1);
						pwm_enable(dc_pwm); break;}		
		case DC_STOP : {gpio_set_value(S3C2410_GPG(2),  0);
					gpio_set_value(S3C2410_GPG(3), 0);
					pwm_disable(dc_pwm); break;}		// 0 : DCMOTER STOP

	  }
}

static int __init dcmot_init(void)
{
	printk("dcmot_init...\n");
	if((result = dcmot_register_cdev()) < 0)
	{
		return result;
	}
	return 0;
}

static void __exit dcmot_exit(void)
{
	cdev_del(&dcmot_cdev);
	unregister_chrdev_region(dcmot_dev, 1);

}


module_init(dcmot_init);
module_exit(dcmot_exit);

MODULE_LICENSE("GPL");

