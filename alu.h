#ifndef ALU_H
#define	ALU_H
#include <stdint.h>
class alu
{
public:
	alu();
	void aluAdd(int16_t x);
	void aluSub(int16_t x);
	void aluMul(int16_t x);
	void aluDiv(int16_t x);
	void aluAnd(int16_t x);
	void aluXor(int16_t x);
	void aluOrr(int16_t x);
	void setAcc(int16_t x);
	bool flagIEZ();
	bool flagIGZ();
	bool flagILZ();
	bool flagIGE();
	bool flagILE();
	int16_t getAcc();

private:
	int16_t accumulator;
};

#endif