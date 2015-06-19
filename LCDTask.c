#include "LCD.c"

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;








/*
//This tasks begins running in usercontrol, from there, it continously runs until an auto has been selected.
//as soon as middle has been selected, the loop stops, and the auto is locked in
//LCD.count keeps track of which auto the lcd screen is on
//once the middle button is pressed, LCD.count will still keep track of which auto screen the lcd was on before middle was pressed
//however, all this lcd loop does is set the LCD.count variable.  This does not actually change anything in auto.
//You must alter your own autonomous method to link up with this LCD.count variable.
//Each auto should have a code.  For example, in our code:
0 = 8 Red Point
1 = 8 Blue Point
2 = 12 Red Point
3 = 12 Blue Point
//Refer to AUTO.c to see how our code chooses which auto to use based on LCD.count. look at startauton
*/
task runLCD(){
	displayLCDCenteredString(0, "Welcome!");
	wait1Msec(700);
	clearLCDLine(0);
	displayLCDCenteredString(0, "Time to pick auto!");
	displayLCDCenteredString(1, "Default auto is no move");
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
			LCDwaitForPress();

			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton) { //since this is option 0, hitting left will bring the LCD to the max option
				LCDwaitForRelease();
				LCD.count = 9;
			}
			else if(nLCDButtons == rightButton)
			{
				LCDwaitForRelease();
				LCD.count += 1;
			}
			break;
		case 1:
			//Display second choice
			displayLCDCenteredString(0, "Blue 8 Point");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDwaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDwaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){
				LCDwaitForRelease();
				LCD.count++;
			}
			break;
		case 2:
			//Display third choice
			displayLCDCenteredString(0, "Red 12 Point");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDwaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDwaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){
				LCDwaitForRelease();
				LCD.count++;
			}
			break;
		case 3:
			//Display fourth choice
			displayLCDCenteredString(0, "Blue 12 Point");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDwaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDwaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				LCDwaitForRelease();
				LCD.count++;
			}
			break;
		case 4:
			//Display fourth choice
			displayLCDCenteredString(0, "Red Strafe Base");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDwaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDwaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				LCDwaitForRelease();
				LCD.count++;
			}
			break;
		case 5:
			//Display fourth choice
			displayLCDCenteredString(0, "Blue Strafe Base");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDwaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDwaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				LCDwaitForRelease();
				LCD.count++;
			}
			break;
		case 6:
			//Display fourth choice
			displayLCDCenteredString(0, "Strafe Right");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDwaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDwaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				LCDwaitForRelease();
				LCD.count++;
			}
			break;
		case 7:
			//Display fourth choice
			displayLCDCenteredString(0, "Strafe Left");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDwaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDwaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				LCDwaitForRelease();
				LCD.count++;
			}
			break;
			case 8:
			//Display fourth choice
			displayLCDCenteredString(0, "Small Pole");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDwaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDwaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				LCDwaitForRelease();
				LCD.count ++;
			}
			break;
		case 9:
			//Display fourth choice
			displayLCDCenteredString(0, "Do Not Move");
			displayLCDCenteredString(1, "<         Enter        >");
			LCDwaitForPress();
			//Increment or decrement "LCD.count" based on button press
			if(nLCDButtons == leftButton){
				LCDwaitForRelease();
				LCD.count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				LCDwaitForRelease();
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
