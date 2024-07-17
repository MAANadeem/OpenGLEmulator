#pragma once
#include <cstdint>
#include <array>

//if needed, implement Fast Interrupt Request Mode

struct CPU {
	enum cpsr_flags {
		N = (1 << 31), //Negative / less than
		Z = (1 << 30), //Zero
		C = (1 << 29), //Carry or borrow or extend
		V = (1 << 28), //Overflow
		I = (1 << 7),  //IRQ disable
		F = (1 << 6),  //FIQ disable
		T = (1 << 5),  //State bit

		M4 = (1 << 4),
		M3 = (1 << 3),
		M2 = (1 << 2),
		M1 = (1 << 1),
		M0 = (1 << 0), //Mode bits
	};

	uint32_t pc; //program counter
	uint32_t cpsr; //current program status register
	std::array<uint32_t, 13> registers;

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

	void Reset();
	void SoftwareInterrupt();
	void InterruptRequest();

	//most likely don't need these
		//void UndefinedInstruction();
		//void PrefetchDataAbort();
		//void FastInterruptRequest();
};

