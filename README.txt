�򵥵��ں�kobject����
ע�⣺
1. struct attribute *my_attrs[] = {
	&kobj_name_attr.attr,
	&kobj_val_attr.attr,
	NULL,
};
���Կ���struct kobj_type {
	void (*release)(struct kobject *);
	struct sysfs_ops	* sysfs_ops;
	struct attribute	** default_attrs;
};
�ṹ����default_attrs��һ�����飬����Ԫ��Ϊstruct attribute�ṹ��ָ�롣
��ʵstruct attribute	** default_attrs;��������һ����ά����ָ�롣
Ϊʲô������struct attribute	* default_attrs[];������ʽ�����أ�����


2.������򵥵����ӿ��Կ�����kobject����Ƕ����Ӹ��ӵĽṹ�����������
�Ľṹ���кܶ��Ա��ɣ�����Щ��Ա��my_sysfs_ops������my_sysfs_ops��ȥ����
Ƕ����struct attribute�����ӵĽṹ�еĺ�����
	�ܽ�һ�¾��ǣ�kobjectǶ�뵽�ĸ����ӵĽṹ��sysfs����һ��Ŀ¼��ʾ���ṹ���
�����ɸ�Ŀ¼�µ��ļ���ʾ���ļ�����struct attribute���ɣ����ļ��Ķ�дӳ�䵽
Ƕ����struct attribute�ĸ����ӵĽṹ�嶨��ĺ�����
	������Ҳ���Կ��������������ļ�������Ҫ����������豸������ȥ�޸��豸������
��һЩ���ԣ���ΪkobjectҪǶ�뵽��Щ���ӵĽṹ���У�������Ӱ����������Ϊ������
��Щ�򵥵��豸��ȫ����ͨ�������ļ���ʾ����cubietruck��led��������ͨ��sysfs
�����ļ����еġ�