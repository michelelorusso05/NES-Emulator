#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Bus;

class CPU {
public:
    CPU(Bus* master);

    enum FLAGS
    {
        // Carry
        C = (1 << 0),
        // Zero
        Z = (1 << 1),
        // Interrupt disable
        I = (1 << 2),
        // Decimal (not implemented)
        D = (1 << 3),
        // CPU processing during interrupt
        B = (1 << 4),
        // Unused
        U = (1 << 5),
        // Overflow
        V = (1 << 6),
        // Negative
        N = (1 << 7)
    };

    // Addressing modes
    uint8_t IMP(); uint8_t IMM();
    uint8_t ZP0(); uint8_t ZPX();
    uint8_t ZPY(); uint8_t REL();
    uint8_t ABS(); uint8_t ABX();
    uint8_t ABY(); uint8_t IND();
    uint8_t IZX(); uint8_t IZY();

    // Instructions
    uint8_t ADC(); uint8_t AND(); uint8_t ASL(); uint8_t BCC();
    uint8_t BCS(); uint8_t BEQ(); uint8_t BIT(); uint8_t BMI();
    uint8_t BNE(); uint8_t BPL(); uint8_t BRK(); uint8_t BVC();
    uint8_t BVS(); uint8_t CLC(); uint8_t CLD(); uint8_t CLI();
    uint8_t CLV(); uint8_t CMP(); uint8_t CPX(); uint8_t CPY();
    uint8_t DEC(); uint8_t DEX(); uint8_t DEY(); uint8_t EOR();
    uint8_t INC(); uint8_t INX(); uint8_t INY(); uint8_t JMP();
    uint8_t JSR(); uint8_t LDA(); uint8_t LDX(); uint8_t LDY();
    uint8_t LSR(); uint8_t NOP(); uint8_t ORA(); uint8_t PHA();
    uint8_t PHP(); uint8_t PLA(); uint8_t PLP(); uint8_t ROL();
    uint8_t ROR(); uint8_t RTI(); uint8_t RTS(); uint8_t SBC();
    uint8_t SEC(); uint8_t SED(); uint8_t SEI(); uint8_t STA();
    uint8_t STX(); uint8_t STY(); uint8_t TAX(); uint8_t TAY();
    uint8_t TSX(); uint8_t TXA(); uint8_t TXS(); uint8_t TYA();

    // Invalid opcodes
    // Common ones (tested by NESTEST.nes)
    uint8_t LAX(); uint8_t SAX(); uint8_t DCP(); uint8_t ISB();
    uint8_t SLO(); uint8_t RLA(); uint8_t SRE(); uint8_t RRA();

    // Uncommon ones (tested by Blargg's test suite)
    uint8_t ANC(); uint8_t ALR(); uint8_t ARR(); uint8_t ANE();
    uint8_t TAS(); uint8_t LXA(); uint8_t LAS(); uint8_t SBX();
    uint8_t SHX(); uint8_t SHA(); uint8_t SHY();

    // JAM
    uint8_t JAM();

    void clock();
    void reset();
    void irq();
    void nmi();

    void halt(bool set) 
    {
        halted = set;
    };

    void clockUntilInstruction();

    // Accumulator
    uint8_t ax = 0x00;
    // Registers
    uint8_t rx = 0x00;
    uint8_t ry = 0x00;
    // Stack pointer
    uint8_t sp = 0x0000;
    // Program counter
    uint16_t pc = 0x0000;
    // Status byte
    uint8_t status = 0x00;

    uint16_t cycles = 0;
    uint8_t opcode = 0;

    uint16_t addr = 0x0000;
    int8_t rel = 0;

    std::string* GetMnemonicForOpcode(uint8_t op)
    {
        return &(lookup[op].name);
    }

    bool isInBRK = false;

    bool irqPending = false;
    bool nmiPending = false;
    bool prevNmiPending = false;
    bool nmiRunning = false;
    bool irqRunning = false;
    bool prevNmiRunning = false;

private:
    bool halted = false;
    bool inhibitIFlag = false;

    Bus* bus = nullptr;

    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);

    uint8_t GetFlag(FLAGS f);
    void SetFlag(FLAGS f, bool s);

    uint8_t fetch();
    uint8_t fetched;


    struct INSTR
    {
        std::string name;
        uint8_t (CPU::*operate)(void) = nullptr;
        uint8_t (CPU::*addrmode)(void) = nullptr;
        uint8_t cycles = 0;
    };

    std::vector<INSTR> lookup;
};