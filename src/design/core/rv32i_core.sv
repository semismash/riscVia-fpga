import rv32i::*;

module rv32i_core (
    input logic clk,            // CPU clock
    input logic rst_n,          // active low reset

    input Instruction instr_in, // next instruction (MEM -> FU)
    input Word data_in,         // input data from (MEM -> LSU)
    input logic if_fault,       // instruction fetch fault (MEM -> FU)
    input logic data_fault,     // data fetch fault (MEM) 

    output Word if_addr,        // instruction fetch address (FU)
    output Word data_addr,      // data address (LSU)
    output Word data_out,       // data out (LSU)    
    output logic write_en,      // write enable (LSU)
    output ReqBytes req_bytes,  // requested bytes amount (LSU)

    output logic halt,          // halt on panic
    output logic stop,          // safe halt

    // telemetry
    output MetaCount meta_instr_count,
    output MetaCount meta_stall_count,
    output MetaCount meta_l_use_count,
    output MetaCount meta_br_flush_count,
);

    // hazard unit
    logic hz_pc_enable;
    logic hz_if_id_enable;
    logic hz_if_id_clear;
    logic hz_id_ex_clear;
    logic hz_meta_is_stall;
    logic hz_meta_is_l_use;
    logic hz_meta_branch_flush;

    // fetch
    logic if_fault_out;
    Instruction instr;

    // Reg File
    logic   reg_w_enable;
    RegAddr rdst_addr;
    Word    rdst_data;
    RegAddr rs1_addr;
    RegAddr rs2_addr;
    Word    rs1_data;
    Word    rs2_data;

    // PC
    Word pc;
    logic pc_in1_sel;
    logic pc_in2_sel;

    // IF/ID
    Word if_id_pc;
    Instruction if_id_instr;
    OpCode if_id_opcode;
    RegAddr if_id_rs1_addr;
    RegAddr if_id_rs2_addr;

    // decoder
    logic mem_to_reg;
    logic imm_to_reg;        
    logic illegal_instr;
    logic d_is_branch;
    logic d_is_jal;
    logic d_is_jalr;
    logic d_stop;
    logic d_valid_instr;

    // imm
    Word imm_val;
    ImmPackFmt imm_type;

    // ID/EX
    Word id_ex_pc;
    RegAddr id_ex_rs1_addr;
    RegAddr id_ex_rs2_addr;
    RegAddr id_ex_rd_addr;
    Word id_ex_rs1_data;
    Word id_ex_rs2_data;
    Word fwd_store_data;  // rs2, forwarded, for store-data path (bypasses the ALU entirely so needs its own mux)
    Word id_ex_imm_val;
    logic id_ex_alu_in1_ropc;
    logic id_ex_alu_in2_roi;    // reconsider this, replace with branch taken condition later on
    AluOp id_ex_alu_op;
    logic id_ex_alu_bypass;
    logic id_ex_mem_read;
    logic id_ex_mem_write;
    logic [2:0] id_ex_funct3;
    logic id_ex_pc_in1_sel;
    logic id_ex_is_branch;
    logic id_ex_is_jal;
    logic id_ex_is_jalr;
    logic id_ex_reg_write;
    logic id_ex_imm_to_reg;
    logic id_ex_mem_to_reg;
    logic id_ex_stop;
    logic id_ex_valid_instr;

    // alu
    AluOp alu_op;
    logic alu_in1_sel;
    logic alu_in2_sel;
    logic alu_bypass;
    logic alu_zero;
    Word alu_out;

    // branch unit
    logic branch_taken;

    // EX/MEM
    Word ex_mem_rs2_val;
    RegAddr ex_mem_rd_addr;
    Word ex_mem_result;
    logic ex_mem_mem_read;
    logic ex_mem_mem_write;
    logic [2:0] ex_mem_funct3;
    logic ex_mem_reg_write;
    logic ex_mem_mem_to_reg;
    logic ex_mem_stop;
    logic ex_mem_valid_instr;

    // lsu
    logic [2:0] funct3;
    logic mem_read;
    logic mem_write;
    Word reg_write_data;

    // MEM/WB
    RegAddr mem_wb_rd_addr;
    Word mem_wb_rd_data;
    logic mem_wb_reg_write;
    logic mem_wb_stop;
    logic mem_wb_valid_instr;

    // forwarding unit
    logic fwd_alu_in1_ex_mem;
    logic fwd_alu_in1_mem_wb;
    logic fwd_alu_in2_ex_mem;
    logic fwd_alu_in2_mem_wb;
    
    // temp fix
    Word ex_result;
    Word pc_plus4;

    assign pc_plus4  = id_ex_pc + 32'd4;
    assign ex_result = (id_ex_is_jal || id_ex_is_jalr) ? pc_plus4 : alu_out;

    reg_file u_reg_file(
        // clk and reset
        .clk            (clk),
        .rst_n          (rst_n), 
        // write
        .w_enable       (mem_wb_reg_write),
        .w_addr         (mem_wb_rd_addr),
        .w_data         (mem_wb_rd_data),
        // read address
        .r_addr1        (rs1_addr),
        .r_addr2        (rs2_addr),
        // reg data output
        .r_data1        (rs1_data),
        .r_data2        (rs2_data)
    );

    pc u_pc(    // x
        // clk and reset
        .clk            (clk),
        .rst_n          (rst_n),
        .pc_enable      (hz_pc_enable),
        // from decoder
        .pcinc_in1_pcor (id_ex_pc_in1_sel),
        .pcinc_in2_doi  (pc_in2_sel),
        // from reg and imm gen, based on decoder signal
        .rs1_in         (id_ex_rs1_data),
        .pc_in          (id_ex_pc),
        .imm_in         (id_ex_imm_val),
        // out
        .pc_out         (pc)
    );

    // hazard_unit u_hazard_unit (
    //     // input
    //     .if_id_opcode       (if_id_opcode),
    //     .if_id_rs1          (if_id_rs1_addr),
    //     .if_id_rs2          (if_id_rs2_addr),
    //     .id_ex_mem_read     (id_ex_mem_read),
    //     .id_ex_reg_write    (id_ex_reg_write),
    //     .id_ex_rdst         (id_ex_rd_addr),
    //     .branch_taken       (branch_taken),
    //     .ex_mem_reg_write   (ex_mem_reg_write),
    //     .ex_mem_rdst        (ex_mem_rd_addr),
    //     .mem_wb_reg_write   (mem_wb_reg_write),
    //     .mem_wb_rdst        (mem_wb_rd_addr),
    //     // output
    //     .pc_enable          (hz_pc_enable),
    //     .if_id_enable       (hz_if_id_enable),
    //     .if_id_clear        (hz_if_id_clear),
    //     .id_ex_clear        (hz_id_ex_clear),
    //     // metadata
    //     .meta_is_stall      (hz_meta_is_stall),
    //     .meta_is_l_use      (hz_meta_is_l_use),
    //     .meta_branch_flush  (hz_meta_branch_flush)
    // );

    hazard_unit u_hazard_unit (
    // IF/ID (incl. OpCode bits)
    .if_id_opcode          (if_id_opcode),
    .id_ex_opcode          (id_ex_opcode),
    .if_id_rs1             (if_id_rs1_addr),
    .if_id_rs2             (if_id_rs2_addr),
    // ID/EX
    .id_ex_rs1             (id_ex_rs1_addr),
    .id_ex_rs2             (id_ex_rs2_addr),
    .id_ex_rd              (id_ex_rd_addr),
    // EX/MEM
    .ex_mem_rd             (ex_mem_rd_addr),
    // MEM/WB
    .mem_wb_rd             (mem_wb_rd_addr),
    // TO STALL UNIT DIRECTLY
    .id_ex_mem_read        (id_ex_mem_read),    // if load (X)
    .id_ex_reg_write       (id_ex_reg_write),   // if reg write (X)
    .branch_taken          (branch_taken),      // check if a branch was taken, to stall control hazards for now (X)
    // TO FORWARDING UNIT DIRECTLY
    .ex_mem_reg_write      (ex_mem_reg_write),
    .mem_wb_reg_write      (mem_wb_reg_write),
    // OUTPUTS
    // STALLING
    .pc_enable             (hz_pc_enable),
    .if_id_enable          (hz_if_id_enable),
    .if_id_clear           (hz_if_id_clear),
    .id_ex_clear           (hz_id_ex_clear),
    // FORWARDING
    .fwd_alu_in1_ex_mem    (fwd_alu_in1_ex_mem),    // forward to alu in 1 from src res in ex mem (X)
    .fwd_alu_in2_ex_mem    (fwd_alu_in2_ex_mem),    // forward to alu in 2 from src res in ex mem (X)
    .fwd_alu_in1_mem_wb    (fwd_alu_in1_mem_wb),    // forward to alu in 1 from src res in ex mem (X)
    .fwd_alu_in2_mem_wb    (fwd_alu_in2_mem_wb),    // forward to alu in 2 from src res in ex mem (X)
    // METADATA
    .meta_branch_flush     (meta_branch_flush),
    .meta_is_stall         (meta_is_stall),
    .meta_is_l_use         (meta_is_l_use)
);

    fetch u_fetch(  // x
        // IN
        .pc_in          (pc),
        .instr_in       (instr_in),
        .is_not_found   (if_fault),
        // OUT
        .mem_fetch_addr (if_addr),
        .instr_out      (instr),
        .mem_fault      (if_fault_out)
    );

    if_id u_if_id (
        // clk and reset
        .clk            (clk),
        .rst_n          (rst_n),
        .stall          (!hz_if_id_enable),
        .clear          (hz_if_id_clear),
        // input
        .i_pc           (if_addr),
        .i_instr        (instr),
        // output
        .o_pc           (if_id_pc),
        .o_instr        (if_id_instr)
    );

    // direct primitive slice (does not require explicit decoding)
    assign if_id_opcode     = OpCode'(if_id_instr[6:0]);
    assign if_id_rs1_addr   = RegAddr'(if_id_instr[19:15]);
    assign if_id_rs2_addr   = RegAddr'(if_id_instr[24:20]);

    decoder u_decoder(
        // IN
        .instr          (if_id_instr),
        //.alu_zero       (alu_zero),
        .rs1_addr       (rs1_addr),
        .rs2_addr       (rs2_addr),
        .rd_addr        (rdst_addr),
        // branches
        .is_branch      (d_is_branch),
        .is_jal         (d_is_jal),
        .is_jalr        (d_is_jalr),
        // ALU
        .alu_op         (alu_op),
        .alu_in1_ropc   (alu_in1_sel),
        .alu_in2_roi    (alu_in2_sel),
        .alu_bypass     (alu_bypass),
        // REG FILE
        .reg_write      (reg_w_enable),
        // LSU
        .mem_read       (mem_read),
        .mem_write      (mem_write),
        .mem_to_reg     (mem_to_reg),
        .imm_to_reg     (imm_to_reg),
        // IMM GEN
        .imm_val        (imm_val),
        // PC
        .pcinc_in1_pcor (pc_in1_sel),
        //.pcinc_in2_doi  (pc_in2_sel), (CHECK AGAIN)
        // funct3
        .funct3         (funct3),
        // panic
        .illegal_instr  (illegal_instr),
        .stop           (d_stop),
        .valid_instr    (d_valid_instr)
    );

    id_ex u_id_ex (
        // clk and reset
        .clk              (clk),
        .rst_n            (rst_n),
        .stall            (1'b0),
        .clear            (hz_id_ex_clear),
        // input
        .i_pc             (if_id_pc),
        .i_rs1_addr       (rs1_addr),
        .i_rs2_addr       (rs2_addr),
        .i_rd_addr        (rdst_addr),
        .i_rs1_data       (rs1_data),
        .i_rs2_data       (rs2_data),
        .i_imm_val        (imm_val),
        .i_alu_in1_ropc   (alu_in1_sel),
        .i_alu_in2_roi    (alu_in2_sel),
        .i_alu_op         (alu_op),
        .i_alu_bypass     (alu_bypass),
        .i_mem_read       (mem_read),
        .i_mem_write      (mem_write),
        .i_funct3         (funct3),
        .i_pc_in1_sel     (pc_in1_sel),
        .i_is_branch      (d_is_branch),
        .i_is_jal         (d_is_jal),
        .i_is_jalr        (d_is_jalr),
        .i_reg_write      (reg_w_enable),
        .i_imm_to_reg     (imm_to_reg),
        .i_mem_to_reg     (mem_to_reg),
        .i_is_stop        (d_stop),
        .i_valid_instr    (d_valid_instr),
        // output
        .o_pc             (id_ex_pc),
        .o_rs1_addr       (id_ex_rs1_addr),
        .o_rs2_addr       (id_ex_rs2_addr),
        .o_rd_addr        (id_ex_rd_addr),
        .o_rs1_data       (id_ex_rs1_data),
        .o_rs2_data       (id_ex_rs2_data),
        .o_imm_val        (id_ex_imm_val),
        .o_alu_in1_ropc   (id_ex_alu_in1_ropc),
        .o_alu_in2_roi    (id_ex_alu_in2_roi),
        .o_alu_op         (id_ex_alu_op),
        .o_alu_bypass     (id_ex_alu_bypass),
        .o_mem_read       (id_ex_mem_read),
        .o_mem_write      (id_ex_mem_write),
        .o_funct3         (id_ex_funct3),
        .o_pc_in1_sel     (id_ex_pc_in1_sel),
        .o_is_branch      (id_ex_is_branch),
        .o_is_jal         (id_ex_is_jal),
        .o_is_jalr        (id_ex_is_jalr),
        .o_reg_write      (id_ex_reg_write),
        .o_imm_to_reg     (id_ex_imm_to_reg),
        .o_mem_to_reg     (id_ex_mem_to_reg),
        .o_is_stop        (id_ex_stop),
        .o_valid_instr    (id_ex_valid_instr)
    );

    alu u_alu(  // x
        // from ID
        .alu_op             (id_ex_alu_op),
        .alu_bypass         (id_ex_alu_bypass),
        .imm_to_reg         (id_ex_imm_to_reg),
        // from REG FILE
        .r_data1            (id_ex_rs1_data),
        .r_data2            (id_ex_rs2_data),
        // from PC & ID
        .pc                 (id_ex_pc),
        .use_pc             (id_ex_alu_in1_ropc),
        // from IMM & ID
        .imm                (id_ex_imm_val),
        .use_imm            (id_ex_alu_in2_roi),  
        // for forwarding
        .fwd_alu_in1_ex_mem (fwd_alu_in1_ex_mem),
        .fwd_alu_in2_ex_mem (fwd_alu_in2_ex_mem),
        .fwd_alu_in1_mem_wb (fwd_alu_in1_mem_wb),
        .fwd_alu_in2_mem_wb (fwd_alu_in2_mem_wb),
        // forwarded data
        .ex_mem_rd_data     (ex_mem_result),
        .mem_wb_rd_data     (mem_wb_rd_data),
        // OUT
        .alu_out            (alu_out),
        .out_zero           (alu_zero)
    );

    branch_unit u_branch_unit (
        // input
        .is_branch      (id_ex_is_branch),
        .is_jal         (id_ex_is_jal),
        .is_jalr        (id_ex_is_jalr),
        .id_ex_funct3   (id_ex_funct3),
        .alu_zero       (alu_zero),
        // output
        .branch_taken   (branch_taken)
    );

    assign pc_in2_sel = branch_taken;

    // forwards data for storing too as rs2 never actually went through ALU, js pass into EX/MEM directly here
    assign fwd_store_data = fwd_alu_in2_ex_mem ? ex_mem_result : fwd_alu_in2_mem_wb ? mem_wb_rd_data : id_ex_rs2_data;

    ex_mem u_ex_mem (
        // clk and reset
        .clk            (clk),
        .rst_n          (rst_n),
        .stall          (1'b0),
        .clear          (1'b0),
        // input
        .i_rs2_val      (fwd_store_data),
        .i_rd_addr      (id_ex_rd_addr),
        .i_result       (ex_result),
        .i_mem_read     (id_ex_mem_read),
        .i_mem_write    (id_ex_mem_write),
        .i_funct3       (id_ex_funct3),
        .i_reg_write    (id_ex_reg_write),
        .i_mem_to_reg   (id_ex_mem_to_reg),
        .i_is_stop      (id_ex_stop),
        .i_valid_instr  (id_ex_valid_instr),
        // output
        .o_rs2_val      (ex_mem_rs2_val),
        .o_rd_addr      (ex_mem_rd_addr),
        .o_result       (ex_mem_result),
        .o_mem_read     (ex_mem_mem_read),
        .o_mem_write    (ex_mem_mem_write),
        .o_funct3       (ex_mem_funct3),
        .o_reg_write    (ex_mem_reg_write),
        .o_mem_to_reg   (ex_mem_mem_to_reg),
        .o_is_stop      (ex_mem_stop),
        .o_valid_instr  (ex_mem_valid_instr)
    );

    lsu u_lsu(
        // IN
        .funct3         (ex_mem_funct3),
        .alu_res        (ex_mem_result),
        .is_mem_read    (ex_mem_mem_read),
        .is_mem_write   (ex_mem_mem_write),
        .rs2_in         (ex_mem_rs2_val),
        .mem_to_reg     (ex_mem_mem_to_reg),
        .data_in        (data_in),
        // OUT
        .mem_addr       (data_addr),
        .write_enable   (write_en),
        .write_data     (data_out),
        .req_bytes      (req_bytes),
        .reg_data       (reg_write_data)
    );

    mem_wb u_mem_wb (
        // clk
        .clk            (clk),
        .rst_n          (rst_n),
        .stall          (1'b0),
        .clear          (1'b0),
        // input
        .i_rd_addr      (ex_mem_rd_addr),
        .i_rd_data      (reg_write_data),
        .i_reg_write    (ex_mem_reg_write),
        .i_is_stop      (ex_mem_stop),
        .i_valid_instr  (ex_mem_valid_instr),
        // output
        .o_rd_addr      (mem_wb_rd_addr),
        .o_rd_data      (mem_wb_rd_data),
        .o_reg_write    (mem_wb_reg_write),
        .o_is_stop      (mem_wb_stop),
        .o_valid_instr  (mem_wb_valid_instr)
    );

    meta u_meta (
        .clk                    (clk),
        .rst_n                  (rst_n),
        .stop_in                (mem_wb_stop),
        .valid_instr            (mem_wb_valid_instr),
        .is_stall               (hz_meta_is_stall),
        .is_l_use               (hz_meta_is_l_use),
        .is_br_flush            (hz_meta_branch_flush),
        .stop_out               (stop),
        .meta_instr_count       (meta_instr_count),
        .meta_stall_count       (meta_stall_count),
        .meta_l_use_count       (meta_l_use_count),
        .meta_br_flush_count    (meta_br_flush_count)
    );

    assign halt = if_fault_out | data_fault | illegal_instr;

endmodule