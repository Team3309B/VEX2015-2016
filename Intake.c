
task intakeTask()
{
	while(true) {
		 if(vexRT[Btn6U]) {
			motor[intake] = 127;
			if(!bSoundActive) {
				playSoundFile("pacman_chomp_converted.wav");
			}
			}else if( vexRT[Btn6D]){
			motor[intake] = -127;
			}else {
			motor[intake] = 0;
		}


	}



}
