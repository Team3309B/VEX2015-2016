#include "LCD.h"

// Init LCD Screen
void LCDinit() {
	LCD->count = 0;
	LCD->line0 = "";
	LCD->line1 = "";
}

//Wait for Press--------------------------------------------------
void LCDwaitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(25);
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void LCDwaitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(25);
}
//----------------------------------------------------------------
