# Disassembler Benchmarks

## Building

All included code is cross platform compatible, currently benchmarks assume x64.  
Build scripts for Visual Studio are included until I get around to cmake

### Windows 
From a Visual Studio Command Prompt with `git` in your `%PATH%`: 
```
git clone https://github.com/moflow/disassembler-benchmarks.git
cd disassembler-benchmarks\src && build.bat
```

Note this will check out src and attempt to build all decoder libraries and benchmarks.  
This currently takes about 7 mins and takes 350 MB for the build trees.

## Benchmarks

Current benchmarks supported  

- decode to struct
- decode to ascii instruction string
- print address and instruction to null device
- decoder accuracy

### Xed Disassembler
```
Disassembler Benchmark: xed-benchmark.exe

target: kernelbase.dll .text
  addr: 0x7fff82711000
length: 1048576 bytes

Benchmark: decode to struct speed..
Time elapsed: 0.140s

Benchmark: decode to ascii speed..
Time elapsed: 0.317s

Benchmark: print ascii to /dev/null speed..
Time elapsed: 0.481s

Benchmark: decoder accuracy..
304598 decoded, 4863 errors
Time elapsed: 0.134s

Disassembler Benchmark complete.
```

### Capstone Disassembler
```
Disassembler Benchmark: capstone-benchmark.exe

target: kernelbase.dll .text
  addr: 0x7fff82711000
length: 1048576 bytes

Benchmark: decode to struct speed..
Time elapsed: 0.132s

Benchmark: decode to ascii speed..
Time elapsed: 0.171s

Benchmark: print ascii to /dev/null speed..
Time elapsed: 0.311s

Benchmark: decoder accuracy..
304587 decoded, 4875 errors
Time elapsed: 0.128s

Disassembler Benchmark complete.
```
