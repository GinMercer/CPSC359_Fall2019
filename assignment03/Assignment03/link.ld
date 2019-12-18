/*
 * Copyright (C) 2018 bzt (bztsrc@github)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

/*  The original file can be found at:
 *
 *     https://github.com/bztsrc/raspi3-tutorial/blob/master/05_uart0/link.ld
 *
 *  Comments have been added to explain what the script does.
 */


/*  The SECTIONS command tells the linker what sections
    should be created in the output executable (.elf) file.  */
SECTIONS
{
    /*  The location counter is initially set to the address 0x80000.
        This is where the text section, containing machine code for
        our program should go on the RPi3.  */
    . = 0x80000;

    /*  Create a .text section in the executable, using all the
        .text sections in the object files  */
    .text : { KEEP(*(.text.boot)) *(.text .text.* .gnu.linkonce.t*) }

    /*  Create a .rodata (read-only data) section in the executable,
        using all the .rodata sections in the object files  */
    .rodata : { *(.rodata .rodata.* .gnu.linkonce.r*) }

    /*  Create a .data section in the executable, using all the
        .data sections in the object files. The _data symbol is
        provided to indicate the starting address of this section  */
    PROVIDE(_data = .);
    .data : { *(.data .data.* .gnu.linkonce.d*) }

    /*  Create a .bss section in the executable, using all the
        .bss sections in the object files. No data or machine
        code is loaded into this section since it will be
        zeroed out when our program starts (in the start.s file).
        The __bss_start and __bss_end symbols record the start
        and end addresses of this section. The section is aligned
        on an address evenly divisible by 16 (quadword aligned).  */
    .bss (NOLOAD) : {
        . = ALIGN(16);
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    }

    /*  Create a symbol which gives the address of memory just
        after the end of all the sections  */
    _end = .;

    /*  The following sections are not included in the executable  */
   /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}

/*  We calculate the size (in doublewords) of the .bss section and
    record it in the __bss_size symbol.  This is used in the
    start.s code to zero out the appropriate amount of memory  */
__bss_size = (__bss_end - __bss_start) >> 3;
