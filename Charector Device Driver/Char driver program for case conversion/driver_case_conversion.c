#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/errno.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

static char ker_buf[100];   //driver local  buffer

static int dev_open(struct inode *inod, struct file *fil);

static ssize_t dev_read(struct file *filep,char *buf,size_t len,loff_t *off);

static ssize_t dev_write(struct file *flip,const char *buff,size_t len,loff_t *off);

static int dev_release(struct inode *inod,struct file *fil);

//structure containing device operation

static struct file_operations fops=

{
	.owner = THIS_MODULE,		 
	.read=dev_read,  //pointer to device read funtion

	.write=dev_write, //pointer to device write function

	.open=dev_open,   //pointer to device open function

	.release=dev_release, //pointer to device realese function

};

static int hello_init(void)   //init function to be called at the time of insmod

{

	int t=register_chrdev(95,"mydev",&fops);

	if(t<0)

		printk(KERN_ALERT "device registration failed\n");

	else

		printk(KERN_ALERT "device registred\n");

	return 0;

}

static void hello_exit(void) //exit function to be called at the time of rmmod
{
	unregister_chrdev(95,"mydev");
	printk(KERN_ALERT "exit");
}

static int dev_open(struct inode *inod, struct file *fil)
{
	printk(KERN_ALERT "device opened\n");
	return 0;
}

static ssize_t dev_read(struct file *filep,char *buf,size_t len,loff_t *off)
{
	printk(KERN_ALERT "device readed\n");
	copy_to_user(buf,ker_buf,len);
	return len;
}

static ssize_t dev_write(struct file *flip,const char *buf,size_t len,loff_t *off)
{
	printk(KERN_ALERT "device writted\n");

	printk(KERN_ALERT " %s\n", buf);

	static int i;
	copy_from_user(ker_buf,buf,len);
	printk(KERN_ALERT " %s\n", ker_buf);
	ker_buf[len]=0;	

	for (i = 0; i < len; i++)
	{
		if ( ker_buf[i] >= 97 && ker_buf[i] <= 122)
		{
			ker_buf[i] = ker_buf[i] - 32;
		}
	}

	return len;
}

static int dev_release(struct inode *inod,struct file *fil)
{
	printk(KERN_ALERT "device closed\n");
	return 0;
}

module_init(hello_init);

module_exit(hello_exit);

