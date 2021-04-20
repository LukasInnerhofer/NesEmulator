#ifndef CPU_H
#define CPU_H

#include <array>
#include <functional>
#include <bitset>
#include <map>
#include <memory>
#include <vector>

#include "memory.h"

namespace LibMos6502
{
	class Mos6502
	{
	public:
		Mos6502(std::shared_ptr<Memory> memory);

		void reset();
		void step();

	private:
		std::shared_ptr<Memory> m_memory;

		uint16_t m_pc;
		uint8_t m_sp;
		uint8_t m_acc;
		uint8_t m_x, m_y;

		std::bitset<8> m_status;
		class StatusBits
		{
		public:
			static constexpr size_t Carry = 0, Zero = 1, Interrupt = 3, Decimal = 4, Overflow = 6, Negative = 7;
		};

		uint8_t m_cycles;

		static constexpr uint16_t pcDefault = 0;
		static constexpr uint8_t spDefault = 0xFD;
		static constexpr uint8_t accDefault = 0;
		static constexpr uint8_t xDefault = 0;
		static constexpr uint8_t yDefault = 0;
		static constexpr uint8_t statusDefault = 0x34;
		static constexpr uint16_t stackOffset = 0x100;

		static constexpr uint16_t nmiVector = 0xFFFA;
		static constexpr uint16_t resetVector = 0xFFFC;
		static constexpr uint16_t irqVector = 0xFFFE;

		uint8_t read8(uint16_t addr);
		uint16_t read16(uint16_t addr);
		void write8(uint16_t addr, uint8_t data);

		void push8(uint8_t data);
		void push16(uint16_t data);
		uint8_t pull8();
		uint16_t pull16();

		uint16_t readAddress();

		void setNZ(uint8_t src);

		void ADC();
		void SBC();
		void AND();
		void ASL();
		void BIT();
		void BRK();

		void compare(uint8_t reg);
		void CMP();
		void CPX();
		void CPY();
		
		void EOR();

		uint8_t decrement(uint8_t src);
		uint8_t increment(uint8_t src);
		void DEC();
		void DEX();
		void DEY();
		void INC();
		void INX();
		void INY();

		void JMP();
		void JSR();
		void LSR();
		void NOP();
		void ORA();
		void ROL();
		void ROR();
		void RTI();
		void RTS();

		void TAX();
		void TAY();
		void TSX();
		void TXA();
		void TXS();
		void TYA();

		void STA();
		void STX();
		void STY();

		void SEC();
		void SED();
		void SEI();

		void branch(bool condition);
		void BCC();
		void BCS();
		void BEQ();
		void BMI();
		void BNE();
		void BPL();
		void BVC();
		void BVS();

		void CLC();
		void CLD();
		void CLI();
		void CLV();

		void LDA();
		void LDX();
		void LDY();

		void PHA();
		void PHP();
		void PLA();
		void PLP();

		void ILL();

		enum class AddressMode { Acc, Imp, Rel, Imm, ZoP, ZpX, ZpY, Abs, AbX, AbY, Pre, Pos, Ill, Ind };

		const std::map<AddressMode, uint8_t> m_argCnts =
		{
			{ AddressMode::Acc, 0 },
			{ AddressMode::Imp, 0 },
			{ AddressMode::Rel, 1 },
			{ AddressMode::Imm, 1 },
			{ AddressMode::ZoP, 1 },
			{ AddressMode::ZpX, 1 },
			{ AddressMode::ZpY, 1 },
			{ AddressMode::Abs, 2 },
			{ AddressMode::AbX, 2 },
			{ AddressMode::AbY, 2 },
			{ AddressMode::Pre, 1 },
			{ AddressMode::Pos, 1 },
			{ AddressMode::Ill, 0 },
			{ AddressMode::Ind, 2 }
		};

		AddressMode m_addrMode;

		typedef struct
		{
			void(Mos6502::* m_instruction)();
			AddressMode m_addressMode;
		} Instruction;

#define I(instruction, addressMode) { &Mos6502::##instruction, AddressMode::##addressMode }
		std::vector<Instruction> m_instructions
		{
			I(ILL, Ill), // 0x00
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0x10
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0x20
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0x30
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0x40
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0x50
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0x60
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0x70
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0x80
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(STA, ZoP),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0x90
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0xA0
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(LDA, Imm),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0xB0
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0xC0
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0xD0
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0xE0
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),

			I(ILL, Ill), // 0xF0
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
			I(ILL, Ill),
		};

		/*const std::vector<uint8_t> m_pcIncs
		{
			2, 2, 0, 0, 0, 2, 2, 0, 1, 2, 1, 0, 0, 3, 3, 0,
			2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
			0, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
			2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
			0, 2, 0, 0, 0, 2, 2, 0, 1, 2, 1, 0, 0, 3, 3, 0,
			2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
			1, 2, 0, 0, 0, 2, 2, 0, 1, 2, 1, 0, 0, 3, 3, 0,
			2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
			0, 2, 0, 0, 2, 2, 2, 0, 1, 0, 1, 0, 3, 3, 3, 0,
			2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 0, 3, 0, 0,
			2, 2, 2, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
			2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
			2, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
			2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
			2, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
			2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0
		};

		const std::vector<uint8_t> m_cycles
		{
			7, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 0, 4, 6, 0,
			2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
			6, 6, 0, 0, 3, 3, 5, 0, 4, 2, 2, 0, 4, 4, 6, 0,
			2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
			6, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 3, 4, 6, 0,
			2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
			6, 6, 0, 0, 0, 3, 5, 0, 4, 2, 2, 0, 5, 4, 6, 0,
			2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
			0, 6, 0, 0, 3, 3, 3, 0, 2, 0, 2, 0, 4, 4, 4, 0,
			2, 6, 0, 0, 4, 4, 4, 0, 2, 5, 2, 0, 0, 5, 0, 0,
			2, 6, 2, 0, 3, 3, 3, 0, 2, 2, 2, 0, 4, 4, 4, 0,
			2, 5, 0, 0, 4, 4, 4, 0, 2, 4, 2, 0, 4, 4, 4, 0,
			2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 0, 4, 4, 6, 0,
			2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
			2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 0, 4, 4, 6, 0,
			2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0
		};*/

		bool m_pageCrossed;
		const std::vector<bool> m_addOnPageCross
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0
		};
	};
}

#endif // CPU_H