// syscall #548
#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/timer.h>

asmlinkage long sys_pjtimer(void) {
	const long BASE = 1e9;
    struct timespec t;
    getnstimeofday(&t);
    return t.tv_sec * BASE + t.tv_nsec;
}
