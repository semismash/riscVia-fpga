module baud_rate_gen #(
    parameter int CLK_FREQ = 10_000_000,
    parameter int BAUD_RATE = 9600,
    parameter int SAMPLING_RATE = 16
) (
    input logic     clk,
    input logic     rst_n,
    output logic    tick
);

    localparam int MAX = ((CLK_FREQ)/(BAUD_RATE * SAMPLING_RATE));
    localparam int WIDTH = $clog2(MAX);

    logic [WIDTH - 1 : 0] counter;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            tick <= '0;
            counter <= '0;
        end else begin
            if (counter >= (MAX - 1)) begin
                tick <= 1'b1;
                counter <= '0;
            end else begin
                tick <= '0;
                counter <= counter + 1'b1;
            end
        end
    end

endmodule