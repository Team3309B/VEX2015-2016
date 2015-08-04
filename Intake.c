
task intakeTask()
{
	while(true) {
		if(isTapped(Button5U) )
			motor[intake] = 127;
		else if(isTapped(Button5D))
			motor[intake] = -127;
		else
			motor[intake] = 0;
	}


}
