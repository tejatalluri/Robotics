const int pulse = 7;
float watt=0.0,price=0,unit=0;
int pinState = 0; 
unsigned  i=0,j=0;
unsigned long interval=3600000; //1 hour delay
unsigned long previousMillis = 0;
/////////////////////////////////////////////////////////////////////
void setup()
{
 pinMode(pulse, INPUT);
 Serial.begin(9600);
}
///////////////////////////////////////////////////////////////////////
void loop()
{

   unsigned long currentMillis=millis();

   pinState = digitalRead(pulse);
   if(pinState == HIGH)
   {
    i++;
    delay(100);
   }
    if(currentMillis - previousMillis >=interval)                      //  for delay calculation
   {
     j=1;
     previousMillis = currentMillis;
    
   }

   if(j==1)
   {
     watt=(i*0.3125);
     unit=watt/1000;
     price=unit*5;
  Serial.begin(9600);  //Baud rate of the GSM/GPRS Module 
  Serial.print("\r");                
  Serial.println("AT+CMGF=1\r");    
  Serial.println("AT+CMGS=\"9788321231\"\r");    //Number to which you want to send the sms
  delay(100);
  Serial.println("Unit:");   //The text of the message to be sent
  delay(10);
  Serial.println(unit,6);
  delay(10);
  Serial.println("Price:");   //The text of the message to be sent
  delay(10);
  Serial.print(price,6);
  delay(10);
  Serial.print("Rs");   //The text of the message to be sent
  delay(10);
  Serial.write(0x1A);
  delay(100); 
    j=0;
   }
}
