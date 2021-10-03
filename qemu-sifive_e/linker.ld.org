MEMORY
{
    rom : ORIGIN = 0x20010000, LENGTH = 0x6A120
    ram : ORIGIN = 0x80000000, LENGTH = 0x4000
}

ENTRY(start)

SECTIONS
{
    .text : {*(.text*)} > rom
    .rodata : {*(.rodata*)} > rom
    .bss : {*(.bss*)} > ram
}

