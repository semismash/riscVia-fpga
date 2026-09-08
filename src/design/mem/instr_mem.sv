import rv32i::*;

module instr_mem #(
    parameter MEM_SIZE_BYTES = 65536    // 64 KB instruction memory
) (
    input logic clk,        // clock signal
    input Word instr_addr,  // instruction memory address

    output Word instr_out,   // output fetched instruction
    output logic instr_not_found, // if instruction not found, raise fault
);

    localparam INST_SIZE_BYTES = DATA_WIDTH >> 3;

    Byte container [MEM_SIZE_BYTES - 1: 0];
    Word addr_reg; // address register to hold for cycle

    always_ff @(posedge clk) begin 
        addr_reg <= instr_addr;
    end

    always_comb begin
        instr_out = '0;
        instr_not_found = 1'b0;
        if (instr_addr >= MEM_SIZE_BYTES - INST_SIZE_BYTES) instr_not_found = 1'b1;
        else instr_out =  {  
            container[instr_addr + 3], // do INST_SIZE_BYTES times
            container[instr_addr + 2], 
            container[instr_addr + 1], 
            container[instr_addr] 
        };
    end

    // add write port later when converting this to cache

endmodule