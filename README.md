# lkm_sysctl_example
Example sysctl kernel module - create a custom runtime kernel parameter
- Creates */proc/sys/example_sysctl/value*
- Check min,max values, ie: *example_sysctl.value={0,1,2,3}*
- Export *example_sysctl_value* for other modules
- Write kernel message when value is changed
- Check for CAP_SYS_ADMIN permission before making changes
- Tested on CentOS kernel-ml-5.10.14, gcc 8.3.1
## Kernel Install
```
yum install binutils-devel readline-devel elfutils-libelf-devel

rpm --import https://www.elrepo.org/RPM-GPG-KEY-elrepo.org
yum install https://www.elrepo.org/elrepo-release-7.el7.elrepo.noarch.rpm

yum install --enablerepo=elrepo-kernel kernel-ml
yum install --enablerepo=elrepo-kernel kernel-ml-{headers,devel,tools,tools-libs,tools-libs-devel}

reboot
```
## GCC (From Software Collections)
```
yum install centos-release-scl
yum-config-manager --enable rhel-server-rhscl-7-rpms
yum install devtoolset-8
```
## Build
```
scl enable devtoolset-8 bash
make clean && make
```
## Usage
```
insmod ./example_sysctl.ko

echo 1 > /proc/sys/example_sysctl/value
sysctl example_sysctl.value=3

grep 'example_sysctl_value' /proc/kallsyms
ffffffffc07c704c r __kstrtab_example_sysctl_value       [example_sysctl]
ffffffffc07c7061 r __kstrtabns_example_sysctl_value     [example_sysctl]
ffffffffc07c703c r __ksymtab_example_sysctl_value       [example_sysctl]
ffffffffc07c84c0 B example_sysctl_value [example_sysctl]

rmmod example_sysctl

dmesg
[ 2695.142625] example_sysctl: module loaded
[ 2700.052218] example_sysctl: do something for example_sysctl_value = 1
[ 2722.583504] example_sysctl: do something for example_sysctl_value = 3
[ 2735.877559] example_sysctl: module unloaded
```
