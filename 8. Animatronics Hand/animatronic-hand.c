#include <Servo.h>	// Header file is added to Access the servo motor
Servo servo1;			// Initializing the servo with Servo 1
Servo servo2;			// Initializing the servo with Servo 2
Servo servo3; 			// Initializing the servo with Servo 3
int a=A0;				// Value in A0 pin will be stored to “a”
int b=A1;				// Value in A1 pin will be stored to “b”
int c=A2;				// Value in A2 pin will be stored to “c”
int val1=0;				// Setting the “val1” variable to zero
int val2=0;				// Setting the “val2”  variable to zero
int val3=0;				// Setting the “val2” variable to zero

void setup()				// One time processing function is set in void setup 
{								// Opening the loop for function
   servo1.attach(10);		// Connecting the Servo1 motor to 10 pin
   servo2.attach(11);		// Connecting the Servo2 motor to 11 pin
   servo3.attach(9);		// Connecting the Servo3 motor to 9 pin
   servo1.write(0);		// Setting the Position of Servo1 to 0 degree
   servo2.write(0);		// Setting the Position of Servo2 to 0 degree
   servo3.write(0);		// Setting the Position of Servo3 to 0 degree
   Serial.begin(9600);   	// Setting the baud rate for serial communication
}								// Closing the loop 

void loop()				// Looping function
{								// Open the Loop	
val1=analogRead(a);	// Read the analog value in “a” & store in “val1” variable
val2=analogRead(b);	// Read the analog value in “b” & store in “val2” variable
val3=analogRead(c);	// Read the analog value in “c” & store in “val3” variable

if(val1<40)				// If condition checks, if val1 is less than 40 or not
{								//Open the loop for IF condition
   servo1.write(180);	// Making Servo1 motor to move towards 180o degree 
   delay(3);				// Delay is given for 3 milli seconds
}								// Close the loop for IF condition

if(val2>200)
{
  servo2.write(0);
  delay(3);
}  

if(val3<40)
  {
   servo3.write(0);
   delay(3);
  } 

  if(val3>200)
{
  servo3.write(180);
  delay(3);
}
}								// Close the Loop

