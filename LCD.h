
struct LCDstruct {
	string line0;
	string line1;
	int count;
};
LCDstruct LCD;
void LCDinit();
void LCDwaitForRelease();
void LCDwaitForPress();
void animateFromBottom(string newLine0, string newLine1);
