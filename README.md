# Benchmarker
Benchmarker is a Linux kernel module that helps you Benchmark pieces of code.

# Using Benchmarker
Place the code you want to benchmark in the function `void inline MeasuredFunction();` and then build the module.
Currently Benchmarker is only useful when benchmarking algorithms and code snippets, not whole programs.
