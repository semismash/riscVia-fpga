# BIOS specific constant declarations
.equ MAX_TIMEOUT_CYCLE, 0x4000000                   # 67 million cycle safety window
.equ UART_STATUS,       0x80000000                  # 0x8000_0000
.equ UART_RXD_OFFSET,   0x4                         # 0x8000_0004
.equ UART_TXD_OFFSET,   0x8                         # 0x8000_0008
.equ PROGRAM_START,     0x1000                      # program entry point
.equ RAM_SIZE,          0x20000                     # 128 KiB RAM (matches size of RAM)
.equ PROGRAM_TOP,       0x20000                     # program top address, everything above that is reserved by BIOS
.equ RAM_TOP,           PROGRAM_START + RAM_SIZE    # PROGRAM_START + RAM_SIZE, top of stack grows down from here, (0x21000)

.equ BIOS_STACK_SIZE    64                          # 64 bytes allocated for BIOS

.include "protocol.inc"

# REGISTER USAGE:
# a0 - callee return value 1
# a1 - callee return value 2
# a0-a4 - function arguments
# a5 - BIOS state
# t0-t6 - temporary function-specific variables
# s0-s11 - global/high-lifetime variables

# MEMORY LAYOUT:
# 0x00000000 - 0x00000FFF: BIOS ROM
# 0x00001000 - 0x0001FFFF: PROGRAM SPACE (PROGRAM STACK DEFAULT: 0x00020000)
# 0x00020000 - 0x00020FBF: BIOS DATA SPACE
# 0x00020FC0 - 0x00021000: BIOS STACK (allocate 64 bytes (16 words) space for BIOS stack)

.global _start

.section .rodata
.align 2

bios_start_msg:
    .string "BIOS Loaded Successfully!"

program_start:      # 0x1000
    .word   PROGRAM_START
ram_size:           # 0x20000
    .word   RAM_SIZE
ram_top:            # 0x21000
    .word   RAM_TOP
program_top:        # 0x20000
    .word   PROGRAM_TOP
bios_stack_top:     # 0x21000
    .word   RAM_TOP
program_stack_top:  # 0x20000
    .word   PROGRAM_TOP

bios_mem_size:
    .word   RAM_TOP - PROGRAM_TOP - BIOS_STACK_SIZE

.section .text

_start:

# BIOS UTILITY
reset:
    # initialize BIOS constants (UART mainly)
    la      s1, UART_STATUS             # s1 - UART STATUS
    addi    s2, s1, UART_RXD_OFFSET     # s2 - UART RX DATA
    addi    s3, s1, UART_TXD_OFFSET     # s3 - UART TX DATA

    la      sp, bios_stack_top      # initialize stack

idle:
    call    uart_rx                 # call uart rx in idle to receive command
    mv      t0, a0                  # move result to t0 scratch reg
    
    # conditional switch table for all different intiialization bytes
    addi    t1, x0, TB_MSG_ECHO     # check msg echo byte
    beq     t0, t1, msg_echo
    addi    t1, x0, TB_ST_INIT      # check self test init
    beq     t0, t1, self_test
    addi    t1, x0, TB_META_START   # check telemetry display innit
    beq     t0, t1, telemetry
    addi    t1, x0, TB_MEM_DUMP     # memory dump
    beq     t0, t1, memory
    addi    t1, x0, TB_NET_ACK      # connection attempt
    beq     t0, t1, connect
    addi    t1, x0, TB_DD_DATA      # check device data request
    beq     t0, t1, device_data
    addi    t1, x0, TB_BIOS_DATA    # check if BIOS data monitoring is turned on
    beq     t0, t1, bios_log

    j       idle                    # loop around if no valid command bytes, no error 

msg_echo:
    call    push_addr       # push address to stack
    call    get_size        # fetch size of message
    call    push_addr       # push address to stack again
    call    gets            # get input string of byte size            

self_test:

telemetry:

memory:

connect:

device_data:

bios_log:

# HELPERS

push_addr:  # push address to stack, always to be used before a call instruction to be used correctly
    addi    t0, ra, 4       # add 4 bytes to caller address (skip two instructions ahead of caller, saved ra + 1 extra for skipping next call)
    addi    sp, sp, -4      # decrement stack pointer
    sw      t0, 0(sp)       # save address of stack pointer to stack
    ret

pop_addr:
    mv      t0, ra          # move current ra to t0
    lw      ra, 0(sp)       # fetch top item from stack
    addi    sp, sp, 4       # increment stack to decrease size
    jr      t0              # jump to the previous ra value (return from original function call)

uart_rx:    # UART polling loops (no interrupts yet :/)
    li      t1, MAX_TIMEOUT_CYCLE
1:
    lbu     t0, 0(s1)       # load UART status byte
    addi    t1, t1, -1      # decrement timeout checker
    beqz    t1, timeout_handler
    andi    t0, t0, 0x01    # mask only bit 1 (RX VALID)
    beqz    t0, 1b          # loop back while uart status is 0 (not yet valid)
    lbu     a0, 0(s2)       # load data byte once status is nonzero (valid byte ready)
    ret

uart_tx:    # NOTE: no need for safety checker here, as its BIOS side, cannot timeout ideally
1:
    lbu     t0, 0(s1)       # load UART status byte
    andi    t0, t0, 0x02    # mask only bit 2 (TX BUSY)
    bnez    t0, 1b          # wait till valid (until tx_busy != 1)
    sb      a2, 0(s3)       # send data via UART channel once no longer busy
    ret

get_size:   # little endian 4 byte size
    addi    t0, x0, 4       # loop 4 times for 4 bytes
    addi    t1, x0, 0       # initialize shift counter to 0 bits
1:  
    call    uart_rx
    sll     t2, a0, t1      # shift new byte left by current shift counter (0 -> 8 -> 16 -> 24)
    or      t3, t3, t2      # merge the shifted byte into final reg
    addi    t1, t1, 8       # increment shift counter by 8 bits for the next byte
    addi    t0, t0, -1      # decrement shift loop counter
    bnez    t0, 1b          # go back if not yet 0

    mv      a0, t3          # move from temp register to return register
    call    pop_addr        # pop stack saved address
    ret

gets:
    li      t0, program_top         # go to start of BIOS data space
    mv      t1, a0                  # program size  
    addi    t2, x0, bios_mem_size   # bios mem size (4032) for data
    bge     t1, t2, 2b              # if message size too high, automatically raise error
1:
    call    uart_rx
    sb      a0, 0(t0)       # store pointer
2:
    li
    j       error_handler

puts:


# HANDLERS
timeout_handler:    # uses a5 for checking operation

error_handler:

