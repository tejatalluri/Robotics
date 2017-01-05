#include<reg52.h>		//Header file
#include<stdio.h>
#define fwd 0x0a;		//Motor Conditions
#define lt 0x06;
#define rt 0x09;
#define rev 0x05;
#define stop 0x00;
unsigned int a;
void main()
{
while(1)
{
a=P0&0x0f;		//Masking
if(a==0x02)		//DTMF Input
{
P2=fwd;		//Motor Condition
}
if(a==0x04)
{
P2=lt;
}
if(a==0x06)
{
P2=rt;
}
if(a==0x08)
{
P2=rev;
}
if(a==0x05)
{
P2=stop;
}
}
}
