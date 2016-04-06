#ifndef OPCODES_H
#define OPCODES_H

#define NOP 	0b00000	//NOP,0 - No OP
#define STD		0b00001	//STA,X - Store acc in address X
#define ADD		0b00010	//ADD,X - Add the value in address X to the acc
#define SUB		0b00011	//SUB,X - Subract the value in address X from the acc
#define MUL		0b00100 //MUL,X
#define DIV		0b00101 //DIV,X
#define AND		0b00110 //AND,X
#define XOR		0b00111 //XOR,X
#define ORR		0b01000 //ORR,X
#define SPI		0b01001 //SPI,0 - Raise Stack Pointer
#define SPD		0b01010 //SPD,0 - Lower Stack Pointer
#define	JMR		0b01011 //JMP,X - Jump to the address stored in X
#define LDA		0b01100 //LDA,0	- Load the address in the acc into the acc (dereference)
#define LDR		0b01101 //LDR,X	- Load the value stored at address X into the acc
#define IEZ		0b01110	//IEZ,X - If acc=0, branch to the value in address X
#define	IGZ		0b01111	//IGZ,X	- >
#define ILZ		0b10000 //ILZ,X	- <
#define IGE		0b10001 //IGE,X	- >=
#define ILE		0b10010 //ILE,X	- <=
#define JMA		0b10011 //JMD,0	- Jump to address in the accumulator
#define STR		0b10100 //STR,X	- Store acc in the value held at address X
#define END		0b11111 //END,0	- End program


#include <stdint.h>

#define LINE(opcode,data) ((opcode<<11)|(data & 0x7FF))
//int16_t line(int16_t opcode, int16_t data);

#endif