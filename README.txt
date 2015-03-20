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

3.kobject_rename(obj,new_name);并没有成功，也就是对kobj_name文件的写并没有成功？
为什么呢？？

4.obj1 = kzalloc(sizeof(struct my_kobj), GFP_KERNEL);并没有对kzalloc结果进行检查


5.某些对应关系。例如my_sysfs_ops其实与源码中kobj_sysfs_ops是一样的，所以
struct attribute所嵌入的结构体要与my_kobj_attr_show中
container_of(attr, struct kobj_attribute, attr);中的struct kobj_attribute类型
要一致，当然my_sysfs_ops完全可以不调用struct attribute所嵌入的结构体中的操作。

第二次提交说明：
kobj_type结构体中的default_attrs并不一定包括kobject对应目录下的所有属性文件。
也就是在add kobject之前kobj_type的default_attrs并不用包括所有属性，但是（kobject.h）
又没有动态添加attr到kobject的接口。

所以要动态添加attr属性可以通过sysfs_create_file接口来实现。这样看来的话kobj_type
只是相当于定义了sysfs_ops、release函数。

就像core.c中在device_add中就是通过device_create_file（对sysfs_create_file的简单
封装，相当于sysfs层的添加文件函数。）添加uevent_attr、devt_attr等属性的。而不是通过
定义default_attrs实现的。

另外一个问题，所有设备的uevent_attr、devt_attr都一样吗？？或者说每个设备的对应
devt_attr属性文件读取设备号的代码都一样吗？？
答案是肯定的，都是在dev_attr_show中由kobject获得对应device、由attribute获得对应的
device_attribute，然后调用device_attribute的show函数（传入获得的device），show函数
通过传入的device得到devt。总体的思想就是通过一层一层的container_of获得对应的数据。