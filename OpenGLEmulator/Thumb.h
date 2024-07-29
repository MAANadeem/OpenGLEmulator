#pragma once
#include "CPU.h"

bool findOverflow(uint32_t a, uint32_t b, uint32_t result) {
	bool signA = BITS(a, 31, 1);
	bool signB = BITS(b, 31, 1);
	bool signR = BITS(result, 31, 1);
	return  ~(signA ^ signB) & (signA ^ signR);
}

//arithmetic carry
bool findCarryA(u32 op1, u32 op2, bool type) {
	int32_t o1 = op1;
	int32_t o2 = op2;
	if (type == 1) { //subtraction
		return o1 >= o2;
	}
	else {
		return o1 + o2 < o1;
	}
}

//shift carry
bool findCarryS(u32 operand, u32 shift, u8 type) {
	switch (type) {
	//left shift
	case 'l':
		if (shift == 0) return false;
		return BITS(operand, 32 - shift, 1);
	//right shift
	case 'r':
		if (shift == 0) return BITS(operand, 31, 1);
		return BITS(operand, shift - 1, 1);
	}
}


void CPU::ExecuteThumb(const uint16_t opcode) {
	bool carry = 0;
	bool overflow = 0;

	u8 select = BITS(opcode, 13, 3);
	
	switch (select) {

	//formats 1 2
	case 0: {
		u8 op = BITS(opcode, 11, 2);
		u8 middle = BITS(opcode, 6, 5);
		u8 rs = BITS(opcode, 3, 3);
		u8 rd = BITS(opcode, 0, 3);
		uint32_t result;
		switch (op) {
		//shift left
		case 0:
			result = registers[rs] << middle;
			carry = findCarryS(registers[rs], middle, 'l');
			break;
		//logical shift right
		case 1:
			result = middle == 0 ? 0: registers[rs] >> middle;
			carry = findCarryS(registers[rs], middle, 'r');
			break;
		//arithmetic shift right
		case 2: {
			bool neg = BITS(registers[rs], 31, 1);
			carry = findCarryS(registers[rs], middle, 'r');
			uint32_t mask = ~((1 << (32 - middle)) - 1);
			if (middle == 0) middle == 32;
			result = neg ? ((registers[rs] >> middle) | mask)
				: registers[rs] >> middle;
			}
			break;
		//simple add/subtract
		case 3: {
			bool imm = BITS(middle, 4, 1);
			bool sub = BITS(middle, 3, 1);
			uint32_t operand = imm ? middle & 0x07 : registers[middle & 0x07]; //register or immediate
			result = sub ? registers[rs] - operand : registers[rs] + operand;
			carry = findCarryA(registers[rs], operand, sub);
			overflow = findOverflow(registers[rs], operand, result);
			}
			break;
		}
		SetCodes(result, carry, overflow);
		registers[rd] = result;
		break;
	}
	//format 3
	case 1: {
		u8 op = BITS(opcode, 11, 2);
		u8 rd = BITS(opcode, 8, 3);
		u8 imm = BITS(opcode, 0, 8);
		u32 result = registers[rd];
		u32 test = 0;
		switch (op) {
		case 0:
			result = imm;
			break;
		case 1: {
			test = 1;
			result = registers[rd] - imm;
			carry = findCarryA(registers[rd], imm, 1);
			overflow = findOverflow(registers[rd], imm, result);
			break;
		}
		case 2:
			result += imm;
			carry = findCarryA(registers[rd], imm, 0);
			overflow = findOverflow(registers[rd], imm, result);
			break;
		case 3:
			result -= imm;
			carry = findCarryA(registers[rd], imm, 1);
			overflow = findOverflow(registers[rd], imm, result);
			break;
		}
		SetCodes(result, carry, overflow);
		if (test != 0) result = registers[rd];
		registers[rd] = result;
		break;
	}
	//formats 4 5 6 7 8
	case 2: {
		u8 firstBit = BITS(opcode, 12, 1);
		u8 secondBit = BITS(opcode, 11, 1);
		u8 thirdBit = BITS(opcode, 10, 1);
		if (firstBit == 1) {
			//format 7 and 8
		}
		//format 6
		else if (secondBit == 1) {
			u8 rd = BITS(opcode, 8, 3);
			u8 imm = BITS(opcode, 0, 8);
		}
		//format 5
		else if (thirdBit == 1) {
			u8 op = BITS(opcode, 8, 2);
			u8 rs = BITS(opcode, 3, 3);
			u8 rd = BITS(opcode, 0, 3);
			u32 test = registers[rd];
			switch (op) {
			case 0: registers[rd] += registers[rs]; break;
			case 1: 
				test -= registers[rs];
				carry = findCarryA(registers[rd], registers[rs], 1);
				overflow = findOverflow(registers[rd], registers[rs], test);
			case 2: registers[rd] = registers[rs]; break;
			case 3:
			}
		}
		else {
			//format 4
			u8 op = BITS(opcode, 6, 4);
			u8 rs = BITS(opcode, 3, 3);
			u8 rd = BITS(opcode, 0, 3);
			u32 result = registers[rd];
			u32 test = 0;
			u32 od = registers[rd];
			u32 os = registers[rs];

			switch (op) {
			case 0: result = od & os; break;
			case 1: result = od ^ os; break;
			case 2: result = od << os; carry = findCarryS(od, os, 'l'); break;
			case 3: result = od >> os; carry = findCarryS(od, os, 'r'); break;
			//change asr when needed
			case 4: result = ((od >> os) | ~((1 << (32 - os)) - 1)); carry = findCarryS(od, os, 'r'); break;
			case 5: result = od + os + GetFlag(cpsr_flags::C); 
				carry = findCarryA(od, os, 0);
				overflow = findOverflow(od, os, result);
				break;
			case 6: result = od - os - !GetFlag(cpsr_flags::C);
				carry = findCarryA(od, os, 1);
				overflow = findOverflow(od, os, result);
				break;
			case 7: result = os == 0 ? result : (result << (32 - os)) | (result >> os); carry = findCarryS(od, os, 'l'); break;
			case 8: result = od & os; test = 1; break;
			case 9: result = 0 - os;
				carry = findCarryA(0, os, 1);
				overflow = findOverflow(0, os, result);
				break;
			case 10: result = od - os; test = 1;
				carry = findCarryA(od, os, 1);
				overflow = findOverflow(od, os, result);
				break;
			case 11: result = od + os; test = 1;
				carry = findCarryA(od, os, 1);
				overflow = findOverflow(od, os, result);
				break;
			case 12: result = od | os; break;
			case 13: result = od * os; break;
			case 14: result = od & ~os; break;
			case 15: result = ~os; break;

			}
			SetCodes(result, carry, overflow);
			if (test != 0) result = registers[rd];
			registers[rd] = result;
		}
		break;
	}

	//format 9
	case 3:
		break;

	//formats 10 11
	case 4: {
		u8 selectBit = BITS(opcode, 12, 1);
		if (selectBit == 1) {
			//format 11
		}
		else {
			//format 10
		}
		break;
	}

	//formats 12 13 14
	case 5:
		break;

	//formats 15 16 17
	case 6:
		break;

	//formats 18 19
	case 7: {
		u8 selectBit = BITS(opcode, 12, 1);
		if (selectBit == 1) {
			//format 19
		}
		else {
			//format 18
		}
		break;
	}
	}
}