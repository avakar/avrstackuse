#include <boost/cstdint.hpp>

enum avr_opcode_t
{
	avr_op_add, avr_op_adc, avr_op_addiw, avr_op_sub, avr_op_subi, avr_op_sbc, avr_op_sbci, avr_op_sbiw,
	avr_op_and, avr_op_andi, avr_op_or, avr_op_ori, avr_op_eor, avr_op_com, avr_op_neg, avr_op_sbr,
	avr_op_cbr, avr_op_inc, avr_op_dec, avr_op_tst, avr_op_clr, avr_op_ser, avr_op_mul, avr_op_muls,
	avr_op_mulsu, avr_op_fmul, avr_op_fmuls, avr_op_fmulsu, avr_op_des,

	avr_op_rjmp, avr_op_ijmp, avr_op_eijmp, avr_op_jmp, avr_op_rcall, avr_op_icall, avr_op_eicall,
	avr_op_call, avr_op_ret, avr_op_reti, avr_op_cpse, avr_op_cp, avr_op_cpc, avr_op_cpi, avr_op_sbrc,
	avr_op_sbrs, avr_op_sbic, avr_op_sbis, avr_op_brbs, avr_op_brbc, avr_op_breq, avr_op_brne, avr_op_brcs,
	avr_op_brcc, avr_op_brsh, avr_op_brlo, avr_op_brmi, avr_op_brpl, avr_op_brge, avr_op_brlt, avr_op_brhs,
	avr_op_brhc, avr_op_brts, avr_op_brtc, avr_op_brvs, avr_op_brvc, avr_op_brie, avr_op_brid,

	avr_op_mov, avr_op_movw, avr_op_ldi, avr_op_lds, avr_op_ld, avr_op_ldd, avr_op_st, avr_op_sts, avr_op_std, avr_op_lpm,
	avr_op_elpm, avr_op_spm, avr_op_in, avr_op_out, avr_op_push, avr_op_pop, avr_op_lsl, avr_op_lsr,
	avr_op_rol, avr_op_ror, avr_op_asr, avr_op_swap, avr_op_bset, avr_op_bclr, avr_op_sbi, avr_op_cbi,
	avr_op_bst, avr_op_bld, avr_op_sec, avr_op_clc, avr_op_sen, avr_op_cln, avr_op_sez, avr_op_clz, avr_op_sei,
	avr_op_cli, avr_op_ses, avr_op_cls, avr_op_sev, avr_op_clv, avr_op_set, avr_op_clt, avr_op_seh, avr_op_clh,

	avr_op_break, avr_op_nop, avr_op_sleep, avr_op_wdr,
};

struct avr_instruction_info
{
	enum address_mode_t
	{
		addr_one_register,
		addr_two_registers,
		addr_io,
		addr_direct_data,
		addr_indirect_data_with_displacement,
		addr_indirect_data,
		addr_indirect_with_predecrement,
		addr_indirect_with_postincrement,
		addr_program_constant,
		addr_program_with_postincrement,
		addr_direct_program,
		addr_indirect_program,
		addr_relative_program,
	};

	avr_opcode_t m_opcode;
	address_mode_t m_address_mode;
};

struct avr_instruction_entry_t
{
	avr_opcode_t op;
	boost::uint_least16_t opcode;
	boost::uint_least16_t mask;
	int length;
	bool superseeded;
};

avr_instruction_entry_t * avr_find_instruction_entry(boost::uint_least16_t word);
