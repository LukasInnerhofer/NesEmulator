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

	void Mos6502::ADC()
	{
		const uint8_t accOld = m_acc;
		const uint8_t src = read8(readAddress());

		const uint16_t sum = m_acc + src + m_status[StatusBits::Carry];
		m_acc = sum & 0xFF;

		m_status[StatusBits::Carry] = sum >= 0x100;
		m_status[StatusBits::Zero] = m_acc == 0;
		m_status[StatusBits::Negative] = m_acc & 0x80;
		m_status[StatusBits::Overflow] =	// Overflow occured if:
			(!((accOld ^ src) & 0x80) &&	// Both numbers had the same sign before AND
				((accOld ^ sum) & 0x80));		// result has a different sign
	}

	void Mos6502::AND()
	{
		m_acc &= read8(readAddress());

		m_status[StatusBits::Zero] = m_acc == 0;
		m_status[StatusBits::Negative] = m_acc & 0x80;
	}

	void Mos6502::ASL()
	{
		const uint16_t addr = readAddress();
		uint8_t src = (m_addrMode == AddrMd::Acc) ? m_acc : read8(addr);

		m_status[StatusBits::Carry] = src & 0x80;

		if (m_addrMode == AddrMd::Acc)
		{
			src = (m_acc <<= 1);
		}
		else
		{
			write8(addr, src <<= 1);
		}

		m_status[StatusBits::Zero] = src == 0;
		m_status[StatusBits::Negative] = src & 0x80;
	}

	void Mos6502::BIT()
	{
		const uint8_t src = read8(readAddress());
	}

	void Mos6502::BRK()
	{

	}

	void Mos6502::CMP()
	{

	}

	void Mos6502::CPX()
	{

	}

	void Mos6502::CPY()
	{

	}

	void Mos6502::step()
	{

	}
}