const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

//Wait for Press--------------------------------------------------
void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void waitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(5);
}
//----------------------------------------------------------------

int count = 0;

/*
//This tasks begins running in usercontrol, from there, it continously runs until an auto has been selected.
//as soon as middle has been selected, the loop stops, and the auto is locked in

//count keeps track of which auto the lcd screen is on
//once the middle button is pressed, count will still keep track of which auto screen the lcd was on before middle was pressed

//however, all this lcd loop does is set the count variable.  This does not actually change anything in auto.
//You must alter your own autonomous method to link up with this count variable.

//Each auto should have a code.  For example, in our code:
0 = 8 Red Point
1 = 8 Blue Point
2 = 12 Red Point
3 = 12 Blue Point

//Refer to AUTO.c to see how our code chooses which auto to use based on count. look at startauton
*/
task runLCD(){
	//Declare count variable to keep track of our choice

	//------------- Beginning of User Interface Code ---------------
	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	//Loop while center button is not pressed, will run continuously until the middle button is pressed
	while(nLCDButtons != centerButton)
	{
		//Switch case that allows the user to choose from 4 different options, this can be changed to add or decrease the number of autos
		switch(count){
		case 0:
			//Display first choice
			displayLCDCenteredString(0, "Nothing");
			displayLCDCenteredString(1, "<        Enter       >");
			waitForPress();

			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton) { //since this is option 0, hitting left will bring the LCD to the max option
				waitForRelease();
				count = 13;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			break;
		case 1:
			//Display second choice
			displayLCDCenteredString(0, "Red Main");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){
				waitForRelease();
				count++;
			}
			break;
		case 2:
			//Display third choice
			displayLCDCenteredString(0, "Blue Red");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){
				waitForRelease();
				count++;
			}
			break;
		case 3:
			//Display fourth choice
			displayLCDCenteredString(0, "Red Side");

			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				waitForRelease();
				count++;
			}
			break;
		case 4:
			//Display fourth choice
			displayLCDCenteredString(0, "Blue Side");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				waitForRelease();
				count++;
			}
			break;
		case 5:
			//Display fourth choice
			displayLCDCenteredString(0, "Red X Pole");

			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				waitForRelease();
				count++;
			}
			break;
		case 6:
			//Display fourth choice
			displayLCDCenteredString(0, "Blue X Pole");

			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				waitForRelease();
				count++;
			}
			break;
		case 7:
			//Display fourth choice
			displayLCDCenteredString(0, "Shoot Preloads");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				waitForRelease();
				count++;
			}
			break;
		case 8:
			//Display fourth choice
			displayLCDCenteredString(0, "Pre and Go");

			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				waitForRelease();
				count++;
			}
			break;
		case 9:
			//Display fourth choice
			displayLCDCenteredString(0, "Pre And Go Bam");

			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				waitForRelease();
				count++;
			}
			break;
		case 10:
			//Display fourth choice
			displayLCDCenteredString(0, "Attack Pole");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				waitForRelease();
				count++;
			}
			break;
		case 11:
			//Display fourth choice
			displayLCDCenteredString(0, "Team A Block");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				waitForRelease();
				count++;
			}
			break;
		case 12:
			//Display fourth choice
			displayLCDCenteredString(0, "SP");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				waitForRelease();
				count++;
			}
			break;
		case 13:
			//Display fourth choice
			displayLCDCenteredString(0, "Aim And Shoot");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){ //since this is the max choice, moving right will loop back to beginning again
				waitForRelease();
				count = 0;
			}
			break;
		default:
			count = 0;
			break;
		}
	}
	//------------- End of User Interface Code ---------------------

}
