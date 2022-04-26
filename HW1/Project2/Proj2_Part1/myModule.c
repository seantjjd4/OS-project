#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_DESCRIPTION("My kernel module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jimmy");

static int my_init(void){
	printk(KERN_ALERT "myModule Init\n");
	return 0;
}

static void my_exit(void){
	printk(KERN_ALERT "myModule Exit\n");
}

module_init(my_init);
module_exit(my_exit);
