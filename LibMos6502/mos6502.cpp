#include "mos6502.h"

namespace LibMos6502
{
	Mos6502::Mos6502(std::shared_ptr<Memory> memory) :
		m_memory(memory),
		m_pc(pcDefault), m_sp(spDefault), m_acc(accDefault), m_x(xDefault), m_y(yDefault), m_status(statusDefault),
		m_cycles(0),
		m_addrMode(AddrMd::Abs), m_pageCrossed(false)
	{

	}

	void Mos6502::reset()
	{
		m_sp = spDefault;
		m_acc = accDefault;
		m_x = xDefault;
		m_y = yDefault;
		m_status = statusDefault;
		m_pc = read16(resetVector);
		m_cycles = 0;
	}

	void Mos6502::step()
	{
		const uint8_t opCode = read8(m_pc);
		m_addrMode = m_addrModes[opCode];
		(this->*m_instructions[opCode])();
		++m_pc;
	}

	uint8_t Mos6502::read8(uint16_t addr)
	{
		++m_cycles;
		return m_memory->read(addr);
	}

	uint16_t Mos6502::read16(uint16_t addr)
	{
		return (read8(addr + 1) << 8) | read8(addr);
	}

	void Mos6502::write8(uint16_t addr, uint8_t data)
	{
		++m_cycles;
		m_memory->read(addr);
	}

	void Mos6502::push8(uint8_t data)
	{
		write8(stackOffset + m_sp--, data);
	}

	void Mos6502::push16(uint16_t data)
	{
		write8(stackOffset + m_sp--, data >> 8);
		write8(stackOffset + m_sp--, data & 0xFF);
	}

	uint16_t Mos6502::readAddress()
	{
		uint16_t addr = 0;

		switch (m_addrMode)
		{
		case AddrMd::Rel:
		case AddrMd::Imm:
			addr = m_pc + 1;
			break;

		case AddrMd::ZoP:
			addr = read8(m_pc + 1);
			break;

		case AddrMd::ZpX:
			addr = (read8(m_pc + 1) + m_x) & 0xFF;
			break;

		case AddrMd::ZpY:
			addr = (read8(m_pc + 1) + m_y) & 0xFF;
			break;

		case AddrMd::Abs:
			addr = read16(m_pc + 1);
			break;

		case AddrMd::AbX:
			addr = read16(m_pc + 1);
			if ((((addr & 0xFF) + m_x) & 0xFF00) != 0)
			{
				m_pageCrossed = true;
			}
			addr += m_x;
			break;

		case AddrMd::AbY:
			addr = read16(m_pc + 1);
			if ((((addr & 0xFF) + m_y) & 0xFF00) != 0)
			{
				m_pageCrossed = true;
			}
			addr += m_y;
			break;

		case AddrMd::Pre:
			addr = (read8(m_pc + 1) + m_x) & 0xFF;
			addr = (read8((addr + 1) & 0xFF) << 8) | read8(addr);
			break;

		case AddrMd::Pos:
			addr = read8(m_pc + 1);
			addr = (read8((addr + 1) & 0xFF) << 8) | read8(addr);
			if ((((addr & 0xFF) + m_y) & 0xFF00) != 0)
			{
				m_pageCrossed = true;
			}
			addr += m_y;
			break;

		case AddrMd::Ind:
			addr = read16(m_pc + 1);
			// 6502 fetches incorrectly if address is at page boundary
			if ((addr & 0xFF) == 0xFF)
			{
				addr = (read8(addr & 0xFF00) << 8) | read8(addr);
			}
			else
			{
				addr = read16(addr);
			}
			break;

		default:
			addr = 0;
			break;
		}

		return addr;
	}

	void Mos6502::setNZ(uint8_t src)
	{
		m_status[StatusBits::Zero] = src == 0;
		m_status[StatusBits::Negative] = src & 0x80;
	}

	void Mos6502::compare(uint8_t reg)
	{
		const uint8_t src = read8(readAddress());
		m_status[StatusBits::Carry] = reg >= src;
		setNZ(reg - src);
	}

	uint8_t Mos6502::decrement(uint8_t src)
	{
		uint8_t result = --src;
		setNZ(result);
		return result;
	}

	uint8_t Mos6502::increment(uint8_t src)
	{
		uint8_t result = ++src;
		setNZ(result);
		return result;
	}

	void Mos6502::ADC()
	{
		const uint8_t accOld = m_acc;
		const uint8_t src = read8(readAddress());
		const uint16_t sum = m_acc + src + m_status[StatusBits::Carry];
		m_acc = sum & 0xFF;

		m_status[StatusBits::Carry] = sum >= 0x100;
		setNZ(m_acc);
		m_status[StatusBits::Overflow] =	// Overflow occured if:
			(!((accOld ^ src) & 0x80) &&	// Both numbers had the same sign before AND
				((accOld ^ sum) & 0x80));	// result has a different sign
	}

	void Mos6502::AND()
	{
		m_acc &= read8(readAddress());
		setNZ(m_acc);
	}

	void Mos6502::ASL()
	{
		if (m_addrMode == AddrMd::Acc)
		{
			m_status[StatusBits::Carry] = m_acc & 0x80;
			m_acc <<= 1;
			setNZ(m_acc);
		}
		else
		{
			const uint16_t addr = readAddress();
			uint8_t src = read8(addr);
			m_status[StatusBits::Carry] = src & 0x80;
			write8(addr, src <<= 1);
			setNZ(src);
		}
	}

	void Mos6502::BIT()
	{
		const uint8_t src = read8(readAddress());
		m_status[StatusBits::Negative] = src & 0x80;
		m_status[StatusBits::Overflow] = src & 0x40;
		m_status[StatusBits::Zero] = (src & m_acc) == 0;
	}

	void Mos6502::BRK()
	{
		push16(m_pc + 2);
		push8(static_cast<uint8_t>(m_status.to_ulong()));
		m_status[StatusBits::Interrupt] = true;
		m_pc = read16(irqVector);
	}

	void Mos6502::CMP()
	{
		compare(m_acc);
	}

	void Mos6502::CPX()
	{
		compare(m_x);
	}

	void Mos6502::CPY()
	{
		compare(m_y);
	}

	void Mos6502::DEC()
	{
		const uint16_t addr = readAddress();
		write8(addr, decrement(read8(addr)));
	}

	void Mos6502::DEX()
	{
		m_x = decrement(m_x);
	}

	void Mos6502::DEY()
	{
		m_y = decrement(m_y);
	}

	void Mos6502::EOR()
	{
		m_acc ^= read8(readAddress());
		setNZ(m_acc);
	}

	void Mos6502::INC()
	{
		const uint16_t addr = readAddress();
		write8(addr, increment(read8(addr)));
	}
	
	void Mos6502::INX()
	{
		m_x = increment(m_x);
	}

	void Mos6502::INY()
	{
		m_y = increment(m_y);
	}
	
	void Mos6502::JMP()
	{
		m_pc = read16(readAddress());
	}

	void Mos6502::JSR()
	{
		push16(m_pc);
		m_pc = read16(readAddress());
	}

	void Mos6502::LSR(){}
	void Mos6502::NOP(){}
	void Mos6502::ORA(){}
	void Mos6502::ROL(){}
	void Mos6502::ROR(){}
	void Mos6502::RTI(){}
	void Mos6502::RTS(){}
	void Mos6502::SBC(){}

	void Mos6502::TAX(){}
	void Mos6502::TAY(){}
	void Mos6502::TSX(){}
	void Mos6502::TXA(){}
	void Mos6502::TXS(){}
	void Mos6502::TYA(){}

	void Mos6502::STA(){}
	void Mos6502::STX(){}
	void Mos6502::STY(){}

	void Mos6502::SEC(){}
	void Mos6502::SED(){}
	void Mos6502::SEI(){}

	void Mos6502::BCC(){}
	void Mos6502::BCS(){}
	void Mos6502::BEQ(){}
	void Mos6502::BMI(){}
	void Mos6502::BNE(){}
	void Mos6502::BPL(){}
	void Mos6502::BVC(){}
	void Mos6502::BVS(){}

	void Mos6502::CLC(){}
	void Mos6502::CLD(){}
	void Mos6502::CLI(){}
	void Mos6502::CLV(){}

	void Mos6502::LDA(){}
	void Mos6502::LDX(){}
	void Mos6502::LDY(){}

	void Mos6502::PHA(){}
	void Mos6502::PHP(){}
	void Mos6502::PLA(){}
	void Mos6502::PLP(){}

	void Mos6502::ILL(){}
}