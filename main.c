//#include<reg52.h> 
//#define KeyPort P3

//sbit LATCH1=P2^0;
//sbit LATCH2=P2^1;


//unsigned char code Data[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
//// 0123456789  

//unsigned char code Zn_data[]={0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80};
//// знакоместо

//void Delay (unsigned int t)
//{   
// while(--t);
//}
//void main (void)
//{
//	int cur_poz = 0;
//	unsigned char cur_num = Data[0];
//	
//	while(1){
//			
//		
//		P0 = 0xf0;
//		
//		
//		
//		
//		KeyPort = 0x0f;
//		if (KeyPort != 0x0f)
//		{
//					if (KeyPort != 0xf0)
//			{
//				
//				KeyPort = 0x7f;
//				if (KeyPort != 0x7f)
//				{
//					switch(KeyPort)
//					{
//						case 0x77: 				

//							cur_num = Data[5];
//		 
//						break;		
//						
//					
//						case 0x7b: 
//		
//						cur_num = Data[6];
//						
//						break;
//						
//						case 0x7d: 
//							
//							cur_num = Data[7];
//		
//						break;
//						
//						case 0x7e: 

//						cur_num = Data[8];
//		
//						
//						break;
//					}
//					
//					
//					
//					
//					
//				}
//				
//					KeyPort = 0xbf;
//				if (KeyPort != 0xbf)
//				{
//					
//					
//					
//					
//					
//					switch(KeyPort)
//					{
//						case 0xb7: 

//							cur_num = Data[1];
//		
//						break;	
//						
//						
//						case 0xbb: 
//		
//							cur_num = Data[2];
//		
//						break;
//						
//						case 0xbd: 
//							
//						cur_num = Data[3];
//		
//						break;
//						
//						case 0xbe: 
//							
//							cur_num = Data[4];
//		
//						break;
//					}
//				}
//				
//					
//				
//					
//				P1 = Zn_data[cur_poz];
//				
//				if(cur_poz == 7){
//					cur_poz = 0;
//				}
//				else{
//					cur_poz++;
//				}
//				
//					
//				
//					Delay(50000);
//					LATCH2 = 1;	   
//					LATCH2 = 0;
//					
//					P1 = cur_num;
//					
//					LATCH1 = 1;	   
//					LATCH1 = 0;
//				
//					
//					
//					
//				
//			}
//			
//		}
//	

//			
//			
//			
//			
//			
//		
//		
//  }
//	
//}


#include<reg52.h> 
#include<intrins.h>

sbit RS = P2^4;   
sbit RW = P2^3;
sbit EN = P2^2;
sbit P20=P2^0;
sbit P21=P2^1;
sbit P35 = P3^5;

#define RS_CLR RS=0 
#define RS_SET RS=1

#define RW_CLR RW=0 
#define RW_SET RW=1 

#define EN_CLR EN=0
#define EN_SET EN=1

#define DataPort P0

void DelayUs2x(unsigned char t)
{   
 while(--t);
}

void DelayMs(unsigned char t)
{
     
 while(t--)
 {
 
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}

 bit LCD_Check_Busy(void) 
 { 
 DataPort= 0xFF; 
 RS_CLR; 
 RW_SET; 
 EN_CLR; 
 _nop_(); 
 EN_SET;
 return (bit)(DataPort & 0x80);
 }

 void LCD_Write_Com(unsigned char com) 
 {  
 while(LCD_Check_Busy()); 
 RS_CLR; 
 RW_CLR; 
 EN_SET; 
 DataPort= com; 
 _nop_(); 
 EN_CLR;
 }

 void LCD_Write_Data(unsigned char Data) 
 { 
 while(LCD_Check_Busy()); 
 RS_SET; 
 RW_CLR; 
 EN_SET; 
 DataPort= Data; 
 _nop_();
 EN_CLR;
 }


 void LCD_Clear(void) 
 { 
 LCD_Write_Com(0x01); 
 DelayMs(5);
 }

 void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
 {     
 if (y == 0) 
 	{     
	 LCD_Write_Com(0x80 + x);    
 	}
 else 
 	{      
 	LCD_Write_Com(0xC0 + x);     
 	}        
 while (*s) 
 	{     
 LCD_Write_Data( *s);     
 s ++;     
 	}
 }

 void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data) 
 {     
 if (y == 0) 
 	{     
 	LCD_Write_Com(0x80 + x);     
 	}    
 else 
 	{     
 	LCD_Write_Com(0xC0 + x);     
 	}        
 LCD_Write_Data( Data);  
 }

 void LCD_Init(void) 
 {
   LCD_Write_Com(0x38);   
   DelayMs(5); 
   LCD_Write_Com(0x38); 
   DelayMs(5); 
   LCD_Write_Com(0x38); 
   DelayMs(5); 
   LCD_Write_Com(0x38);  
   LCD_Write_Com(0x08);   
   LCD_Write_Com(0x01);   
   LCD_Write_Com(0x06);    
   DelayMs(5); 
   LCD_Write_Com(0x0C);   
   }
   

void main(void) 
{ 
	P1=0x00;
	P20=0; 
	P21=0; 
	P35=0; 
	P1=0xFF;
LCD_Init(); 
LCD_Clear();
while (1) 
 {  
  LCD_Write_Char(7,0,'o');
  LCD_Write_Char(8,0,'k');
  LCD_Write_String(1,1,"HK_Electronics");
  while(1);
 }
}





