// metadata unit (flip-flop) for debugging, and instruction counter too

module meta (
    input logic clk,
    input logic rst_n,
    input logic valid_instr,
    // interfacing with meta unit
    input logic clear,  // syncrhonous clear
    // from hazard unit for telemetry data
    input logic is_stall,
    input logic is_l_use,
    input logic is_br_flush,
    // output
    output MetaCount meta_instr_count,
    output MetaCount meta_stall_count,
    output MetaCount meta_l_use_count,
    output MetaCount meta_br_flush_count
);

    MetaCount instr_count;   // upto 2^32 instructions tracking
    MetaCount stall_count;
    MetaCount l_use_count;
    MetaCount br_flush_count;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n || clear) begin
            instr_count     <= '0;
            stall_count     <= '0;
            l_use_count     <= '0;
            br_flush_count  <= '0;
        end else begin
            if (valid_instr)    instr_count     <= instr_count + 1'b1;
            if (is_stall)       stall_count     <= stall_count + 1'b1;
            if (is_l_use)       l_use_count     <= l_use_count + 1'b1;
            if (is_br_flush)    br_flush_count  <= br_flush_count + 2'd2;    // add 2 cycles here since flushes void 2 cycles worth of instructions
        end
    end

    assign meta_instr_count = instr_count;
    assign meta_stall_count = stall_count;
    assign meta_l_use_count = l_use_count;
    assign meta_br_flush_count = br_flush_count;

endmodule