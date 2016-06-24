#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/hardirq.h>
#include <linux/preempt.h>
#include <linux/sched.h>
int inline MeasuredFunction(void)
{
  return 88*66*98*76/9*77;
}

static int __init BenchmarkStart(void)
{
  unsigned long InterruptFlags;
  uint64_t StartVal, EndVal;
  unsigned ClkCyclesLow, ClkCyclesHigh, ClkCyclesLow1, ClkCyclesHigh1;
  preempt_disable();
  raw_local_irq_save(InterruptFlags);

  //Now we can get to work, we own the CPU
  asm volatile("CPUID\n\t"
  "RDTSC\n\t"
  "mov %%edx, %0\n\t"
  "mov %%eax, %1\n\t": "=r" (ClkCyclesHigh), "=r" (ClkCyclesLow) :: "%rax", "%rbx", "%rcx", "%rdx");
  MeasuredFunction();
  asm volatile("RDTSCP\n\t"
  "mov %%edx, %0\n\t"
  "mov %%eax, %1\n\t": "=r" (ClkCyclesHigh1), "=r" (ClkCyclesLow1) :: "%rax", "%rbx", "%rcx", "%rdx");

  raw_local_irq_restore(InterruptFlags);
  preempt_enable();
  StartVal = ( ((uint64_t)ClkCyclesHigh << 32) | ClkCyclesLow );
  EndVal = ( ((uint64_t)ClkCyclesHigh1 << 32) | ClkCyclesLow1 );
  EndVal = (EndVal - StartVal);
  printk(KERN_INFO "Benchmarker: Code Execution Time (in clock cycles): %lld\n", EndVal);
  return 0;
}

static void __exit BenchmarkEnd(void)
{
  printk(KERN_INFO "Benchmarker: Module Execution Ended.\n");
}

module_init(BenchmarkStart);
module_exit(BenchmarkEnd);
