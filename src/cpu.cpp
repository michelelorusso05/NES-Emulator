#include "cpu.h"
#include "bus.hpp"

// #define DEBUG_LOG

#ifdef DEBUG_LOG
    #include <iostream>
#endif

CPU::CPU(Bus* master)
{
    bus = master;

    lookup = 
	{
//          x0                                 x1                                 x2                                 x3                                 x4                                 x5                                 x6                                 x7                                 x8                                 x9                                 xA                                 xB                                 xC                                 xD                                 xE                                 xF                   
/* 0x */{ "BRK", &CPU::BRK, &CPU::IMP, 7 },{ "ORA", &CPU::ORA, &CPU::IZX, 6 },{ "JAM", &CPU::JAM, &CPU::IMP, 2 },{ "SLO", &CPU::SLO, &CPU::IZX, 8 },{ "NOP", &CPU::NOP, &CPU::ZP0, 3 },{ "ORA", &CPU::ORA, &CPU::ZP0, 3 },{ "ASL", &CPU::ASL, &CPU::ZP0, 5 },{ "SLO", &CPU::SLO, &CPU::ZP0, 5 },{ "PHP", &CPU::PHP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::IMM, 2 },{ "ASL", &CPU::ASL, &CPU::IMP, 2 },{ "ANC", &CPU::ANC, &CPU::IMM, 2 },{ "NOP", &CPU::NOP, &CPU::ABS, 4 },{ "ORA", &CPU::ORA, &CPU::ABS, 4 },{ "ASL", &CPU::ASL, &CPU::ABS, 6 },{ "SLO", &CPU::SLO, &CPU::ABS, 6 },
/* 1x */{ "BPL", &CPU::BPL, &CPU::REL, 2 },{ "ORA", &CPU::ORA, &CPU::IZY, 5 },{ "JAM", &CPU::JAM, &CPU::IMP, 2 },{ "SLO", &CPU::SLO, &CPU::IZY, 8 },{ "NOP", &CPU::NOP, &CPU::ZPX, 4 },{ "ORA", &CPU::ORA, &CPU::ZPX, 4 },{ "ASL", &CPU::ASL, &CPU::ZPX, 6 },{ "SLO", &CPU::SLO, &CPU::ZPX, 6 },{ "CLC", &CPU::CLC, &CPU::IMP, 2 },{ "ORA", &CPU::ORA, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "SLO", &CPU::SLO, &CPU::ABY, 7 },{ "NOP", &CPU::NOP, &CPU::ABX, 4 },{ "ORA", &CPU::ORA, &CPU::ABX, 4 },{ "ASL", &CPU::ASL, &CPU::ABX, 7 },{ "SLO", &CPU::SLO, &CPU::ABX, 7 },
/* 2x */{ "JSR", &CPU::JSR, &CPU::ABS, 6 },{ "AND", &CPU::AND, &CPU::IZX, 6 },{ "JAM", &CPU::JAM, &CPU::IMP, 2 },{ "RLA", &CPU::RLA, &CPU::IZX, 8 },{ "BIT", &CPU::BIT, &CPU::ZP0, 3 },{ "AND", &CPU::AND, &CPU::ZP0, 3 },{ "ROL", &CPU::ROL, &CPU::ZP0, 5 },{ "RLA", &CPU::RLA, &CPU::ZP0, 5 },{ "PLP", &CPU::PLP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::IMM, 2 },{ "ROL", &CPU::ROL, &CPU::IMP, 2 },{ "ANC", &CPU::ANC, &CPU::IMM, 2 },{ "BIT", &CPU::BIT, &CPU::ABS, 4 },{ "AND", &CPU::AND, &CPU::ABS, 4 },{ "ROL", &CPU::ROL, &CPU::ABS, 6 },{ "RLA", &CPU::RLA, &CPU::ABS, 6 },
/* 3x */{ "BMI", &CPU::BMI, &CPU::REL, 2 },{ "AND", &CPU::AND, &CPU::IZY, 5 },{ "JAM", &CPU::JAM, &CPU::IMP, 2 },{ "RLA", &CPU::RLA, &CPU::IZY, 8 },{ "NOP", &CPU::NOP, &CPU::ZPX, 4 },{ "AND", &CPU::AND, &CPU::ZPX, 4 },{ "ROL", &CPU::ROL, &CPU::ZPX, 6 },{ "RLA", &CPU::RLA, &CPU::ZPX, 6 },{ "SEC", &CPU::SEC, &CPU::IMP, 2 },{ "AND", &CPU::AND, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "RLA", &CPU::RLA, &CPU::ABY, 7 },{ "NOP", &CPU::NOP, &CPU::ABX, 4 },{ "AND", &CPU::AND, &CPU::ABX, 4 },{ "ROL", &CPU::ROL, &CPU::ABX, 7 },{ "RLA", &CPU::RLA, &CPU::ABX, 7 },
/* 4x */{ "RTI", &CPU::RTI, &CPU::IMP, 6 },{ "EOR", &CPU::EOR, &CPU::IZX, 6 },{ "JAM", &CPU::JAM, &CPU::IMP, 2 },{ "SRE", &CPU::SRE, &CPU::IZX, 8 },{ "NOP", &CPU::NOP, &CPU::ZP0, 3 },{ "EOR", &CPU::EOR, &CPU::ZP0, 3 },{ "LSR", &CPU::LSR, &CPU::ZP0, 5 },{ "SRE", &CPU::SRE, &CPU::ZP0, 5 },{ "PHA", &CPU::PHA, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::IMM, 2 },{ "LSR", &CPU::LSR, &CPU::IMP, 2 },{ "ALR", &CPU::ALR, &CPU::IMM, 2 },{ "JMP", &CPU::JMP, &CPU::ABS, 3 },{ "EOR", &CPU::EOR, &CPU::ABS, 4 },{ "LSR", &CPU::LSR, &CPU::ABS, 6 },{ "SRE", &CPU::SRE, &CPU::ABS, 6 },
/* 5x */{ "BVC", &CPU::BVC, &CPU::REL, 2 },{ "EOR", &CPU::EOR, &CPU::IZY, 5 },{ "JAM", &CPU::JAM, &CPU::IMP, 2 },{ "SRE", &CPU::SRE, &CPU::IZY, 8 },{ "NOP", &CPU::NOP, &CPU::ZPX, 4 },{ "EOR", &CPU::EOR, &CPU::ZPX, 4 },{ "LSR", &CPU::LSR, &CPU::ZPX, 6 },{ "SRE", &CPU::SRE, &CPU::ZPX, 6 },{ "CLI", &CPU::CLI, &CPU::IMP, 2 },{ "EOR", &CPU::EOR, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "SRE", &CPU::SRE, &CPU::ABY, 7 },{ "NOP", &CPU::NOP, &CPU::ABX, 4 },{ "EOR", &CPU::EOR, &CPU::ABX, 4 },{ "LSR", &CPU::LSR, &CPU::ABX, 7 },{ "SRE", &CPU::SRE, &CPU::ABX, 7 },
/* 6x */{ "RTS", &CPU::RTS, &CPU::IMP, 6 },{ "ADC", &CPU::ADC, &CPU::IZX, 6 },{ "JAM", &CPU::JAM, &CPU::IMP, 2 },{ "RRA", &CPU::RRA, &CPU::IZX, 8 },{ "NOP", &CPU::NOP, &CPU::ZP0, 3 },{ "ADC", &CPU::ADC, &CPU::ZP0, 3 },{ "ROR", &CPU::ROR, &CPU::ZP0, 5 },{ "RRA", &CPU::RRA, &CPU::ZP0, 5 },{ "PLA", &CPU::PLA, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::IMM, 2 },{ "ROR", &CPU::ROR, &CPU::IMP, 2 },{ "ARR", &CPU::ARR, &CPU::IMM, 2 },{ "JMP", &CPU::JMP, &CPU::IND, 5 },{ "ADC", &CPU::ADC, &CPU::ABS, 4 },{ "ROR", &CPU::ROR, &CPU::ABS, 6 },{ "RRA", &CPU::RRA, &CPU::ABS, 6 },
/* 7x */{ "BVS", &CPU::BVS, &CPU::REL, 2 },{ "ADC", &CPU::ADC, &CPU::IZY, 5 },{ "JAM", &CPU::JAM, &CPU::IMP, 2 },{ "RRA", &CPU::RRA, &CPU::IZY, 8 },{ "NOP", &CPU::NOP, &CPU::ZPX, 4 },{ "ADC", &CPU::ADC, &CPU::ZPX, 4 },{ "ROR", &CPU::ROR, &CPU::ZPX, 6 },{ "RRA", &CPU::RRA, &CPU::ZPX, 6 },{ "SEI", &CPU::SEI, &CPU::IMP, 2 },{ "ADC", &CPU::ADC, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "RRA", &CPU::RRA, &CPU::ABY, 7 },{ "NOP", &CPU::NOP, &CPU::ABX, 4 },{ "ADC", &CPU::ADC, &CPU::ABX, 4 },{ "ROR", &CPU::ROR, &CPU::ABX, 7 },{ "RRA", &CPU::RRA, &CPU::ABX, 7 },
/* 8x */{ "NOP", &CPU::NOP, &CPU::IMM, 2 },{ "STA", &CPU::STA, &CPU::IZX, 6 },{ "NOP", &CPU::NOP, &CPU::IMM, 2 },{ "SAX", &CPU::SAX, &CPU::IZX, 6 },{ "STY", &CPU::STY, &CPU::ZP0, 3 },{ "STA", &CPU::STA, &CPU::ZP0, 3 },{ "STX", &CPU::STX, &CPU::ZP0, 3 },{ "SAX", &CPU::SAX, &CPU::ZP0, 3 },{ "DEY", &CPU::DEY, &CPU::IMP, 2 },{ "NOP", &CPU::NOP, &CPU::IMM, 2 },{ "TXA", &CPU::TXA, &CPU::IMP, 2 },{ "ANE", &CPU::ANE, &CPU::IMM, 2 },{ "STY", &CPU::STY, &CPU::ABS, 4 },{ "STA", &CPU::STA, &CPU::ABS, 4 },{ "STX", &CPU::STX, &CPU::ABS, 4 },{ "SAX", &CPU::SAX, &CPU::ABS, 4 },
/* 9x */{ "BCC", &CPU::BCC, &CPU::REL, 2 },{ "STA", &CPU::STA, &CPU::IZY, 6 },{ "JAM", &CPU::JAM, &CPU::IMP, 2 },{ "SHA", &CPU::SHA, &CPU::IZY, 6 },{ "STY", &CPU::STY, &CPU::ZPX, 4 },{ "STA", &CPU::STA, &CPU::ZPX, 4 },{ "STX", &CPU::STX, &CPU::ZPY, 4 },{ "SAX", &CPU::SAX, &CPU::ZPY, 4 },{ "TYA", &CPU::TYA, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::ABY, 5 },{ "TXS", &CPU::TXS, &CPU::IMP, 2 },{ "TAS", &CPU::TAS, &CPU::ABY, 5 },{ "SHY", &CPU::SHY, &CPU::ABX, 5 },{ "STA", &CPU::STA, &CPU::ABX, 5 },{ "SHX", &CPU::SHX, &CPU::ABY, 5 },{ "SHA", &CPU::SHA, &CPU::ABY, 5 },
/* Ax */{ "LDY", &CPU::LDY, &CPU::IMM, 2 },{ "LDA", &CPU::LDA, &CPU::IZX, 6 },{ "LDX", &CPU::LDX, &CPU::IMM, 2 },{ "LAX", &CPU::LAX, &CPU::IZX, 6 },{ "LDY", &CPU::LDY, &CPU::ZP0, 3 },{ "LDA", &CPU::LDA, &CPU::ZP0, 3 },{ "LDX", &CPU::LDX, &CPU::ZP0, 3 },{ "LAX", &CPU::LAX, &CPU::ZP0, 3 },{ "TAY", &CPU::TAY, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::IMM, 2 },{ "TAX", &CPU::TAX, &CPU::IMP, 2 },{ "LXA", &CPU::LXA, &CPU::IMM, 2 },{ "LDY", &CPU::LDY, &CPU::ABS, 4 },{ "LDA", &CPU::LDA, &CPU::ABS, 4 },{ "LDX", &CPU::LDX, &CPU::ABS, 4 },{ "LAX", &CPU::LAX, &CPU::ABS, 4 },
/* Bx */{ "BCS", &CPU::BCS, &CPU::REL, 2 },{ "LDA", &CPU::LDA, &CPU::IZY, 5 },{ "JAM", &CPU::JAM, &CPU::IMP, 2 },{ "LAX", &CPU::LAX, &CPU::IZY, 5 },{ "LDY", &CPU::LDY, &CPU::ZPX, 4 },{ "LDA", &CPU::LDA, &CPU::ZPX, 4 },{ "LDX", &CPU::LDX, &CPU::ZPY, 4 },{ "LAX", &CPU::LAX, &CPU::ZPY, 4 },{ "CLV", &CPU::CLV, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::ABY, 4 },{ "TSX", &CPU::TSX, &CPU::IMP, 2 },{ "LAS", &CPU::LAS, &CPU::ABY, 4 },{ "LDY", &CPU::LDY, &CPU::ABX, 4 },{ "LDA", &CPU::LDA, &CPU::ABX, 4 },{ "LDX", &CPU::LDX, &CPU::ABY, 4 },{ "LAX", &CPU::LAX, &CPU::ABY, 4 },
/* Cx */{ "CPY", &CPU::CPY, &CPU::IMM, 2 },{ "CMP", &CPU::CMP, &CPU::IZX, 6 },{ "NOP", &CPU::NOP, &CPU::IMM, 2 },{ "DCP", &CPU::DCP, &CPU::IZX, 8 },{ "CPY", &CPU::CPY, &CPU::ZP0, 3 },{ "CMP", &CPU::CMP, &CPU::ZP0, 3 },{ "DEC", &CPU::DEC, &CPU::ZP0, 5 },{ "DCP", &CPU::DCP, &CPU::ZP0, 5 },{ "INY", &CPU::INY, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::IMM, 2 },{ "DEX", &CPU::DEX, &CPU::IMP, 2 },{ "SBX", &CPU::SBX, &CPU::IMM, 2 },{ "CPY", &CPU::CPY, &CPU::ABS, 4 },{ "CMP", &CPU::CMP, &CPU::ABS, 4 },{ "DEC", &CPU::DEC, &CPU::ABS, 6 },{ "DCP", &CPU::DCP, &CPU::ABS, 6 },
/* Dx */{ "BNE", &CPU::BNE, &CPU::REL, 2 },{ "CMP", &CPU::CMP, &CPU::IZY, 5 },{ "JAM", &CPU::JAM, &CPU::IMP, 2 },{ "DCP", &CPU::DCP, &CPU::IZY, 8 },{ "NOP", &CPU::NOP, &CPU::ZPX, 4 },{ "CMP", &CPU::CMP, &CPU::ZPX, 4 },{ "DEC", &CPU::DEC, &CPU::ZPX, 6 },{ "DCP", &CPU::DCP, &CPU::ZPX, 6 },{ "CLD", &CPU::CLD, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "DCP", &CPU::DCP, &CPU::ABY, 7 },{ "NOP", &CPU::NOP, &CPU::ABX, 4 },{ "CMP", &CPU::CMP, &CPU::ABX, 4 },{ "DEC", &CPU::DEC, &CPU::ABX, 7 },{ "DCP", &CPU::DCP, &CPU::ABX, 7 },
/* Ex */{ "CPX", &CPU::CPX, &CPU::IMM, 2 },{ "SBC", &CPU::SBC, &CPU::IZX, 6 },{ "NOP", &CPU::NOP, &CPU::IMM, 2 },{ "ISB", &CPU::ISB, &CPU::IZX, 8 },{ "CPX", &CPU::CPX, &CPU::ZP0, 3 },{ "SBC", &CPU::SBC, &CPU::ZP0, 3 },{ "INC", &CPU::INC, &CPU::ZP0, 5 },{ "ISB", &CPU::ISB, &CPU::ZP0, 5 },{ "INX", &CPU::INX, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::IMM, 2 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::IMM, 2 },{ "CPX", &CPU::CPX, &CPU::ABS, 4 },{ "SBC", &CPU::SBC, &CPU::ABS, 4 },{ "INC", &CPU::INC, &CPU::ABS, 6 },{ "ISB", &CPU::ISB, &CPU::ABS, 6 },
/* Fx */{ "BEQ", &CPU::BEQ, &CPU::REL, 2 },{ "SBC", &CPU::SBC, &CPU::IZY, 5 },{ "JAM", &CPU::JAM, &CPU::IMP, 2 },{ "ISB", &CPU::ISB, &CPU::IZY, 8 },{ "NOP", &CPU::NOP, &CPU::ZPX, 4 },{ "SBC", &CPU::SBC, &CPU::ZPX, 4 },{ "INC", &CPU::INC, &CPU::ZPX, 6 },{ "ISB", &CPU::ISB, &CPU::ZPX, 6 },{ "SED", &CPU::SED, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "ISB", &CPU::ISB, &CPU::ABY, 7 },{ "NOP", &CPU::NOP, &CPU::ABX, 4 },{ "SBC", &CPU::SBC, &CPU::ABX, 4 },{ "INC", &CPU::INC, &CPU::ABX, 7 },{ "ISB", &CPU::ISB, &CPU::ABX, 7 },
	};
}

uint8_t CPU::read(uint16_t addr)
{
    return CPU::bus->read(addr);
}

void CPU::write(uint16_t addr, uint8_t data)
{
    CPU::bus->write(addr, data);
}

void CPU::clock()
{
    if (halted)
        return;

    if (cycles == 0)
    {
        if (irqPending)
        {
            irq();
            irqPending = false;
            return;
        }

        if (nmiRunning)
        {
            prevNmiRunning = true;
        }
        if (prevNmiRunning && !nmiRunning)
        {
            prevNmiRunning = false;
            nmi();
        }
        else
        {
            opcode = read(pc);

            pc++;

            cycles = lookup[opcode].cycles;

            uint8_t addrModeAdditionalCycles = (this->*lookup[opcode].addrmode)();
            uint8_t operationAdditionalCycles = (this->*lookup[opcode].operate)();

            cycles += (addrModeAdditionalCycles & operationAdditionalCycles);

            inhibitIFlag = false;
        }

        nmiRunning = false;
    }

    if (!prevNmiPending && nmiPending)
        nmiRunning = true;

    prevNmiPending = nmiPending;

    cycles--;
}

void CPU::clockUntilInstruction()
{
    while (cycles > 0)
        clock();

    clock();
}

void CPU::reset()
{
    halted = false;

    ax = 0;
    rx = 0;
    ry = 0;
    sp = 0xFD;
    status = 0x34;

    addr = 0xFFFC;
    uint8_t lo = read(addr);
    uint8_t hi = read(addr + 1);

    pc = lo | (hi << 8);

    addr = 0;
    rel = 0;
    fetched = 0;

    cycles = 8;

    nmiPending = false;
    nmiRunning = false;
    prevNmiPending = false;
    irqPending = false;
    irqRunning = false;
}

void CPU::irq()
{

    // Interrupts are disabled
    if (GetFlag(I) || inhibitIFlag)
        return;

    if (!irqPending)
    {
        irqPending = true;
        return;
    }
    write(0x0100 + sp, (pc >> 8) & 0xFF);
    sp--;
    write(0x0100 + sp, pc & 0xFF);
    sp--;

    SetFlag(FLAGS::B, 0);
    SetFlag(FLAGS::U, 1);

    write(0x0100 + sp, status);
    sp--;

    SetFlag(FLAGS::I, 1);

    addr = 0xFFFE;
    uint8_t lo = read(addr);
    uint8_t hi = read(addr + 1);

    pc = lo | (hi << 8);

    cycles = 7;
}

void CPU::nmi()
{
    write(0x0100 + sp, (pc >> 8) & 0xFF);
    sp--;
    write(0x0100 + sp, pc & 0xFF);
    sp--;

    SetFlag(FLAGS::B, 0);
    SetFlag(FLAGS::U, 1);

    write(0x0100 + sp, status);
    sp--;

    SetFlag(FLAGS::I, 1);

    addr = 0xFFFA;
    uint8_t lo = read(addr);
    uint8_t hi = read(addr + 1);

    pc = lo | (hi << 8);

    cycles = 7;
}

uint8_t CPU::GetFlag(CPU::FLAGS f)
{
    return ((status & f) > 0) ? 1 : 0;
}

void CPU::SetFlag(CPU::FLAGS f, bool s)
{
    if (s)
        CPU::status |= f;
    else
        CPU::status &= (~f);
}

// Addressing modes
// These functions return 1 if they cross a page boundary, requiring another clock cycle on the emulated 6502.

// Target is hardcoded to the opcode. Doesn't edit addresses.
// Some opcodes have both IMP and memory access addressing. These opcodes always reference the accumulator as the implicit register.
// IMPlied
uint8_t CPU::IMP()
{
    fetched = ax;
    return 0;
}

// Source is a literal value. Doesn't edit addresses.
// IMMediate
uint8_t CPU::IMM()
{
    addr = pc++;
    return 0;
}

// Zero Page
uint8_t CPU::ZP0()
{
    addr = read(pc);
    pc++;
    addr = addr & 0x00FF;
    return 0;
}

// Zero Page (X addressing)
uint8_t CPU::ZPX()
{
    addr = read(pc) + rx;
    pc++;
    addr = addr & 0x00FF;
    return 0;
}

// Zero Page (Y addressing)
uint8_t CPU::ZPY()
{
    addr = read(pc) + ry;
    pc++;
    addr = addr & 0x00FF;
    return 0;
}

// RELative
uint8_t CPU::REL()
{
    rel = int8_t(read(pc));
    pc++;
    return 0;
}

// ABSolute
uint8_t CPU::ABS()
{
    uint8_t lo = read(pc++);
    uint8_t hi = read(pc++);

    addr = (hi << 8) | lo;

    return 0;
}

// ABSolute (X addressing)
uint8_t CPU::ABX()
{
    uint8_t lo = read(pc++);
    uint8_t hi = read(pc++);

    addr = (hi << 8) | lo;
    addr += rx;

    return ((addr & 0xFF00) == (hi << 8)) ? 0 : 1;
}

// ABSolute (Y addressing)
uint8_t CPU::ABY()
{
    uint8_t lo = read(pc++);
    uint8_t hi = read(pc++);

    addr = (hi << 8) | lo;
    addr += ry;

    return ((addr & 0xFF00) == (hi << 8)) ? 0 : 1;
}

// INDirect (pointer)
uint8_t CPU::IND()
{
    uint8_t lo = read(pc++);
    uint8_t hi = read(pc++);

    uint16_t ptr = (hi << 8) | lo;

    // 6502 IND access hardware bug
    if (lo == 0xFF)
        addr = read(ptr) | (read((ptr) & 0xFF00) << 8);
    else
        addr = read(ptr) | (read(ptr + 1) << 8);

    return 0;
}

// Indirect (Zero page X addressing)
uint8_t CPU::IZX()
{

    uint8_t ad = read(pc++);
    uint16_t ptr = (ad + rx) & 0xFF;

    addr = read(ptr) | (read((ptr + 1) & 0xFF) << 8);

    return 0;
}

// Indirect (Zero page Y addressing)
uint8_t CPU::IZY()
{
    uint8_t a = read(pc++);

    uint16_t ptr = read(a) | ((read((a + 1) & 0xFF)) << 8);
    addr = ptr + ry;

    return ((ptr & 0xFF00) != (addr & 0xFF00)) ? 1 : 0;
}

// Instructions
// These functions return 1 if a page boundary cross increments the clock cycles.
// Some functions (such as ASL) take always the same number of cycles to complete, either if a page boundary cross happened or not.

uint8_t CPU::fetch()
{
    if (lookup[opcode].addrmode != &CPU::IMP)
        fetched = read(addr);
    return fetched;
}

/**
 * @brief ADC - Add with carry
 * 
 * @return uint8_t 
 */
uint8_t CPU::ADC()
{
    fetch();

    uint16_t temp = ax + fetched + GetFlag(FLAGS::C);

    SetFlag(FLAGS::C, temp & 0xFF00);
    SetFlag(FLAGS::V, ((~(ax ^ fetched)) & (ax ^ temp)) & 0x80);

    ax = temp & 0x00FF;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 1;
}

/**
 * @brief AND - Logic AND with accumulator
 * 
 * @return uint8_t 
 */
uint8_t CPU::AND()
{
    fetch();
    ax &= fetched;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 1;
}

/**
 * @brief ASL - Arithmetic left shift
 * 
 * @return uint8_t 
 */
uint8_t CPU::ASL() 
{
    fetch();

    SetFlag(FLAGS::C, fetched & 0x80);

    fetched <<= 1;

    SetFlag(FLAGS::Z, fetched == 0);
    SetFlag(FLAGS::N, fetched & 0x80);

    if (lookup[opcode].addrmode == &CPU::IMP)
        ax = fetched;
    else
        write(addr, fetched);

    return 0;
}

/**
 * @brief BCC - Branch if Carry is reset
 * 
 * @return uint8_t 
 */
uint8_t CPU::BCC() 
{
    if (GetFlag(FLAGS::C) == 0)
    {
        cycles++;

        addr = pc + rel;

        if ((pc & 0xFF00) != (addr & 0xFF00))
            cycles++;

        pc = addr;
    }

    return 0;
}

/**
 * @brief BCS - Branch if Carry is set
 * 
 * @return uint8_t 
 */
uint8_t CPU::BCS() 
{
    if (GetFlag(FLAGS::C) > 0)
    {
        cycles++;

        addr = pc + rel;

        if ((pc & 0xFF00) != (addr & 0xFF00))
            cycles++;

        pc = addr;
    }

    return 0;
}

/**
 * @brief BEQ - Branch if equal
 * 
 * @return uint8_t 
 */
uint8_t CPU::BEQ() 
{
    if (GetFlag(FLAGS::Z) > 0)
    {
        cycles++;

        addr = pc + rel;

        if ((pc & 0xFF00) != (addr & 0xFF00))
            cycles++;

        pc = addr;
    }
    return 0;
}

/**
 * @brief BIT - Test bits with accumulator
 * 
 * @return uint8_t 
 */
uint8_t CPU::BIT() 
{
    fetch();

    SetFlag(FLAGS::Z, (ax & fetched) == 0);
    SetFlag(FLAGS::N, fetched & 0x80);
    SetFlag(FLAGS::V, fetched & 0x40);

    return 0;
}

/**
 * @brief BMI - Branch if result is negative
 * 
 * @return uint8_t 
 */
uint8_t CPU::BMI() 
{
    if (GetFlag(FLAGS::N) > 0)
    {
        cycles++;

        addr = pc + rel;

        if ((pc & 0xFF00) != (addr & 0xFF00))
            cycles++;

        pc = addr;
    }
    return 0;
}

/**
 * @brief BNE - Branch if not equal
 * 
 * @return uint8_t 
 */
uint8_t CPU::BNE() 
{
    if (GetFlag(FLAGS::Z) == 0)
    {
        cycles++;

        addr = pc + rel;

        if ((pc & 0xFF00) != (addr & 0xFF00))
            cycles++;

        pc = addr;
    }

    return 0;
}

/**
 * @brief BPL - Branch if result is positive
 * 
 * @return uint8_t 
 */
uint8_t CPU::BPL() 
{
    if (GetFlag(FLAGS::N) == 0)
    {
        cycles++;

        addr = pc + rel;

        if ((pc & 0xFF00) != (addr & 0xFF00))
            cycles++;

        pc = addr;
    }

    return 0;
}

/**
 * @brief BRK - Software interrupt
 * 
 * @return uint8_t 
 */

uint8_t CPU::BRK() 
{
    isInBRK = true;
    pc += 1;

    write(0x0100 + sp, ((pc >> 8) & 0xFF));
    sp--;
    write(0x0100 + sp, (pc & 0xFF));
    sp--;

    write(0x0100 + sp, (status | 0x30));
    sp--;

    SetFlag(FLAGS::I, 1);
    
    addr = 0xFFFE;
    uint8_t lo = read(addr);
    uint8_t hi = read(addr + 1);

    pc = lo | (hi << 8);

    return 0;
}

/**
 * @brief BVC - Branch if Overflow flag is reset
 * 
 * @return uint8_t 
 */
uint8_t CPU::BVC() 
{
    if (GetFlag(FLAGS::V) == 0)
    {
        cycles++;

        addr = pc + rel;

        if ((pc & 0xFF00) != (addr & 0xFF00))
            cycles++;

        pc = addr;
    }

    return 0;
}

/**
 * @brief BVS - Branch if Overflow flag is set
 * 
 * @return uint8_t 
 */
uint8_t CPU::BVS() 
{
    if (GetFlag(FLAGS::V) > 0)
    {
        cycles++;

        addr = pc + rel;

        if ((pc & 0xFF00) != (addr & 0xFF00))
            cycles++;

        pc = addr;
    }

    return 0;
}

/**
 * @brief CLC - Clear Carry flag
 * 
 * @return uint8_t 
 */
uint8_t CPU::CLC() 
{
    SetFlag(FLAGS::C, false);
    return 0;
}

/**
 * @brief CLD - Clear Decimal flag
 * 
 * @return uint8_t 
 */
uint8_t CPU::CLD() 
{
    SetFlag(FLAGS::D, false);
    return 0;
}

/**
 * @brief CLI - Clear Interrupt flag
 * 
 * @return uint8_t 
 */
uint8_t CPU::CLI() 
{
    SetFlag(FLAGS::I, false);
    inhibitIFlag = true;
    return 0;
}

/**
 * @brief CLV - Clear Overflow flag
 * 
 * @return uint8_t 
 */
uint8_t CPU::CLV() 
{
    SetFlag(FLAGS::V, false);
    return 0;
}

/**
 * @brief CMP - Arithmetic comparison between accumulator and value
 * 
 * @return uint8_t 
 */
uint8_t CPU::CMP() 
{
    fetch();

    uint8_t r = ax - fetched;

    SetFlag(FLAGS::Z, r == 0);
    SetFlag(FLAGS::N, r & 0x80);
    SetFlag(FLAGS::C, ax >= fetched);

    return 1;
}

/**
 * @brief CPX - Arithmetic comparison between X register and value
 * 
 * @return uint8_t 
 */
uint8_t CPU::CPX() 
{
    fetch();
    
    uint8_t r = rx - fetched;

    SetFlag(FLAGS::Z, r == 0);
    SetFlag(FLAGS::N, r & 0x80);
    SetFlag(FLAGS::C, rx >= fetched);

    return 0;
}

/**
 * @brief CMP - Arithmetic comparison between Y register and value
 * 
 * @return uint8_t 
 */
uint8_t CPU::CPY() 
{
    fetch();
    
    uint8_t r = ry - fetched;

    SetFlag(FLAGS::Z, r == 0);
    SetFlag(FLAGS::N, r & 0x80);
    SetFlag(FLAGS::C, ry >= fetched);

    return 0;
}

/**
 * @brief DEC - Decrement accumulator
 * 
 * @return uint8_t 
 */
uint8_t CPU::DEC() 
{
    fetch();

    uint8_t t = fetched - 1;
    write(addr, t);

    SetFlag(FLAGS::Z, t == 0);
    SetFlag(FLAGS::N, t & 0x80);

    return 0;
}

/**
 * @brief DEX - Decrement X register
 * 
 * @return uint8_t 
 */
uint8_t CPU::DEX() 
{
    rx--;

    SetFlag(FLAGS::Z, rx == 0);
    SetFlag(FLAGS::N, rx & 0x80);

    return 0;
}

/**
 * @brief DEY - Decrement Y register
 * 
 * @return uint8_t 
 */
uint8_t CPU::DEY() 
{
    ry--;

    SetFlag(FLAGS::Z, ry == 0);
    SetFlag(FLAGS::N, ry & 0x80);
   
    return 0;
}

/**
 * @brief EOR - Logic XOR with accumulator
 * 
 * @return uint8_t 
 */
uint8_t CPU::EOR() 
{
    fetch();

    ax ^= fetched;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 1;
}

/**
 * @brief INC - Increment accumulator
 * 
 * @return uint8_t 
 */
uint8_t CPU::INC() 
{
    fetch();

    uint8_t t = fetched + 1;
    write(addr, t);

    SetFlag(FLAGS::Z, t == 0);
    SetFlag(FLAGS::N, t & 0x80);

    return 0;
}

/**
 * @brief INX - Increment X register
 * 
 * @return uint8_t 
 */
uint8_t CPU::INX() 
{
    rx++;

    SetFlag(FLAGS::Z, rx == 0);
    SetFlag(FLAGS::N, rx & 0x80);
   
    return 0;
}

/**
 * @brief INY - Increment Y register
 * 
 * @return uint8_t 
 */
uint8_t CPU::INY() 
{
    ry++;

    SetFlag(FLAGS::Z, ry == 0);
    SetFlag(FLAGS::N, ry & 0x80);
   
    return 0;
}

/**
 * @brief JMP - Jump to address
 * 
 * @return uint8_t 
 */
uint8_t CPU::JMP() 
{
    pc = addr;
    return 0;
}

/**
 * @brief JSR - Jump to subroutine
 * 
 * @return uint8_t 
 */
uint8_t CPU::JSR() 
{
    // JSR stores in stack the address of the last byte of the JSR instruction (aka the high byte of the pointed address)
    pc--;

    write(0x0100 + sp, (pc >> 8) & 0x00FF);
    sp--;
    write(0x0100 + sp, pc & 0x00FF);
    sp--;

    pc = addr;   

    return 0;
}

/**
 * @brief LDA - Load memory in accumulator
 * 
 * @return uint8_t 
 */
uint8_t CPU::LDA() 
{
    fetch();

    ax = fetched;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 1;
}

/**
 * @brief LDX - Load memory in X register
 * 
 * @return uint8_t 
 */
uint8_t CPU::LDX() 
{
    fetch();

    rx = fetched;

    SetFlag(FLAGS::Z, rx == 0);
    SetFlag(FLAGS::N, rx & 0x80);

    return 1;
}

/**
 * @brief LDY - Load memory in Y register
 * 
 * @return uint8_t 
 */
uint8_t CPU::LDY() 
{
    fetch();

    ry = fetched;

    SetFlag(FLAGS::Z, ry == 0);
    SetFlag(FLAGS::N, ry & 0x80);

    return 1;
}

/**
 * @brief LSR - Logical right shift
 * 
 * @return uint8_t 
 */
uint8_t CPU::LSR() 
{
    fetch();

    SetFlag(FLAGS::C, fetched & 0x01);

    fetched >>= 1;

    SetFlag(FLAGS::Z, fetched == 0);
    SetFlag(FLAGS::N, false);

    if (lookup[opcode].addrmode == &CPU::IMP)
        ax = fetched;
    else
        write(addr, fetched);

    return 0;
}

/**
 * @brief NOP - No operation
 * 
 * @return uint8_t 
 */
uint8_t CPU::NOP() 
{
    switch (opcode) {
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 1;
	}

    return 0;
}

/**
 * @brief ORA - Logic OR with accumulator
 * 
 * @return uint8_t 
 */
uint8_t CPU::ORA() 
{
    fetch();

    ax |= fetched;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 1;
}

/**
 * @brief PHA - Push accumulator to stack
 * 
 * @return uint8_t 
 */
uint8_t CPU::PHA() 
{
    write(0x0100 + sp, ax);
    sp--;

    return 0;
}

/**
 * @brief PHP - Push status register to stack
 * 
 * @return uint8_t 
 */
uint8_t CPU::PHP() 
{
    write(0x0100 + sp, status | 0x30);
    sp--;

    return 0;
}

/**
 * @brief PLA - Pull accumulator from stack
 * 
 * @return uint8_t 
 */
uint8_t CPU::PLA() 
{
    sp++;
    ax = read(0x0100 + sp);

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 0;
}

/**
 * @brief PLP - Pull status register from stack
 * 
 * @return uint8_t 
 */
uint8_t CPU::PLP() 
{
    sp++;
    status = (read(0x0100 + sp) & (~FLAGS::B) & (~FLAGS::U));
    
    return 0;
}

/**
 * @brief ROL - Left rotate
 * 
 * @return uint8_t 
 */
uint8_t CPU::ROL() 
{
    fetch();

    uint8_t t = (fetched << 1) | GetFlag(FLAGS::C);

    SetFlag(FLAGS::C, fetched & 0x80);
    SetFlag(FLAGS::Z, t == 0);
    SetFlag(FLAGS::N, t & 0x80);

    if (lookup[opcode].addrmode == &CPU::IMP)
        ax = t;
    else
        write(addr, t);

    return 0;
}

/**
 * @brief ROR - Right rotate
 * 
 * @return uint8_t 
 */
uint8_t CPU::ROR() 
{
    fetch();

    uint8_t t = (fetched >> 1) | (GetFlag(FLAGS::C) << 7);

    SetFlag(FLAGS::C, fetched & 0x01);
    SetFlag(FLAGS::Z, t == 0);
    SetFlag(FLAGS::N, t & 0x80);

    if (lookup[opcode].addrmode == &CPU::IMP)
        ax = t;
    else
        write(addr, t);

    return 0;
}

/**
 * @brief RTI - Return from interrupt
 * 
 * @return uint8_t 
 */
uint8_t CPU::RTI() 
{
    sp++;
    status = read(0x0100 + sp);

    sp++;
    uint8_t lo = read(0x0100 + sp);
    sp++;
    uint8_t hi = read(0x0100 + sp);

    pc = (lo | (hi << 8));

    if (isInBRK)
        isInBRK = false;

    return 0;
}

/**
 * @brief RTS - Return from subroutine
 * 
 * @return uint8_t 
 */
uint8_t CPU::RTS() 
{
    sp++;
    uint8_t lo = read(0x0100 + sp);
    sp++;
    uint8_t hi = read(0x0100 + sp);

    pc = lo | (hi << 8);
    pc++;

    return 0;
}

/**
 * @brief SBC - Subtraction with borrow in
 * 
 * @return uint8_t 
 */
uint8_t CPU::SBC() 
{    
    fetch();

    uint16_t temp = ax + (~fetched & 0xFF) + GetFlag(FLAGS::C);
    
    SetFlag(FLAGS::C, temp & 0xFF00);
    SetFlag(FLAGS::V, ((ax ^ fetched) & (ax ^ temp)) & 0x80);

    ax = temp & 0x00FF;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);
    
    return 1;
}

/**
 * @brief SEC - Set Carry flag
 * 
 * @return uint8_t 
 */
uint8_t CPU::SEC() 
{
    SetFlag(FLAGS::C, true);
    return 0;
}

/**
 * @brief SED - Set Decimal flag
 * 
 * @return uint8_t 
 */
uint8_t CPU::SED() 
{
    SetFlag(FLAGS::D, true);
    return 0;
}

/**
 * @brief SEI - Set Interrupt flag
 * 
 * @return uint8_t 
 */
uint8_t CPU::SEI() 
{
    SetFlag(FLAGS::I, true);
    return 0;
}

/**
 * @brief STA - Store accumulator in memory
 * 
 * @return uint8_t 
 */
uint8_t CPU::STA() 
{
    write(addr, ax);

    return 0;
}

/**
 * @brief STX - Store X register in memory
 * 
 * @return uint8_t 
 */
uint8_t CPU::STX() 
{
    write(addr, rx);
    return 0;
}

/**
 * @brief STY - Store Y register in memory
 * 
 * @return uint8_t 
 */
uint8_t CPU::STY() 
{
    write(addr, ry);
    return 0;
}

/**
 * @brief TAX - Transfer accumulator to X register
 * 
 * @return uint8_t 
 */
uint8_t CPU::TAX() 
{
    rx = ax;

    SetFlag(FLAGS::Z, rx == 0);
    SetFlag(FLAGS::N, rx & 0x80);

    return 0;
}

/**
 * @brief TAY - Transfer accumulator to Y register
 * 
 * @return uint8_t 
 */
uint8_t CPU::TAY() 
{
    ry = ax;

    SetFlag(FLAGS::Z, ry == 0);
    SetFlag(FLAGS::N, ry & 0x80);
    
    return 0;
}

/**
 * @brief TSX - Transfer stack pointer to X register
 * 
 * @return uint8_t 
 */
uint8_t CPU::TSX() 
{
    rx = sp;

    SetFlag(FLAGS::Z, rx == 0);
    SetFlag(FLAGS::N, rx & 0x80);

    return 0;
}

/**
 * @brief TXA - Transfer X register to accumulator
 * 
 * @return uint8_t 
 */
uint8_t CPU::TXA() 
{
    ax = rx;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 0;
}

/**
 * @brief TXS - Transfer X register to stack pointer
 * 
 * @return uint8_t 
 */
uint8_t CPU::TXS() 
{
    sp = rx;

    return 0;
}

/**
 * @brief TYA - Transfer Y register to accumulator
 * 
 * @return uint8_t 
 */
uint8_t CPU::TYA() 
{
    ax = ry;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 0;
}

/// Undocumented opcodes

/**
 * @brief LAX - LDA + LDX
 * 
 * @return uint8_t
 */
uint8_t CPU::LAX()
{
    fetch();
    ax = fetched;
    rx = fetched;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 1;
}

/**
 * @brief SAX - Store (ax AND rx) in memory
 * 
 * @return uint8_t 
 */
uint8_t CPU::SAX()
{
    write(addr, (ax & rx));

    return 0;
}

/**
 * @brief DCP - Decrement memory by one then Compare with accumulator
 * 
 * @return uint8_t 
 */
uint8_t CPU::DCP()
{
    fetch();
    fetched--;
    write(addr, fetched);

    uint8_t r = ax - fetched;

    SetFlag(FLAGS::Z, r == 0);
    SetFlag(FLAGS::N, r & 0x80);
    SetFlag(FLAGS::C, ax >= fetched);

    return 0;
}

/**
 * @brief ISC - Increment memory by one then SBC
 * 
 * @return uint8_t 
 */
uint8_t CPU::ISB()
{
    fetch();
    fetched++;
    write(addr, fetched);

    uint16_t temp = ax + (~fetched & 0xFF) + GetFlag(FLAGS::C);
    
    SetFlag(FLAGS::C, temp & 0xFF00);
    SetFlag(FLAGS::V, ((ax ^ fetched) & (ax ^ temp)) & 0x80);

    ax = temp & 0x00FF;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 0;
}

/**
 * @brief SLO - Arithmetic Shift Left then OR Memory with accumulator
 * 
 * @return uint8_t 
 */
uint8_t CPU::SLO()
{
    fetch();
    SetFlag(FLAGS::C, (fetched & 0x80) > 0);
    fetched <<= 1;
    write(addr, fetched);

    ax |= fetched;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 0;
}

/**
 * @brief RLA - Rotate Left then AND with accumulator
 * 
 * @return uint8_t 
 */
uint8_t CPU::RLA()
{
    fetch();

    uint8_t t = (fetched << 1) | GetFlag(FLAGS::C);

    SetFlag(FLAGS::C, fetched & 0x80);

    write(addr, t);

    ax &= t;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 0;
}

/**
 * @brief SRE - Logical Shift Rigth then EOR memory with accumulator
 * 
 * @return uint8_t 
 */
uint8_t CPU::SRE()
{
    fetch();
    SetFlag(FLAGS::C, (fetched & 0x01) > 0);
    fetched >>= 1;
    write(addr, fetched);

    ax ^= fetched;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 0;
}

/**
 * @brief RRA - Rotate Right and Add memory to accumulator
 * 
 * @return uint8_t 
 */
uint8_t CPU::RRA()
{
    fetch();

    uint8_t t = (fetched >> 1) | (GetFlag(FLAGS::C) << 7);
    write(addr, t);
    SetFlag(FLAGS::C, fetched & 0x01);

    uint16_t temp = ax + t + GetFlag(FLAGS::C);

    SetFlag(FLAGS::C, temp & 0xFF00);
    SetFlag(FLAGS::V, ((~(ax ^ t)) & (ax ^ temp)) & 0x80);

    ax = temp & 0x00FF;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 0;
}

/**
 * @brief ANC - AND memory with accumulator then move N flag to C flag
 * The "moving" is actually the C flag being set as if an ASL also happened.
 * 
 * @return uint8_t 
 */
uint8_t CPU::ANC()
{
    fetch();
    ax &= fetched;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);
    SetFlag(FLAGS::C, ax & 0x80);

    return 0;
}

/**
 * @brief ALR - AND then Logical Shift Right
 * 
 * @return uint8_t 
 */
uint8_t CPU::ALR()
{
    fetch();

    ax &= fetched;

    SetFlag(FLAGS::C, ax & 0x01);

    ax >>= 1;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, 0);


    return 0;
}

/**
 * @brief AND accumulator then ROR
 * 
 * @return uint8_t 
 */
uint8_t CPU::ARR()
{
    fetch();

    ax &= fetched;
    ax = ((ax >> 1) | (GetFlag(FLAGS::C) << 7));

    SetFlag(FLAGS::N, ax & 0x80);
    SetFlag(FLAGS::Z, ax == 0);
    
    SetFlag(FLAGS::C, ax & 0x40);
    SetFlag(FLAGS::V, ((ax & 0x40) > 0) ^ ((ax & 0x20) > 0));

    return 0;
}

/**
 * @brief LXA - LAX immediate
 * 
 * @return uint8_t 
 */
uint8_t CPU::LXA()
{
    fetch();
    ax = fetched;
    rx = fetched;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);
    return 0;
}

/**
 * @brief SBX - Subtract memory from accumulator AND register X
 * 
 * @return uint8_t 
 */
uint8_t CPU::SBX()
{
    fetch();
    uint8_t andResult = (ax & rx);

    SetFlag(FLAGS::C, andResult >= fetched);

    rx = andResult - fetched;

    SetFlag(FLAGS::Z, rx == 0);
    SetFlag(FLAGS::N, rx & 0x80);

    return 0;
}

/**
 * @brief SHA - Store accumulator AND address
 * 
 * @return uint8_t 
 */
uint8_t CPU::SHA()
{
    uint16_t ad = (((ax & ((addr >> 8) + 1)) << 8) | (addr & 0xFF));
    write(ad, ax & ((addr >> 8) + 1));

    return 0;
}

/**
 * @brief SHX - Store register X AND Address
 * 
 * @return uint8_t 
 */
uint8_t CPU::SHX()
{
    uint16_t ad = (((rx & ((addr >> 8) + 1)) << 8) | (addr & 0xFF));
    write(ad, rx & ((addr >> 8) + 1));

    return 0;
}

/**
 * @brief SHY - Store register Y AND Address
 * 
 * @return uint8_t 
 */
uint8_t CPU::SHY()
{
    uint16_t ad = (((ry & ((addr >> 8) + 1)) << 8) | (addr & 0xFF));
    write(ad, ry & ((addr >> 8) + 1));

    return 0;
}

/**
 * @brief LAS - AND memory with Stack Pointer
 * 
 * @return uint8_t 
 */
uint8_t CPU::LAS()
{
    fetch();
    uint8_t result = (fetched & sp);
    ax = result;
    rx = result;
    sp = result;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 1;
}

/**
 * @brief ANE - Non-deterministic Operation of Accumulator, Index Register X, Memory and Bus Contents
 * 
 * @return uint8_t 
 */
uint8_t CPU::ANE()
{
    fetch();

    ax = (ax & (rand() & 0xFF)) & rx & fetched;

    SetFlag(FLAGS::Z, ax == 0);
    SetFlag(FLAGS::N, ax & 0x80);

    return 0;
}

/**
 * @brief TAS - Transfer accumulator AND register X to stack pointer then store stack pointer AND upper byte of address + 1 in memory
 * 
 * @return uint8_t 
 */
uint8_t CPU::TAS()
{
    sp = (ax & rx);
    write(addr, sp & (((uint8_t)(addr >> 8)) + 1));

    return 0;
}

/**
 * @brief JAM - Halt the processor
 * 
 * @return uint8_t 
 */
uint8_t CPU::JAM()
{
    halted = true;
    return 0;
}

#include <sstream>
#include <iomanip>

std::string CPU::GetDisassembledInstructions(uint8_t numberOfInstructions)
{
    std::stringstream ss;
    
    uint16_t p = pc;
    uint8_t opcode;

    for (int i = 0; i < numberOfInstructions; i++)
    {
        opcode = read(p);
        ss << "0x" << std::setfill('0') << std::setw(4) << std::hex << p << "\t\t" << lookup[opcode].name;

        // Implicit (nothing)
        if (lookup[opcode].addrmode == &CPU::IMP)
            ;
        // Immediate (#value)
        else if (lookup[opcode].addrmode == &CPU::IMM)
        {
            p++;
            ss << '\t' << '#' << std::setw(2) << std::hex << (int) read(p);
        }
        // Zero page (0x00addr)
        else if (lookup[opcode].addrmode == &CPU::ZP0)
        {
            p++;
            ss << '\t' << "0x" << std::setw(2) << std::hex << (int) read(p);
        }
        // Zero page X (0x00addr, X)
        else if (lookup[opcode].addrmode == &CPU::ZPX)
        {
            p++;
            ss << '\t' << "0x" << std::setw(2) << std::hex << (int) read(p) << ", X";
        }
        // Zero page Y (0x00addr, Y)
        else if (lookup[opcode].addrmode == &CPU::ZPY)
        {
            p++;
            ss << '\t' << "0x" << std::setw(2) << std::hex << (int) read(p) << ", Y";
        }
        // Relative (0xaddr)
        else if (lookup[opcode].addrmode == &CPU::REL)
        {
            p++;
            int8_t offset = read(p);
            ss << '\t' << "0x" << std::setw(4) << std::hex << (int) (p + 1 + offset);
        }
        // Absolute (0xaddr)
        else if (lookup[opcode].addrmode == &CPU::ABS)
        {
            p++;
            uint8_t lo = read(p);
            p++;
            uint8_t hi = read(p);
            uint16_t a = (lo | (hi << 8));

            ss << '\t' << "0x" << std::setw(4) << std::hex << a;
        }
        // Absolute X (0xaddr, X)
        else if (lookup[opcode].addrmode == &CPU::ABX)
        {
            p++;
            uint8_t lo = read(p);
            p++;
            uint8_t hi = read(p);
            uint16_t a = (lo | (hi << 8));

            ss << '\t' << "0x" << std::setw(4) << std::hex << a << ", X";
        }
        // Absolute Y (0xaddr, Y)
        else if (lookup[opcode].addrmode == &CPU::ABY)
        {
            p++;
            uint8_t lo = read(p);
            p++;
            uint8_t hi = read(p);
            uint16_t a = (lo | (hi << 8));

            ss << '\t' << "0x" << std::setw(4) << std::hex << a << ", Y";
        }
        // Indirect ((0xaddr))
        else if (lookup[opcode].addrmode == &CPU::IND)
        {
            p++;
            uint8_t lo = read(p);
            p++;
            uint8_t hi = read(p);
            uint16_t a = (lo | (hi << 8));

            ss << '\t' << "(0x" << std::setw(4) << std::hex << a << ")";
        }
        // Indirect Zero page X ((0x00addr, X))
        else if (lookup[opcode].addrmode == &CPU::IZX)
        {
            p++;
            uint8_t a = read(p);

            ss << '\t' << "(0x" << std::setw(2) << std::hex << (int) a << ", X)";
        }
        // Indirect Zero page Y ((0x00addr), Y)
        else if (lookup[opcode].addrmode == &CPU::IZY)
        {
            p++;
            uint8_t a = read(p);

            ss << '\t' << "(0x" << std::setw(2) << std::hex << (int) a << "), Y";
        }

        ss << std::endl;

        // Move one instruction forward
        p++;
    }

    return ss.str();
}