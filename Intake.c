
task intakeTask()
{
	while(true) {
		if( vexRT[Btn5UXmtr2] ) {
			motor[intake] = 127;
			}else if( vexRT[Btn5DXmtr2]){
			motor[intake] = -127;
			}else if(vexRT[Btn5U]) {
			motor[intake] = 127;
			}else if( vexRT[Btn5D]){
			motor[intake] = -127;
			}else if( vexRT[Btn6UXmtr2] ) {
			motor[intake] = 127;
			}else if( vexRT[Btn6DXmtr2]){
			motor[intake] = -127;
			}else if(vexRT[Btn6U]) {
			motor[intake] = 63;
			}else if( vexRT[Btn6D]){
			motor[intake] = -63;
			}else {
			motor[intake] = 0;
		}
	}



}
