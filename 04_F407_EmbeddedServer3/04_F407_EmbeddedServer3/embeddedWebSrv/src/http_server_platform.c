/* Copyright (c) 2011-2018 Atmel Corporation. All rights reserved.
*
* \asf_license_start
*
* \page License
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* 3. The name of Atmel may not be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* 4. This software may only be redistributed and used in connection with an
*    Atmel microcontroller product.
*
* THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
* EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* \asf_license_stop
*
*/
#include <stdbool.h>
#include "http_server_platform.h"
#include "stm32f4xx_discovery_407.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal.h"


//systick is used just to demonstrate SSI replacement. no functional connection to HTTP server or platform port
static unsigned long MilliTimer=0;
void HAL_SYSTICK_Callback(void){
	MilliTimer++;
}

static unsigned long int timerValCC=0;
static const char *serverTestCGIPath = "/ledt.cgi";


/*wrapper functions for type sanity.
if this is not done casting fp to void will cause compiler warnings
*/
static void *http_localfs_fopen_w(const char *filename);
static int http_localfs_fclose_w(void *fp);
static size_t http_localfs_fread_w(void *ptr, size_t size, size_t nmemb, void *fp);
static int http_localfs_fgetc_w(void *fp);
static int http_localfs_fseek_w(void *fp, long offset, int whence);
static int http_localfs_feof_w(void *fp);

static void *http_localfs_fopen_w(const char *filename) { return (void *)http_localfs_fopen(filename); }
static int http_localfs_fclose_w(void *fp) { return http_localfs_fclose((http_localfs_filesystem_fp_t)fp); }
static size_t http_localfs_fread_w(void *ptr, size_t size, size_t nmemb, void *fp) { return http_localfs_fread(ptr, size, nmemb, (http_localfs_filesystem_fp_t)fp); }
static int http_localfs_fgetc_w(void *fp) { return http_localfs_fgetc((http_localfs_filesystem_fp_t)fp); }
static int http_localfs_fseek_w(void *fp, long offset, int whence) { return http_localfs_fseek((http_localfs_filesystem_fp_t)fp, offset, whence); }
static int http_localfs_feof_w(void *fp) { return http_localfs_feof((http_localfs_filesystem_fp_t)fp); }

http_net_netops_t *httpNetops;
static bool gbHTTPSrvSendDone=false;
static bool gbHTTPSrvRecvDone=false;
static int32_t gi32HTTPSrvRxLen=0;
extern SOCKET tcp_server_socket;

int integerValue=0;

void tcpServerSocketEventHandler(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
	//TODO: check if this is HTTP socket
	switch (u8Msg) {
		case SOCKET_MSG_CONNECT:
		{
		}
		break;
		case SOCKET_MSG_SEND:
		{
			gbHTTPSrvSendDone=true;
		}
		break;
		case SOCKET_MSG_RECV:
		{
			tstrSocketRecvMsg* pstrRx = (tstrSocketRecvMsg*)pvMsg;
			gi32HTTPSrvRxLen = pstrRx->s16BufferSize;
			if((gi32HTTPSrvRxLen<0) && (gi32HTTPSrvRxLen!=SOCK_ERR_TIMEOUT)) {
				PRINT_ERROR("ERROR >> Receive error for Rx socket (Err=%ld).\r\n",gi32HTTPSrvRxLen);
			}
			gbHTTPSrvRecvDone=true;
		}
		break;
		default: break;
	}
}

int http_server_WINC15x0_net_read(int socket, unsigned char *readBuffer, int readBufferLength, int timeoutMs){
	//as of now, read is meant only for HTTP request headers. So, in case there is more data coming fro host
	//allocate a larger buffer in config. Later to accomodate post and other data input methods, we will implement
	// a RX FIFO pool.
	
	gbHTTPSrvRecvDone=false;
	if (SOCK_ERR_NO_ERROR!=recv(socket,readBuffer,readBufferLength,timeoutMs)){
		PRINT_ERROR("ERROR >> recv failed\r\n");
		return -1;
	}
	//call handle_events until we get rx callback
	while (false==gbHTTPSrvRecvDone){
		m2m_wifi_handle_events(NULL);
	}
	
	//length will be updated in the callback
	if (gi32HTTPSrvRxLen>0){
		return gi32HTTPSrvRxLen;
	}

	return -1;
}
int http_server_WINC15x0_net_write(int socket, unsigned char *writeBuffer, int writeBufferLength, int timeoutMs){
	//static int WINC1500_write(Network* n, unsigned char* buffer, int len, int timeout_ms) {
	gbHTTPSrvSendDone=false;
	if (SOCK_ERR_NO_ERROR!=send(socket,writeBuffer,writeBufferLength,timeoutMs)){
		PRINT_ERROR("ERROR >> send error");
		return -1;
	}
	//wait for send callback . Not essential. but let us do it for now.
	while (false==gbHTTPSrvSendDone){
		m2m_wifi_handle_events(NULL);
	}

	//TODO: figure out how to get actual send length from callback
	//this length will be updated in the callback
	//return gu32MQTTBrokerSendLen;
	return writeBufferLength;
}

void http_server_WINC15x0_net_disconnect(int socket){
	close(socket);
	tcp_server_socket=-1;
}

/*callbacks to replace SSI string timerVal*/
int http_server_timerVal_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength);
int http_server_timerVal_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength)
{
	if (0 != strcmp("timerVal", SSIString)) //not a mandatory check
	{
		printf("SSI string missmatch in timerVal callback\r\n");
		return -1;
	}
	sprintf(replacerBuffer,"%lu",HAL_GetTick());
	replacerBuffer[bufferLength] = 0;
	return 0;
}

int http_server_timerValCallCount_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength);
int http_server_timerValCallCount_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength)
{
	if (0 != strcmp("timerValCC", SSIString)) //not a mandatory check
	{
		printf("SSI string missmatch in timerVal callback\r\n");
		return -1;
	}
	timerValCC++;
	sprintf(replacerBuffer,"%lu",timerValCC);
	replacerBuffer[bufferLength] = 0;
	return 0;
}


int httpServerTest_cgiPathFunction(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength);
int httpServerTest_cgiPathFunction(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength)
{
	printf(CGIPath);

	if (0 == strcmp(CGIPath, serverTestCGIPath)){
	if ((bufferLength <= 0) || NULL == replacerBuffer)
	return -1;
	char pStatus=0;

	printf("CGI func called !!!!!!!!!!!!!!!!!!!!");
	BSP_LED_Toggle(LED1);
	if(true==HAL_GPIO_ReadPin(LED1_GPIO_PORT,LED1_PIN)){
		BSP_LED_On(LED1);
		BSP_LED_On(LED2);
		BSP_LED_On(LED3);
		BSP_LED_Off(LED4);
		pStatus=1;
	}
	else if(false==HAL_GPIO_ReadPin(LED1_GPIO_PORT,LED1_PIN)){
		BSP_LED_Off(LED1);
		BSP_LED_Off(LED2);
		BSP_LED_Off(LED3);
		BSP_LED_On(LED4);
		pStatus=0;
	}
	
	sprintf(replacerBuffer,"{  \"LEDstatus\":  %d }",pStatus);
	return strlen(replacerBuffer);
	}

	else if(0 == strcmp(CGIPath, "/integerValue.cgi")){
		printf("INTEGER!!!!!!!!!!!!!!!!!!!!!! !!!!!!!!!!!!!!!!!!!!");
		integerValue++;
		sprintf(replacerBuffer,"{  \"integerValue\":  %d }",integerValue);
		return strlen(replacerBuffer);
	}
	else{
		return -1;}
}

//http_server_init for WINC1500 based platforms
int http_server_WINC15x0_init(void)
{
	http_localfs_deinit(); //just in case previous test left it in stale state
	http_localfs_init();

	//register index file to localfs
	int retval = http_localfs_registerFile(path_index_html, (char *)&index_html, index_html_len, 0);
	if (retval < 0)
	{
		printf("!! test_http_server(registerFile failed)\r\n");
		return -1;
	}
	retval = http_localfs_registerFile(path_timerVal_ssi, (char *)&timerVal_ssi, timerVal_ssi_len, 0);
	if (retval < 0)
	{
		printf("!! test_http_server(registerFile failed for timerVal_ssi)\r\n");
		return -1;
	}
	//register local fs fops.
	http_file_fops_t localFSFops;
	http_file_init_fopsStruct(&localFSFops);
	
	localFSFops.fopen = http_localfs_fopen_w;
	localFSFops.fclose = http_localfs_fclose_w;
	localFSFops.fread = http_localfs_fread_w;
	localFSFops.fgetc = http_localfs_fgetc_w;
	localFSFops.fseek = http_localfs_fseek_w;
	localFSFops.eof = http_localfs_feof_w;
	http_file_register_fops(localFSFops);

	//register netops
	http_net_netops_t http_WINC_netops;
	http_net_init_netopsStruct(&http_WINC_netops);
	
	http_WINC_netops.http_net_read = http_server_WINC15x0_net_read;
	http_WINC_netops.http_net_write = http_server_WINC15x0_net_write;
	http_WINC_netops.http_net_disconnect = http_server_WINC15x0_net_disconnect;
	httpNetops = http_net_register_netops(http_WINC_netops);
	
	//now register an SSI string. file has already been registered in fs
	http_SSI_deRegister_all();
	http_SSI_replacer_t *SSIReplacementHandle;
	SSIReplacementHandle = http_SSI_register_replacer("timerVal", http_server_timerVal_SSI_replacer_cb);
	if (NULL == SSIReplacementHandle)
	{
		printf("http_SSI_register_replacer timerVal failed\r\n");
		return -1;
	}
	
	SSIReplacementHandle = http_SSI_register_replacer("timerValCC", http_server_timerValCallCount_SSI_replacer_cb);
	if (NULL == SSIReplacementHandle)
	{
		printf("http_SSI_register_replacer timerValCC failed\r\n");
		return -1;
	}
	
	//now register a CGI path function
	http_CGI_pathFunction_t *cgiPathHandle2;

	cgiPathHandle2 = http_CGI_register_pathFunction(serverTestCGIPath, httpServerTest_cgiPathFunction, HTTP_contentType_json);
	if (NULL == cgiPathHandle2)
	{
		printf("http_CGI_register_pathFunction failed");
		return -1;
	}
	
	return 0;
}
