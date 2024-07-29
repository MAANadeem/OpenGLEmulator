#include "CPU.h"
#include "Thumb.h"
#include "Arm.h"

bool CPU::GetFlag(cpsr_flags f) {
	return ((cpsr & f) > 0) ? 1 : 0;
}
void CPU::SetFlag(cpsr_flags f, bool v) {
	cpsr = v ? cpsr | f : cpsr & ~f;
}
uint32_t CPU::GetReg(int index) {
	return registers[index];
}

void CPU::SetCodes(u32 result, bool carry, bool overflow) {
	SetFlag(cpsr_flags::N, BITS(result, 31, 1));
	SetFlag(cpsr_flags::Z, result == 0);
	SetFlag(cpsr_flags::C, carry);
	SetFlag(cpsr_flags::V, overflow);
}

void CPU::Clock() {

}
void CPU::Reset() {

}
void CPU::SoftwareInterrupt() {

}
void CPU::InterruptRequest() {

}