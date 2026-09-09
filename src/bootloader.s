.equ UART_STATUS,       0x80000000  # 0x8000_0000
.equ UART_DATA_OFFSET,  0x4         # 0x8000_0004
.equ MAGIC_NUMBER,      0xCA        # magic number 0xCA for byte size verification, used as double guard
.equ PROGRAM_START,     0x1000      # program entry point
.equ RAM_SIZE,          0x20000     # 128 KiB RAM (matches size of RAM)
.equ STACK_TOP,         0x21000     # PROGRAM_START + RAM_SIZE, top of stack grows down from here
.equ MAX_SAFE_CYCLE,    0x4000000   # 67 million cycle safety window
    # ^^^ reset to prevent bootloader from hanging if no uart bytes received
    # need to evaluate if required or causes performance impact
    # also no, the '67' is unintentional

.section .text
.global _start

_start: # assume that when a program ends, there is a jump instruction that automatically goes back to memory 0x00000000

    # initialization

    la   s1, UART_STATUS
    addi s2, s1, UART_DATA_OFFSET
    li   s3, MAGIC_NUMBER

    reset:
        addi a0, x0, 0          # clear uart status reg (x10)
        addi a1, x0, 0          # clear uart data reg   (x11)
        addi s4, x0, 0      # size bytes

    idle:
        call uart_loop
        beq  a1, s3, load_size
        j idle

    load_size:
        addi t0, x0, 4      # loop 4 times for 4 bytes
    1:
        call uart_loop
        slli s4, s4, 8      # shift 8 bits to the left
        ori  s4, s4, a1     # merge new byte to built count
        addi t0, t0, -1     # decrement 
        bnez t0, 1b         # go back if not yet 0
        j verify

    verify:
        call uart_loop
        beq  a1, s3, load_program
        j reset

    load_program:
        li   t2, PROGRAM_START   # write pointer
    2:
        call uart_loop
        sb   a1, 0(t2)      # store byte in memory
        addi t2, t2, 1      # increment pointer (pointer goes upwards, wheeee!)
        addi s4, s4, -1     # decerment byte count
        bnez s4, 2b         # go back if not yet zero

        # set up stack that grows down, and then jump to pogram
        li   sp, STACK_TOP          # intiialize stack ptr just in case to top of RAM (0x21000)
        li   t0, PROGRAM_START
        jalr x0, 0(t0)

    # UART communication
    uart_loop:
        li   t1, MAX_SAFE_CYCLE
    3:
        lbu  a0, 0(s1)   # load UART status byte
        addi t1, t1, -1  # decrement safety checker, prevents load-use stall... pretty neat!
        beqz t1, reset
        beqz a0, 3b      # loop back while uart status is 0 (not yet valid)
        lbu  a1, 0(s2)   # load data byte once status is nonzero (valid byte ready)
        ret

    # i (partially) wrote this on my notes app on my mobile when i was in class lmfao