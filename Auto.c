
void startauton()
{
	x = startx;
	y = starty;
	//for (int i = 0; i < LCD.
	runShooterAt(120);
	wait1Msec(2000);
	setElevator(70);
	wait1Msec(6000);
	setElevator(0);
	runShooterAt(0);
}
