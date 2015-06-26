
struct LCDstruct {
	char* line0;
	char* line1;
	int count;
};
LCDstruct LCD;
void LCDinit();
void LCDwaitForRelease();
void LCDwaitForPress();
void animateFromBottom(char* newLine0, char* newLine1);
void animateFromLeft(char* newLine0, char* newLine1);
void animateFromRight(char* newLine0, char* newLine1);
void animateFromTop(char* newLine0, char* newLine1);
