#include <linux/init.h>  
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/random.h>

MODULE_LICENSE("IDEK CORPORATION");

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

struct birthday *birthday_list, *tmp, *ptr;
struct list_head *pos;

int myInit(void){
	

	int i;
	int BD_data[5][3] = {{1999, 2, 6}, {2000, 1, 1}, {2001, 8, 7},
			      {2002, 7, 7}, {2003, 6, 9}};
	birthday_list = kmalloc(sizeof(*birthday_list), GFP_KERNEL);
	birthday_list->year = 2001;
	birthday_list->month = 9;
	birthday_list->day = 5;
	
	INIT_LIST_HEAD(&(birthday_list->list));
	printk(KERN_INFO "...Creating Module...\n");
	
	for(i=0; i<5; i++){
		ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
		ptr->year = BD_data[i][0];
		ptr->month = BD_data[i][1];
		ptr->day = BD_data[i][2];
		list_add(&(ptr->list), &(birthday_list->list));
	}

	printk(KERN_INFO "...Traveresing List...\n");
	list_for_each(pos, &(birthday_list->list)){
		tmp = list_entry(pos, struct birthday, list);
		printk("%d/%d/%d\n", tmp->year, tmp->month, tmp->day);
	}
	return 0;
}

void myExit(void){
	printk(KERN_INFO "...Removing Module...\n");  
	list_for_each_entry_safe(ptr, tmp, &birthday_list->list, list){
		printk(KERN_INFO "%d/%d/%d Removed", ptr->year, ptr->month, ptr->day);
		list_del(&(ptr->list));
		kfree(ptr);
	}
	printk(KERN_INFO "...Free All Memory...\n"); 
}

module_init(myInit);

module_exit(myExit);
