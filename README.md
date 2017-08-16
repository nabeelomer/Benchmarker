# Benchmarker
Micro-benchmarking framework kernel module for Linux on Intel x86-64 CPUs

# Building Benchmarker
Place the code you want to benchmark in the function `void inline MeasuredFunction();` and then execute the following in a terminal:
``` bash
# Clone the repo
~/$ git clone https://github.com/nabeelomer/Benchmarker.git
~/$ cd Benchmarker
# Build the module
~/Benchmarker$ make
# Install the module
~/Benchmarker$ sudo make install
# Display the output
~/Benchmarker$ make output
# Uninstall the module
~/Benchmarker$ sudo make uninstall
```
