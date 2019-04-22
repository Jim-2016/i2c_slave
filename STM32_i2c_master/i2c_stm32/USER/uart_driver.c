#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"

int uart_baud_setting(int baud)
{
	uart_init(baud);
//	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	return 0;
}


int uart_print_receive()
{
	u16 t;  
	u16 len;	
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);//�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
			break;
		}
		else
		{
			continue;
		}
	}
	return 0;
}



