package uart;

    localparam UART_BAUD_RATE = 9600;
    localparam UART_SAMPLING_RATE = 16;

    typedef enum logic [1:0] {
        IDLE,
        START,
        DATA,
        STOP
    } State;

endpackage