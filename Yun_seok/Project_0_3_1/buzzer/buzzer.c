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

//#include "buzzer.h"
#define DRV_NAME		"buzzer"

static int buz_open(struct inode *inode, struct file *filp);
static int buz_release(struct inode *inode, struct file *filp);
static int buz_register_cdev(void);
static int buz_Buzonoff(struct file *filp, unsigned int cmd, unsigned long arg);
static int __init buz_init(void);
static void __exit buz_exit(void);


struct file_operations buz_fops = { 
	.owner	= THIS_MODULE,
	.open      	= buz_open,
	.release   	= buz_release,
	.read	= buz_Buzonoff,
};

static int buz_major = 0, buz_minor = 0;
static int result;
static dev_t buz_dev;
struct cdev buz_cdev;

static int buz_open(struct inode *inode, struct file *filp)
{	printk("buz_open...\n");
	s3c_gpio_cfgpin(S3C2410_GPB(1), S3C_GPIO_SFN(1));	// set GPB[1] OUTPUT - Buzzer

	return 0;
}

static int buz_release(struct inode *inode, struct file *filp)
{
	printk("Device has been closed...\n");
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
	volatile static int i;

	switch(cmd) {
		case 0: {gpio_set_value(S3C2410_GPB(1), 0);break;}		// 0: OFF
		case 1: {										        // 1: ON
					for(i=0;i<0xfff;i++){
						gpio_set_value(S3C2410_GPB(1), 1);				
						udelay(100);
						gpio_set_value(S3C2410_GPB(1), 0);	
						udelay(100);
					}
					break;
				}
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

