import rv32i::*;

// this module directly links the LSU to MMIO devices (for example, the UART controller)
module mmio_interface (
    input logic clk,

    input  Word mmio_data_addr,
    input  ReqBytes req_bytes,
    input  logic write_enable,
    input  Word mmio_data_in,

    // to LSU
    output Word mmio_data_out,
    output logic mmio_data_ready,

    // TO I/O modules:
    // UART RX/TX
    input logic [7:0] rx_data,
    input logic rx_valid,
    output logic [7:0] tx_data,
    output logic tx_start,
    input logic tx_busy
);

    // no data fault raised, value simply discarded
    // MMIO is defined as everything after 0x80000000 (until 0xFFFFFFFF, 32-bit address space limit)
    // since we adjust mmio address, wrap-around condition due to 32-bit int limit is impossible

    Word mem_addr_0, mem_addr_1, mem_addr_2, mem_addr_3;

    logic mmio_corrected_addr;
    assign mmio_corrected_addr = {1'b0, mmio_data_addr[30:0]};  // subtract 0x80000000 from mmio addr input internally to adjust address

    logic mmioplus1, mmioplus2, mmioplus3;
    assign mmioplus1 = mmio_corrected_addr + 1'd1;
    assign mmioplus2 = mmio_corrected_addr + 1'd2;
    assign mmioplus3 = mmio_corrected_addr + 1'd3;

    // if out of bounds, saturate to 0x7FFFFFFF [0xFFFFFFFF]; this address is guaranteed to be unused
    assign mem_addr_0 = mmio_corrected_addr;
    assign mem_addr_1 = (mmioplus1 < MMIO_SIZE_BYTES) ? mmioplus1 : 32'h7FFFFFFF;
    assign mem_addr_2 = (mmioplus2 < MMIO_SIZE_BYTES) ? mmioplus2 : 32'h7FFFFFFF;
    assign mem_addr_3 = (mmioplus3 < MMIO_SIZE_BYTES) ? mmioplus3 : 32'h7FFFFFFF;

    always_ff @(posedge clk) begin
        if (req_bytes == 0) begin
            mmio_data_out <= '0;
        end else begin
            if (write_enable) begin // output function

            end else begin  // input function

            end
        end
    end

endmodule