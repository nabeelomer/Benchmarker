#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/hardirq.h>
#include <linux/preempt.h>
#include <linux/sched.h>

void inline MeasuredFunction()
{
  int a = 0;
  a++;
}

static int __init BenchmarkStart()
{
  unsigned long flags;
  uint64_t start, end;
  unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

  printk(KERN_INFO, "Loading test module...\n");
  preempt_disable(); /*we disable preemption on our CPU*/
  raw_local_irq_save(flags); /*we disable hard interrupts on our CPU*/
  /*at this stage we exclusively own the CPU*/
  asm volatile("CPUID\n\t"
  "RDTSC\n\t"
  "mov %%edx, %0\n\t"
  "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low) :: "%rax", "%rbx", "%rcx", "%rdx");
  MeasuredFunction();
  asm volatile("RDTSCP\n\t"
  "mov %%edx, %0\n\t"
  "mov %%eax, %1\n\t": "=r" (cycles_high1), "=r" (cycles_low1) :: "%rax", "%rbx", "%rcx", "%rdx");
  raw_local_irq_restore(flags); /*we enable hard interrupts on our CPU*/
  preempt_enable(); /*we enable preemption*/
  start = ( ((uint64_t)cycles_high << 32) | cycles_low );
  end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
  printk(KERN_INFO, "\n function execution time was %llu clock cycles", (end - start));
  return 0;
}

static void __exit BenchmarkEnd()
{
  printk(KERN_INFO, "Module Execution Ended.");
}

module_init(BenchmarkStart);
module_exit(BenchmarkEnd);
