#ifndef CPU_H
#define CPU_H

#include <array>
#include <functional>
#include <bitset>
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

#define I(instr) &Mos6502::##instr
		// Associates opcodes with instructions
		const std::vector<void(Mos6502::*)()> m_instructions
		{
			I(BRK), I(ORA), I(ILL), I(ILL), I(ILL), I(ORA), I(ASL), I(ILL), I(PHP), I(ORA), I(ASL), I(ILL), I(ILL), I(ORA), I(ASL), I(ILL),
			I(BPL), I(ORA), I(ILL), I(ILL), I(ILL), I(ORA), I(ASL), I(ILL), I(CLC), I(ORA), I(ILL), I(ILL), I(ILL), I(ORA), I(ASL), I(ILL),
			I(JSR), I(AND), I(ILL), I(ILL), I(BIT), I(AND), I(ROL), I(ILL), I(PLP), I(AND), I(ROL), I(ILL), I(BIT), I(AND), I(ROL), I(ILL),
			I(BMI), I(AND), I(ILL), I(ILL), I(ILL), I(AND), I(ROL), I(ILL), I(SEC), I(AND), I(ILL), I(ILL), I(ILL), I(AND), I(ROL), I(ILL),
			I(RTI), I(EOR), I(ILL), I(ILL), I(ILL), I(EOR), I(LSR), I(ILL), I(PHA), I(EOR), I(LSR), I(ILL), I(JMP), I(EOR), I(LSR), I(ILL),
			I(BVC), I(EOR), I(ILL), I(ILL), I(ILL), I(EOR), I(LSR), I(ILL), I(CLI), I(EOR), I(ILL), I(ILL), I(ILL), I(EOR), I(LSR), I(ILL),
			I(RTS), I(ADC), I(ILL), I(ILL), I(ILL), I(ADC), I(ROR), I(ILL), I(PLA), I(ADC), I(ROR), I(ILL), I(JMP), I(ADC), I(ROR), I(ILL),
			I(BVS), I(ADC), I(ILL), I(ILL), I(ILL), I(ADC), I(ROR), I(ILL), I(SEI), I(ADC), I(ILL), I(ILL), I(ILL), I(ADC), I(ROR), I(ILL),
			I(ILL), I(STA), I(ILL), I(ILL), I(STY), I(STA), I(STX), I(ILL), I(DEY), I(ILL), I(TXA), I(ILL), I(STY), I(STA), I(STX), I(ILL),
			I(BCC), I(STA), I(ILL), I(ILL), I(STY), I(STA), I(STX), I(ILL), I(TYA), I(STA), I(TXS), I(ILL), I(ILL), I(STA), I(ILL), I(ILL),
			I(LDY), I(LDA), I(LDX), I(LDX), I(LDY), I(LDA), I(LDX), I(ILL), I(TAY), I(LDA), I(TAX), I(ILL), I(LDY), I(LDA), I(LDX), I(LDX),
			I(BCS), I(LDA), I(ILL), I(ILL), I(LDY), I(LDA), I(LDX), I(ILL), I(CLV), I(LDA), I(TSX), I(ILL), I(LDY), I(LDA), I(LDX), I(ILL),
			I(CPY), I(CMP), I(ILL), I(ILL), I(CPY), I(CMP), I(DEC), I(ILL), I(INY), I(CMP), I(DEX), I(ILL), I(CPY), I(CMP), I(DEC), I(ILL),
			I(BNE), I(CMP), I(ILL), I(ILL), I(ILL), I(CMP), I(DEC), I(ILL), I(CLD), I(CMP), I(ILL), I(ILL), I(ILL), I(CMP), I(DEC), I(ILL),
			I(CPX), I(SBC), I(ILL), I(ILL), I(CPX), I(SBC), I(INC), I(ILL), I(INX), I(SBC), I(NOP), I(ILL), I(CPX), I(SBC), I(INC), I(ILL),
			I(BEQ), I(SBC), I(ILL), I(ILL), I(ILL), I(SBC), I(INC), I(ILL), I(SED), I(SBC), I(ILL), I(ILL), I(ILL), I(SBC), I(INC), I(ILL)
		};

		enum class AddrMd { Acc, Imp, Rel, Imm, ZoP, ZpX, ZpY, Abs, AbX, AbY, Pre, Pos, Ill, Ind };
		AddrMd m_addrMode;
#define A(addrMode) AddrMd::##addrMode
		const std::vector<AddrMd> m_addrModes
		{
			A(Imp), A(Pre), A(Ill), A(Ill), A(Ill), A(ZoP), A(ZoP), A(Ill),
			A(Imp), A(Imm), A(Acc), A(Ill), A(Ill), A(Abs), A(Abs), A(Ill),
			A(Rel), A(Pos), A(Ill), A(Ill), A(Ill), A(ZpX), A(ZpX), A(Ill),
			A(Imp), A(AbY), A(Ill), A(Ill), A(Ill), A(AbX), A(AbX), A(Ill),
			A(Abs), A(Pre), A(Ill), A(Ill), A(ZoP), A(ZoP), A(ZoP), A(Ill),
			A(Imp), A(Imm), A(Acc), A(Ill), A(Abs), A(Abs), A(Abs), A(Ill),
			A(Rel), A(Pos), A(Ill), A(Ill), A(Ill), A(ZpX), A(ZpX), A(Ill),
			A(Imp), A(AbY), A(Ill), A(Ill), A(Ill), A(AbX), A(AbX), A(Ill),
			A(Imp), A(Pre), A(Ill), A(Ill), A(Ill), A(ZoP), A(ZoP), A(Ill),
			A(Imp), A(Imm), A(Acc), A(Ill), A(Abs), A(Abs), A(Abs), A(Ill),
			A(Rel), A(Pos), A(Ill), A(Ill), A(Ill), A(ZpX), A(ZpX), A(Ill),
			A(Imp), A(AbY), A(Ill), A(Ill), A(Ill), A(AbX), A(AbX), A(Ill),
			A(Imp), A(Pre), A(Ill), A(Ill), A(Ill), A(ZoP), A(ZoP), A(Ill),
			A(Imp), A(Imm), A(Acc), A(Ill), A(Ind), A(Abs), A(Abs), A(Ill),
			A(Rel), A(Pos), A(Ill), A(Ill), A(Ill), A(ZpX), A(ZpX), A(Ill),
			A(Imp), A(AbY), A(Ill), A(Ill), A(Ill), A(AbX), A(AbX), A(Ill),
			A(Ill), A(Pre), A(Ill), A(Ill), A(ZoP), A(ZoP), A(ZoP), A(Ill),
			A(Imp), A(Ill), A(Imp), A(Ill), A(Abs), A(Abs), A(Abs), A(Ill),
			A(Rel), A(Pos), A(Ill), A(Ill), A(ZpX), A(ZpX), A(ZpY), A(Ill),
			A(Imp), A(AbY), A(Imp), A(Ill), A(Ill), A(AbX), A(Ill), A(Ill),
			A(Imm), A(Pre), A(Imm), A(Ill), A(ZoP), A(ZoP), A(ZoP), A(Ill),
			A(Imp), A(Imm), A(Imp), A(Ill), A(Abs), A(Abs), A(Abs), A(Imm),
			A(Rel), A(Pos), A(Ill), A(Ill), A(ZpX), A(ZpX), A(ZpY), A(Ill),
			A(Imp), A(AbY), A(Imp), A(Ill), A(AbX), A(AbX), A(AbY), A(Ill),
			A(Imm), A(Pre), A(Ill), A(Ill), A(ZoP), A(ZoP), A(ZoP), A(Ill),
			A(Imp), A(Imm), A(Imp), A(Ill), A(Abs), A(Abs), A(Abs), A(Ill),
			A(Rel), A(Pos), A(Ill), A(Ill), A(Ill), A(ZpX), A(ZpX), A(Ill),
			A(Imp), A(AbY), A(Ill), A(Ill), A(Ill), A(AbX), A(AbX), A(Ill),
			A(Imm), A(Pre), A(Ill), A(Ill), A(ZoP), A(ZoP), A(ZoP), A(Ill),
			A(Imp), A(Imm), A(Imp), A(Ill), A(Abs), A(Abs), A(Abs), A(Ill),
			A(Rel), A(Pos), A(Ill), A(Ill), A(Ill), A(ZpX), A(ZpX), A(Ill),
			A(Imp), A(AbY), A(Ill), A(Ill), A(Ill), A(AbX), A(AbX), A(Ill)
		};

		const std::vector<uint8_t> m_pcIncs
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

		/*const std::vector<uint8_t> m_cycles
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