import rv32i::*;

module rom #(   // currently houses only the bootloader
    parameter ROM_SIZE_BYTES = 4096   // 4 KiB, size of ROM
) (
    input  logic clk,
    input  Word  instr_addr,   // 0-based, relative to ROM's own start
    output Word  instr_out,
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

endmodule