/*BEGIN_LEGAL

Copyright (c) 2016 Intel Corporation

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

END_LEGAL */
/// @file xed-min.c
/// @brief a minimal toy example of using the decoder.

#include "xed/xed-interface.h"
#include "xed/xed-disas.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv);

int main(int argc, char** argv) {
    xed_machine_mode_enum_t mmode;
    xed_address_width_enum_t stack_addr_width;
    xed_bool_t long_mode = 1;

    // initialize the XED tables -- one time.
    xed_tables_init();

    // The state of the machine -- required for decoding
    if (long_mode) {
        mmode=XED_MACHINE_MODE_LONG_64;
        stack_addr_width = XED_ADDRESS_WIDTH_64b;
    }
    else {
        mmode=XED_MACHINE_MODE_LEGACY_32;
        stack_addr_width = XED_ADDRESS_WIDTH_32b;
    }

    // Setup variables for disassembling .text of kernelbase.dll
    unsigned long long code_addr = (unsigned long long)GetModuleHandleA("kernelbase.dll") + 0x1000;
    unsigned long long curr_addr = 0;
    unsigned long code_len = 1024 * 1024;
    unsigned long code_offset = 0;
    unsigned long insn_count = 0;
    unsigned long error_count = 0;

    printf("target: kernelbase.dll .text\n");
    printf("  addr: 0x%llx\n", code_addr);
    printf("length: %d bytes\n\n", code_len);

	clock_t clockstart = clock();

    while(code_offset <= code_len) {
        xed_error_enum_t xed_error;
        xed_decoded_inst_t xedd;
        xed_decoded_inst_zero(&xedd);
        xed_decoded_inst_set_mode(&xedd, mmode, stack_addr_width);

        curr_addr = code_addr + code_offset;
        xed_error = xed_decode(&xedd, XED_STATIC_CAST(const xed_uint8_t*, &curr_addr), 15);
        if (xed_error != XED_ERROR_NONE) {
          //printf("%llx: DECODE ERROR: %s\n", curr_addr, xed_error_enum_t2str(xed_error));
          code_offset++;
          continue;
        }

        // print disassembly string to memory buffer
		char insn_text[64];
        if(xed_format_context(XED_SYNTAX_INTEL, &xedd, insn_text, sizeof(insn_text), 0, 0, 0))
        {
          //printf("%llx:\t%s\n", curr_addr, &insn_text);
        }
        else
        {
          //printf("%llx: DISASSEMBLY ERROR\n", curr_addr);
          code_offset++;
          continue;
        }
                
        code_offset += xed_decoded_inst_get_length(&xedd);

    }

	clock_t clockdiff = clock() - clockstart;
	int msec = clockdiff * 1000 / CLOCKS_PER_SEC;
	printf("Time elapsed: %d.%ds", msec / 1000, msec % 1000);


    return 0;
    (void) argc; (void) argv; //pacify compiler
}
