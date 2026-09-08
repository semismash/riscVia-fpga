module fwd_unit (
    // Dependencies
    // ID/EX
    input logic dep_id_ex_rd_if_id_rs1,
    input logic dep_id_ex_rd_if_id_rs2,
    // EX/MEM
    input logic dep_ex_mem_rd_id_ex_rs1,
    input logic dep_ex_mem_rd_id_ex_rs2,
    // MEM/WB
    input logic dep_mem_wb_rd_id_ex_rs1,
    input logic dep_mem_wb_rd_id_ex_rs2,
    // non-zero bits to prevent accidental stalls if using locked zero register
    input logic id_ex_rs1_not_x0,
    input logic id_ex_rs2_not_x0,
    // if read registers are even valid to begin with
    input logic id_ex_rs1_valid,
    input logic id_ex_rs2_valid,
    // write signal from registers
    input logic ex_mem_reg_write,
    input logic mem_wb_reg_write,
    // OUTPUT
    output logic fwd_alu_in1_ex_mem, // forward to alu in 1 from src res in ex mem
    output logic fwd_alu_in2_ex_mem, // forward to alu in 2 from src res in ex mem
    output logic fwd_alu_in1_mem_wb, // forward to alu in 1 from src res in ex mem
    output logic fwd_alu_in2_mem_wb  // forward to alu in 2 from src res in ex mem
);

    // Conditions for forwarding
    /*
    1. If EX/MEM[rd] == ID/EX[rs1 | rs2] for R/I type instructions
    2. If MEM/WB[rd] == ID/EX[rs1 | rs2] for R/I type instructions
    3. If MEM/WB[rd] == ID/EX[rs1 | rs2] for load type instructions
    */

    assign fwd_alu_in1_ex_mem = id_ex_rs1_valid && id_ex_rs1_not_x0 && ex_mem_reg_write && dep_ex_mem_rd_id_ex_rs1;
    assign fwd_alu_in1_mem_wb = id_ex_rs1_valid && id_ex_rs1_not_x0 && mem_wb_reg_write && dep_mem_wb_rd_id_ex_rs1;
    assign fwd_alu_in2_ex_mem = id_ex_rs2_valid && id_ex_rs2_not_x0 && ex_mem_reg_write && dep_ex_mem_rd_id_ex_rs2;
    assign fwd_alu_in2_mem_wb = id_ex_rs2_valid && id_ex_rs2_not_x0 && mem_wb_reg_write && dep_mem_wb_rd_id_ex_rs2;


endmodule