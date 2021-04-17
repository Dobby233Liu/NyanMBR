#include <stdlib.h>
#include <x86.h>

#define lastIntroNote 0+26*2
#define lastNote song_LEN // very last entry in song

unsigned int soundIndex = 0; // NTS: use song only for indexing. NOTE: may want to expand
unsigned short soundWait = 0;

// NOTE: this is supposed to run per tick
void playNote(){
	if (soundIndex > lastNote)
		soundIndex = lastIntroNote; // jump to loop point

	soundWait--;
	if (soundWait != -1) // quirk: not >
		return;

	unsigned short _cursor = song[soundIndex++]; // ax
	// ???: cx <- ah
	unsigned char *freq = (freq >> 8) & 0xff; // ah
	freq = freq & 0x1F; // and ah, 00011111b

	// Set the frequency
	IO_Write(0x42, freq);

	soundWait = soundWait >> 5; // SHR
}

const char* nyanTimeString = "You've Nyaned for 00000.0 seconds!";
const int nyanTimeStringLen = strlen(nyanTimeString) - 1;

#define nyanTimeVideoStart 3840
unsigned int nyanTimeBin = 0
void countNyan(){
	nyanTimeBin++;
	int cursor = nyanTimeStringLen * 2;
	while (cursor > 0){
		cursor -= 2;
		char digit = MEM_Read(0xb800 + nyanTimeVideoStart + cursor);
		if (digit < '0' || digit > '9')
			continue;
		if (++digit == '9'+1)
			digit = '0';
		MEM_Write(0xb800 + nyanTimeVideoStart + cursor, digit);
	}
}

unsigned int frameIndex = 0;
#define frameSize (80*50) / 2 // Raw binary size of a frame
#define lastFrame frames_LEN // very last entry of frames
unsigned short introPlaying = 1;

void displayFrame() {
	if (soundIndex < lastIntroNote && introPlaying) {
		drawIntroFrame();
		return;
	}

	if (introPlaying) {
		// Reset the frame index when the intro is done
		frameIndex = 0;

		// Revert the message characters
		for (int i = 0; i < messageLength; i++)
			MEM_Write(0xb800 + 0x00DC + i, 0);
		
		introPlaying = 0;
	}

	drawNormalFrame();
	
	// Reset frame index when the last frame has been reached
	if (frameIndex > lastFrame)
		frameIndex = 0;
}

// todo: %include "Animation/Image/initDrawing.asm"
// %include "Animation/Image/drawIntroFrame.asm"
// %include "Animation/Image/drawNormalFrame.asm"