#include<reg52.h>  //header files of microcontroller
#include<stdio.h>   // header files of C
#define lt 0x06;       // User define function
#define rt 0x09;      // User define function
#define st 0x0a;      // User define function
#define stop 0x0f;
#define rev 0x05;     // User define function
unsigned int a;        // Declaring variable globally  
void main()              //main Program  starts
{
while(1)
{
	a=P0&0x0f;
	if(a==0x06)
	{
		P2=lt;
	}
	if(a==0x09)
	{
		P2=rt;
	}
if(a==0x0a)
	{
		P2=st;
	}
	if(a==0x05)
	{
		P2=rev;
	}
	if(a==0x0f)
	{
		P2=stop;
	}
}
}
