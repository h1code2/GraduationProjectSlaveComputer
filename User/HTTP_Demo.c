#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "usart2.h"

/**
  * @brief   组HTTP POST报文
  * @param   pkt   报文缓存指针
  * @param   key   API_KEY定义在Main.c文件中，需要根据自己的设备修改
  *	@param 	 devid 设备ID，定义在main.c文件中，需要根据自己的设备修改
  *	@param 	 dsid  数据流ID
  *	@param 	 val   字符串形式的数据点的值
  * @retval  整个包的长度
  */
uint32_t HTTP_PostPkt(char *pkt, char *key, char *devid, char *dsid, char *val)
{
    char dataBuf[100] = {0};
    char lenBuf[10] = {0};
    *pkt = 0;

    sprintf(dataBuf, ",;%s,%s", dsid, val);     //采用分割字符串格式:type = 5
    sprintf(lenBuf, "%d", strlen(dataBuf));

    strcat(pkt, "POST /devices/");
    strcat(pkt, devid);
    strcat(pkt, "/datapoints?type=5 HTTP/1.1\r\n");

    strcat(pkt, "api-key:");
    strcat(pkt, key);
    strcat(pkt, "\r\n");

    strcat(pkt, "Host:api.heclouds.com\r\n");

    strcat(pkt, "Content-Length:");
    strcat(pkt, lenBuf);
    strcat(pkt, "\r\n\r\n");

    strcat(pkt, dataBuf);

    return strlen(pkt);
}


//请求图片
uint32_t Http_GetPkt(uint8_t pkt[])
{
  char buffer[100] = {0};
	sprintf(buffer,"GET /api/to_arr/?lock_id=%s HTTP/1.1\r\nHost:lock.huangtongx.cn\r\n\r\n",pkt);
	printf("%s",buffer);
	USART2_Write(USART2, (unsigned char *)(buffer), strlen(buffer));
}

//请求锁的状态
uint32_t Http_GetSta(uint8_t pkt[])
{
	char buffer[100] = {0};
	sprintf(buffer,"GET /api/lockStatus/?lock_id=%s HTTP/1.1\r\nHost:lock.huangtongx.cn\r\n\r\n",pkt);
	printf("%s",buffer);
	USART2_Write(USART2, (unsigned char *)(buffer), strlen(buffer));
}

uint32_t Http_GetClose(uint8_t pkt[])
{
	char buffer[100] = {0};
	sprintf(buffer,"GET /api/closeLock/?lock_id=%s HTTP/1.1\r\nHost:lock.huangtongx.cn\r\n\r\n",pkt);
	printf("%s",buffer);
	USART2_Write(USART2, (unsigned char *)(buffer), strlen(buffer));
}