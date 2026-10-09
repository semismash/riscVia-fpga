# BIOS specific constant declarations
.equ MAX_TIMEOUT_CYCLE, 0x4000000   # 67 million cycle safety window
.equ UART_STATUS,       0x80000000  # 0x8000_0000
.equ UART_RXD_OFFSET,   0x4         # 0x8000_0004
.equ UART_TXD_OFFSET,   0x8         # 0x8000_0008

# REGISTER USAGE:
# a0 - callee return value 1
# a1 - callee return value 2
# a5 - 

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
1:
    

puts:

self_test:

telemetry:

memory:

connect:

device_data:

bios_log:

# HELPERS
uart_rx:
    li      t1, MAX_TIMEOUT_CYCLE
1:
    lbu     a0, 0(s1)      # load UART status byte
    addi    t1, t1, -1     # decrement safety checker timer
    beqz    t1, timeout_handler
    andi    a0, a0, 0x01   # mask only bit 1 (RX VALID)
    beqz    a0, 1b         # loop back while uart status is 0 (not yet valid)
    lbu     a1, 0(s2)      # load data byte once status is nonzero (valid byte ready)
    ret

# a1 = TX DATA (ARG)
uart_tx:    # NOTE: no need for safety checker here, as its BIOS side
1:
    lbu     a0, 0(s1)      # load UART status byte
    andi    a0, a0, 0x02   # mask only bit 2 (TX BUSY)
    bnez    a0, 1b         # wait till valid (until tx_busy != 1)
    sb      a1, 0(s3)      # send data via UART channel once no longer busy
    ret

# HANDLERS
timeout_handler:    # uses a2 for operation
    

