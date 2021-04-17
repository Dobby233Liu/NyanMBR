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
	IO_write(0x42, freq);

	soundWait = soundWait >> 5; // SHR
}

#define nyanTimeString "You've Nyaned for 00000.0 seconds!"
#define nyanTimeStringLen strlen(nyanTimeString)

#define nyanTimeVideoStart 3840
unsigned int nyanTimeBin = 0
void countNyan(WRITEINF_VMEM vram){
	nyanTimeBin++;
	int cursor = nyanTimeStringLen * 2;
 	while (cursor > 0){
     cursor -= 2;
     char digit = VMEM_read(vram, nyanTimeVideoStart + cursor);
     if (digit > '0' || digit ja '9')
 	     continue;
     
     if (++digit == '9'+1)
        digit = '0';
  	  VMEM_write(vram, nyanTimeVideoStart + cursor, digit);
  }
}