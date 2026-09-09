import rv32i::*;

module top(
    input logic clk,    // clock
    input logic rst_n,  // active low reset
    output logic halt,  // halt detect
    output logic stop,  // safe stop
    // telemetry data
    output MetaCount meta_instr_count,
    output MetaCount meta_stall_count,
    output MetaCount meta_l_use_count,
    output MetaCount meta_br_flush_count
);

    // from CPU
    Word if_addr        /* verilator public_flat_rw */;
    Word data_addr      /* verilator public_flat_rw */;
    Word write_data     /* verilator public_flat_rw */;
    logic write_enable  /* verilator public_flat_rw */;
    ReqBytes req_bytes  /* verilator public_flat_rw */;

    // to CPU
    Instruction instr;
    Word read_data;
    logic if_fault;
    logic data_fault;

    rv32i_core u_cpu(
        //clk and reset
        .clk            (clk),
        .rst_n          (rst_n),
        // IN
        .instr_in       (instr),
        .data_in        (read_data),
        .if_fault       (if_fault),
        .data_fault     (data_fault),
        // OUT
        .if_addr        (if_addr),
        .data_addr      (data_addr),
        .data_out       (write_data), 
        .write_en       (write_enable),
        .req_bytes      (req_bytes),
        // HALT
        .halt           (halt),
        .stop           (stop),
        // TELEMETRY
        .meta_instr_count       (meta_instr_count),
        .meta_stall_count       (meta_stall_count),
        .meta_l_use_count       (meta_l_use_count),
        .meta_br_flush_count    (meta_br_flush_count)
    );

    mem #(
        .ROM_SIZE_BYTES     (ROM_SIZE_BYTES),
        .RAM_SIZE_BYTES     (RAM_SIZE_BYTES)
    ) u_mem (
        .clk                (clk),
        .rst_n              (rst_n),
        // instruction fetch
        .instr_addr         (if_addr),
        .instr_out          (instr),
        .instr_not_found    (if_fault),
        // data access
        .data_addr          (data_addr),
        .req_bytes          (req_bytes),
        .write_enable       (write_enable),
        .data_in            (write_data),
        .data_out           (read_data),
        .data_not_found     (data_fault)
    );
    
endmodule
