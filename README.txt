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

3.kobject_rename(obj,new_name);��û�гɹ���Ҳ���Ƕ�kobj_name�ļ���д��û�гɹ���
Ϊʲô�أ���

4.obj1 = kzalloc(sizeof(struct my_kobj), GFP_KERNEL);��û�ж�kzalloc������м��


5.ĳЩ��Ӧ��ϵ������my_sysfs_ops��ʵ��Դ����kobj_sysfs_ops��һ���ģ�����
struct attribute��Ƕ��Ľṹ��Ҫ��my_kobj_attr_show��
container_of(attr, struct kobj_attribute, attr);�е�struct kobj_attribute����
Ҫһ�£���Ȼmy_sysfs_ops��ȫ���Բ�����struct attribute��Ƕ��Ľṹ���еĲ�����

�ڶ����ύ˵����
kobj_type�ṹ���е�default_attrs����һ������kobject��ӦĿ¼�µ����������ļ���
Ҳ������add kobject֮ǰkobj_type��default_attrs�����ð����������ԣ����ǣ�kobject.h��
��û�ж�̬���attr��kobject�Ľӿڡ�

����Ҫ��̬���attr���Կ���ͨ��sysfs_create_file�ӿ���ʵ�֡����������Ļ�kobj_type
ֻ���൱�ڶ�����sysfs_ops��release������

����core.c����device_add�о���ͨ��device_create_file����sysfs_create_file�ļ�
��װ���൱��sysfs�������ļ������������uevent_attr��devt_attr�����Եġ�������ͨ��
����default_attrsʵ�ֵġ�

����һ�����⣬�����豸��uevent_attr��devt_attr��һ���𣿣�����˵ÿ���豸�Ķ�Ӧ
devt_attr�����ļ���ȡ�豸�ŵĴ��붼һ���𣿣�
���ǿ϶��ģ�������dev_attr_show����kobject��ö�Ӧdevice����attribute��ö�Ӧ��
device_attribute��Ȼ�����device_attribute��show�����������õ�device����show����
ͨ�������device�õ�devt�������˼�����ͨ��һ��һ���container_of��ö�Ӧ�����ݡ�