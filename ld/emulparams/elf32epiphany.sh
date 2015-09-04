TEMPLATE_NAME=elf32
MACHINE=
SCRIPT_NAME=elf
OUTPUT_FORMAT="elf32-epiphany"
NO_REL_RELOCS=yes
# See also `include/elf/epiphany.h'

MMR_ADDR=0x00000000
MMR_LEN=0x100

#RESERVED_ADDR=0x00000100
#RESERVED_LEN=8128

IVT_ADDR=0x00000000
IVT_LEN=0x040

# ??? This fails: 'Not enough room for program headers, try linking with -N'
#TEXT_START_ADDR=0x00000040

#The following two lines would allow small to medium sized programs
#to run in the first 1 MB.
#TEXT_START_ADDR=0x00000060
#EXECUTABLE_SYMBOLS='PROVIDE (___bss_start = __bss_start); PROVIDE (___heap_start = end); PROVIDE (___heap_end = (0x0c0000)); PROVIDE (___stack = (0x0ffff0));'

TEXT_START_ADDR='DEFINED (__text_start) ? __text_start : 0x80000000'
EXECUTABLE_SYMBOLS='
PROVIDE (__heap_start = end);
PROVIDE (__heap_end = (0x81800000));
PROVIDE (__stack = (0x81fffff0));
PROVIDE (___bss_start = __bss_start);
PROVIDE (___heap_start = __heap_start);
PROVIDE (___heap_end = __heap_end);
PROVIDE (___stack = __stack);
'

#Smuggle an alignemnt directive in here so that .bss is aligned.
OTHER_SDATA_SECTIONS='. = ALIGN(8);'


ARCH=epiphany
ENTRY=_start
EMBEDDED=yes
ELFSIZE=32
ALIGNMENT=8
#MAXPAGESIZE=8192
MAXPAGESIZE=1
WRITABLE_RODATA=
#OTHER_RELOCATING_SECTIONS=
#OTHER_READONLY_SECTIONS=
#OTHER_READWRITE_SECTIONS=
