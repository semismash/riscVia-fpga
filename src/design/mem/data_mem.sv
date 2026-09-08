import rv32i::*;

module data_mem #(
    parameter MEM_SIZE_BYTES = 65536    // 64 KB instruction memory
) (
    input logic clk,                // clock signal

    input Word data_addr,            // data address
    input ReqBytes req_bytes,       // number of requested bytes by lsu

    input logic write_enable,       // enable write if high, only read by default
    input Word data_in,             // write to address of data_addr, write req_bytes bytes

    output Word data_out,           // fetched data
    output logic data_not_found      // data not found

);

    Byte container [MEM_SIZE_BYTES - 1: 0];

    // data read
    always_comb begin
        data_out = '0;
        data_not_found = 1'b0;
        if (req_bytes == ZERO) begin    // dont do anything if zero
        end else if ((data_addr + req_bytes) > MEM_SIZE_BYTES) begin
            data_not_found = 1'b1;
        end else begin
            case (req_bytes)    // DATA_WIDTH IN BYTES MUST BE >= THAN ALL ReqBytes CASES
                ONE: data_out = 
                    {{(DATA_WIDTH - 8){1'b0}}, container[data_addr]};
                TWO: data_out = 
                    {{(DATA_WIDTH - 16){1'b0}}, 
                        container[data_addr + 1], 
                        container[data_addr]
                        };
                FOUR: data_out = 
                    {{(DATA_WIDTH - 32){1'b0}}, 
                        container[data_addr + 3], 
                        container[data_addr + 2], 
                        container[data_addr + 1], 
                        container[data_addr]
                        };
                default: data_not_found = 1'b1;
            endcase
        end
    end

    // data write
    always_ff @(posedge clk) begin
        if (write_enable && !data_not_found) begin
            case(req_bytes)
                ONE: begin
                    container[data_addr]     <= data_in[7:0];
                end
                TWO: begin
                    container[data_addr]     <= data_in[7:0];
                    container[data_addr + 1] <= data_in[15:8];
                end
                FOUR: begin
                    container[data_addr]     <= data_in[7:0];
                    container[data_addr + 1] <= data_in[15:8];
                    container[data_addr + 2] <= data_in[23:16];
                    container[data_addr + 3] <= data_in[31:24];
                end
                default: begin end
            endcase
        end
    end

endmodule