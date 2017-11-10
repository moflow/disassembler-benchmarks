#include <stdio.h>
#include <time.h>
#include <inttypes.h>

FILE *devnull; // initialized to Windows NUL device

void disas_init()
{
}

void benchmark_decode_bytes(uint64_t addr, uint32_t len)
{
	uint64_t curr_addr = 0;
	uint32_t offset = 0;

	while (offset <= len) 
	{
		// per-iteration decoder init

		curr_addr = addr + offset;
		// disas one instruction here
		if (error) 
		{
			offset++;
			continue;
		}
		offset += // insn size
	}
}

void benchmark_decode_ascii(uint64_t addr, uint32_t len)
{
	uint64_t curr_addr = 0;
	uint32_t offset = 0;

	while (offset <= len)
	{
		// per-iteration decoder init

		curr_addr = addr + offset;
		// disas one instruction here
		if (error)
		{
			offset++;
			continue;
		}
		uint8_t insn_text[64];
		// write mnemonic and opcode text to buffer
		offset += // insn size
	}
}

void benchmark_decode_print(uint64_t addr, uint32_t len)
{
	uint64_t curr_addr = 0;
	uint32_t offset = 0;

	while (offset <= len)
	{
		// per-iteration decoder init

		curr_addr = addr + offset;
		// disas one instruction here
		if (error)
		{
			offset++;
			continue;
		}
		uint8_t insn_text[64];
		// write mnemonic and opcode text to buffer
		fprintf(devnull, "%llx:\t%s\n", curr_addr, &insn_text);
		offset += // insn size
	}
}

uint32_t insn_count = 0;
uint32_t error_count = 0;
void benchmark_accuracy(uint64_t addr, uint32_t len)
{
	uint64_t curr_addr = 0;
	uint32_t offset = 0;

	insn_count = 0;
	error_count = 0;
	while (offset <= len)
	{
		// per-iteration decoder init

		curr_addr = addr + offset;
		// disas one instruction here
		if (error)
		{
			error_count++;
			offset++;
			continue;
		}
		insn_count++;
		offset += // insn size
	}
}

int main(int argc, char **argv) 
{
	clock_t clockstart, clockdiff;
	uint32_t msec = 0;

	uint64_t code_addr = 0;
	uint32_t code_len = 0; 
	uint32_t offset = 0;

	printf("\nDisassembler Benchmark: %s\n\n", argv[0]);

	devnull = fopen("nul", "w");
	if (devnull == NULL)
	{
		fputs("could not open 'nul'", stderr);
	}

	disas_init();
	
	code_len = 1024 * 1024;
	code_addr = 0x00007fff00000000 + (uint32_t)GetModuleHandleA("kernelbase.dll") + 0x1000;
	printf("target: kernelbase.dll .text\n");
	printf("  addr: 0x%llx\n", code_addr);
	printf("length: %d bytes\n\n", code_len);

	printf("Benchmark: decode to struct speed.. \n");
	clockstart = clock();
	benchmark_decode_bytes(code_addr, code_len);
	clockdiff = clock() - clockstart;
	msec = clockdiff * 1000 / CLOCKS_PER_SEC;
	printf("Time elapsed: %d.%03ds\n\n", msec / 1000, msec % 1000);

	printf("Benchmark: decode to ascii speed.. \n");
	clockstart = clock();
	benchmark_decode_ascii(code_addr, code_len);
	clockdiff = clock() - clockstart;
	msec = clockdiff * 1000 / CLOCKS_PER_SEC;
	printf("Time elapsed: %d.%03ds\n\n", msec / 1000, msec % 1000);

	printf("Benchmark: print ascii to /dev/null speed.. \n");
	clockstart = clock();
	benchmark_decode_print(code_addr, code_len);
	clockdiff = clock() - clockstart;
	msec = clockdiff * 1000 / CLOCKS_PER_SEC;
	printf("Time elapsed: %d.%03ds\n\n", msec / 1000, msec % 1000);

	printf("Benchmark: decoder accuracy.. \n");
	clockstart = clock();
	benchmark_accuracy(code_addr, code_len);
	clockdiff = clock() - clockstart;
	msec = clockdiff * 1000 / CLOCKS_PER_SEC;
	printf("%d decoded, %d errors\n", insn_count, error_count);
	printf("Time elapsed: %d.%03ds\n\n", msec / 1000, msec % 1000);

	printf("Disassembler Benchmark complete.\n\n");

	fclose(devnull);
	//disas_fini();
	return 0;
}