import rv32i::*;

module alu #(
    parameter DATA_WIDTH = rv32i::DATA_WIDTH,
    parameter ADDR_WIDTH = rv32i::ADDR_WIDTH
)(
    input AluOp alu_op,

    input logic alu_bypass,     // bypass ALU completely, output zero
    input logic imm_to_reg,     // imm value directly is ALU output

    input Word r_data1,
    input Word r_data2,

    input Word pc,
    input logic use_pc,     // switch between r_data1 (0) or pc (1) for data1

    input Word imm,
    input logic use_imm,    // switch between r_data2 (0) or imm (1) for data2

    // for forwarding
    input logic fwd_alu_in1_ex_mem,
    input logic fwd_alu_in2_ex_mem,
    input logic fwd_alu_in1_mem_wb,
    input logic fwd_alu_in2_mem_wb,
    // forwarded data
    input Word ex_mem_rd_data,
    input Word mem_wb_rd_data,

    output Word alu_out,
    output logic out_zero
);

    Word data1;
    Word data2;

    always_comb begin
        data1 = '0;
        data2 = '0;
        if (alu_bypass) begin
            alu_out = '0;
        end else if (imm_to_reg) begin
            alu_out = imm;
        end else begin
            // forward takes priority over normal source, independent of data2
            if (fwd_alu_in1_ex_mem) data1 = ex_mem_rd_data;        // prioritize EX/MEM over MEM/WB
            else if (fwd_alu_in1_mem_wb) data1 = mem_wb_rd_data;
            else if (use_pc == 1'b0) data1 = r_data1;
            else data1 = pc;
            // forward takes priority over normal source, independent of data1
            if (fwd_alu_in2_ex_mem) data2 = ex_mem_rd_data;        // prioritize EX/MEM over MEM/WB
            else if (fwd_alu_in2_mem_wb) data2 = mem_wb_rd_data;
            else if (use_imm == 1'b0) data2 = r_data2;
            else data2 = imm;
            case (alu_op)
                ADD: alu_out = data1 + data2;
                SUB: alu_out = data1 - data2;
                XOR: alu_out = data1 ^ data2;
                OR:  alu_out = data1 | data2;
                AND: alu_out = data1 & data2;
                SLL: alu_out = data1 << data2[ADDR_WIDTH-1:0];
                SRL: alu_out = data1 >> data2[ADDR_WIDTH-1:0];
                SRA: alu_out = $signed(data1) >>> data2[ADDR_WIDTH-1:0];
                SLT: alu_out = ($signed(data1) < $signed(data2)) ? 1 : 0;
                SLTU: alu_out = (data1 < data2) ? 1 : 0;
                default: alu_out = '0;
            endcase
        end
    end

    assign out_zero = (alu_out == 0); // set less than flag is always inverse of zero flag

endmodule