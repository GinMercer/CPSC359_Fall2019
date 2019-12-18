#  This is a basic Makefile for cross-compiling C language and A64 (aarch64)
#  assembly code into a kernel8.img, which can be run on the Raspberry Pi 3
#  or using the Qemu emulator.
#
#  To compile your project, type 'make' or 'make all' at the command line.
#  This will create the kernel8.img file, plus a kernel8.dump file. The
#  dump file is a text file which shows the structure and contents of the
#  executable file (kernel8.elf), and may be useful when debugging.
#
#  To remove all the intermediate files from your directory, type
#  'make clean' at the command line.
#
#  Typing 'make run' will execute your program (contained in the
#  kernel8.img file) using the Qemu emulator. Qemu is started using
#  flags that set it to emulate a Raspberry Pi 3.
#
#  Note that this Makefile relies on linker script file normally
#  named 'link.ld'. The rules in this file tell the ld linker
#  how to create and structure the executable file (kernel8.elf).
#  Read the comments in link.ld for more information.


#  The following indicates where the Linaro gcc toolchain has been
#  installed on the host machine. If the toolchain was installed
#  at another location in the file hierarchy, then this line will
#  have to be changed.
INSTALL_DIRECTORY = /usr/local/linaro/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-elf/bin/

#  The following are the complete paths to the gcc compiler,
#  the as assembler, the ld linker, and the objcopy and objdump
#  facilities.
GCC = $(INSTALL_DIRECTORY)aarch64-elf-gcc
AS = $(INSTALL_DIRECTORY)aarch64-elf-as
LD = $(INSTALL_DIRECTORY)aarch64-elf-ld
OBJCOPY = $(INSTALL_DIRECTORY)aarch64-elf-objcopy
OBJDUMP = $(INSTALL_DIRECTORY)aarch64-elf-objdump

#  This following gives the name of the linker script file
#  used by the ld linker when linking together all the
#  object (.o) files. This file should be in the same
#  directory as your source files and Makefile.
LINK_SCRIPT = link.ld

#  The following gives the suffixes assumed for the project's
#  source code files that will be compiled or assembled. All
#  files ending in .asm or .s or .c will be compiled or assembled
#  into object code, and put into files ending in .o
ASM_SOURCE_FILES = $(wildcard *.asm)
S_SOURCE_FILES = $(wildcard *.s)
C_SOURCE_FILES = $(wildcard *.c)
ASM_OBJECT_FILES = $(ASM_SOURCE_FILES:.asm=.o)
S_OBJECT_FILES = $(S_SOURCE_FILES:.s=.o)
C_OBJECT_FILES = $(C_SOURCE_FILES:.c=.o)

#  These C flags are used when invoking gcc, and tell the
#  compiler to show all warnings, to do level 2 optimization,
#  and to create freestanding code that does not include
#  the usual libraries and startup code.
C_FLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles

#  These link flags tell the ld linker not to include the
#  usual libraries and startup code.
LD_FLAGS = -nostdlib -nostartfiles

#  These flags tell the objdump facility to disassemble code
#  sections in the executable (.elf file), to display source
#  code intermixed with disassembly (if possible), to
#  display the full contents of any sections requested,
#  and to display section header summaries.
OBJDUMP_FLAGS = -d -S -s -h



#  This is the Makefile's main target
all: clean kernel8.img

#  The following is a suffix rule that indicates how
#  a file ending in .asm should be processed to create
#  a corresponding file ending in .o (i.e. a file that
#  contains object code). The .asm file is assumed to
#  contain m4 macros plus A64 assembly code. The .asm
#  file is first run through the m4 preprocessor, and
#  produces a corresponding .S file that contains pure
#  assembly code. Secondly, the .S file is assembled
#  using the 'as' assembler, producing a corresponding
#  .o file.
%.o: %.asm
	m4 $< > $*.S
	$(AS) $*.S -o $@

#  The following suffix rule indicates how a file
#  ending in .s should be processed to create a
#  corresponding file ending in .o (i.e. a file that
#  contains object code). The .s file should contain
#  pure A64 assemble code (no macros!).
%.o: %.s
	$(AS) $< -o $@

#  The following rule indicates how a file ending
#  in .c should be processed to create a corresponding
#  file ending in .o (i.e. a file that contains
#  object code). The .c file should contain pure
#  C code.
%.o: %.c
	$(GCC) $(C_FLAGS) -c $< -o $@

#  The following target indicates how to create the
#  kernel8.img file. This target depends on all of
#  the .o files created from .asm or .s or .c source
#  code files. The 'ld' linker links all these .o
#  files together to create a temporary kernel8.elf
#  file. The 'objcopy' facility then creates a
#  kernel8.img file from the .elf file, and finally
#  'objdump' is invoked to create a kernel8.dump
#  text file, which shows the structure and contents
#  of the .elf file.
kernel8.img: $(ASM_OBJECT_FILES) $(S_OBJECT_FILES) $(C_OBJECT_FILES)
	$(LD) $(LD_FLAGS) $(ASM_OBJECT_FILES) $(S_OBJECT_FILES) $(C_OBJECT_FILES) -T $(LINK_SCRIPT) -o kernel8.elf
	$(OBJCOPY) -O binary kernel8.elf kernel8.img
	$(OBJDUMP) $(OBJDUMP_FLAGS) kernel8.elf > kernel8.dump

#  This target removes all intermediate files with the
#  .o and .S and .dump suffixes, as well as kernel8.elf.
#  Any warning or error messages are thrown away (redirected
#  to /dev/null), and if errors occur, processing will
#  still continue.
clean:
	rm kernel8.elf *.o *.S *.dump >/dev/null 2>/dev/null || true

#  The following target runs the kernel8.img file in
#  the Qemu emulator while emulating a Raspberry Pi 3.
#  Any serial I/O is handled using standard input and
#  output.
run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio
