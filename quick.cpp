#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <iterator>
#include <boost/cstdint.hpp>

#include "avr_instruction_info.hpp"

template <typename Address>
struct instruction
{
	typedef Address address_type;

	address_type first;
	std::size_t target_first, routine_first;
	address_type last;
	std::size_t target_last, routine_last;
};

template <typename Address>
struct flow_graph
{
	typedef Address address_type;

	std::vector<address_type> target_addresses;
	std::vector<address_type> routine_addresses;
	std::map<address_type, instruction<address_type> > instr_graph;
};

template <typename Program, typename Traits>
flow_graph<typename Traits::address_type> make_flow_graph(
	Program const & program, typename Traits::address_type address, Traits const & traits)
{
	typedef typename Traits::address_type address_type;

	flow_graph<address_type> res;
	
	std::vector<address_type> address_stack(1, address);
	std::set<address_type> added_addresses;

	while (!address_stack.empty())
	{
		instruction<address_type> inst = { address_stack.back(), res.target_addresses.size(), res.routine_addresses.size() };
		address_stack.pop_back();

		inst.last = traits.targets(program, inst.first,
			std::back_inserter(res.target_addresses), std::back_inserter(res.routine_addresses));

		if (inst.first == inst.last)
		{
			std::cout << "invalid instruction" << std::endl;
			continue;
		}

		inst.target_last = res.target_addresses.size();
		inst.routine_last = res.routine_addresses.size();
		res.instr_graph.insert(std::make_pair(inst.first, inst));

		for (std::size_t i = inst.target_first; i < inst.target_last; ++i)
		{ 
			if (added_addresses.insert(res.target_addresses[i]).second)
				address_stack.push_back(res.target_addresses[i]);
		}

		for (std::size_t i = inst.routine_first; i < inst.routine_last; ++i)
		{
			if (added_addresses.insert(res.routine_addresses[i]).second)
				address_stack.push_back(res.routine_addresses[i]);
		}
	}

	return res;
}


struct avr_core
{
	typedef boost::uint_fast32_t address_type;

	template <typename Program>
	static avr_instruction_entry_t const * get_one(Program const & program, address_type address)
	{
		if (program.size() <= address + 2)
			return 0;

		typedef boost::uint_least16_t char16_t;
		char16_t word = program[address];
		word |= char16_t(program[address+1]) << 8;

		return avr_find_instruction_entry(word);
	}

	template <typename Program, typename TargetIterator, typename RoutineIterator>
	static address_type targets(Program const & program, address_type address,
		TargetIterator target, RoutineIterator routine)
	{
		if (program.size() <= address + 2)
			return address;

		typedef boost::uint_least16_t char16_t;
		char16_t word = program[address];
		word |= char16_t(program[address+1]) << 8;

		avr_instruction_entry_t * entry = avr_find_instruction_entry(word);
		if (entry == 0)
			return address;

		switch (entry->op)
		{
		case avr_op_rjmp:
		case avr_op_rcall:
			{
				char16_t t = word & 0x07ff;
				address_type new_address = (word & 0x0800)? address + 2 - 2*(-t & 0x07ff): address + 2 + 2*t;

				if (entry->op == avr_op_rjmp)
					*target++ = new_address;
				else
				{
					*target++ = address + 2;
					*routine++ = new_address;
				}
			}
			break;

		case avr_op_jmp:
			if (program.size() < address + 4)
				return address;
			*target++ = 2*(program[address+2] | (program[address+3] << 8));
			break;

		case avr_op_call:
			if (program.size() < address + 4)
				return address;
			*target++ = address + 4;
			*routine++ = 2*(program[address+2] | (program[address+3] << 8));
			break;

		case avr_op_ijmp:
		case avr_op_eijmp:
		case avr_op_ret:
		case avr_op_reti:
			break;

		case avr_op_icall:
		case avr_op_eicall:
			*target++ = address + 2;
			break;

		case avr_op_brbs:
		case avr_op_brbc:
			{
				char16_t t = (word & 0x01f8) >> 3;
				address_type new_address = (word & 0x0200)? address + 2 - 2*(-t & 0x3f): address + 2 + 2*t;
				*target++ = address + 2;
				*target++ = new_address;
			}
			break;

		case avr_op_sbrc:
		case avr_op_sbrs:
		case avr_op_sbic:
		case avr_op_sbis:
		case avr_op_cpse:
			{
				if (program.size() < address + 4)
					return address;
				word = program[address+2] | (program[address+3] << 8);
				avr_instruction_entry_t * new_entry = avr_find_instruction_entry(word);
				if (new_entry == 0)
					return address;

				*target++ = address + 2*entry->length;
				*target++ = address + 2*entry->length + 2*new_entry->length;
			}
			break;

		default:
			*target++ = address + 2*entry->length;
			break;
		}

		return address + 2*entry->length;
	}
};

int main()
{
	std::ifstream fin("receiver.bin", std::ios::in | std::ios::binary);

	typedef boost::uint_least8_t char8_t;
	std::vector<char8_t> data((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());

	flow_graph<avr_core::address_type> g = make_flow_graph(data, avr_core::address_type(0), avr_core());
	
	std::map<avr_core::address_type, int> routine_stack_usage;
	std::vector<avr_core::address_type> routine_stack;
	std::set<avr_core::address_type> processed_routines;

	routine_stack.push_back(0);
	processed_routines.insert(0);

	while (!routine_stack.empty())
	{
		avr_core::address_type routine_address = routine_stack.back();
		routine_stack.pop_back();

		std::map<avr_core::address_type, int> stack_sizes;
		stack_sizes[routine_address] = 0;

		std::vector<avr_core::address_type> s;
		s.push_back(routine_address);

		int routine_max = 0;

		while (!s.empty())
		{
			avr_core::address_type addr = s.back();
			s.pop_back();

			int stack_size = stack_sizes[addr];

			instruction<avr_core::address_type> const & intr = g.instr_graph[addr];

			avr_instruction_entry_t const * entries = avr_core::get_one(data, addr);

			switch (entries->op)
			{
			case avr_op_push:
				++stack_size;
				break;
			case avr_op_pop:
				if (stack_size < 0)
					std::cout << "Stack underflow: " << std::hex << addr << std::endl;
				--stack_size;
				break;
			}

			if (intr.target_first == intr.target_last && stack_size != 0)
				std::cout << "Unfreed stack in leaf: " << std::hex << addr << std::endl;

			for (std::size_t i = intr.target_first; i < intr.target_last; ++i)
			{
				std::map<avr_core::address_type, int>::const_iterator
					ci = stack_sizes.find(g.target_addresses[i]);
				if (ci == stack_sizes.end())
				{
					std::size_t nn = g.target_addresses[i];
					nn = 0;

					stack_sizes[g.target_addresses[i]] = stack_size;
					s.push_back(g.target_addresses[i]);
					routine_max = (std::max)(routine_max, stack_size);
				}
				else if (ci->second != stack_size)
					std::cerr << "stack size mismatch at " << addr << std::endl;
			}

			for (std::size_t i = intr.routine_first; i < intr.routine_last; ++i)
			{
				if (processed_routines.find(g.routine_addresses[i]) == processed_routines.end())
				{
					processed_routines.insert(g.routine_addresses[i]);
					routine_stack.push_back(g.routine_addresses[i]);
				}
			}
		}

		routine_stack_usage[routine_address] = routine_max;
	}
}
