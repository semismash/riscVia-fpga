import rv32i::*;

module mem_wb ( // 40 bits
    input logic clk,
    input logic rst_n,  // asynchronous active low reset
    input logic stall,
    input logic clear,  // synchronous active high clear

    input RegAddr i_rd_addr,      // 5 bits
    input Word i_rd_data,         // 32 bits
    input logic i_reg_write,      // 1 bit
    input logic i_is_stop,        // 1 bit
    input logic i_valid_instr,    // 1 bit

    output RegAddr o_rd_addr,
    output Word o_rd_data,
    output logic o_reg_write,
    output logic o_is_stop,
    output logic o_valid_instr,
);

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n || clear) begin
            o_rd_addr       <= '0;
            o_rd_data       <= '0;
            o_reg_write     <= '0;
            o_is_stop       <= '0;
            o_valid_instr   <= '0;
        end else if (!stall) begin  // do normal logic if NOT a stall
            o_rd_addr       <= i_rd_addr;
            o_rd_data       <= i_rd_data;
            o_reg_write     <= i_reg_write;
            o_is_stop       <= i_is_stop;
            o_valid_instr   <= i_valid_instr;
        end
    end

endmodule