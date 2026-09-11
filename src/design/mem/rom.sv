import rv32i::*;

module rom #(   // currently houses only the bootloader
    parameter ROM_SIZE_BYTES = 4096   // 4 KiB, size of ROM
) (
    input  logic clk,
    input  logic rst_n,
    input  Word  instr_addr,        // 0-based, relative to ROM's own start
    output Word  instr_out,         // mem not busy (not fetching something rn)
    output logic instr_valid,       // signal to send back for instruction fetch
    output logic instr_not_found
);

    localparam INST_SIZE_BYTES = DATA_WIDTH >> 3;

    Byte container [ROM_SIZE_BYTES - 1:0];
    initial begin
        $readmemh("bootloader.hex", container);
    end

    logic fault_reg;

    always_ff @(posedge clk) begin
        if (instr_addr >= (ROM_SIZE_BYTES - INST_SIZE_BYTES)) begin
            fault_reg <= 1'b1;
            instr_out <= '0;
        end else begin
            fault_reg <= 1'b0;
            instr_out <= {
                container[instr_addr + 3],
                container[instr_addr + 2],
                container[instr_addr + 1],
                container[instr_addr]
            };
        end
    end
    assign instr_not_found = fault_reg;

    //  tie to high as answers in one cycle (PC address fetches are never misses, always happens in any cycle)
    logic instr_valid_q;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) instr_valid_q <= 1'b0;
        else        instr_valid_q <= 1'b1;
    end
    assign instr_valid = instr_valid_q;

endmodule