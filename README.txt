简单的内核kobject测试
注意：
1. struct attribute *my_attrs[] = {
	&kobj_name_attr.attr,
	&kobj_val_attr.attr,
	NULL,
};
可以看看struct kobj_type {
	void (*release)(struct kobject *);
	struct sysfs_ops	* sysfs_ops;
	struct attribute	** default_attrs;
};
结构体中default_attrs是一个数组，数组元素为struct attribute结构体指针。
其实struct attribute	** default_attrs;本身看来是一个二维数组指针。
为什么不采用struct attribute	* default_attrs[];这种形式定义呢？？？


2.从这个简单的例子可以看出，kobject常常嵌入更加复杂的结构，这个更复杂
的结构体有很多成员组成，而这些成员由my_sysfs_ops操作，my_sysfs_ops又去调用
嵌入了struct attribute更复杂的结构中的函数。
	总结一下就是，kobject嵌入到的更复杂的结构在sysfs中有一个目录表示，结构体的
变量由该目录下的文件表示。文件是有struct attribute生成，对文件的读写映射到
嵌入了struct attribute的更复杂的结构体定义的函数。
	从这里也可以看出，操作属性文件并不是要操作具体的设备，而是去修改设备、驱动
的一些属性（因为kobject要嵌入到这些复杂的结构体中），进而影响驱动的行为。但是
有些简单的设备完全可以通过属性文件表示，如cubietruck的led操作就是通过sysfs
属性文件进行的。