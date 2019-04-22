#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "usmart.h"	 
#include "24cxx.h"	 

/************************************************
 ALIENTEK��ӢSTM32������ʵ��22
 IIC ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

			 	
//Ҫд�뵽24c02���ַ�������
const u8 TEXT_Buffer[]={"Elite STM32 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)	
	

 int i2c_eeprom_demo(void)
 {
	
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();				//������ʼ��		 	 	
	AT24CXX_Init();			//IIC��ʼ�� 
 	while(AT24CXX_Check())//��ⲻ��24c02
	{
		printf("CHECK ERROR I2C EEPROM\n");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	} 
	printf("CHECK I2C EEPROM OK\n");
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)//KEY_1����,д��24C02
		{
			AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
			printf("24C02 Write Finished!\n");//��ʾ�������
		}
		if(key==KEY0_PRES)//KEY0����,��ȡ�ַ�������ʾ
		{
 			printf("Start Read 24C02....\n");
			AT24CXX_Read(0,datatemp,SIZE);
			printf("The Data Readed Is: %s\n ",datatemp);//��ʾ�������
		}
		
		for(i=0;i<20;i++)
		{
			delay_ms(2);
			LED0=!LED0;//��ʾϵͳ��������	
		}		   
	}
}
 


int i2c_byte_demo(u8 eeprom_addr,u8 data)
{
	u8 key;
	u16 i=0;
	u8 temp;
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();				//������ʼ��	
	
	IIC_Init();
	printf("\n\rhello world\n\r");
 	while(AT24CXX_Check())//��ⲻ��24c02
	{
		printf("\n\rCHECK ERROR I2C EEPROM\n\r");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	} 	
	printf("\n\rCHECK I2C EEPROM OK\n\r");
	
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)//KEY_1����,д��24C02
		{
			IIC_Start();  
			IIC_Send_Byte(0XA0);//divice address
			IIC_Wait_Ack();	
			IIC_Send_Byte(eeprom_addr);
			IIC_Wait_Ack();
			IIC_Send_Byte(data);
			IIC_Wait_Ack();  		    	   
			IIC_Stop();//����һ��ֹͣ���� 
			delay_ms(10);
			printf("\n\r24C02 Write Finished!\n\r");//��ʾ�������
		}
		if(key==KEY0_PRES)//KEY0����,��ȡ�ַ�������ʾ
		{
 			printf("\n\rStart Read 24C02....\n\r");
			IIC_Start(); 
			IIC_Send_Byte(0XA0);
			IIC_Wait_Ack(); 
			IIC_Send_Byte(eeprom_addr);
			IIC_Wait_Ack();

			IIC_Start();  	 	   
			IIC_Send_Byte(0XA1);           //�������ģʽ			   
			IIC_Wait_Ack();	 
			temp=IIC_Read_Byte(0);		   
			IIC_Stop();//����һ��ֹͣ����	   
			if(temp==data)
			{
					printf("\n\rREAD OK\n\r");
			}
			else{printf("\n\rREAD ERROR\n\r");}
			printf("\n\rThe Data Readed Is: %x\n\r",temp);//��ʾ�������
		}
		
		for(i=0;i<20;i++)
		{
			delay_ms(2);
			LED0=!LED0;//��ʾϵͳ��������	
		}		   
	}
}




int i2c_self_demo(u8 eeprom_addr,u8 data)
{
	u8 key;
	u16 i=0;
	u8 temp;
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();				//������ʼ��	
	
	i2c_initial();
	printf("\n\rhello world\n\r");
 	while(AT24CXX_Check())//��ⲻ��24c02
	{
		printf("\n\rCHECK ERROR I2C EEPROM\n\r");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	} 	
	printf("\n\rCHECK I2C EEPROM OK\n\r");
	
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)//KEY_1����,д��24C02
		{
			start_bit();  
			send_byte(0XA0);//divice address
			detect_ack();	
			send_byte(eeprom_addr);
			detect_ack();
			send_byte(data);
			detect_ack();  		    	   
			stop_bit();//����һ��ֹͣ���� 
			delay_ms(10);
			printf("\n\r24C02 Write Finished!\n\r");//��ʾ�������
		}
		if(key==KEY0_PRES)//KEY0����,��ȡ�ַ�������ʾ
		{
 			printf("\n\rStart Read 24C02....\n\r");
			start_bit(); 
			send_byte(0XA0);
			detect_ack(); 
			send_byte(eeprom_addr);
			detect_ack();

			start_bit();  //change later	 
//      restart();		//both is ok	
			send_byte(0XA1);           //�������ģʽ			   
			detect_ack();	 
			temp=receive_byte(0);		   
			stop_bit();//����һ��ֹͣ����	   
			if(temp==data)
			{
					printf("\n\rREAD OK\n\r");
			}
			else{printf("\n\rREAD ERROR\n\r");}
			printf("\n\rThe Data Readed Is: %x\n\r",temp);//��ʾ�������
		}
		
		for(i=0;i<20;i++)
		{
			delay_ms(2);
			LED0=!LED0;//��ʾϵͳ��������	
		}		   
	}
}







int i2c_self_demo_2(u8 index)
{
	u8 key;
	u16 i=0;
	u8 temp;
	u8 data[2];
	u8 recv[2];
	data[0]=0x22;
	data[1]=0x33;

	
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();				//������ʼ��	
	
	i2c_initial();
	printf("\n\rhello world\n\r");
	while(AT24CXX_Check())//��ⲻ��24c02
	{
		printf("\n\rCHECK ERROR I2C EEPROM\n\r");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	} 	
	printf("\n\rCHECK I2C EEPROM OK\n\r");
	
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)//KEY_1����,д��24C02
		{
			i2c_write(0XA0,index,1,data);
			delay_ms(10);
			printf("\n\r24C02 Write Finished!\n\r");//��ʾ�������
		}
		if(key==KEY0_PRES)//KEY0����,��ȡ�ַ�������ʾ
		{
 			printf("\n\rStart Read 24C02....\n\r");
/*			start_bit(); 
			send_byte(0XA0);
			detect_ack(); 
			send_byte(index);
			detect_ack();

			start_bit();  //change later	
//			restart();
			send_byte(0XA1);           //�������ģʽ			   
			detect_ack();	 
			temp=receive_byte(0);		   
			stop_bit();//����һ��ֹͣ����	   
			if(temp==data[0])
			{
					printf("\n\rREAD OK\n\r");
			}
			else{printf("\n\rREAD ERROR\n\r");}
			printf("\n\rThe Data Readed Is: %x\n\r",temp);//��ʾ�������		*/	
			i2c_read(0XA0,index,1,recv);
		}
	}
	return 0;
}