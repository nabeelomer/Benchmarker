#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/hardirq.h>
#include <linux/preempt.h>
#include <linux/sched.h>
void inline MeasuredFunction(void)
{
  int a = 0;
  a++;
  a++;
}

static int __init BenchmarkStart(void)
{
  unsigned long flags;
  uint64_t start, end;
  unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

  printk(KERN_WARNING "Benchmarker1: Loading test module.\n");
  //Disable Premption on this CPU
  preempt_disable();
  //Disable hard interrupts
  raw_local_irq_save(flags);
  //Now we can get to work, we exclusively own the CPU
  asm volatile("CPUID\n\t"
  "RDTSC\n\t"
  "mov %%edx, %0\n\t"
  "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low) :: "%rax", "%rbx", "%rcx", "%rdx");
  MeasuredFunction();
  asm volatile("RDTSCP\n\t"
  "mov %%edx, %0\n\t"
  "mov %%eax, %1\n\t": "=r" (cycles_high1), "=r" (cycles_low1) :: "%rax", "%rbx", "%rcx", "%rdx");
  //Enable hard interrupts
  raw_local_irq_restore(flags);
  //Enable preemption
  preempt_enable();
  start = ( ((uint64_t)cycles_high << 32) | cycles_low );
  end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
  printk(KERN_WARNING "Benchmarker1: function execution time was %llu clock cycles.", (end - start));
  return 0;
}

static void __exit BenchmarkEnd(void)
{
  printk(KERN_WARNING "Benchmarker1: Module Execution Ended.");
}

module_init(BenchmarkStart);
module_exit(BenchmarkEnd);
