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

#include "buzzer.h"
#define DRV_NAME		"buzzer"

static int buz_open(struct inode *inode, struct file *filp);
static int buz_release(struct inode *inode, struct file *filp);
static int buz_register_cdev(void);
static int buz_Buzonoff(struct file *filp, unsigned int cmd, unsigned long arg);
static int __init buz_init(void);
static void __exit buz_exit(void);

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

static struct pwm_device *bz_pwm;

struct pwm_duty_t pwm_duty;

struct file_operations buz_fops = { 
	.owner	= THIS_MODULE,
	.open      	= buz_open,
	.release   	= buz_release,
	.unlocked_ioctl		= buz_Buzonoff,
};

static int buz_major = 0, buz_minor = 0;
static int result;
static dev_t buz_dev;
struct cdev buz_cdev;

static int buz_open(struct inode *inode, struct file *filp)
{	printk("buz_open...\n");
	s3c_gpio_cfgpin(S3C2410_GPB(1), S3C_GPIO_SFN(2));	// set GPB[1] : 1 OUTPUT - Buzzer
	bz_pwm = pwm_request(1, "bz_pwm");	
	if( NULL == bz_pwm )
	{
		printk("bz_pwm Fail!!\n");
		return -1;
	}
	pwm_duty.pulse_width = 150000;
	pwm_duty.period = 200000;
	pwm_config(bz_pwm, pwm_duty.pulse_width, pwm_duty.period);
	return 0;
}

static int buz_release(struct inode *inode, struct file *filp)
{
	printk("Device has been closed...\n");
	pwm_free( bz_pwm );
	return 0;
}

static int buz_register_cdev(void)
{
	int error;
	if(buz_major) {
		buz_dev = MKDEV(buz_major, buz_minor);
		error = register_chrdev_region(buz_dev, 1, "buz");
	} else {
		error = alloc_chrdev_region(&buz_dev, buz_minor, 1, "buz");
		buz_major = MAJOR(buz_dev);
	}
	if(error < 0) {
		printk(KERN_WARNING "can't get major %d\n", buz_major);
		return result;
	}
	printk("major number=%d\n", buz_major);

	cdev_init(&buz_cdev, &buz_fops);
	buz_cdev.owner = THIS_MODULE;
	buz_cdev.ops = &buz_fops;
	error = cdev_add(&buz_cdev, buz_dev, 1);

	if(error)
		printk(KERN_NOTICE "Register Error %d\n", error);

	return 0;

}
static int buz_Buzonoff(struct file *filp, unsigned int cmd, unsigned long arg)
{	
	static int i;

	switch(cmd) {
		case BUZZER_OFF : {pwm_disable(bz_pwm); break;}		// 0: OFF
		case BUZZER_ON : {pwm_enable(bz_pwm); break;}		// 1: ON					
	}
}

static int __init buz_init(void)
{
	printk("buz_init...\n");
	if((result = buz_register_cdev()) < 0)
	{
		return result;
	}
	return 0;
}

static void __exit buz_exit(void)
{
	cdev_del(&buz_cdev);
	unregister_chrdev_region(buz_dev, 1);

}


module_init(buz_init);
module_exit(buz_exit);

MODULE_LICENSE("GPL");

