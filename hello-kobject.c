#include <linux/device.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/slab.h>

#include <linux/types.h>
#include <linux/cdev.h>
MODULE_AUTHOR("mrhopehub <mrhopehub@163.com>");
MODULE_DESCRIPTION("hello kobject");
MODULE_LICENSE("GPL");
struct my_kobj
{
	int val;
	struct kobject kobj;
};
ssize_t name_show(struct kobject *obj, struct kobj_attribute *attr, char *buffer)
{
	printk("读取kobj的name:%s\n",obj->name);
	return 0;
}
 
ssize_t name_store(struct kobject *obj, struct kobj_attribute *attr,
        const char *buffer, size_t size)
{
	int i;
	char new_name[100];
	printk("当前kobj的name是:%s\n",obj->name);
	printk("写kobj的name，通过kobject_rename修改kobj的name！\n");
	for(i=0; i<size; i++)
	{
		new_name[i] = buffer[i];
	}
	new_name[i] = '\0';
	printk("kobj的新名字为:%s\n",new_name);
	kobject_rename(obj,new_name);
	printk("kobj的name修改完成，kobj的当前name为:%s\n",obj->name);
	return size;
}

ssize_t val_show(struct kobject *obj, struct kobj_attribute *attr, char *buffer)
{
	printk("读my_kobj的val:%d\n",container_of(obj,struct my_kobj,kobj)->val);
	return 0;
}
 
ssize_t val_store(struct kobject *obj, struct kobj_attribute *attr,
        const char *buffer, size_t size)
{
	printk("当前my_kobj的val为:%d\n",container_of(obj,struct my_kobj,kobj)->val);
	sscanf(buffer, "%d", &container_of(obj,struct my_kobj,kobj)->val);
	printk("修改完成，val的新值为:%d\n",container_of(obj,struct my_kobj,kobj)->val);
	return size;
}
struct kobj_attribute kobj_name_attr =
{
	.attr	= {.name = "kobj_name",0666},
	.show	= name_show,
	.store	= name_store,
};
struct kobj_attribute kobj_val_attr =
{
	.attr	= {.name = "kobj_val",0666},
	.show	= val_show,
	.store	= val_store,
};
struct attribute *my_attrs[] = {
	&kobj_name_attr.attr,
	&kobj_val_attr.attr,
	NULL,
};
static ssize_t my_kobj_attr_show(struct kobject *kobj, struct attribute *attr,
			      char *buf)
{
	struct kobj_attribute *kattr;
	ssize_t ret = -EIO;

	kattr = container_of(attr, struct kobj_attribute, attr);
	if (kattr->show)
		ret = kattr->show(kobj, kattr, buf);
	return ret;
}
static ssize_t my_kobj_attr_store(struct kobject *kobj, struct attribute *attr,
			       const char *buf, size_t count)
{
	struct kobj_attribute *kattr;
	ssize_t ret = -EIO;

	kattr = container_of(attr, struct kobj_attribute, attr);
	if (kattr->store)
		ret = kattr->store(kobj, kattr, buf, count);
	return ret;
}
const struct sysfs_ops my_sysfs_ops = {
	.show	= my_kobj_attr_show,
	.store	= my_kobj_attr_store,
};
static void my_kobj_release(struct kobject *kobj)
{
	struct my_kobj *tmp = container_of(kobj, struct my_kobj, kobj);
	kfree(tmp);
}
static struct kobj_type my_ktype = 
{
	.release	= my_kobj_release,
	.sysfs_ops	= &my_sysfs_ops,
	.default_attrs	= my_attrs,
};
static struct my_kobj *obj1;
static int __init hello_kobject_init(void)
{
	obj1 = kzalloc(sizeof(struct my_kobj), GFP_KERNEL);
	kobject_init_and_add(&obj1->kobj, &my_ktype, NULL, "mykobj1");
	obj1->val = 0;
	return 0;
}
static void __exit hello_kobject_exit(void)
{
	kobject_del(&obj1->kobj);
	kobject_put(&obj1->kobj);
}
module_init(hello_kobject_init);
module_exit(hello_kobject_exit);
