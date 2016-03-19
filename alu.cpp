#include "alu.h"

alu::alu()
{
	accumulator = 0;
}
void alu::aluAdd(int16_t x)
{
	accumulator += x;
}
void alu::aluSub(int16_t x)
{
	accumulator = accumulator-x;
}
void alu::aluMul(int16_t x)
{
	accumulator = accumulator * x;
}
void alu::aluDiv(int16_t x)
{
	accumulator = accumulator/x;
}
void alu::aluAnd(int16_t x)
{
	accumulator = accumulator & x;
}
void alu::aluXor(int16_t x)
{
	accumulator = accumulator ^ x;
}
void alu::aluOrr(int16_t x)
{
	accumulator = accumulator | x;
}
void alu::setAcc(int16_t x)
{
	accumulator = x;
}
int16_t alu::getAcc()
{
	return accumulator;
}

bool alu::flagIEZ()
{
	return (accumulator==0);
}
bool alu::flagIGZ()
{
	return (accumulator > 0);
}
bool alu::flagILZ()
{
	return (accumulator < 0);
}
bool alu::flagIGE()
{
	return (accumulator >= 0);
}
bool alu::flagILE()
{
	return (accumulator <= 0);
}