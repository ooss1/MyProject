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
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>

#define DRV_NAME		"sub motor"

#define L		0
#define R		1

static int submot_open(struct inode *inode, struct file *filp);
static int submot_release(struct inode *inode, struct file *filp);
static int submot_register_cdev(void);
static int he_subMotonoff(struct file *filp, unsigned int cmd, unsigned long arg);
static int __init submot_init(void);
static void __exit submot_exit(void);


struct file_operations submot_fops = { 
	.owner	= THIS_MODULE,
    	.open      	= submot_open,
    	.release   	= submot_release,
	.write	= he_subMotonoff,
};

static int submot_major = 0, submot_minor = 0;
static int result;
static dev_t submot_dev;
struct cdev submot_cdev;

static int submot_open(struct inode *inode, struct file *filp)
{	printk("submot_open...\n");
	s3c_gpio_cfgpin(S3C2410_GPG(1), S3C_GPIO_SFN(1));	// set GPG[1] OUTPUT - SubMotor
	 return 0;
}

static int submot_release(struct inode *inode, struct file *filp)
{
    printk("Device has been closed...\n");
    return 0;
}

static int submot_register_cdev(void)
{
	int error;
	if(submot_major) {
		submot_dev = MKDEV(submot_major, submot_minor);
		error = register_chrdev_region(submot_dev, 1, "submot");
	} else {
		error = alloc_chrdev_region(&submot_dev, submot_minor, 1, "submot");
		submot_major = MAJOR(submot_dev);
	}
	if(error < 0) {
		printk(KERN_WARNING "can't get major %d\n", submot_major);
		return result;
	}
	printk("major number=%d\n", submot_major);

	cdev_init(&submot_cdev, &submot_fops);
	submot_cdev.owner = THIS_MODULE;
	submot_cdev.ops = &submot_fops;
	error = cdev_add(&submot_cdev, submot_dev, 1);

	if(error)
		printk(KERN_NOTICE "Register Error %d\n", error);

	return 0;

}
static int he_subMotonoff(struct file *filp, unsigned int cmd, unsigned long arg)
{
	  switch(cmd) {	
		case L : {gpio_set_value(S3C2410_GPG(1),  1); mdelay(1.5);
			     gpio_set_value(S3C2410_GPG(1),  0); mdelay(18.5); break;}		
		case R : {gpio_set_value(S3C2410_GPG(1),  1); mdelay(2.4);
			      gpio_set_value(S3C2410_GPG(1),  0);  mdelay(17.6); break;}
	  }
}

static int __init submot_init(void)
{
	printk("submot_init...\n");
	if((result = submot_register_cdev()) < 0)
	{
		return result;
	}
	return 0;
}

static void __exit submot_exit(void)
{
	cdev_del(&submot_cdev);
	unregister_chrdev_region(submot_dev, 1);

}


module_init(submot_init);
module_exit(submot_exit);

MODULE_LICENSE("GPL");

