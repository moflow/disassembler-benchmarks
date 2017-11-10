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

The current input is 1 MB taken from the kernelbase.dll .text section generated via:  
`dd if=/mnt/c/Windows/System32/KernelBase.dll of=kernelbase.text bs=1 skip=0x400 count=$((1024*1024))`


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

### BeaEngine Disassembler
```
Disassembler Benchmark: beaengine-benchmark.exe

target: kernelbase.dll .text
  addr: 0x7fff82711000
length: 1048576 bytes

Benchmark: decode to struct speed..
Time elapsed: 0.084s

Benchmark: decode to ascii speed..
Time elapsed: 0.106s

Benchmark: print ascii to /dev/null speed..
Time elapsed: 0.252s

Benchmark: decoder accuracy..
304597 decoded, 4600 errors
Time elapsed: 0.084s

Disassembler Benchmark complete.
```

### Distorm Disassembler
```
Disassembler Benchmark: distorm-benchmark.exe

target: kernelbase.dll .text
  addr: 0x7fff82711000
length: 1048576 bytes

Benchmark: decode to struct speed..
Time elapsed: 0.066s

Benchmark: decode to ascii speed..
Time elapsed: 0.123s

Benchmark: print ascii to /dev/null speed..
Time elapsed: 0.288s

Benchmark: decoder accuracy..
309181 decoded, 72 errors
Time elapsed: 0.059s

Disassembler Benchmark complete.
```
