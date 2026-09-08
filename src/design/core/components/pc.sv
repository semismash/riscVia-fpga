import rv32i::*;
localparam INST_BYTE_SIZE = DATA_WIDTH >> 3;

module pc(
    input logic clk,
    input logic rst_n,      // active low reset
    input logic pc_enable,  // enable PC incrementation if enabled
    
    input logic pcinc_in1_pcor, // choose whether in1 of alu inc is pc or rs1
    input logic pcinc_in2_doi,  // choose whether in2 of alu inc is 4 (default) or imm

    input Word rs1_in,      // take rs1 if req
    input Word pc_in,       // take pc value from pipeline register to accurate jump
    input Word imm_in,      // take imm_in if req

    output Word pc_out      // pc output (cur val)
);

    Word pc;      // pc cur value
    Word pc_next; // pc next value

    always_comb begin
        Word in1;
        Word in2;
        if (pcinc_in2_doi == 1'b0) begin        // PC = PC + 4
            in1 = pc;   // check if PC or pc_in (i think its PC only but still)
            in2 = INST_BYTE_SIZE;
        end else if (pcinc_in1_pcor == 1'b1) begin      // JALR -> PC = rs1 + imm
            in1 = rs1_in;
            in2 = imm_in;
        end else begin      // JAL -> PC = PC + imm
            in1 = pc_in;
            in2 = imm_in;
        end
        pc_next = (in1 + in2) & ~Word'(32'b1);
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            pc <= '0;
        end else if (pc_enable) begin
            pc <= pc_next;
        end
    end

    assign pc_out = pc;

endmodule
