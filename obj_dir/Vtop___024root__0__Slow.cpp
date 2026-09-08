// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

VL_ATTR_COLD void Vtop___024root___eval_static__TOP(Vtop___024root* vlSelf);
VL_ATTR_COLD void Vtop___024root____Vm_traceActivitySetAll(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root___eval_static__TOP(vlSelf);
    Vtop___024root____Vm_traceActivitySetAll(vlSelf);
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
}

VL_ATTR_COLD void Vtop___024root___eval_static__TOP(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static__TOP\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9124449291403006271ull);
    vlSelf->top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2324538194100007937ull);
}

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("src/design\\top.sv", 3, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 10000 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtop___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtop___024root___eval_triggers_vec__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers_vec__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtop___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtop___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__stl\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

extern const VlUnpacked<CData/*0:0*/, 16> Vtop__ConstPool__TABLE_h50f0aed2_0;

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*3:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    vlSelfRef.stop = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__stop_signal;
    vlSelfRef.meta_instr_count = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__instr_count;
    vlSelfRef.meta_stall_count = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__stall_count;
    vlSelfRef.meta_l_use_count = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count;
    vlSelfRef.meta_br_flush_count = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count;
    vlSelfRef.top__DOT__write_enable = 0U;
    vlSelfRef.top__DOT__write_data = 0U;
    if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_read)))) {
        if (vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_write) {
            vlSelfRef.top__DOT__write_enable = 1U;
            if ((0U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3))) {
                vlSelfRef.top__DOT__write_data = (0x000000ffU 
                                                  & vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_rs2_val);
            } else if ((1U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3))) {
                vlSelfRef.top__DOT__write_data = (0x0000ffffU 
                                                  & vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_rs2_val);
            } else if ((2U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3))) {
                vlSelfRef.top__DOT__write_data = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_rs2_val;
            }
        }
    }
    vlSelfRef.top__DOT__if_addr = vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pc;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2_valid 
        = ((0x33U == (0x0000007fU & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)) 
           | ((0x23U == (0x0000007fU & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)) 
              | (0x63U == (0x0000007fU & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr))));
    vlSelfRef.top__DOT__data_addr = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result;
    vlSelfRef.top__DOT__req_bytes = 0U;
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0 = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_jal) 
                                                | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_jalr));
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode 
        = (0x0000007fU & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr);
    vlSelfRef.top__DOT__u_cpu__DOT__alu_in1_sel = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__alu_in2_sel = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__alu_bypass = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__reg_w_enable = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_write = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_read = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__alu_op = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_to_reg = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__imm_to_reg = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__pc_in1_sel = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__d_is_branch = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__d_is_jal = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__d_is_jalr = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 5U;
    vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__d_stop = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__d_valid_instr = 1U;
    if ((0x00000040U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        if ((0x00000020U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((0x00000010U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                        if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                            if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                                vlSelfRef.top__DOT__u_cpu__DOT__alu_bypass = 1U;
                                vlSelfRef.top__DOT__u_cpu__DOT__d_stop = 1U;
                                vlSelfRef.top__DOT__u_cpu__DOT__d_valid_instr = 0U;
                            } else {
                                vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                            }
                        } else {
                            vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                        }
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                    }
                } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__alu_bypass = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 0U;
                        vlSelfRef.top__DOT__u_cpu__DOT__d_stop = 1U;
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                }
            } else if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                        if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                            vlSelfRef.top__DOT__u_cpu__DOT__reg_w_enable = 1U;
                            vlSelfRef.top__DOT__u_cpu__DOT__alu_in1_sel = 1U;
                            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 4U;
                            vlSelfRef.top__DOT__u_cpu__DOT__d_is_jal = 1U;
                        } else {
                            vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                        }
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                }
            } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__reg_w_enable = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__alu_in1_sel = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__pc_in1_sel = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 0U;
                        vlSelfRef.top__DOT__u_cpu__DOT__d_is_jalr = 1U;
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                }
            } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__alu_in2_sel = 0U;
                    vlSelfRef.top__DOT__u_cpu__DOT__alu_op 
                        = ((0x00004000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                            ? ((0x00002000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                                ? 0x0cU : 0x0dU) : 
                           ((0x00002000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                             ? 0U : 4U));
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 2U;
                    vlSelfRef.top__DOT__u_cpu__DOT__d_is_branch = 1U;
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
        }
    } else if ((0x00000020U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        if ((0x00000010U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
            } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__reg_w_enable = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__imm_to_reg = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 3U;
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                }
            } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__0__return_op 
                        = ((0x00004000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                            ? ((0x00002000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                                ? ((0x00001000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                                    ? 6U : 5U) : ((0x00001000U 
                                                   & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                                                   ? 
                                                  ((0x40000000U 
                                                    & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                                                    ? 0x0bU
                                                    : 0x0aU)
                                                   : 4U))
                            : ((0x00002000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                                ? ((0x00001000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                                    ? 0x0cU : 0x0dU)
                                : ((0x00001000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                                    ? 8U : ((0x40000000U 
                                             & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                                             ? 1U : 0U))));
                    vlSelfRef.top__DOT__u_cpu__DOT__reg_w_enable = 1U;
                    vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__0__Vfuncout 
                        = vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__0__return_op;
                    vlSelfRef.top__DOT__u_cpu__DOT__alu_in2_sel = 0U;
                    vlSelfRef.top__DOT__u_cpu__DOT__alu_op 
                        = vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__0__Vfuncout;
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
            }
        } else if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
        } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
        } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                vlSelfRef.top__DOT__u_cpu__DOT__mem_write = 1U;
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 1U;
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
        }
    } else if ((0x00000010U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
        } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__reg_w_enable = 1U;
                    vlSelfRef.top__DOT__u_cpu__DOT__alu_in1_sel = 1U;
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 3U;
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
            }
        } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__1__return_op 
                    = ((0x00004000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                        ? ((0x00002000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                            ? ((0x00001000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                                ? 6U : 5U) : ((0x00001000U 
                                               & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                                               ? ((0x40000000U 
                                                   & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                                                   ? 0x0bU
                                                   : 0x0aU)
                                               : 4U))
                        : ((0x00002000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                            ? ((0x00001000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                                ? 0x0cU : 0x0dU) : 
                           ((0x00001000U & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)
                             ? 8U : 0U)));
                vlSelfRef.top__DOT__u_cpu__DOT__reg_w_enable = 1U;
                vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__1__Vfuncout 
                    = vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__1__return_op;
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 0U;
                vlSelfRef.top__DOT__u_cpu__DOT__alu_op 
                    = vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__1__Vfuncout;
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
        }
    } else if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
    } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
    } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            vlSelfRef.top__DOT__u_cpu__DOT__reg_w_enable = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__mem_to_reg = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__mem_read = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 0U;
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
        }
    } else if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr = 1U;
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__d_valid_instr = 0U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2 = 0U;
    if (vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_bypass) {
        vlSelfRef.top__DOT__u_cpu__DOT__alu_out = 0U;
    } else if (vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_to_reg) {
        vlSelfRef.top__DOT__u_cpu__DOT__alu_out = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_val;
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
            = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_in1_ropc)
                ? vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc
                : vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs1_data);
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2 
            = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_in2_roi)
                ? vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_val
                : vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs2_data);
        vlSelfRef.top__DOT__u_cpu__DOT__alu_out = (
                                                   (8U 
                                                    & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op))
                                                    ? 
                                                   ((4U 
                                                     & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op))
                                                     ? 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op))
                                                      ? 0U
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op))
                                                       ? 
                                                      (VL_LTS_III(32, vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1, vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)
                                                        ? 1U
                                                        : 0U)
                                                       : 
                                                      ((vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                                        < vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)
                                                        ? 1U
                                                        : 0U)))
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op))
                                                       ? 
                                                      VL_SHIFTRS_III(32,32,5, vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1, 
                                                                     (0x0000001fU 
                                                                      & vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2))
                                                       : 
                                                      (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                                       >> 
                                                       (0x0000001fU 
                                                        & vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op))
                                                       ? 0U
                                                       : 
                                                      (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                                       << 
                                                       (0x0000001fU 
                                                        & vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)))))
                                                    : 
                                                   ((4U 
                                                     & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op))
                                                     ? 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op))
                                                       ? 0U
                                                       : 
                                                      (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                                       & vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op))
                                                       ? 
                                                      (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                                       | vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)
                                                       : 
                                                      (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                                       ^ vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)))
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op))
                                                      ? 0U
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op))
                                                       ? 
                                                      (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                                       - vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)
                                                       : 
                                                      (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                                       + vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)))));
    }
    vlSelfRef.top__DOT__instr = 0U;
    if ((0x0000fffcU > vlSelfRef.top__DOT__if_addr)) {
        vlSelfRef.top__DOT__instr = (((((IData)(vlSelfRef.top__DOT__u_instr_mem__DOT__container
                                                [(0x0000ffffU 
                                                  & ((IData)(3U) 
                                                     + vlSelfRef.top__DOT__if_addr))]) 
                                        << 8U) | vlSelfRef.top__DOT__u_instr_mem__DOT__container
                                       [(0x0000ffffU 
                                         & ((IData)(2U) 
                                            + vlSelfRef.top__DOT__if_addr))]) 
                                      << 0x00000010U) 
                                     | (((IData)(vlSelfRef.top__DOT__u_instr_mem__DOT__container
                                                 [(0x0000ffffU 
                                                   & ((IData)(1U) 
                                                      + vlSelfRef.top__DOT__if_addr))]) 
                                         << 8U) | vlSelfRef.top__DOT__u_instr_mem__DOT__container
                                        [(0x0000ffffU 
                                          & vlSelfRef.top__DOT__if_addr)]));
    }
    vlSelfRef.top__DOT__data_fault = 0U;
    vlSelfRef.top__DOT__read_data = 0U;
    if (vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_read) {
        if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3))) {
            if ((1U & (~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3) 
                          >> 1U)))) {
                vlSelfRef.top__DOT__req_bytes = ((1U 
                                                  & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3))
                                                  ? 2U
                                                  : 1U);
            }
        } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3))) {
            if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3)))) {
                vlSelfRef.top__DOT__req_bytes = 4U;
            }
        } else {
            vlSelfRef.top__DOT__req_bytes = ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3))
                                              ? 2U : 1U);
        }
    } else if (vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_write) {
        if ((0U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3))) {
            vlSelfRef.top__DOT__req_bytes = 1U;
        } else if ((1U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3))) {
            vlSelfRef.top__DOT__req_bytes = 2U;
        } else if ((2U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3))) {
            vlSelfRef.top__DOT__req_bytes = 4U;
        }
    }
    if ((0U != (IData)(vlSelfRef.top__DOT__req_bytes))) {
        if ((0x00010000U < (vlSelfRef.top__DOT__data_addr 
                            + (IData)(vlSelfRef.top__DOT__req_bytes)))) {
            vlSelfRef.top__DOT__data_fault = 1U;
        } else if ((1U != (IData)(vlSelfRef.top__DOT__req_bytes))) {
            if ((2U != (IData)(vlSelfRef.top__DOT__req_bytes))) {
                if ((4U != (IData)(vlSelfRef.top__DOT__req_bytes))) {
                    vlSelfRef.top__DOT__data_fault = 1U;
                }
            }
        }
        if ((0x00010000U >= (vlSelfRef.top__DOT__data_addr 
                             + (IData)(vlSelfRef.top__DOT__req_bytes)))) {
            if ((1U == (IData)(vlSelfRef.top__DOT__req_bytes))) {
                vlSelfRef.top__DOT__read_data = vlSelfRef.top__DOT__u_data_mem__DOT__container
                    [(0x0000ffffU & vlSelfRef.top__DOT__data_addr)];
            } else if ((2U == (IData)(vlSelfRef.top__DOT__req_bytes))) {
                vlSelfRef.top__DOT__read_data = ((vlSelfRef.top__DOT__u_data_mem__DOT__container
                                                  [
                                                  (0x0000ffffU 
                                                   & ((IData)(1U) 
                                                      + vlSelfRef.top__DOT__data_addr))] 
                                                  << 8U) 
                                                 | vlSelfRef.top__DOT__u_data_mem__DOT__container
                                                 [(0x0000ffffU 
                                                   & vlSelfRef.top__DOT__data_addr)]);
            } else if ((4U == (IData)(vlSelfRef.top__DOT__req_bytes))) {
                vlSelfRef.top__DOT__read_data = (((
                                                   ((IData)(vlSelfRef.top__DOT__u_data_mem__DOT__container
                                                            [
                                                            (0x0000ffffU 
                                                             & ((IData)(3U) 
                                                                + vlSelfRef.top__DOT__data_addr))]) 
                                                    << 8U) 
                                                   | vlSelfRef.top__DOT__u_data_mem__DOT__container
                                                   [
                                                   (0x0000ffffU 
                                                    & ((IData)(2U) 
                                                       + vlSelfRef.top__DOT__data_addr))]) 
                                                  << 0x00000010U) 
                                                 | (((IData)(vlSelfRef.top__DOT__u_data_mem__DOT__container
                                                             [
                                                             (0x0000ffffU 
                                                              & ((IData)(1U) 
                                                                 + vlSelfRef.top__DOT__data_addr))]) 
                                                     << 8U) 
                                                    | vlSelfRef.top__DOT__u_data_mem__DOT__container
                                                    [
                                                    (0x0000ffffU 
                                                     & vlSelfRef.top__DOT__data_addr)]));
            }
        }
    }
    __Vtableidx1 = (((0U == vlSelfRef.top__DOT__u_cpu__DOT__alu_out) 
                     << 3U) | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_funct3));
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__branch_passed 
        = Vtop__ConstPool__TABLE_h50f0aed2_0[__Vtableidx1];
    vlSelfRef.halt = ((0x0000fffcU <= vlSelfRef.top__DOT__if_addr) 
                      | ((IData)(vlSelfRef.top__DOT__data_fault) 
                         | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr)));
    vlSelfRef.top__DOT__u_cpu__DOT__reg_write_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result;
    if (vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_read) {
        if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3))) {
            if ((1U & (~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3) 
                          >> 1U)))) {
                vlSelfRef.top__DOT__u_cpu__DOT__reg_write_data 
                    = ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3))
                        ? (0x0000ffffU & vlSelfRef.top__DOT__read_data)
                        : (0x000000ffU & vlSelfRef.top__DOT__read_data));
            }
        } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3))) {
            if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3)))) {
                vlSelfRef.top__DOT__u_cpu__DOT__reg_write_data 
                    = vlSelfRef.top__DOT__read_data;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__reg_write_data 
                = ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3))
                    ? (((- (IData)((1U & (vlSelfRef.top__DOT__read_data 
                                          >> 0x0fU)))) 
                        << 0x00000010U) | (0x0000ffffU 
                                           & vlSelfRef.top__DOT__read_data))
                    : (((- (IData)((1U & (vlSelfRef.top__DOT__read_data 
                                          >> 7U)))) 
                        << 8U) | (0x000000ffU & vlSelfRef.top__DOT__read_data)));
        }
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pcinc_in2_doi 
        = (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_branch) 
            & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__branch_passed)) 
           | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0));
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pcinc_in2_doi) {
        if (vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc_in1_sel) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in1 
                = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs1_data;
            vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in2 
                = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_val;
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in1 
                = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc;
            vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in2 
                = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_val;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in1 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pc;
        vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in2 = 4U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pc_next 
        = (0xfffffffeU & (vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in1 
                          + vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in2));
    vlSelfRef.top__DOT__u_cpu__DOT__hz_pc_enable = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_if_id_enable = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_id_ex_clear = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__meta_is_stall = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__meta_is_l_use = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__is_l_use_no_gap 
        = ((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_read) 
             & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_reg_write)) 
            & (0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rd_addr))) 
           & ((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2_valid) 
                | ((0x13U == (0x0000007fU & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)) 
                   | ((3U == (0x0000007fU & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)) 
                      | ((0x67U == (0x0000007fU & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)) 
                         | (0x73U == (0x0000007fU & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr)))))) 
               & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rd_addr) 
                  == (0x0000001fU & (vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr 
                                     >> 0x0000000fU)))) 
              | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2_valid) 
                 & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rd_addr) 
                    == (0x0000001fU & (vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr 
                                       >> 0x00000014U))))));
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pcinc_in2_doi) {
        vlSelfRef.top__DOT__u_cpu__DOT__hz_id_ex_clear = 1U;
    } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__is_l_use_no_gap) {
        vlSelfRef.top__DOT__u_cpu__DOT__hz_pc_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__hz_if_id_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__hz_id_ex_clear = 1U;
        vlSelfRef.top__DOT__u_cpu__DOT__meta_is_stall = 1U;
        vlSelfRef.top__DOT__u_cpu__DOT__meta_is_l_use = 1U;
    }
}

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
        Vtop___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtop___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtop___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtop___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtop___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vtop___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root____Vm_traceActivitySetAll(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root____Vm_traceActivitySetAll\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
}

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1638864771569018232ull);
    vlSelf->halt = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11049222807502041558ull);
    vlSelf->stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16026904639853099817ull);
    vlSelf->meta_instr_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10015820582880033300ull);
    vlSelf->meta_stall_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14134897821726767834ull);
    vlSelf->meta_l_use_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9335564172548842940ull);
    vlSelf->meta_br_flush_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3248577445493138422ull);
    vlSelf->top__DOT__if_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9948625378764159429ull);
    vlSelf->top__DOT__data_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16073976394386819418ull);
    vlSelf->top__DOT__write_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 554206876145221615ull);
    vlSelf->top__DOT__write_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5791377118671855880ull);
    vlSelf->top__DOT__req_bytes = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 16775011400878586817ull);
    vlSelf->top__DOT__instr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3126867797622976717ull);
    vlSelf->top__DOT__read_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 56483938310836132ull);
    vlSelf->top__DOT__data_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8167140621540713626ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_pc_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15097604899420171104ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_if_id_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8078186626949710136ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_id_ex_clear = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5469036487018072866ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_meta_is_stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12873730535212990782ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_meta_is_l_use = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16572838530136802213ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_meta_branch_flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15078727076717298173ull);
    vlSelf->top__DOT__u_cpu__DOT__reg_w_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10223263319588754604ull);
    vlSelf->top__DOT__u_cpu__DOT__rdst_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17065176272422443287ull);
    vlSelf->top__DOT__u_cpu__DOT__pc_in1_sel = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4031094445959648418ull);
    vlSelf->top__DOT__u_cpu__DOT__if_id_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1709853132189231410ull);
    vlSelf->top__DOT__u_cpu__DOT__if_id_instr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18411245862516480260ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5494201134156193131ull);
    vlSelf->top__DOT__u_cpu__DOT__imm_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10333335306906697625ull);
    vlSelf->top__DOT__u_cpu__DOT__illegal_instr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14818882104295685375ull);
    vlSelf->top__DOT__u_cpu__DOT__d_is_branch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15609380771558330870ull);
    vlSelf->top__DOT__u_cpu__DOT__d_is_jal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10496328843272864426ull);
    vlSelf->top__DOT__u_cpu__DOT__d_is_jalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 67005864643446593ull);
    vlSelf->top__DOT__u_cpu__DOT__d_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13525898123576513929ull);
    vlSelf->top__DOT__u_cpu__DOT__d_valid_instr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15351992385630302526ull);
    vlSelf->top__DOT__u_cpu__DOT__imm_type = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 17771432074263927410ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13811012327199315214ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_rs1_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 5510206514123928825ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_rs2_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 11391892174079173309ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_rd_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 1284006743651788119ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_rs1_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7200547187505777306ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_rs2_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 685965317621172872ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_imm_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6943186970993868990ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_alu_in1_ropc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2604175333716274025ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_alu_in2_roi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17683051422305902623ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_alu_op = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 5414918197405413712ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_alu_bypass = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12459983598956300446ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12647249009249248702ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16655142461626830243ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 7048750492435766523ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_pc_in1_sel = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14392788305842454303ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_is_branch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7944670826139486196ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_is_jal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3809299081348756410ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_is_jalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2795056145993351996ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16251735131458765682ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_imm_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9222393995847866136ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18405855007728579971ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6628400893274382243ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_valid_instr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9884091738772220562ull);
    vlSelf->top__DOT__u_cpu__DOT__alu_op = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 12758967225510099876ull);
    vlSelf->top__DOT__u_cpu__DOT__alu_in1_sel = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15870090315687284172ull);
    vlSelf->top__DOT__u_cpu__DOT__alu_in2_sel = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15916634701875632495ull);
    vlSelf->top__DOT__u_cpu__DOT__alu_bypass = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9049029015462005213ull);
    vlSelf->top__DOT__u_cpu__DOT__alu_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3482279785517445549ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_rs2_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2732589158360952590ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_rd_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 13775499201085202000ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3986449201690900979ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6891396199096775498ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16433501515530112205ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 7358728625184629902ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11669702140753607184ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13334913426715958517ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9505698503944766965ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_valid_instr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14393220491820429867ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11728375109217349596ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8396010597759043545ull);
    vlSelf->top__DOT__u_cpu__DOT__reg_write_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4252256717780325557ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_wb_rd_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9841072902432727225ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_wb_rd_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17994396378917634444ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_wb_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5380692490876238206ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_wb_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7768551789704405039ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_wb_valid_instr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3769117203145249260ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_opcode = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7288527285578457779ull);
    vlSelf->top__DOT__u_cpu__DOT__meta_is_stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14985430870743088885ull);
    vlSelf->top__DOT__u_cpu__DOT__meta_is_l_use = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17130976420207120270ull);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->top__DOT__u_cpu__DOT__u_reg_file__DOT__registers[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1375488913775379883ull);
    }
    vlSelf->top__DOT__u_cpu__DOT__u_reg_file__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3297519375640141125ull);
    vlSelf->top__DOT__u_cpu__DOT__u_pc__DOT__pcinc_in2_doi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17573726952508183958ull);
    vlSelf->top__DOT__u_cpu__DOT__u_pc__DOT__pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1399258308895884909ull);
    vlSelf->top__DOT__u_cpu__DOT__u_pc__DOT__pc_next = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11855832878590989954ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8193924015858267261ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__is_l_use_no_gap = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4307761914958492497ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 14033807547098626134ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 4286665488713578528ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 17442344079847020893ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 11129129801425507308ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__data1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14033296306717898790ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__data2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12677144840115112110ull);
    vlSelf->top__DOT__u_cpu__DOT__u_branch_unit__DOT__branch_passed = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5030301645421667381ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__stop_signal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12421637888803468164ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__instr_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15613914127732262431ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__stall_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11702730034716601678ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 385372348010913071ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12465170206570378654ull);
    for (int __Vi0 = 0; __Vi0 < 65536; ++__Vi0) {
        vlSelf->top__DOT__u_instr_mem__DOT__container[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17838547526792547713ull);
    }
    vlSelf->top__DOT__u_instr_mem__DOT__addr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17482381438776612688ull);
    for (int __Vi0 = 0; __Vi0 < 65536; ++__Vi0) {
        vlSelf->top__DOT__u_data_mem__DOT__container[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6583783866916463061ull);
    }
    vlSelf->__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__0__Vfuncout = 0;
    vlSelf->__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__0__return_op = 0;
    vlSelf->__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__1__Vfuncout = 0;
    vlSelf->__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__1__return_op = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
