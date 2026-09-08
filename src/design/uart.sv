package uart;

    typedef enum logic [1:0] {
        IDLE,
        START,
        DATA,
        STOP
    } State;

endpackage