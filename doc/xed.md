# Intel XED2 Disassembler Library

The Intel XED2 disassembler library is a high performance disassembly library that traditionally was included with the PIN toolkit. It was recently became open source under an Apache License. 



### Capabilities

- Disassembly: x86, amd64
- Assembly: x86, amd64
- Semantics



### Building

The project builds into a static library with little effort. You have the option whether to include functionality for either decoder or encoder APIs. 

```
mkdir build
cd build
git clone https://github.com/intelxed/xed.git xed
git clone https://github.com/intelxed/mbuild.git mbuild
cd xed
./mfile.py install
```
The resulting build will be in a date stamped directory in `build/xed/kits` 
Copy the include and lib directories from the build to the directory with the xed benchmark code. 

To build the tool used for benchmarking execute the following in a Visual Studio Command Prompt: 

```
cl /Zx /I include xed-benchmark.c xed.lib kernel32.lib xed-ild.lib
```



### Benchmark

The current benchmark tests instruction decoder speed by disassembling the .text section of a currently mapped library. By default we use the memory mapping of `c:\windows\system32\kernelbase.dll` because it is mapped into every process and the .text section is about 1.5 MB. 



### Results

Current results decoding 1 MB of kernelbase.dll on my surface book i7

```
$ time ./xed-benchmark.exe
kernelbase.dll .text segment: ffffffffc4ff1000

real    0m1.104s
```
