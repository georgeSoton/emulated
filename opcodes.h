#ifndef OPCODES_H
#define OPCODES_H

#define NOP 	0b00000
#define STR		0b00001
#define ADD		0b00010
#define SUB		0b00011
#define MUL		0b00100
#define DIV		0b00101
#define AND		0b00110
#define XOR		0b00111
#define ORR		0b01000
#define SPI		0b01001
#define SPD		0b01010
#define	JMP		0b01011
#define LDA		0b01100
#define LDR		0b01101
#define IEZ		0b01110
#define	IGZ		0b01111
#define ILZ		0b10000
#define IGE		0b10001
#define ILE		0b10010
#define JMD		0b10011
#define END		0b11111


#include <stdint.h>

#define LINE(opcode,data) ((opcode<<11)|(data & 0x7FF))
//int16_t line(int16_t opcode, int16_t data);

#endif