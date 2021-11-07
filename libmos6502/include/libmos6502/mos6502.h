#ifndef MOS6502_H
#define MOS6502_H

#include <array>
#include <chrono>
#include <bitset>
#include <functional>
#include <map>
#include <memory>
#include <vector>

#if defined(LIBMOS6502_LOG)
#include <fstream>
#endif

#include "libmos6502/memory.h"
#include "libutilities/non_null.h"

namespace LibMos6502
{

class Mos6502
{
public:
	Mos6502(NonNullSharedPtr<Memory> memory);

	void reset();
	void step(
#if defined(LIBMOS6502_LOG)
		std::ofstream& log
#endif
	);

	uint8_t getCycles();

private:
	NonNullSharedPtr<Memory> m_memory;

	uint16_t m_pc;
	uint8_t m_sp;
	uint8_t m_acc;
	uint8_t m_x, m_y;

	std::bitset<8> m_status;
	struct StatusBits
	{
		static constexpr size_t 
			Carry { 0 }, 
			Zero { 1 }, 
			Interrupt { 2 }, 
			Decimal { 3 }, 
			Overflow { 6 }, 
			Negative { 7 };

		StatusBits() = delete;
	};

	uint8_t m_cycles;
	uint16_t m_newPc;

	static constexpr uint16_t pcDefault{0};
	static constexpr uint8_t spDefault{0xFD};
	static constexpr uint8_t accDefault{0};
	static constexpr uint8_t xDefault{0};
	static constexpr uint8_t yDefault{0};
	static constexpr uint8_t statusDefault{0x24};
	static constexpr uint16_t stackOffset{0x100};

	static constexpr uint16_t nmiVector{0xFFFA};
	static constexpr uint16_t resetVector{0xFFFC};
	static constexpr uint16_t irqVector{0xFFFE};

	uint8_t read8(uint16_t addr);
	uint16_t read16(uint16_t addr);
	uint16_t readPage16(uint16_t addr);
	void write8(uint16_t addr, uint8_t data);

	uint8_t readArg8(uint16_t addr);
	uint16_t readArg16(uint16_t addr);

	void push8(uint8_t data);
	void push16(uint16_t data);
	uint8_t pull8();
	uint16_t pull16();
	void pullStatus();

	uint16_t readAddress(bool assumePageCross);

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

	AddressMode m_addrMode;

	typedef struct
	{
		void(Mos6502::* m_instruction)();
		AddressMode m_addressMode;
#if defined(LIBMOS6502_LOG)
		std::string m_name;
#endif
	} Instruction;

#if defined(LIBMOS6502_LOG)
#define I(instruction, addressMode) { &Mos6502::instruction, AddressMode::addressMode, #instruction }
#else
#define I(instruction, addressMode) { &Mos6502::instruction, AddressMode::addressMode }
#endif // defined(LIBMOS6502_LOG)
	std::vector<Instruction> m_instructions
	{
		I(ILL, Ill), // 0x00
		I(ORA, Pre),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ORA, ZoP),
		I(ASL, ZoP),
		I(ILL, Ill),
		I(PHP, Imp),
		I(ORA, Imm),
		I(ASL, Acc),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ORA, Abs),
		I(ASL, Abs),
		I(ILL, Ill),

		I(BPL, Rel), // 0x10
		I(ORA, Pos),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ORA, ZpX),
		I(ASL, ZpX),
		I(ILL, Ill),
		I(CLC, Imp),
		I(ORA, AbY),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ORA, AbX),
		I(ASL, AbX),
		I(ILL, Ill),

		I(JSR, Abs), // 0x20
		I(AND, Pre),
		I(ILL, Ill),
		I(ILL, Ill),
		I(BIT, ZoP),
		I(AND, ZoP), 
		I(ROL, ZoP), 
		I(ILL, Ill), 
		I(PLP, Imp), 
		I(AND, Imm), 
		I(ROL, Acc), 
		I(ILL, Ill), 
		I(BIT, Abs),
		I(AND, Abs),
		I(ROL, Abs),
		I(ILL, Ill),

		I(BMI, Rel), // 0x30
		I(AND, Pos),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(AND, ZpX),
		I(ROL, ZpX),
		I(ILL, Ill),
		I(SEC, Imp),
		I(AND, AbY),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(AND, AbX),
		I(ROL, AbX),
		I(ILL, Ill),

		I(RTI, Imp), // 0x40
		I(EOR, Pre),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(EOR, ZoP),
		I(LSR, ZoP),
		I(ILL, Ill),
		I(PHA, Imp),
		I(EOR, Imm),
		I(LSR, Acc),
		I(ILL, Ill),
		I(JMP, Abs),
		I(EOR, Abs),
		I(LSR, Abs),
		I(ILL, Ill),

		I(BVC, Rel), // 0x50
		I(EOR, Pos),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(EOR, ZpX),
		I(LSR, ZpX),
		I(ILL, Ill),
		I(ILL, Ill),
		I(EOR, AbY),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(EOR, AbX),
		I(LSR, AbX),
		I(ILL, Ill),

		I(RTS, Imp), // 0x60
		I(ADC, Pre),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ADC, ZoP),
		I(ROR, ZoP),
		I(ILL, Ill),
		I(PLA, Imp),
		I(ADC, Imm),
		I(ROR, Acc),
		I(ILL, Ill),
		I(JMP, Ind),
		I(ADC, Abs),
		I(ROR, Abs),
		I(ILL, Ill),

		I(BVS, Rel), // 0x70
		I(ADC, Pos),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ADC, ZpX),
		I(ROR, ZpX),
		I(ILL, Ill),
		I(SEI, Imp),
		I(ADC, AbY),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ADC, AbX),
		I(ROR, AbX),
		I(ILL, Ill),

		I(ILL, Ill), // 0x80
		I(STA, Pre),
		I(ILL, Ill),
		I(ILL, Ill),
		I(STY, ZoP),
		I(STA, ZoP),
		I(STX, ZoP),
		I(ILL, Ill),
		I(DEY, Imp),
		I(ILL, Ill),
		I(TXA, Imp),
		I(ILL, Ill),
		I(STY, Abs),
		I(STA, Abs),
		I(STX, Abs),
		I(ILL, Ill),

		I(BCC, Rel), // 0x90
		I(STA, Pos),
		I(ILL, Ill),
		I(ILL, Ill),
		I(STY, ZpX),
		I(STA, ZpX),
		I(STX, ZpY),
		I(ILL, Ill),
		I(TYA, Imp),
		I(STA, AbY),
		I(TXS, Imp),
		I(ILL, Ill),
		I(ILL, Ill),
		I(STA, AbX),
		I(ILL, Ill),
		I(ILL, Ill),

		I(LDY, Imm), // 0xA0
		I(LDA, Pre),
		I(LDX, Imm),
		I(ILL, Ill),
		I(LDY, ZoP),
		I(LDA, ZoP),
		I(LDX, ZoP),
		I(ILL, Ill),
		I(TAY, Imp),
		I(LDA, Imm),
		I(TAX, Imp),
		I(ILL, Ill),
		I(LDY, Abs),
		I(LDA, Abs),
		I(LDX, Abs),
		I(ILL, Ill),

		I(BCS, Rel), // 0xB0
		I(LDA, Pos),
		I(ILL, Ill),
		I(ILL, Ill),
		I(LDY, ZpX),
		I(LDA, ZpX),
		I(LDX, ZpY),
		I(ILL, Ill),
		I(CLV, Imp),
		I(LDA, AbY),
		I(TSX, Imp),
		I(ILL, Ill),
		I(LDY, AbX),
		I(LDA, AbX),
		I(LDX, AbY),
		I(ILL, Ill),

		I(CPY, Imm), // 0xC0
		I(CMP, Pre),
		I(ILL, Ill),
		I(ILL, Ill),
		I(CPY, ZoP),
		I(CMP, ZoP),
		I(DEC, ZoP),
		I(ILL, Ill),
		I(INY, Imp),
		I(CMP, Imm),
		I(DEX, Imp),
		I(ILL, Ill),
		I(CPY, Abs),
		I(CMP, Abs),
		I(DEC, Abs),
		I(ILL, Ill),

		I(BNE, Rel), // 0xD0
		I(CMP, Pos),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(CMP, ZpX),
		I(DEC, ZpX),
		I(ILL, Ill),
		I(CLD, Imp),
		I(CMP, AbY),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(CMP, AbX),
		I(DEC, AbX),
		I(ILL, Ill),

		I(CPX, Imm), // 0xE0
		I(SBC, Pre),
		I(ILL, Ill),
		I(ILL, Ill),
		I(CPX, ZoP),
		I(SBC, ZoP),
		I(INC, ZoP),
		I(ILL, Ill),
		I(INX, Imp),
		I(SBC, Imm),
		I(NOP, Imp),
		I(ILL, Ill),
		I(CPX, Abs),
		I(SBC, Abs),
		I(INC, Abs),
		I(ILL, Ill),

		I(BEQ, Rel), // 0xF0
		I(SBC, Pos),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(SBC, ZpX),
		I(INC, ZpX),
		I(ILL, Ill),
		I(SED, Imp),
		I(SBC, AbY),
		I(ILL, Ill),
		I(ILL, Ill),
		I(ILL, Ill),
		I(SBC, AbX),
		I(INC, AbX),
		I(ILL, Ill),
	};
};

}

#endif // MOS6502_H
