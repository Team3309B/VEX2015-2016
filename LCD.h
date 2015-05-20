
struct LCD {
	string line0;
	string line1;
	int count;
};

void LCDinit();
void LCDwaitForRelease();
void LCDwaitForPress();
