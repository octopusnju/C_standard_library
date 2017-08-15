#ifndef __SMP_MB_H__
#define __SMP_MB_H__

#define smp_mb() mb()
#define smp_rmb() rmb()
#define smp_wmb() wmb()

#define mb() asm volatile("mfence":::"memory")
#define rmb() asm volatile("lfence":::"memory")
#define wmb() asm volatile("sfence":::"memory")

#endif /*__SMP_MB_H__*/
