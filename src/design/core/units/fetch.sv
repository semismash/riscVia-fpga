import rv32i::*;

module fetch #( // just a wrapper lol
    parameter DATA_WIDTH = rv32i::DATA_WIDTH
) (
    input Word pc_in,           // take from pc
    input Word instr_in,        // raw instruction from mem
    input logic is_not_found,   // if instruction not found, taken from mem

    output Word mem_fetch_addr, // send fetch addr to mem
    output Word instr_out,      // output respective instruction to decoder
    output logic mem_fault      // mem fault
);

    assign mem_fetch_addr = pc_in;
    assign instr_out = instr_in;
    assign mem_fault = is_not_found;
    
endmodule
