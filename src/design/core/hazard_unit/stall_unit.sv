module stall_unit(
    // ID/EX - IF/ID dependencies
    input logic dep_id_ex_rd_if_id_rs1,
    input logic dep_id_ex_rd_if_id_rs2,
    // non-zero bits to prevent accidental stalls if using locked zero register
    input logic id_ex_rd_not_x0,
    // classification bits to check read and write to stall accordingly
    input logic id_ex_mem_read,     // if load (load-use)
    input logic id_ex_reg_write,    // if writing to reg (mostly to disqualify non-load instructions)
    input logic branch_taken,       // check if a branch was taken, to stall control hazards for now
    // if read registers are even valid to begin with
    input logic if_id_rs1_valid,
    input logic if_id_rs2_valid,
    // OUTPUTS
    output logic if_id_clear,
    output logic id_ex_clear,
    output logic pc_enable,
    output logic if_id_enable,
    // METADATA
    output logic meta_branch_flush,
    output logic meta_is_stall,
    output logic meta_is_l_use
);

    // stall unit currently handles two things -
    // 1. load-use hazards with 0 instruction gap (to be kept with this use for the forseeable future)
    // 2. control hazards (to create bubbles, to be shifted out soon with branch prediction implementation)

    logic is_l_use_no_gap;

    always_comb begin

        pc_enable = 1'b1;
        if_id_enable = 1'b1;
        if_id_clear = 1'b0;
        id_ex_clear = 1'b0;

        meta_is_stall = 1'b0;
        meta_is_l_use = 1'b0;
        meta_branch_flush = 1'b0;

        is_l_use_no_gap = id_ex_mem_read && id_ex_reg_write && id_ex_rd_not_x0 &&
            ((if_id_rs1_valid && dep_id_ex_rd_if_id_rs1) || (if_id_rs2_valid && dep_id_ex_rd_if_id_rs2));

        if (branch_taken) begin  // prioritize control hazards
            if_id_clear = 1'b1;
            id_ex_clear = 1'b1;
            meta_branch_flush = 1'b1;
        end else if (is_l_use_no_gap) begin // stall for load-use no gap hazard
            pc_enable     = 1'b0;
            if_id_enable  = 1'b0;
            id_ex_clear   = 1'b1;
            meta_is_stall = 1'b1;
            meta_is_l_use = 1'b1;
        end
    end

endmodule