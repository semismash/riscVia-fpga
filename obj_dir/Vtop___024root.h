// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(rst_n,0,0);
        VL_OUT8(halt,0,0);
        VL_OUT8(stop,0,0);
        CData/*0:0*/ top__DOT__write_enable;
        CData/*2:0*/ top__DOT__req_bytes;
        CData/*0:0*/ top__DOT__data_fault;
        CData/*0:0*/ top__DOT__u_cpu__DOT__hz_pc_enable;
        CData/*0:0*/ top__DOT__u_cpu__DOT__hz_if_id_enable;
        CData/*0:0*/ top__DOT__u_cpu__DOT__hz_id_ex_clear;
        CData/*0:0*/ top__DOT__u_cpu__DOT__hz_meta_is_stall;
        CData/*0:0*/ top__DOT__u_cpu__DOT__hz_meta_is_l_use;
        CData/*0:0*/ top__DOT__u_cpu__DOT__hz_meta_branch_flush;
        CData/*0:0*/ top__DOT__u_cpu__DOT__reg_w_enable;
        CData/*0:0*/ top__DOT__u_cpu__DOT__pc_in1_sel;
        CData/*0:0*/ top__DOT__u_cpu__DOT__mem_to_reg;
        CData/*0:0*/ top__DOT__u_cpu__DOT__imm_to_reg;
        CData/*0:0*/ top__DOT__u_cpu__DOT__illegal_instr;
        CData/*0:0*/ top__DOT__u_cpu__DOT__d_is_branch;
        CData/*0:0*/ top__DOT__u_cpu__DOT__d_is_jal;
        CData/*0:0*/ top__DOT__u_cpu__DOT__d_is_jalr;
        CData/*0:0*/ top__DOT__u_cpu__DOT__d_stop;
        CData/*0:0*/ top__DOT__u_cpu__DOT__d_valid_instr;
        CData/*2:0*/ top__DOT__u_cpu__DOT__imm_type;
        CData/*4:0*/ top__DOT__u_cpu__DOT__id_ex_rs1_addr;
        CData/*4:0*/ top__DOT__u_cpu__DOT__id_ex_rs2_addr;
        CData/*4:0*/ top__DOT__u_cpu__DOT__id_ex_rd_addr;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_alu_in1_ropc;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_alu_in2_roi;
        CData/*3:0*/ top__DOT__u_cpu__DOT__id_ex_alu_op;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_alu_bypass;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_mem_read;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_mem_write;
        CData/*2:0*/ top__DOT__u_cpu__DOT__id_ex_funct3;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_pc_in1_sel;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_is_branch;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_is_jal;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_is_jalr;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_reg_write;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_imm_to_reg;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_mem_to_reg;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_stop;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_valid_instr;
        CData/*3:0*/ top__DOT__u_cpu__DOT__alu_op;
        CData/*0:0*/ top__DOT__u_cpu__DOT__alu_in1_sel;
        CData/*0:0*/ top__DOT__u_cpu__DOT__alu_in2_sel;
        CData/*0:0*/ top__DOT__u_cpu__DOT__alu_bypass;
        CData/*4:0*/ top__DOT__u_cpu__DOT__ex_mem_rd_addr;
        CData/*0:0*/ top__DOT__u_cpu__DOT__ex_mem_mem_read;
        CData/*0:0*/ top__DOT__u_cpu__DOT__ex_mem_mem_write;
        CData/*2:0*/ top__DOT__u_cpu__DOT__ex_mem_funct3;
        CData/*0:0*/ top__DOT__u_cpu__DOT__ex_mem_reg_write;
        CData/*0:0*/ top__DOT__u_cpu__DOT__ex_mem_mem_to_reg;
        CData/*0:0*/ top__DOT__u_cpu__DOT__ex_mem_stop;
        CData/*0:0*/ top__DOT__u_cpu__DOT__ex_mem_valid_instr;
        CData/*0:0*/ top__DOT__u_cpu__DOT__mem_read;
        CData/*0:0*/ top__DOT__u_cpu__DOT__mem_write;
        CData/*4:0*/ top__DOT__u_cpu__DOT__mem_wb_rd_addr;
        CData/*0:0*/ top__DOT__u_cpu__DOT__mem_wb_reg_write;
        CData/*0:0*/ top__DOT__u_cpu__DOT__mem_wb_stop;
        CData/*0:0*/ top__DOT__u_cpu__DOT__mem_wb_valid_instr;
        CData/*0:0*/ top__DOT__u_cpu__DOT__id_ex_opcode;
        CData/*0:0*/ top__DOT__u_cpu__DOT__meta_is_stall;
        CData/*0:0*/ top__DOT__u_cpu__DOT__meta_is_l_use;
    };
    struct {
        CData/*0:0*/ top__DOT__u_cpu__DOT__u_pc__DOT__pcinc_in2_doi;
        CData/*0:0*/ top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2_valid;
        CData/*0:0*/ top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__is_l_use_no_gap;
        CData/*6:0*/ top__DOT__u_cpu__DOT__u_decoder__DOT__opcode;
        CData/*2:0*/ top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type;
        CData/*6:0*/ top__DOT__u_cpu__DOT__u_id_ex__DOT__i_opcode;
        CData/*6:0*/ top__DOT__u_cpu__DOT__u_id_ex__DOT__o_opcode;
        CData/*0:0*/ top__DOT__u_cpu__DOT__u_branch_unit__DOT__branch_passed;
        CData/*0:0*/ top__DOT__u_cpu__DOT__u_meta__DOT__stop_signal;
        CData/*3:0*/ __Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__0__Vfuncout;
        CData/*3:0*/ __Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__0__return_op;
        CData/*3:0*/ __Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__1__Vfuncout;
        CData/*3:0*/ __Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__1__return_op;
        CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_0;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VstlPhaseResult;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __VicoPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__rst_n__0;
        CData/*0:0*/ __VactPhaseResult;
        CData/*0:0*/ __VnbaPhaseResult;
        VL_OUT(meta_instr_count,31,0);
        VL_OUT(meta_stall_count,31,0);
        VL_OUT(meta_l_use_count,31,0);
        VL_OUT(meta_br_flush_count,31,0);
        IData/*31:0*/ top__DOT__if_addr;
        IData/*31:0*/ top__DOT__data_addr;
        IData/*31:0*/ top__DOT__write_data;
        IData/*31:0*/ top__DOT__instr;
        IData/*31:0*/ top__DOT__read_data;
        IData/*31:0*/ top__DOT__u_cpu__DOT__rdst_data;
        IData/*31:0*/ top__DOT__u_cpu__DOT__if_id_pc;
        IData/*31:0*/ top__DOT__u_cpu__DOT__if_id_instr;
        IData/*31:0*/ top__DOT__u_cpu__DOT__id_ex_pc;
        IData/*31:0*/ top__DOT__u_cpu__DOT__id_ex_rs1_data;
        IData/*31:0*/ top__DOT__u_cpu__DOT__id_ex_rs2_data;
        IData/*31:0*/ top__DOT__u_cpu__DOT__id_ex_imm_val;
        IData/*31:0*/ top__DOT__u_cpu__DOT__alu_out;
        IData/*31:0*/ top__DOT__u_cpu__DOT__ex_mem_rs2_val;
        IData/*31:0*/ top__DOT__u_cpu__DOT__ex_mem_result;
        IData/*31:0*/ top__DOT__u_cpu__DOT__reg_write_data;
        IData/*31:0*/ top__DOT__u_cpu__DOT__mem_wb_rd_data;
        IData/*31:0*/ top__DOT__u_cpu__DOT__u_reg_file__DOT__i;
        IData/*31:0*/ top__DOT__u_cpu__DOT__u_pc__DOT__pc;
        IData/*31:0*/ top__DOT__u_cpu__DOT__u_pc__DOT__pc_next;
        IData/*31:0*/ top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in1;
        IData/*31:0*/ top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in2;
        IData/*31:0*/ top__DOT__u_cpu__DOT__u_alu__DOT__data1;
        IData/*31:0*/ top__DOT__u_cpu__DOT__u_alu__DOT__data2;
        IData/*31:0*/ top__DOT__u_cpu__DOT__u_meta__DOT__instr_count;
        IData/*31:0*/ top__DOT__u_cpu__DOT__u_meta__DOT__stall_count;
        IData/*31:0*/ top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count;
        IData/*31:0*/ top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count;
        IData/*31:0*/ top__DOT__u_instr_mem__DOT__addr_reg;
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<IData/*31:0*/, 32> top__DOT__u_cpu__DOT__u_reg_file__DOT__registers;
        VlUnpacked<CData/*7:0*/, 65536> top__DOT__u_instr_mem__DOT__container;
        VlUnpacked<CData/*7:0*/, 65536> top__DOT__u_data_mem__DOT__container;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
        VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    };

    // INTERNAL VARIABLES
    Vtop__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* namep);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
