// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Rodolfo Andrés Rivas Matta-Mull.asm
// CDA 3201C - Intro to Logic Design - Fall 2021
// Assignment 4
// 09/30/2021

// My solution is based on my pseudocode:
// x = 0
// LOOP:
// 	if (R1 == 0) goto END
// 	x = x + R0
// 	R1 = R1 - 1
// 	goto LOOP
// END
//
// The result will be in x.
// This pseudocode ran successfully on paper.

// Put your code here.
// Set x = 0 (x being R2)
	@0
	D=A
	@R2
	M=D

// Entering the loop.
(LOOP)
	// if (R1 == 0) goto END
	@R1
	D=M
	@END
	D;JEQ

	// x = x + R0
	@R0
	D=M
	@R2
	M=M+D

	// R1 = R1 - 1
	@R1
	M=M-1

	// goto LOOP
	@LOOP
	0;JMP

// Termination.
(END)
 	@END
 	0;JMP
