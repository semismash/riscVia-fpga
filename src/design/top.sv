import rv32i::*;

module top(
    input logic clk,    // clock
    input logic rst_n,  // active low reset

    // debugging
    output logic halt,  // halt detect
    output logic instr_fault,
    output logic data_fault,
    output logic illegal_instr,
    output logic stop,  // safe stop
    // CPU I/O
    input logic i_rx,
    output logic o_tx

    // telemetry data
    // output MetaCount meta_instr_count,
    // output MetaCount meta_stall_count,
    // output MetaCount meta_l_use_count,
    // output MetaCount meta_br_flush_count
);

    // from CPU
    Word if_addr            /* verilator public_flat_rw */;
    Word data_addr          /* verilator public_flat_rw */;
    Word write_data         /* verilator public_flat_rw */;
    logic write_enable      /* verilator public_flat_rw */;
    ReqBytes req_bytes      /* verilator public_flat_rw */;
    logic instr_valid       /* verilator public_flat_rw */;
    logic data_req_start    /* verilator public_flat_rw */;
    logic data_valid        /* verilator public_flat_rw */;

    // to CPU
    Instruction instr;
    Word read_data;
    logic if_fault;
    logic data_fault;

    rv32i_core u_cpu (
        // clock and reset
        .clk (clk),                         // x
        .rst_n (rst_n),                     // x
        // IN
        .instr_in (instr),                  // x
        .data_in (read_data),               // x
        .if_fault (if_fault),               // x
        .data_fault (data_fault),           // x
        .instr_valid (instr_valid),         // x
        .data_valid (data_valid),           // x
        // OUT
        .if_addr (if_addr),                 // x
        .data_addr (data_addr),             // x
        .data_out (write_data),             // x
        .write_en (write_enable),           // x
        .req_bytes (req_bytes),             // x
        .data_req_start (data_req_start),   // x
        // HALT
        .halt (halt),   // x
        .instr_fault    (instr_fault),  // x
        .data_fault     (data_fault),   // x
        .illegal_instr  (illegal_instr_fault),  // x
        .stop (stop),   // x
        // UART
        .i_rx (i_rx),
        .o_tx (o_tx)
        // TELEMETRY
        // .meta_instr_count (meta_instr_count),       // x
        // .meta_stall_count (meta_stall_count),       // x
        // .meta_l_use_count (meta_l_use_count),       // x
        // .meta_br_flush_count (meta_br_flush_count)  // x
    );


    mem #(
        .ROM_SIZE_BYTES     (ROM_SIZE_BYTES),   // x
        .RAM_SIZE_BYTES     (RAM_SIZE_BYTES)    // x
    ) u_mem (
        .clk                (clk),              // x
        .rst_n              (rst_n),            // x
        // instruction fetch
        .instr_addr         (if_addr),          // x
        .instr_out          (instr),            // x
        .instr_valid        (instr_valid),      // x
        .instr_not_found    (if_fault),         // x
        // data access
        .data_addr          (data_addr),        // x
        .req_bytes          (req_bytes),        // x
        .write_enable       (write_enable),     // x
        .data_in            (write_data),       // x
        .data_req_start     (data_req_start),   // x
        .data_out           (read_data),        // x
        .data_valid         (data_valid),       // x
        .data_not_found     (data_fault)        // x
    );
    
endmodule
