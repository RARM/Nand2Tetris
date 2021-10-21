// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed.
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Rodolfo Andrés Rivas Matta-Fill.asm
// CDA 3201C - Intro to Logic Design - Fall 2021
// Assignment 4
// 09/30/2021


// Notes by Rodolfo Andrés Rivas Matta:
// Some observations of the Hack Machine:
// Total RAM registers of the Hack machine = 16384 (That's 16K, addresses from 0 to 16383)
//
// SCREEN = address 16384 (hex value 0x4000)
// 	The screen is 256 rows of 512 pixels (32 registers of 16 bit) per row.
// 	Therefore, it is a total of 8192 registers (that's 8K) for the memory map.
// 	The last register would be at address 24,575 (hex value 0x6000 minus 1)
//
// KBD = address 24,576 (hex value 0x6000)
//
// My pseudocode below:
//
// goto LISTEN // Ensures first draw.
// START:
// 	if (color == 0 AND RAM[KBD] == 0 OR color != 0 AND RAM[KBD] != 0) goto START
// 		// The previous condition uses precedence of logical operators.
// 		// It avoids rewritting on the screen. In other words, it just
// 		// updates the screen if there has been a change.
// LISTEN:
// 	color = (RAM[KBD] == 0) ? 0 : -1
// 	position = KBD - 1 // Right where the screen ends.
// LOOP: // This is the drawing.
// 	if (postion < SCREEN) goto START
// 	RAM[position] = color
// 	position--
// 	goto LOOP
//
//
// The pseudocode above is considerably condensed. Some operations
// come from C/C++. However, these can be implemented in the Hack
// Assembly language. As demostrated below.
//
// Note, though, that the pseudocode is divided in three parts: the
// checking (START), the update (LISTEN), and the drawing (LOOP).
// Throughout the program the variable color will contain the current
// state of the whole screen (1 when it is dark and 0 when it is white).
//
// KBD will be saved in the virtual register R0 for the comparison
// to keep the value of KBD untouched during the comparisons.



// My source-code --------------------------------------------------------
	// goto LISTEN
	@LISTEN
	0;JMP

(START)
	// if (color == 0 AND RAM[KBD] == 0 OR color != 0 AND RAM[KBD] != 0) goto START

	// Saving the status of RAM[KBD].
	@KBD
	D=M
	@R0
	M=D

	// color == 0 AND RAM[KBD] == 0
	@color
	D=M
	@R0
	D=D-M // It should give 0 only if color and KBD are 0 and <0 otherwise.

	@START
	D;JEQ // Short-circuit.

	// color != 0 AND RAM[KBD] != 0
	@color
	D=M
	@LISTEN
	D;JEQ // Jump if color == 0. Short-circuiting principle again.

	@R0
	D=M
	@LISTEN
	D;JEQ // Same as color == 0, but for RAM[KBD] == 0.

	// goto START
	@START
	0;JMP

(LISTEN)
	// 	color = (RAM[KBD] == 0) ? 0 : -1
	@KBD
	D=M
	@CLRFLS // Color False.
	D;JNE

	@color // color = 0
	M=0
	@CLREND // Color end of ternary operator.
	0;JMP

	(CLRFLS) // color = -1
	@color
	M=-1

	(CLREND)

	@KBD // position = KBD - 1
	D=A  // Right where the screen ends.
	@position
	M=D-1

(LOOP) // This is the drawing.
	// if (postion < SCREEN) goto START
	@position
	D=M
	@SCREEN
	D=D-A
	@START
	D;JLT

	// 	RAM[position] = color
	@color
	D=M
	@position
	A=M
	M=D

	// 	position--
	@position
	M=M-1

	// 	goto LOOP
	@LOOP
	0;JMP
