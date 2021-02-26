#include <linux/version.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sysctl.h>
#include <linux/security.h>

/* module information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("csh@github");
MODULE_DESCRIPTION("example sysctl");
MODULE_VERSION("1.0");

static struct ctl_table_header *sysctl_th;

/* default, min, max values */
int example_sysctl_value = 0;
static int min_val = 0;
static int max_val = 3;

static int example_prog_handler(struct ctl_table *table, int write, void *buffer, size_t *lenp, loff_t *ppos) {
	int rc = 0;

	/* check permission */
	if(write && !capable(CAP_SYS_ADMIN)) {
		return -EPERM;
	}

	/* checks min,max values before write  */
	rc = proc_dointvec_minmax(table, write, buffer, lenp, ppos);

	//printk(KERN_ALERT "example_sysctl: call example_prog_handler(), write:%d example_sysctl_value:%d rc:%d\n",write,example_sysctl_value,rc);

	if(rc < 0) {
		return rc;
	}

	if(write) {
		switch(example_sysctl_value) {
			case 0:
				printk(KERN_ALERT "example_sysctl: do something for example_sysctl_value = %d\n",example_sysctl_value);
			break;
			case 1:
				printk(KERN_ALERT "example_sysctl: do something for example_sysctl_value = %d\n",example_sysctl_value);
			break;
			case 2:
				printk(KERN_ALERT "example_sysctl: do something for example_sysctl_value = %d\n",example_sysctl_value);
			break;
			case 3:
				printk(KERN_ALERT "example_sysctl: do something for example_sysctl_value = %d\n",example_sysctl_value);
			break;
		}
	}

	return rc;
}

static struct ctl_table sysctl_table[] = {
	{
		.procname	= "value",
		.data		= &example_sysctl_value,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= example_prog_handler,
		.extra1		= &min_val,
		.extra2		= &max_val,
        },

	{}
};

static struct ctl_table sysctl_dir_table[] = {
        {
		.procname 	= "example_sysctl",
		.mode		= 0555,
		.child		= sysctl_table
        },

	{}
};

static int __init example_sysctl_init(void) {

	if(!(sysctl_th = register_sysctl_table(sysctl_dir_table))) {
		printk(KERN_ALERT "ERROR: loading example_sysctl\n");
		return EPERM;
	}

	printk(KERN_ALERT "example_sysctl: module loaded\n");
	return(0);
}

static void __exit example_sysctl_exit(void) {

	if(sysctl_th) {
		unregister_sysctl_table(sysctl_th);
	}

	sysctl_th = NULL;
	printk(KERN_ALERT "example_sysctl: module unloaded\n");
}

/* export the value for other modules */
EXPORT_SYMBOL(example_sysctl_value);

module_init(example_sysctl_init);
module_exit(example_sysctl_exit);
