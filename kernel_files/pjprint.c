// syscall #549 
#include <linux/linkage.h>
#include <linux/kernel.h>
#define BASE 1e9

asmlinkage void sys_pjprint(int pid, long start, long end) {
	if(pid==0)
		printk(KERN_INFO "[RELEASE]");
	else
    	printk(KERN_INFO "[Project1] %d %ld.%09ld %ld.%09ld", pid, start / BASE, start % BASE, end / BASE, end % BASE);
}
