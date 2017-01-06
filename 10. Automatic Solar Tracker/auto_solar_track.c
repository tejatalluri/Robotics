
int base1= 2;    //Motor Connection Pins         
int base2 = 3; 
int top1 = 4;
int top2 = 5;

int LDR1 = A0;   //sensor Pins
int LDR2 = A1;

int a = 420;   //Sensor 1 Normal Lighting Value (High Resistance)
int b = 100;   //Sensor 1 Maximum Lighting Value (Low Resistance)
int c = 200;   //Sensor 2 
int d = 80;   //Sensor 2 Maximum Lighting Value

int x;         //Sensor 1 Present Value
int y;         //Sensor 2 Present Value

void setup()
{
  
  Serial.begin(9600);
  
  pinMode(base1, OUTPUT);   //Motor setup
  pinMode(base2, OUTPUT);
  pinMode(top1, OUTPUT);
  pinMode(top2, OUTPUT);
  
}

void loop()
{
  Serial.print(analogRead(LDR1));  //Sensors Analog Value Display in serial monitor
  Serial.print("\t");
  Serial.print(analogRead(LDR2));
  Serial.println();
  delay(700);
  
  x = analogRead(LDR1);
  y = analogRead(LDR2);

if((y >= d)&&(y <= c))                    //Sensor 2 is High Priority.. whenever sensor 2 detects light, Top motor will tilt towards Clockwise
{
    digitalWrite(top1, LOW);
    digitalWrite(top2, HIGH);
    delay(200); 
    digitalWrite(top1, LOW);
    digitalWrite(top2, LOW);
    delay(100); 
}
if( y < d)                            //Sensor 2 value maximum. so stop
{
  digitalWrite(top1, LOW);
  digitalWrite(top2, LOW);
}

else if (y >= c)                       //when sensor 2 dont have any light then sensor 1 conditions work (low priority)
{
if((x >= (a-30)) && (x <= (a+30)))     //Normal lighting, Base motor rotates
   {
    digitalWrite(base1, HIGH);
    digitalWrite(base2, LOW);
    delay(200); 
    digitalWrite(base1, LOW);
    digitalWrite(base2, LOW);
    delay(100); 
   }   
if((x <= (a-31)) && (x >= b))     //Sensor 1 detects light, Top motor till Clock Wise
{
    digitalWrite(top1, HIGH);
    digitalWrite(top2, LOW);
    delay(200); 
    digitalWrite(top1, LOW);
    digitalWrite(top2, LOW);
    delay(100); 
}
if(x <= b)                        //sensor 1 value maximum, so stop
{
    digitalWrite(top1, LOW);
    digitalWrite(top2, LOW);
}      
if(x >= (a+30))                    //sensor 1 value greater than normal lighting value, so top motor come back home position to get normal lighting
{
    digitalWrite(top1, LOW);
    digitalWrite(top2, HIGH);
    delay(200); 
    digitalWrite(top1, LOW);
    digitalWrite(top2, LOW);
    delay(100); 
}
}  
}
