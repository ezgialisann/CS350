#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION("0.01");


static int __init hello_init(void){
   printk(KERN_ALERT "Hello World\n");
   return 0;
}

static void __exit hello_exit(void){
   printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("Ezgi Nur Alışan");
MODULE_DESCRIPTION("First driver");


