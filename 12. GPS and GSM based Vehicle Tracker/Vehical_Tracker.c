#include <Arduino.h>
#include <avr/pgmspace.h>
#include <SoftwareSerial.h>  // Used to allow serial communication on other digital pins of the Arduino Uno
#include <TinyGPS++.h>       // This library compact and easy-to-use methods for extracting position, date, time, altitude, speed, and course form consumer GPS devices


//Constants

const unsigned int textScanTimeout = 15UL; // secs between scans for inbound texts


//Global Variables

TinyGPSPlus gps;                  // Create a GPS instance
char s[80];                       // Generic buffer
SoftwareSerial ssGprs(7,8);       // Serial Communication pins to which the Gprs modem is connected (Rx,Tx)
SoftwareSerial ssGps(4,3);        // Serial COmmunication pins to which the GPS module is connected (Rx,Tx)


//Forward Declerations

void delOldSms();
void doGpsIo();
void gpsTest();
void powerUpSms();
int8_t sentAtCmd(char* atCmd, char* matchStr, unsigned int timeout);


// Process Gpa's Output

void doGpsTo() {

char c;

//accept each character from GPS and send to the GPS decoder

while (ssGps.available() > 0) {
    c=ssGps.read();
    Serial.print(c);
    gps.encode(c);
    }
} // doGpsIo


//Function to send AT commands to the GSM Module
int8_t sendAtCmd(char* atCmd, char* matchStr, unsigned int timeout) {
char c;
uint8_t x = 0;
uint8_t answer = 0;
unsigned long previous;

delay(100);

while(ssGprs.available() > 0)  // flush  the receive buffer
ssGprs.read();

ssGprs.print(atCmd);           // send the AT command

previous = millis();

// this loop waits for the answer

do {
if (x== sizeof(s)-1){
    Serial.println(F("**S buffer overflow**"));
    while(true){}
    }
// if there is data in the input buffer, read it and check for the answer


if(ssGprs.available()!=0){

c=ssGprs.read();
if(c == '\r' || c == '\n')         // if full line is read without finding text, clear the buffer
x=0;
s[x] = c;
s[x+1] = '\0';                     // GSM response is stored in the array "s"

if( strstr(s, matchStr) != NULL)   // Check if the desired answer is in the response of the GSM 

    answer = 1;

    }

    x = x+1;
}

// Waits for the answer with time out 

} while ((answer ==0) && ((millis() - previous) < timeout));

return answer;

} // sendAtCmd

// Check wheather the GSM module is powered on 

void poweUpSms()

const int onModulePin = 9;
uint8_t answer = 0;

// check if module is started

answer = sendAtCmd("AT","OK",2000);

if (answer ==0) {

   //power on pulse

    digitalWrite(onModulePin, HIGH);
    delay(3000);
    digitalWrite(onModulePin, LOW);

    //waits for an answer from the module

while (answer == 0) { // send AT every two seconds and wait for the answer
    answer = sendAtCmd("AT", "OK", 2000);
}

    }

} // powerUpSms

// Delete all text messages from server

void delOldSms() {
sendAtCmd("at+cmgda =  \"DEL ALL\"","OK", 5000);

} //delOldSms

// send coordinates via text message

void send Coord(

 {
 int8_t answer;
 
 sendAtCmd("AT+CMGF=1", "OK", 1000); // sets the SMS mode to text
 
 answer = sendAtCmd("AT+CMGS=\"Phone Number\"", ">", 2000);
 
 if(answer == 1){
 
    ssGprs.print(F("https://www.google.com/maps/?q="));
    ssGprs.print(gps.location.lat(),6);
    ssGprs.print(F(",");
    ssGprs.print(gps.location.lng(),6);
    ssGprs.print(F(";"));
    ssGprs.write(0X1A);
    answer = sendAtCmd("","OK",20000);
    if(answer == 1)
       Serial.println(F(" SMS Sent"));
 
       else
 
        Serial.println(F(" SMS Send Error));

 }
 
 } // sendCoord
 
 void setup() {
 Serial.begin(19200);  // Baud rate of the Serial port of the Arduino board
 ssGprs.begin(4800);   // Baud rate of the GSM Module
 ssGps.begin(4800);    // Baud rate of the GPS Module
 
 ssGprs.listen();      // Listen to the GPRS Rx pin
 powerUpSms();         // Wait for the GSM Module to power on
 delOldSms();          // Deleting and waiting SMS messages
 ssGps.listen();       // Listen to the GPS Rx pin
 } // setup
 
 // If any waiting texts, send coordinates
 
 void doSmsMsg() {
 
 if (SendAtCmd("at+cmg1=\"All\"","+CMGL:",5000) ==1) { // If new text is found, respond by sending coordinates
    Serial.println("New SMS Found");
	sendCoord();
	delOldSms();
	}
 } //doSmsMsg
 
 // loop
 
 void loop() {
 char c; 
 unsigned long timeout = OUL;
 
 Serial.println("Press 'T' to send coordiantes via text.");
 
 while(true) {
    
	if(Serial.available()) {
	c = Serial.read();
	while (Serial.available())
	Serial.read();
	if(c == 'T' || c == 't') {
	ssGprs.listen();              // Listen to GSM Module while we send coordinates
	sendCoord();                  // send coordinates as SMS message
	ssGps.listen();               // go back to listening to GPS
	
	}
	
	}
	
doGpsIo();                            // Decode next gps character
if (millis() > timeout) {             // Every timeout secs, check for SMS
    ssGprs.listen();                  // start listening to GSM Module
	doSmsMsg(); 
	ssGps.listen();               // Go back to listening to GPS
	timeout = millis() + textScanTimeout * 1000UL;
	
	}
	
	
	} // main while
	
	} // loop





