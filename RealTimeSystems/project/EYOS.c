#include "stm32f30x.h"

unsigned char Stacks[8][0x200];

unsigned long GlobalTime;
#define MAXGLOBALTIME 0x10000000

struct {
    unsigned int GPR[13];
    void *PC;
    void *LR;
    void *SP;
    unsigned int PSW; // xPSR
} contexts[8];

extern void *Tasks[];
unsigned char tnum;
unsigned char tcur;
typedef void (*func)(void);

void SaveContext(void *conptr);
void RestoreContext(void *conptr);

void OSkernel() {
	if (++GlobalTime >= MAXGLOBALTIME) {
		GlobalTime = 0;
	}
	
	SaveContext(&contexts[tcur]);
	
	tcur = (tcur + 1) % (tnum+1);
	if(tcur == 0)
	{
		tcur = 1;
	}
	
	RestoreContext(&contexts[tcur]);
}

void OSinit() {
    int i;
    
    // context init
    i = 0;
    
    while (Tasks[i] != 0) {
        contexts[i + 1].PC = (void *)(((int) (Tasks[i])) | (1));
        contexts[i + 1].SP = &Stacks[i][0x200 - 4];
        contexts[i + 1].PSW = 0x01000000;
        i++;
    }
    
    tnum = i;
    tcur = 0;
    
	NVIC->ISER[0] |=0x00008000;
	
    for (;;) {
    }
}
