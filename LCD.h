#ifndef LCD_HEADER
#define LCD_HEADER
#define MAX_AUTO_COMMANDS 10
struct LCDstruct {
	char* line0; // Top line of LCD Screen
	char* line1; // Bottom line of LCD Screen
	int count; // Used to keep track of what screen of a menu you are on
	string auto[MAX_AUTO_COMMANDS];
	int autoPosition; // Keeps track of next open auto slot
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
void LCDAnimateFromLeft(int line, char* newLine0, char* newLine1);
void LCDAnimateFromRight(int line, char* newLine0, char* newLine1);
void LCDAddAuto( char* autoText );
#endif
