import rv32i::*;

module dep_analyzer (   // dependency analyzer
    // IF/ID (incl. OpCode bits)
    input OpCode if_id_opcode,
    input OpCode id_ex_opcode,
    input RegAddr if_id_rs1,
    input RegAddr if_id_rs2,
    // ID/EX
    input RegAddr id_ex_rs1,
    input RegAddr id_ex_rs2,
    input RegAddr id_ex_rd,
    // EX/MEM
    input RegAddr ex_mem_rd,
    // MEM/WB
    input RegAddr mem_wb_rd,

    // outputs (naming scheme = dep_source_dest)
    // ID/EX
    output logic dep_id_ex_rd_if_id_rs1,
    output logic dep_id_ex_rd_if_id_rs2,
    // EX/MEM
    output logic dep_ex_mem_rd_id_ex_rs1,
    output logic dep_ex_mem_rd_id_ex_rs2,
    // MEM/WB
    output logic dep_mem_wb_rd_id_ex_rs1,
    output logic dep_mem_wb_rd_id_ex_rs2,

    // extra bits to check if its not zero regiter
    output logic id_ex_rs1_not_x0,
    output logic id_ex_rs2_not_x0,
    output logic id_ex_rd_not_x0,
    // check if rs1 or rs2 usage is even valid
    output logic if_id_rs1_valid,   // for stall unit (load use with no gap)
    output logic if_id_rs2_valid,
    output logic id_ex_rs1_valid,   // for forwardable hazards
    output logic id_ex_rs2_valid
);

    // for stalls (catches load-use early)
    assign dep_id_ex_rd_if_id_rs1 = (id_ex_rd == if_id_rs1);
    assign dep_id_ex_rd_if_id_rs2 = (id_ex_rd == if_id_rs2);

    // for forwarding
    assign dep_ex_mem_rd_id_ex_rs1 = (ex_mem_rd == id_ex_rs1);
    assign dep_ex_mem_rd_id_ex_rs2 = (ex_mem_rd == id_ex_rs2);
    
    assign dep_mem_wb_rd_id_ex_rs1 = (mem_wb_rd == id_ex_rs1);
    assign dep_mem_wb_rd_id_ex_rs2 = (mem_wb_rd == id_ex_rs2);

    // non-zero check
    assign id_ex_rs1_not_x0 = (id_ex_rs1 != '0);
    assign id_ex_rs2_not_x0 = (id_ex_rs2 != '0);
    assign id_ex_rd_not_x0  = (id_ex_rd  != '0);

    // rs1 & rs2 validity check
    assign if_id_rs1_valid = 
        (if_id_opcode == OP_R)      ||
        (if_id_opcode == OP_I)      ||
        (if_id_opcode == OP_I_L)    ||
        (if_id_opcode == OP_S)      ||
        (if_id_opcode == OP_B)      ||
        (if_id_opcode == OP_I_J)    ||
        (if_id_opcode == OP_I_E);
    assign if_id_rs2_valid = 
        (if_id_opcode == OP_R)      ||
        (if_id_opcode == OP_S)      ||
        (if_id_opcode == OP_B);
    assign id_ex_rs1_valid = 
        (id_ex_opcode == OP_R)      ||
        (id_ex_opcode == OP_I)      ||
        (id_ex_opcode == OP_I_L)    ||
        (id_ex_opcode == OP_S)      ||
        (id_ex_opcode == OP_B)      ||
        (id_ex_opcode == OP_I_J)    ||
        (id_ex_opcode == OP_I_E);
    assign id_ex_rs2_valid = 
        (id_ex_opcode == OP_R)      ||
        (id_ex_opcode == OP_S)      ||
        (id_ex_opcode == OP_B);

endmodule