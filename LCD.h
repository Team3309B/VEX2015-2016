#ifndef LCD_HEADER
#define LCD_HEADER
struct LCDstruct {
	char* line0; // Top line of LCD Screen
	char* line1; // Bottom line of LCD Screen
	int count; // Used to keep track of what screen of a menu you are on
	string auto[5];
};
LCDstruct LCD;
void LCDInit();
void LCDWaitForRelease();
void LCDWaitForPress();
void LCDClear0();
void LCDClear1();
void LCDClear();
void LCDSetLine01(char* newLine0, char* newLine1);
void LCDSetLine10(char*  newLine1, char*  newLine0);
void LCDSetLine0(char*  newLine0);
void LCDSetLine1(char*  newLine1);
void LCDAnimateFromBottom(char* newLine0, char* newLine1);
void LCDAnimateFromLeft(char* newLine0, char* newLine1);
void LCDAnimateFromRight(char* newLine0, char* newLine1);
void LCDAnimateFromTop(char* newLine0, char* newLine1);
#endif
