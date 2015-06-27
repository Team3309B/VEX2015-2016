#include "LCD.c"

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

void 	LCDrunIntroScreen() {
	LCDAnimateFromBottom("WELCOME!", "TEAM 3309 LCD PROGRAM");
	wait1Msec(250);
	LCDAnimateFromBottom("MAIN MENU INCOMING" , ":)");
	wait1Msec(250);
}

void LCDrunMainMenu() {

}

task runLCD(){
	LCDrunIntroScreen();
	LCDrunMainMenu();
	wait1Msec(1500);
	//------------- Beginning of User Interface Code ---------------
	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	//Loop while center button is not pressed, will run continuously until the middle button is pressed
	while(nLCDButtons != centerButton)
	{
		//Switch case that allows the user to choose from 4 different options, this can be changed to add or decrease the number of autos
		switch(LCD.count){
		case 0:
			//Display first choice
			displayLCDCenteredString(0, "Red 8 Point");
			displayLCDCenteredString(1, "<        Enter       >");
			LCDWaitForPress();

			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton) { //since this is option 0, hitting left will bring the LCD to the max option
				LCDWaitForRelease();
				LCD.count = 9;
			}
			else if(nLCDButtons == rightButton)
			{
				LCDWaitForRelease();
				LCD.count += 1;
			}
			break;
		case 1:
			//Display second choice
			displayLCDCenteredString(0, "Blue 8 Point");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDWaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDWaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){
				LCDWaitForRelease();
				LCD.count++;
			}
			break;
		case 2:
			//Display third choice
			displayLCDCenteredString(0, "Red 12 Point");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDWaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDWaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){
				LCDWaitForRelease();
				LCD.count++;
			}
			break;
		case 3:
			//Display fourth choice
			displayLCDCenteredString(0, "Blue 12 Point");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDWaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDWaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				LCDWaitForRelease();
				LCD.count++;
			}
			break;
		case 4:
			//Display fourth choice
			displayLCDCenteredString(0, "Red Strafe Base");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDWaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDWaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				LCDWaitForRelease();
				LCD.count++;
			}
			break;
		case 5:
			//Display fourth choice
			displayLCDCenteredString(0, "Blue Strafe Base");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDWaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDWaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				LCDWaitForRelease();
				LCD.count++;
			}
			break;
		case 6:
			//Display fourth choice
			displayLCDCenteredString(0, "Strafe Right");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDWaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDWaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				LCDWaitForRelease();
				LCD.count++;
			}
			break;
		case 7:
			//Display fourth choice
			displayLCDCenteredString(0, "Strafe Left");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDWaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDWaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				LCDWaitForRelease();
				LCD.count++;
			}
			break;
			case 8:
			//Display fourth choice
			displayLCDCenteredString(0, "Small Pole");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDWaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDWaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				LCDWaitForRelease();
				LCD.count ++;
			}
			break;
		case 9:
			//Display fourth choice
			displayLCDCenteredString(0, "Do Not Move");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDWaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDWaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				LCDWaitForRelease();
				LCD.count = 0;
			}
			break;
		default:
			LCD.count = 0;
			break;
		}
	}
	//------------- End of User Interface Code ---------------------

}
