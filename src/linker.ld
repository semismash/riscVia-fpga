/* LINKER SCRIPT */

MEMORY
{
    RAM (rwx) : ORIGIN = 0x00000000, LENGTH = 0x21000
}

ENTRY(_start)

SECTIONS
{
    . = 0x00000000;

    .text : {
        *(.text)
        *(.text.*)
    } > RAM

    .rodata : {
        *(.rodata)
        *(.rodata.*)
    } > RAM

    .data : {
        *(.data)
        *(.data.*)
    } > RAM

    .bss : {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    } > RAM

    /* Reserve 0x1000 onward for the loaded program - bootloader
       code/data must not grow past this point. */
    ASSERT(. <= 0x1000, "Bootloader image overflows into PROGRAM_START (0x1000) region")

    /DISCARD/ : {
        *(.comment)
        *(.eh_frame)
    }
}