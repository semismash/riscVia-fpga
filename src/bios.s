# BIOS specific constant declarations
.equ MAX_TIMEOUT_CYCLE, 0x4000000   # 67 million cycle safety window
.equ UART_STATUS,       0x80000000  # 0x8000_0000
.equ UART_RXD_OFFSET,   0x4         # 0x8000_0004
.equ UART_TXD_OFFSET,   0x8         # 0x8000_0008

.include "protocol.inc"

# REGISTER USAGE:
# a0 - callee return value 1
# a1 - callee return value 2
# a2-a4 - function arguments
# a5 - BIOS state
# t0-t6 - temporary function-specific variables
# s0-s11 - global/high-lifetime variables

.global _start

.section .rodata
.align 2

bios_start_msg:
    .string "BIOS Loaded Successfully!"

.section .text

_start:
    # jump table here for reference, to be removed later
    j reset
    j idle
    j puts
    j self_test
    j telemetry
    j memory
    j connect
    j run
    j device_data
    j bios_log

# BIOS UTILITY
reset:
    # initialize BIOS constants (UART mainly)
    la      s1, UART_STATUS
    addi    s2, s1, UART_RXD_OFFSET
    addi    s3, s1, UART_TXD_OFFSET

idle:
    call    uart_loop               # call loop in idle to receive command
    mv      t1, a0                  # move result to t1 scratch reg
    
    # conditional switch table for all different intiialization bytes
    addi    t2, x0, TB_MSG_ECHO     # check msg echo byte
    beq     t1, t2, puts
    addi    t2, x0, TB_ST_INIT      # check self test init
    beq     t1, t2, self_test
    addi    t2, x0, TB_META_START   # check telemetry display innit
    beq     t1, t2, telemetry
    addi    t2, x0, TB_MEM_DUMP     # memory dump
    beq     t1, t2, memory
    addi    t2, x0, TB_NET_ACK      # connection attempt
    beq     t1, t2, connect
    addi    t2, x0, TB_DD_DATA      # check device data request
    beq     t1, t2, device_data
    addi    t2, x0, TB_BIOS_DATA    # check if BIOS data monitoring is turned on
    beq     t1, t2, bios_log
    
    j       idle                    # loop around if no valid command bytes, no error 

puts:

self_test:

telemetry:

memory:

connect:

device_data:

bios_log:

# HELPERS

uart_rx:    # UART polling loops (no interrupts yet :/)
    li      t1, MAX_TIMEOUT_CYCLE
1:
    lbu     t0, 0(s1)      # load UART status byte
    addi    t1, t1, -1     # decrement safety checker timer
    beqz    t1, timeout_handler
    andi    t0, t0, 0x01   # mask only bit 1 (RX VALID)
    beqz    t0, 1b         # loop back while uart status is 0 (not yet valid)
    lbu     a0, 0(s2)      # load data byte once status is nonzero (valid byte ready)
    ret

uart_tx:    # NOTE: no need for safety checker here, as its BIOS side
1:
    lbu     t0, 0(s1)      # load UART status byte
    andi    t0, t0, 0x02   # mask only bit 2 (TX BUSY)
    bnez    t0, 1b         # wait till valid (until tx_busy != 1)
    sb      a2, 0(s3)      # send data via UART channel once no longer busy
    ret

# HANDLERS
timeout_handler:    # uses a5 for checking operation

error_handler:

