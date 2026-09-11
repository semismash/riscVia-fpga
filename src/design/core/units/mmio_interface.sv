import rv32i::*;

typedef enum Word {
    UART_STATUS     = 32'h00000000,     // includes both rx_valid (LSB) + tx_busy (LSB + 1)
    UART_RX_DATA    = 32'h00000004,
    UART_TX_DATA    = 32'h00000008
} MMIOAddress;

// this module directly links the LSU to MMIO devices (for example, the UART controller)
module mmio_interface (
    input logic clk,
    input logic rst_n,

    input  Word mmio_data_addr,
    input  ReqBytes req_bytes,
    input  logic write_enable,
    input  Word mmio_data_in,

    // to LSU
    output Word mmio_data_out,
    output logic mmio_data_ready,

    // TO I/O modules:
    // UART RX/TX
    input Byte uart_rx_data,
    input logic uart_rx_valid,
    output Byte uart_tx_data,
    output logic uart_tx_start,
    input logic uart_tx_busy
);

    // no data fault raised, value simply discarded
    // MMIO is defined as everything after 0x80000000 (until 0xFFFFFFFF, 32-bit address space limit)
    // since we adjust mmio address, wrap-around condition due to 32-bit int limit is impossible

    Word mem_addr_0, mem_addr_1, mem_addr_2, mem_addr_3;
    Byte mem_data_write_0, mem_data_write_1, mem_data_write_2, mem_data_write_3; 

    MMIOAddress mmio_corrected_addr;
    assign mmio_corrected_addr = MMIOAddress'({1'b0, mmio_data_addr[30:0]});

    // DEVELOPERS NOTE: In this file, nomeclature wise, corrected addresses will be referred to by [square brackets]

    MMIOAddress mmioplus1, mmioplus2, mmioplus3;
    assign mmioplus1 = MMIOAddress'(mmio_corrected_addr + 1'd1);
    assign mmioplus2 = MMIOAddress'(mmio_corrected_addr + 2'd2);
    assign mmioplus3 = MMIOAddress'(mmio_corrected_addr + 2'd3);

    // if out of bounds, saturate to 0xFFFFFFFF [0x7FFFFFFF]; this address is guaranteed to be unused
    assign mem_addr_0 = mmio_corrected_addr;
    assign mem_addr_1 = (mmioplus1 < MMIO_SIZE_BYTES) ? Word'(mmioplus1) : 32'h7FFFFFFF;
    assign mem_addr_2 = (mmioplus2 < MMIO_SIZE_BYTES) ? Word'(mmioplus2) : 32'h7FFFFFFF;
    assign mem_addr_3 = (mmioplus3 < MMIO_SIZE_BYTES) ? Word'(mmioplus3) : 32'h7FFFFFFF;

    // I/O interfacing port addresses
    Byte p_uart_status;    // 0x80000000   [0x00000000] (I)
    Byte p_uart_rx_data;   // 0x80000004   [0x00000004] (I)
    Byte p_uart_tx_data;   // 0x8000000C   [0x00000008] (O)

    // INPUTS
    assign p_uart_status  = {6'b0, uart_tx_busy, uart_rx_valid};
    assign p_uart_rx_data = uart_rx_data;
    
    // OUTPUTS
    assign uart_tx_data   = p_uart_tx_data;

    // unified function: use for all four read addresses to avoid redundancy
    function automatic Byte mmio_read_byte(input MMIOAddress addr);
        case (addr)
            UART_STATUS:  mmio_read_byte = p_uart_status;
            UART_RX_DATA: mmio_read_byte = p_uart_rx_data;
            default:      mmio_read_byte = 8'h00;  // ports not covered are pulled down to 0
        endcase
    endfunction

    always_comb begin
        mem_data_write_0 = '0;
        mem_data_write_1 = '0;
        mem_data_write_2 = '0;
        mem_data_write_3 = '0;
        if (write_enable) begin
            case (req_bytes)
                ONE: begin
                    mem_data_write_0 = mmio_data_in[7:0];
                end
                TWO: begin
                    mem_data_write_0 = mmio_data_in[7:0];
                    mem_data_write_1 = mmio_data_in[15:8];
                end
                FOUR: begin
                    mem_data_write_0 = mmio_data_in[7:0];
                    mem_data_write_1 = mmio_data_in[15:8];
                    mem_data_write_2 = mmio_data_in[23:16];
                    mem_data_write_3 = mmio_data_in[31:24];
                end
                default: begin
                end
            endcase
        end
    end

    // finds the lane which targetted TX_DATA
    logic tx_write_hit;
    Byte tx_write_byte;
    always_comb begin
        tx_write_hit  = 1'b0;
        tx_write_byte = 8'h00;
        if (mem_addr_0 == UART_TX_DATA) begin
            tx_write_hit  = 1'b1;
            tx_write_byte = mem_data_write_0;
        end else if (mem_addr_1 == UART_TX_DATA) begin
            tx_write_hit  = 1'b1;
            tx_write_byte = mem_data_write_1;
        end else if (mem_addr_2 == UART_TX_DATA) begin
            tx_write_hit  = 1'b1;
            tx_write_byte = mem_data_write_2;
        end else if (mem_addr_3 == UART_TX_DATA) begin
            tx_write_hit  = 1'b1;
            tx_write_byte = mem_data_write_3;
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin  // reset values on rst_n signal
        if (!rst_n) begin
            mmio_data_ready <= 1'b0;
            uart_tx_start   <= 1'b0;
            mmio_data_out   <= '0;
        end else begin

            // initialization
            uart_tx_start   <= 1'b0;
            mmio_data_ready <= (req_bytes != ZERO);     // set high when mem access data ready, LSU installs

            if (write_enable) begin     // output function
                if (tx_write_hit) begin                 // checks all 4 possible lanes
                    p_uart_tx_data <= tx_write_byte;
                    uart_tx_start  <= 1'b1;
                end
                mmio_data_out <= '0;
                // writes to invalid ports are discarded
            end else begin              // input function
                mmio_data_out <= {
                    mmio_read_byte(mem_addr_3), 
                    mmio_read_byte(mem_addr_2), 
                    mmio_read_byte(mem_addr_1), 
                    mmio_read_byte(mem_addr_0)
                };
            end
        end
    end

endmodule