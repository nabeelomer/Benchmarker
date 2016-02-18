# Benchmarker
Benchmarker is a Linux kernel module that helps you Benchmark pieces of code on Intel x86 and x86-64 CPUs.

# Building Benchmarker
Place the code you want to benchmark in the function `void inline MeasuredFunction();` and then execute the following in a terminal:
```
# Build the module
$ make
# Install the module
$ sudo make install
# Display the output
$ make output
# Uninstall the module
$ sudo make uninstall
```
Currently Benchmarker is only useful when benchmarking algorithms and code snippets, not whole programs.
