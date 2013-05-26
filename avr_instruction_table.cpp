#include "avr_instruction_info.hpp"
#include <boost/cstdint.hpp>

#include <iostream>

template <typename T>
void foo(T t)
{
    std::cout << t << std::endl;
}

template
void foo(int t);

avr_instruction_entry_t instructions[] =
{
	{ avr_op_adc,   0x1c00, 0xfc00, 1 },
	{ avr_op_add,   0x0c00, 0xfc00, 1 },
	{ avr_op_addiw, 0x9600, 0xff00, 1 },
	{ avr_op_and,   0x2000, 0xfc00, 1 },
	{ avr_op_andi,  0x7000, 0xf000, 1 },
	{ avr_op_asr,   0x9405, 0xfe0f, 1 },
	{ avr_op_bclr,  0x9414, 0xff8f, 1 },
	{ avr_op_bld,   0xf800, 0xfe08, 1 },
	{ avr_op_brbc,  0xf400, 0xfc00, 1 },
	{ avr_op_brbs,  0xf000, 0xfc00, 1 },

	{ avr_op_brcc,  0xf400, 0xfc07, 1, true },
	{ avr_op_brcs,  0xf000, 0xfc07, 1, true },
	{ avr_op_breq,  0xf001, 0xfc07, 1, true },
	{ avr_op_brge,  0xf404, 0xfc07, 1, true },
	{ avr_op_brhc,  0xf405, 0xfc07, 1, true },
	{ avr_op_brhs,  0xf005, 0xfc07, 1, true },
	{ avr_op_brid,  0xf407, 0xfc07, 1, true },
	{ avr_op_brie,  0xf007, 0xfc07, 1, true },
	{ avr_op_brie,  0xf007, 0xfc07, 1, true },
	{ avr_op_brlo,  0xf000, 0xfc07, 1, true },
	{ avr_op_brlt,  0xf004, 0xfc07, 1, true },
	{ avr_op_brmi,  0xf002, 0xfc07, 1, true },
	{ avr_op_brne,  0xf401, 0xfc07, 1, true },
	{ avr_op_brpl,  0xf402, 0xfc07, 1, true },
	{ avr_op_brsh,  0xf400, 0xfc07, 1, true },
	{ avr_op_brtc,  0xf406, 0xfc07, 1, true },
	{ avr_op_brts,  0xf006, 0xfc07, 1, true },
	{ avr_op_brvc,  0xf003, 0xfc07, 1, true },
	{ avr_op_brvc,  0xf403, 0xfc07, 1, true },
	{ avr_op_brvs,  0xf003, 0xfc07, 1, true },

	{ avr_op_break, 0x9598, 0xffff, 1 },
	{ avr_op_bset,  0x9408, 0xff8f, 1 },
	{ avr_op_bst,   0xfa00, 0xfe08, 1 },

	{ avr_op_call,  0x940e, 0xfe0e, 2 },
	{ avr_op_cbi,   0x9800, 0xff00, 1 },
	{ avr_op_cbr,   0x7000, 0xf000, 1 },
	{ avr_op_clc,   0x9488, 0xffff, 1 },
	{ avr_op_clh,   0x94d8, 0xffff, 1 },
	{ avr_op_cli,   0x94f8, 0xffff, 1 },
	{ avr_op_cln,   0x94a8, 0xffff, 1 },
	{ avr_op_clr,   0x2400, 0xfc00, 1 },
	{ avr_op_cls,   0x94c8, 0xffff, 1 },
	{ avr_op_clt,   0x94e8, 0xffff, 1 },
	{ avr_op_clv,   0x94b8, 0xffff, 1 },
	{ avr_op_clz,   0x9498, 0xffff, 1 },
	{ avr_op_com,   0x9400, 0xfe0f, 1 },
	{ avr_op_cp,    0x1400, 0xfc00, 1 },
	{ avr_op_cpc,   0x0400, 0xfc00, 1 },
	{ avr_op_cpi,   0x3000, 0xf000, 1 },
	{ avr_op_cpse,  0x1000, 0xfc00, 1 },
	{ avr_op_dec,   0x940a, 0xfe0f, 1 },
	{ avr_op_des,   0x940b, 0xff0f, 1 },
	{ avr_op_eicall,0x9519, 0xffff, 1 },
	{ avr_op_eijmp, 0x9419, 0xffff, 1 },

	{ avr_op_elpm,  0x95d8, 0xffff, 1 },
	{ avr_op_elpm,  0x9006, 0xfe0f, 1 },
	{ avr_op_elpm,  0x9007, 0xfe0f, 1 },

	{ avr_op_fmul,  0x0308, 0xff88, 1 },
	{ avr_op_fmuls, 0x0380, 0xff88, 1 },
	{ avr_op_fmulsu,0x0388, 0xff88, 1 },

	{ avr_op_icall, 0x9509, 0xffff, 1 },
	{ avr_op_ijmp,  0x9409, 0xffff, 1 },
	{ avr_op_in,    0xb000, 0xf800, 1 },
	{ avr_op_inc,   0x9403, 0xfe0f, 1 },
	{ avr_op_jmp,   0x940c, 0xfe0e, 2 },

	{ avr_op_ld,    0x900c, 0xfe0f, 1 },
	{ avr_op_ld,    0x900d, 0xfe0f, 1 },
	{ avr_op_ld,    0x900e, 0xfe0f, 1 },

	{ avr_op_ld,    0x8008, 0xfe0f, 1 },
	{ avr_op_ld,    0x9009, 0xfe0f, 1 },
	{ avr_op_ld,    0x900a, 0xfe0f, 1 },
	{ avr_op_ldd,   0x8008, 0xd208, 1 },

	{ avr_op_ld,    0x8000, 0xfe0f, 1 },
	{ avr_op_ld,    0x9001, 0xfe0f, 1 },
	{ avr_op_ld,    0x9002, 0xfe0f, 1 },
	{ avr_op_ldd,   0x8000, 0xd208, 1 },

	{ avr_op_ldi,   0xe000, 0xf000, 1 },
	{ avr_op_lds,   0x9000, 0xfe0f, 2 },
	{ avr_op_lds,   0xa000, 0xfc00, 1 },
	
	{ avr_op_lpm,   0x95c8, 0xffff, 1 },
	{ avr_op_lpm,   0x9004, 0xfc0f, 1 },
	{ avr_op_lpm,   0x9005, 0xfc0f, 1 },

	{ avr_op_lsl,   0x0c00, 0xfc00, 1 },
	{ avr_op_lsr,   0x9406, 0xfe0f, 1 },

	{ avr_op_mov,   0x2c00, 0xfc00, 1 },
	{ avr_op_movw,  0x0100, 0xff00, 1 },

	{ avr_op_mul,   0x9c00, 0xfc00, 1 },
	{ avr_op_muls,  0x0200, 0xff00, 1 },
	{ avr_op_mulsu, 0x0300, 0xff88, 1 },

	{ avr_op_neg,   0x9401, 0xfe0f, 1 },
	{ avr_op_nop,   0x0000, 0xffff, 1 },

	{ avr_op_or,    0x2800, 0xfc00, 1 },
	{ avr_op_ori,   0x6000, 0xf000, 1 },
	{ avr_op_out,   0xb800, 0xf800, 1 },
	{ avr_op_pop,   0x900f, 0xfe0f, 1 },
	{ avr_op_push,  0x920f, 0xfe0f, 1 },
	{ avr_op_push,  0x920f, 0xfe0f, 1 },
	{ avr_op_rcall, 0xd000, 0xf000, 1 },
	{ avr_op_ret,   0x9508, 0xffff, 1 },
	{ avr_op_reti,  0x9518, 0xffff, 1 },
	{ avr_op_rjmp,  0xc000, 0xf000, 1 },
	{ avr_op_rol,   0x1c00, 0xfc00, 1 }, //adc
	{ avr_op_ror,   0x9407, 0xfe0f, 1 },
	{ avr_op_sbc,   0x0800, 0xfc00, 1 },
	{ avr_op_sbci,  0x4000, 0xf000, 1 },
	{ avr_op_sbi,   0x9a00, 0xff00, 1 },
	{ avr_op_sbic,  0x9900, 0xff00, 1 },
	{ avr_op_sbis,  0x9b00, 0xff00, 1 },
	{ avr_op_sbiw,  0x9700, 0xff00, 1 },
	{ avr_op_sbr,   0x6000, 0xf000, 1 },
	{ avr_op_sbrc,  0xfc00, 0xfe08, 1 },
	{ avr_op_sbrs,  0xfe00, 0xfe08, 1 },

	{ avr_op_sec,   0x9408, 0xffff, 1 },
	{ avr_op_seh,   0x9458, 0xffff, 1 },
	{ avr_op_sei,   0x9478, 0xffff, 1 },
	{ avr_op_sen,   0x9428, 0xffff, 1 },
	{ avr_op_ser,   0xef0f, 0xff0f, 1 },
	{ avr_op_ses,   0x9448, 0xffff, 1 },
	{ avr_op_set,   0x9468, 0xffff, 1 },
	{ avr_op_sev,   0x9438, 0xffff, 1 },
	{ avr_op_sez,   0x9418, 0xffff, 1 },
	
	{ avr_op_sleep, 0x9588, 0xffff, 1 },
	{ avr_op_spm,   0x95e8, 0xffff, 1 },
	{ avr_op_spm,   0x95f8, 0xffff, 1 },

	{ avr_op_st,    0x920c, 0xfe0f, 1 },
	{ avr_op_st,    0x920d, 0xfe0f, 1 },
	{ avr_op_st,    0x920e, 0xfe0f, 1 },

	{ avr_op_st,    0x8208, 0xfe0f, 1 },
	{ avr_op_st,    0x9209, 0xfe0f, 1 },
	{ avr_op_st,    0x920a, 0xfe0f, 1 },
	{ avr_op_std,   0x8208, 0xd208, 1 },

	{ avr_op_st,    0x8200, 0xfe0f, 1 },
	{ avr_op_st,    0x9201, 0xfe0f, 1 },
	{ avr_op_st,    0x9202, 0xfe0f, 1 },
	{ avr_op_std,   0x8200, 0xd208, 1 },

	{ avr_op_sts,   0x9200, 0xfe0f, 2 },
	{ avr_op_sts,   0xa800, 0xf800, 1 },

	{ avr_op_sub,   0x1800, 0xfc00, 1 },
	{ avr_op_subi,  0x5000, 0xf000, 1 },
	{ avr_op_swap,  0x9402, 0xfe0f, 1 },
	{ avr_op_tst,   0x2000, 0xfc00, 1 },
	{ avr_op_wdr,   0x95a8, 0xffff, 1 },
};

avr_instruction_entry_t * avr_find_instruction_entry(boost::uint_least16_t word)
{
	for (int i = 0; i < sizeof instructions / sizeof instructions[0]; ++i)
	{
		if ((word & instructions[i].mask) == instructions[i].opcode)
			return instructions + i;
	}

	return 0;
}
