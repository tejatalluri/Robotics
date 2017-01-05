#include<reg52.h>  //header files of microcontroller
#include<stdio.h>   // header files of C
#define lt 0x06;       // User define function
#define rt 0x09;      // User define function
#define st 0x0a;      // User define function
#define stop 0x0f;
#define rev 0x05;     // User define function
unsigned int a;        // Declaring variable globally  
void delay(unsigned int t)
{
	int i,j;
	for(i=0;i<t;i++)
	{
		for(j=0;j<1275;j++);
	}
}	
void main() //main Program  starts
{
while(1)
{
a=P1&0x03;//masking
if(a==0x01)
{
	P2=rev;
	P0=rev;
	delay(50);
	P2=stop;
	P0=P2;
	delay(50);
	P2=lt;
	P0=P2;
	delay(50);
}
if(a==0x02)
{
	P2=rev;
	P0=P2;
                   delay(50);
	P2=stop;
	P0=P2;
	delay(50);
	P2=rt;	
	P0=P2;
	delay(50);

}
if(a==0x03)
{
P2=rev;
P0=P2;
delay(50);
}
if(a==0x00)
                {
               P2=st;
	P0=P2;
	delay(50);
                 }
}
}