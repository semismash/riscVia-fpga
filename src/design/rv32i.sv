package rv32i;
    
    localparam DATA_WIDTH = 32;
    localparam ADDR_WIDTH = 5;

    typedef logic [rv32i::DATA_WIDTH-1:0] Instruction;
    typedef logic [rv32i::DATA_WIDTH-1:0] Word;
    typedef logic [7:0] Byte;
    typedef logic [ADDR_WIDTH-1:0] RegAddr;

    typedef logic [31:0] MetaCount;

    localparam BITS_FIT = $clog2(DATA_WIDTH>>3) + 1;    // 3
    typedef enum logic [BITS_FIT - 1:0] {  // to be shared between LSU and mem module
        ZERO = 'd0,
        ONE  = 'd1,
        TWO  = 'd2,
        FOUR = 'd4
    } ReqBytes;

    typedef enum logic [6:0] {  //7 bits for opcode
        OP_NOP      = 7'b0000000,
        OP_R        = 7'b0110011,
        OP_I        = 7'b0010011,
        OP_I_L      = 7'b0000011,
        OP_S        = 7'b0100011,
        OP_B        = 7'b1100011,
        OP_J        = 7'b1101111,
        OP_I_J      = 7'b1100111,
        OP_LUI      = 7'b0110111,
        OP_AUIPC    = 7'b0010111,
        OP_I_E      = 7'b1110011,
        OP_STOP     = 7'b1111111
    } OpCode;

    typedef enum logic [3:0] { 
        ADD  = 4'b0000,
        SUB  = 4'b0001,
        XOR  = 4'b0100,
        OR   = 4'b0101,
        AND  = 4'b0110,
        SLL  = 4'b1000,
        SRL  = 4'b1010,
        SRA  = 4'b1011,
        SLT  = 4'b1101,
        SLTU = 4'b1100
    } AluOp;

    typedef enum logic [2:0] { 
        I, S, B, U, J, N // default
    } ImmPackFmt;

endpackage
