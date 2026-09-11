import rv32i::*;

module fetch #(
    parameter DATA_WIDTH = rv32i::DATA_WIDTH
) (
    // clock, reset, and stall
    input logic clk,
    input logic rst_n,
    input logic stall,
    // inputs
    input Word pc_in,           // take from pc
    input Word instr_in,        // raw instruction from mem
    input logic is_not_found,   // if instruction not found, taken from mem
    input logic instr_valid,    // only advances if instruction fetch is completed
    // outputs
    output Word pc_out,         // this goes to IF/ID register
    output Word mem_fetch_addr, // send fetch addr to mem
    output Word instr_out,      // output respective instruction to decoder
    output logic mem_fault,     // mem fault
    output logic fetch_valid,   // passthrough of instr_valid
);

    Word pc_q;   // hold pc until instruction fetch is complete

    assign mem_fetch_addr = pc_in;
    assign instr_out = instr_in;
    assign mem_fault = is_not_found;
    assign fetch_valid = instr_valid;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            pc_q <= '0;
        end else if (stall) begin
            pc_q <= pc_q;
        end else begin
            pc_q <= pc_in;
        end
    end

    assign pc_out = pc_q;
    
endmodule
