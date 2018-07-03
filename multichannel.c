   #include<reg51.h>
   #include"functions.h"
   #include"lcd.c"
   #include"channels.c"	 
  void main()
{	 
     Adc_init();					  
	 Lcd_Init();
      Lcd_Line_Disp(1,5);
	  Lcddata_Str("GREEN  HOUSE");
      Lcd_Line_Disp(2,6);
	  Lcddata_Str("MONITORING");
	  Delay(150);
	  Lcd_Display_Clear();
	  Lcd_Line_Disp(1,1);
	  Lcddata_Str("CH1:");
      Lcd_Line_Disp(1,10);
	  Lcddata_Str("LUX");
       Lcd_Cursor_off();
      Lcd_Line_Disp(2,1);
	  Lcddata_Str("CH2:");
      Lcd_Line_Disp(2,8);
	  Lcddata_Str("%");
	  Lcd_Cursor_off();
	  Lcd_Line_Disp(2,10);
	  Lcddata_Str("CH3:");
      Lcd_Line_Disp(2,16);
	  Lcddata_Chr(0xdf);
	  Lcd_Cursor_off();
   while (1)
   {

/////////////////////////////////CHANNEL::1////////VOLTAGE////////////////////////////////////////////// 	
	a=0;											  
	b=0;		//CHANNEL 1
	c=0;
	light_fun();
	a=1;	 // CHANNEL 0
	b=0;
	c=0;
	humidity_fun();
 /////////////////////////////////CHANNEL::3///////voltage/////////////////////////////////////////////// 	
	a=0;
	b=1;  	  //CHANNEL 2
	c=0;
	temp_fun();
/////////////////////////////////CHANNEL::5//LIGHT SENSOR////////////////////////////////////////////////	
  }
  }
	 sbit START=P2^0;
	 sbit EOC=P2^1;
	 sbit ALE=P2^2;
	 sbit OE=P2^3;

	 sbit a=P3^5;
 	 sbit b=P3^6;
	 sbit c=P3^7;
 Adc_init()
	  {
	   START=0;
	   EOC=1;
	   ALE=0;
	   OE=0;
	   }
 humidity_fun()
 {
Delay(1);
  ALE=1;
  Delay(1);
  START=1;
  Delay(1);
  ALE=0;
  START=0;
   if(EOC==1)
 {
  OE=1;
  r1=P0;
  Delay(5);
  OE=0;
  r1=r1*(0.01953);
  
  
  RH=r1/0.033;			  
  h1=RH/100;			  
  k=RH%100;
  h2=k/10;
  h3=k%10;
  Lcd_Line_Disp(2,5);  	  
  Lcddata_Chr(h2);
  Lcddata_Chr(h3);
 }
temp_fun()
	{
	   Delay(1);
  ALE=1;
  Delay(1);
  START=1;
  Delay(1);
  ALE=0;
  START=0;
 if(EOC==1)
 { 
  OE=1;
  r1=P0;
  Delay(5);
  OE=0;
  r1=r1*(0.01953);
 r3=r1*100;
  k=r3/10;
  t3=k/10;
  t2=k%10;
  t1=r3%10;  
  Lcd_Line_Disp(2,14);
  Lcddata_Chr(t2);
  Lcddata_Chr(t1);
   } 
light_fun()
	{
	unsigned int a1,b1,c1,i;		 
  Delay(1);
  ALE=1;
  Delay(1);
  START=1;
  Delay(1);
  ALE=0;
  START=0;
 for(i=0;i<1000;i++);
 for(i=0;i<1000;i++);
 while(EOC==1);
  while(EOC==0);
  OE=1;
    r1=P0;
    Delay(5);
    OE=0;
    r1=r1*(0.01953);    //r1,r2,r3,k,d1,d2,d3
    a1=1900/r1;
    b1=a1-700;
    c1=b1/2.2;
    lux= c1;                       
    d4=lux/1000;
    k=lux%1000;
d3=k/100;
p=k%100;
d2=p/10;
d1=p%10;
Lcd_Line_Disp(1,5);  
Lcddata_Chr(d4);
Lcddata_Chr(d3);
Lcddata_Chr(d2);
Lcddata_Chr(d1);
}
sfr ldata=0X90;//PORT 1
sbit rs=P2^5;
sbit rw=P2^6;
sbit en=P2^7;
Lcd_Init()
  {        
Lcddata_Cmd(0x38);		
Lcddata_Cmd(0x0E);
Lcddata_Cmd(0x01);
//lcdcmd(0x80);
   }
///////////////////////////////////////////////////////////////////

Lcddata_Chr(unsigned char value)
		{
		ldata=value;
		rs=1;
		rw=0;
		en=1;
		Delay(1);
		en=0;
		Delay(1);
		return;
		}	
/////////////////////////////////////////////////////////////////// 
Delay(unsigned int k)
		{
		int i,j;
		for (i=0;i<=k;i++)
		for (j=0;j<=1275;j++);
		}
///////////////////////////////////////////////////////////////////////////	
Lcddata_Cmd(unsigned char value)
		{
		ldata=value;
		rs=0;
		rw=0;
		en=1;
		Delay(1);
		en=0;
return;
		}						   
///////////////////////////////////////////////////////////////////////////
 Lcddata_Str(char *temp) 
    {
while(*temp!='\0')
	{			   
	ldata=*temp;	 
rs=1;
rw=0;
en=1;
Delay(1);
en=0;
temp++;
}
}
//////////////////////////////////////////////////////////////////////////
Lcd_Cursor_off()
{
 Lcddata_Cmd(0x0C);
}
/////////////////////////////////////////////////////////////////////////
Lcd_Display_Clear()
{
Lcddata_Cmd(0x01);
}
////////////////////////////////////////////////////////////////////////
Lcd_Line_Disp(unsigned int line,unsigned int position)
{
if(line==1)
{
 Lcddata_Cmd(0x7F+position);
}
if(line==2)
{
 Lcddata_Cmd(0xBF+position);
}
if(line==3)
{
 Lcddata_Cmd(0x93+position);
}
if(line==4)
{
 Lcddata_Cmd(0xD3+position);
}
}
///////////////////////////////////////////////////////////////////////////
Lcd_Line_Clear(unsigned int clear)
{
  if(clear==1)
  {
   Lcddata_Cmd(0x80);
   Lcddata_Str("                    ");
  }
   if(clear==2)
  {
   Lcddata_Cmd(0xc0);
   Lcddata_Str("                    ");
  }
  if(clear==3)
  {
   Lcddata_Cmd(0x94);
   Lcddata_Str("                    ");
  }
   if(clear==4)
  {
   Lcddata_Cmd(0xd4);
   Lcddata_Str("                    ");
  }
}
////////////////////////////////////////////////////////////////////////////// 
