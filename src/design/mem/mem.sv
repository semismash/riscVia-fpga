import rv32i::*;

module mem #(
    parameter ROM_SIZE_BYTES = 4096,
    parameter RAM_SIZE_BYTES = 131072
) (
    input logic clk,
    input logic rst_n,

    // instruction fetch: absolute address, full memory map
    input  Word  instr_addr,
    output Word  instr_out,
    output logic instr_valid,
    output logic instr_not_found,

    // data access: absolute address, full memory map
    // ROM is protected: reads are allowed, writes are disallowed
    // MMIO starts from address 0x80000000, handled by LSU itself
    input  Word data_addr,
    input  ReqBytes req_bytes,
    input  logic write_enable,
    input  Word data_in,
    input  logic data_req_start,
    output Word data_out,
    output logic data_valid,
    output logic data_not_found
);

    localparam Word RAM_BASE = ROM_SIZE_BYTES;

    // instruction fetch
    logic sel_rom;
    assign sel_rom = (instr_addr < RAM_BASE);

    logic sel_rom_q;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) sel_rom_q <= 1'b1;   // reset vector fetches from ROM first
        else        sel_rom_q <= sel_rom;
    end

    Word  rom_instr_out, ram_instr_out;
    logic rom_instr_valid, ram_instr_valid;
    logic rom_instr_fault, ram_instr_fault;

    boot_rom #(
        .ROM_SIZE_BYTES(ROM_SIZE_BYTES)
    ) u_boot_rom (
        .clk             (clk),
        .rst_n           (rst_n), 
        .instr_addr      (instr_addr),            // rom's own bounds check rejects ram-range addresses
        .instr_out       (rom_instr_out),
        .instr_valid     (rom_instr_valid),
        .instr_not_found (rom_instr_fault)
    );

    unified_ram #(
        .MEM_SIZE_BYTES(RAM_SIZE_BYTES)
    ) u_ram (
        .clk             (clk),
        .rst_n           (rst_n),
        .instr_addr      (instr_addr - RAM_BASE),
        .instr_out       (ram_instr_out),
        .instr_valid     (ram_instr_valid),
        .instr_not_found (ram_instr_fault),

        .data_addr       (data_addr - RAM_BASE),
        .req_bytes       (req_bytes),
        .write_enable    (write_enable),
        .data_in         (data_in),
        .data_req_start  (data_req_start),
        .data_out        (data_out),
        .data_valid      (data_valid),
        .data_not_found  (data_not_found)
    );

    assign instr_out = sel_rom_q ? rom_instr_out : ram_instr_out;
    assign instr_valid = sel_rom_q ? rom_instr_valid : ram_instr_valid;
    assign instr_not_found = sel_rom_q ? rom_instr_fault : ram_instr_fault;

endmodule
