import uart::*;

module uart_tx #(
    parameter int CLK_FREQ = 10_000_000,    // default 10 mhz
    parameter int BAUD_RATE = 9600
) (
    // clock and reset
    input logic         clk,
    input logic         rst_n,
    // validity
    input logic         tx_start,   // start transmission
    // data input
    input logic [7:0]   tx_data,
    // output bit
    output logic        tx,
    output logic        tx_busy     // high = currently transmitting a signal
);

    logic baud_tick;

    baud_rate_gen #(
        .CLK_FREQ         (CLK_FREQ),
        .BAUD_RATE        (BAUD_RATE),
        .SAMPLING_RATE    (1)
    ) u_baud_rate_gen (
        .clk              (clk),
        .rst_n            (rst_n),
        .tick             (baud_tick)
    );

    State cur_state;
    logic [2:0] data_cntr;
    logic [7:0] data_reg;
    logic start_pending;   // latched tx_start, waiting for a baud_tick boundary

    assign tx_busy = (cur_state != IDLE) || start_pending;

    always_ff @(posedge clk or negedge rst_n) begin
        if(!rst_n) begin
            cur_state     <= IDLE;
            data_cntr     <= '0;
            data_reg      <= '0;
            tx            <=  1'b1;   // hold to high on reset
            start_pending <=  1'b0;
        end else begin
            unique case (cur_state)
                default: begin  // covers IDLE
                    tx <= 1'b1; // hold high until start signal is given
                    if (tx_start && !start_pending) begin
                        data_reg <= tx_data;
                        start_pending <= 1'b1;
                    end
                    if (start_pending && baud_tick) begin
                        cur_state <= START;
                        tx  <= 1'b0;
                        start_pending <= 1'b0;
                    end
                end
                START: begin
                    tx <= 1'b0; // maintain to 0
                    if (baud_tick) begin    // one full period elapsed
                        cur_state <= DATA;
                        data_cntr <= 3'd0;
                        tx <= data_reg[0];  // start with LSB
                    end
                end
                DATA: begin
                    tx <= data_reg[0];  // always shift LSB of register out, reg gets shifted downwards anyways
                    if (baud_tick) begin
                        if (data_cntr == 3'd7) begin
                            cur_state <= STOP;
                            tx <= 1'b1; // drive high for STOP bit
                        end else begin
                            data_reg <= {1'b0, data_reg[6:0]};
                            data_cntr <= data_cntr + 1'b1;
                        end
                    end
                end
                STOP: begin
                    tx <= 1'b1; // hold high for stop
                    if (baud_tick) begin
                        cur_state <= IDLE;  // reset to idle
                    end
                end
            endcase
        end
    end

endmodule