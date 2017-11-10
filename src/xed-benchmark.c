#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include "xed/xed-interface.h"
#include "xed/xed-disas.h"

FILE *devnull; // initialized to Windows NUL device

xed_machine_mode_enum_t mmode;
xed_address_width_enum_t stack_addr_width;
xed_bool_t long_mode = 1;
void disas_init()
{
	xed_tables_init();
	if (long_mode) 
	{
		mmode = XED_MACHINE_MODE_LONG_64;
		stack_addr_width = XED_ADDRESS_WIDTH_64b;
	}
	else 
	{
		mmode = XED_MACHINE_MODE_LEGACY_32;
		stack_addr_width = XED_ADDRESS_WIDTH_32b;
	}
}

void benchmark_decode_bytes(uint64_t addr, uint32_t len)
{
	uint64_t curr_addr = 0;
	uint32_t offset = 0;

	while (offset <= len) 
	{
		xed_error_enum_t xed_error;
		xed_decoded_inst_t xedd;
		xed_decoded_inst_zero(&xedd);
		xed_decoded_inst_set_mode(&xedd, mmode, stack_addr_width);

		curr_addr = addr + offset;
		xed_error = xed_decode(&xedd, XED_STATIC_CAST(const xed_uint8_t*, curr_addr), 15);
		if (xed_error != XED_ERROR_NONE) 
		{
			offset++;
			continue;
		}
		offset += xed_decoded_inst_get_length(&xedd);
	}
}

void benchmark_decode_ascii(uint64_t addr, uint32_t len)
{
	uint64_t curr_addr = 0;
	uint32_t offset = 0;

	while (offset <= len) 
	{
		xed_error_enum_t xed_error;
		xed_decoded_inst_t xedd;
		xed_decoded_inst_zero(&xedd);
		xed_decoded_inst_set_mode(&xedd, mmode, stack_addr_width);

		curr_addr = addr + offset;
		xed_error = xed_decode(&xedd, XED_STATIC_CAST(const xed_uint8_t*, curr_addr), 15);
		if (xed_error != XED_ERROR_NONE) 
		{
			offset++;
			continue;
		}

		uint8_t insn_text[64];
		xed_format_context(XED_SYNTAX_INTEL, &xedd, insn_text, sizeof(insn_text), 0, 0, 0);
		offset += xed_decoded_inst_get_length(&xedd);
	}
}

void benchmark_decode_print(uint64_t addr, uint32_t len)
{
	uint64_t curr_addr = 0;
	uint32_t offset = 0;

	while (offset <= len) 
	{
		xed_error_enum_t xed_error;
		xed_decoded_inst_t xedd;
		xed_decoded_inst_zero(&xedd);
		xed_decoded_inst_set_mode(&xedd, mmode, stack_addr_width);

		curr_addr = addr + offset;
		xed_error = xed_decode(&xedd, XED_STATIC_CAST(const xed_uint8_t*, curr_addr), 15);
		if (xed_error != XED_ERROR_NONE) 
		{
			offset++;
			continue;
		}

		uint8_t insn_text[64];
		xed_format_context(XED_SYNTAX_INTEL, &xedd, insn_text, sizeof(insn_text), 0, 0, 0);
		fprintf(devnull, "%llx:\t%s\n", curr_addr, &insn_text);
		offset += xed_decoded_inst_get_length(&xedd);
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
		xed_error_enum_t xed_error;
		xed_decoded_inst_t xedd;
		xed_decoded_inst_zero(&xedd);
		xed_decoded_inst_set_mode(&xedd, mmode, stack_addr_width);

		curr_addr = addr + offset;
		xed_error = xed_decode(&xedd, XED_STATIC_CAST(const xed_uint8_t*, curr_addr), 15);
		if (xed_error != XED_ERROR_NONE) 
		{
			error_count++;
			offset++;
			continue;
		}
		insn_count++;
		offset += xed_decoded_inst_get_length(&xedd);
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