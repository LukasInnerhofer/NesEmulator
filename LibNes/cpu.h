#ifndef CPU_H
#define CPU_H

#include <array>
#include <functional>
#include <bitset>
#include <memory>
#include <vector>

#include "mapper.h"
#include "ppu.h"

class Nes;

class Cpu
{
public:
	Cpu(const std::shared_ptr<Mapper>& mapper, const std::shared_ptr<Ppu>& ppu);

	void reset();
	void step();

private:
	std::shared_ptr<Mapper> m_mapper;
	std::shared_ptr<Ppu> m_ppu;

	// 2 kByte RAM
	std::vector<uint8_t> m_ram;
	static constexpr size_t ramSize = 0x800;

	uint16_t m_pc;
	uint8_t m_sp;
	uint8_t m_acc;
	uint8_t m_x, m_y;

	std::bitset<8> m_status;
	static class StatusBits
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

	static constexpr uint16_t nmiVector =	0xFFFA;
	static constexpr uint16_t resetVector = 0xFFFC;
	static constexpr uint16_t irqVector =	0xFFFE;

	uint8_t read8 (const uint16_t& addr);
	uint16_t read16(const uint16_t& addr);
	void write8(const uint16_t& addr, const uint8_t& data);

	uint16_t readAddress();

	void ADC();
	void AND();
	void ASL();
	void BIT();
	void BRK();
	void CMP();
	void CPX();
	void CPY();
	void DEC();
	void DEX();
	void DEY();
	void EOR();
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
	void SBC();

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

	// Associates opcodes with instructions
	const std::vector<void(Cpu::*)()> m_instructions
	{
		&Cpu::BRK, &Cpu::ORA, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::ORA, &Cpu::ASL, &Cpu::ILL, &Cpu::PHP, &Cpu::ORA, &Cpu::ASL, &Cpu::ILL, &Cpu::ILL, &Cpu::ORA, &Cpu::ASL, &Cpu::ILL,
		&Cpu::BPL, &Cpu::ORA, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::ORA, &Cpu::ASL, &Cpu::ILL, &Cpu::CLC, &Cpu::ORA, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::ORA, &Cpu::ASL, &Cpu::ILL,
		&Cpu::JSR, &Cpu::AND, &Cpu::ILL, &Cpu::ILL, &Cpu::BIT, &Cpu::AND, &Cpu::ROL, &Cpu::ILL, &Cpu::PLP, &Cpu::AND, &Cpu::ROL, &Cpu::ILL, &Cpu::BIT, &Cpu::AND, &Cpu::ROL, &Cpu::ILL,
		&Cpu::BMI, &Cpu::AND, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::AND, &Cpu::ROL, &Cpu::ILL, &Cpu::SEC, &Cpu::AND, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::AND, &Cpu::ROL, &Cpu::ILL,
		&Cpu::RTI, &Cpu::EOR, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::EOR, &Cpu::LSR, &Cpu::ILL, &Cpu::PHA, &Cpu::EOR, &Cpu::LSR, &Cpu::ILL, &Cpu::JMP, &Cpu::EOR, &Cpu::LSR, &Cpu::ILL,
		&Cpu::BVC, &Cpu::EOR, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::EOR, &Cpu::LSR, &Cpu::ILL, &Cpu::CLI, &Cpu::EOR, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::EOR, &Cpu::LSR, &Cpu::ILL,
		&Cpu::RTS, &Cpu::ADC, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::ADC, &Cpu::ROR, &Cpu::ILL, &Cpu::PLA, &Cpu::ADC, &Cpu::ROR, &Cpu::ILL, &Cpu::JMP, &Cpu::ADC, &Cpu::ROR, &Cpu::ILL,
		&Cpu::BVS, &Cpu::ADC, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::ADC, &Cpu::ROR, &Cpu::ILL, &Cpu::SEI, &Cpu::ADC, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::ADC, &Cpu::ROR, &Cpu::ILL,
		&Cpu::ILL, &Cpu::STA, &Cpu::ILL, &Cpu::ILL, &Cpu::STY, &Cpu::STA, &Cpu::STX, &Cpu::ILL, &Cpu::DEY, &Cpu::ILL, &Cpu::TXA, &Cpu::ILL, &Cpu::STY, &Cpu::STA, &Cpu::STX, &Cpu::ILL,
		&Cpu::BCC, &Cpu::STA, &Cpu::ILL, &Cpu::ILL, &Cpu::STY, &Cpu::STA, &Cpu::STX, &Cpu::ILL, &Cpu::TYA, &Cpu::STA, &Cpu::TXS, &Cpu::ILL, &Cpu::ILL, &Cpu::STA, &Cpu::ILL, &Cpu::ILL,
		&Cpu::LDY, &Cpu::LDA, &Cpu::LDX, &Cpu::LDX, &Cpu::LDY, &Cpu::LDA, &Cpu::LDX, &Cpu::ILL, &Cpu::TAY, &Cpu::LDA, &Cpu::TAX, &Cpu::ILL, &Cpu::LDY, &Cpu::LDA, &Cpu::LDX, &Cpu::LDX,
		&Cpu::BCS, &Cpu::LDA, &Cpu::ILL, &Cpu::ILL, &Cpu::LDY, &Cpu::LDA, &Cpu::LDX, &Cpu::ILL, &Cpu::CLV, &Cpu::LDA, &Cpu::TSX, &Cpu::ILL, &Cpu::LDY, &Cpu::LDA, &Cpu::LDX, &Cpu::ILL,
		&Cpu::CPY, &Cpu::CMP, &Cpu::ILL, &Cpu::ILL, &Cpu::CPY, &Cpu::CMP, &Cpu::DEC, &Cpu::ILL, &Cpu::INY, &Cpu::CMP, &Cpu::DEX, &Cpu::ILL, &Cpu::CPY, &Cpu::CMP, &Cpu::DEC, &Cpu::ILL,
		&Cpu::BNE, &Cpu::CMP, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::CMP, &Cpu::DEC, &Cpu::ILL, &Cpu::CLD, &Cpu::CMP, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::CMP, &Cpu::DEC, &Cpu::ILL,
		&Cpu::CPX, &Cpu::SBC, &Cpu::ILL, &Cpu::ILL, &Cpu::CPX, &Cpu::SBC, &Cpu::INC, &Cpu::ILL, &Cpu::INX, &Cpu::SBC, &Cpu::NOP, &Cpu::ILL, &Cpu::CPX, &Cpu::SBC, &Cpu::INC, &Cpu::ILL,
		&Cpu::BEQ, &Cpu::SBC, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::SBC, &Cpu::INC, &Cpu::ILL, &Cpu::SED, &Cpu::SBC, &Cpu::ILL, &Cpu::ILL, &Cpu::ILL, &Cpu::SBC, &Cpu::INC, &Cpu::ILL 
	};

	enum class AddrMd { Acc, Imp, Rel, Imm, ZoP, ZpX, ZpY, Abs, AbX, AbY, Pre, Pos, Ill, Ind };
	AddrMd m_addrMode;
	const std::vector<AddrMd> m_addrModes
	{
		AddrMd::Imp, AddrMd::Pre, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::ZoP, AddrMd::ZoP, AddrMd::Ill,	
		AddrMd::Imp, AddrMd::Imm, AddrMd::Acc, AddrMd::Ill, AddrMd::Ill, AddrMd::Abs, AddrMd::Abs, AddrMd::Ill,
		AddrMd::Rel, AddrMd::Pos, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::ZpX, AddrMd::ZpX, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::AbY, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::AbX, AddrMd::AbX, AddrMd::Ill,
		AddrMd::Abs, AddrMd::Pre, AddrMd::Ill, AddrMd::Ill, AddrMd::ZoP, AddrMd::ZoP, AddrMd::ZoP, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::Imm, AddrMd::Acc, AddrMd::Ill, AddrMd::Abs, AddrMd::Abs, AddrMd::Abs, AddrMd::Ill,
		AddrMd::Rel, AddrMd::Pos, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::ZpX, AddrMd::ZpX, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::AbY, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::AbX, AddrMd::AbX, AddrMd::Ill,
		AddrMd::Imp, AddrMd::Pre, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::ZoP, AddrMd::ZoP, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::Imm, AddrMd::Acc, AddrMd::Ill, AddrMd::Abs, AddrMd::Abs, AddrMd::Abs, AddrMd::Ill,
		AddrMd::Rel, AddrMd::Pos, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::ZpX, AddrMd::ZpX, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::AbY, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::AbX, AddrMd::AbX, AddrMd::Ill,
		AddrMd::Imp, AddrMd::Pre, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::ZoP, AddrMd::ZoP, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::Imm, AddrMd::Acc, AddrMd::Ill, AddrMd::Ind, AddrMd::Abs, AddrMd::Abs, AddrMd::Ill,
		AddrMd::Rel, AddrMd::Pos, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::ZpX, AddrMd::ZpX, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::AbY, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::AbX, AddrMd::AbX, AddrMd::Ill,
		AddrMd::Ill, AddrMd::Pre, AddrMd::Ill, AddrMd::Ill, AddrMd::ZoP, AddrMd::ZoP, AddrMd::ZoP, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::Ill, AddrMd::Imp, AddrMd::Ill, AddrMd::Abs, AddrMd::Abs, AddrMd::Abs, AddrMd::Ill,
		AddrMd::Rel, AddrMd::Pos, AddrMd::Ill, AddrMd::Ill, AddrMd::ZpX, AddrMd::ZpX, AddrMd::ZpY, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::AbY, AddrMd::Imp, AddrMd::Ill, AddrMd::Ill, AddrMd::AbX, AddrMd::Ill, AddrMd::Ill,
		AddrMd::Imm, AddrMd::Pre, AddrMd::Imm, AddrMd::Ill, AddrMd::ZoP, AddrMd::ZoP, AddrMd::ZoP, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::Imm, AddrMd::Imp, AddrMd::Ill, AddrMd::Abs, AddrMd::Abs, AddrMd::Abs, AddrMd::Imm,
		AddrMd::Rel, AddrMd::Pos, AddrMd::Ill, AddrMd::Ill, AddrMd::ZpX, AddrMd::ZpX, AddrMd::ZpY, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::AbY, AddrMd::Imp, AddrMd::Ill, AddrMd::AbX, AddrMd::AbX, AddrMd::AbY, AddrMd::Ill,
		AddrMd::Imm, AddrMd::Pre, AddrMd::Ill, AddrMd::Ill, AddrMd::ZoP, AddrMd::ZoP, AddrMd::ZoP, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::Imm, AddrMd::Imp, AddrMd::Ill, AddrMd::Abs, AddrMd::Abs, AddrMd::Abs, AddrMd::Ill,
		AddrMd::Rel, AddrMd::Pos, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::ZpX, AddrMd::ZpX, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::AbY, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::AbX, AddrMd::AbX, AddrMd::Ill,
		AddrMd::Imm, AddrMd::Pre, AddrMd::Ill, AddrMd::Ill, AddrMd::ZoP, AddrMd::ZoP, AddrMd::ZoP, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::Imm, AddrMd::Imp, AddrMd::Ill, AddrMd::Abs, AddrMd::Abs, AddrMd::Abs, AddrMd::Ill,
		AddrMd::Rel, AddrMd::Pos, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::ZpX, AddrMd::ZpX, AddrMd::Ill, 
		AddrMd::Imp, AddrMd::AbY, AddrMd::Ill, AddrMd::Ill, AddrMd::Ill, AddrMd::AbX, AddrMd::AbX, AddrMd::Ill
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

#endif // CPU_H