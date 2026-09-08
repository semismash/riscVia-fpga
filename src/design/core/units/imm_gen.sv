import rv32i::*;

module imm_gen (
    input Instruction instr,
    input ImmPackFmt imm_type,

    output Word imm_out
);

    always_comb begin
        case (imm_type)
            I: imm_out = {{21{instr[31]}}, instr[30:20]};
            S: imm_out = {{21{instr[31]}}, {instr[30:25], instr[11:7]}};
            B: imm_out = {{20{instr[31]}}, instr[7], instr[30:25], instr[11:8], 1'b0};
            U: imm_out = {instr[31:12], {12{1'b0}}};
            J: imm_out = {{12{instr[31]}}, instr[19:12], instr[20], instr[30:25], instr[24:21], 1'b0};
            default: imm_out = {32{1'b0}};
        endcase 
    end

endmodule
