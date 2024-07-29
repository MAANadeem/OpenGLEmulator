#pragma once
#include <cstdint>
#include <array>

//if needed, implement Fast Interrupt Request Mode

#define BITS(x, b, n) ((x >> b) & ((1 << n) - 1)) //retrieves n bits from x starting at bit b

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

class CPU {
public:
	enum cpsr_flags {
		N = (1 << 31), //Negative / less than
		Z = (1 << 30), //Zero
		C = (1 << 29), //Carry or borrow or extend
		V = (1 << 28), //Overflow
		I = (1 << 7),  //IRQ disable
		F = (1 << 6),  //FIQ disable
		T = (1 << 5),  //State bit (arm/thumb mode)

		M4 = (1 << 4),
		M3 = (1 << 3),
		M2 = (1 << 2),
		M1 = (1 << 1),
		M0 = (1 << 0), //Mode bits
	};

	uint32_t pc; //program counter
	uint32_t cpsr; //current program status register
	std::array<uint32_t, 13> registers; //open registers 0 - 12

	//User Mode
	uint32_t sp; //stack pointer 
	uint32_t lr; //link register
	
	//Supervisor Mode
	uint32_t sp_svc;
	uint32_t lr_svc;
	uint32_t SPSR_svc;

	//Interupt Mode
	uint32_t sp_irq;
	uint32_t lr_irq;
	uint32_t SPSR_iqr;

	//most likely don't need these
		//void UndefinedInstruction();
		//void PrefetchDataAbort();
		//void FastInterruptRequest();

public:
	void Clock();
	void Reset();
	void SoftwareInterrupt();
	void InterruptRequest();

	void ExecuteThumb(const uint16_t opcode);
	void ExecuteArm(const uint32_t opcode);
	
	uint32_t GetReg(int index);

public:
	void SetFlag(cpsr_flags f, bool v);
	bool GetFlag(cpsr_flags f);

	void SetCodes(u32 result, bool carry, bool overflow);
};

