// syscall #548
#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#define BASE 1e9

asmlinkage long sys_pjtimer(void) {
    struct timespec t;
    getnstimeofday(&t);
    return t.tv_sec * BASE + t.tv_nsec;
}
