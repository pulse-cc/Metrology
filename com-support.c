/* 
 * Дмитрий Обувалин
 *
 * $Id$
 */

#include "com-support.h"
#include <stdio.h>

#define COUNTER_WRITE_DELAY 100
#define countof(x) (sizeof(x) / sizeof(x[0]))
#define ERROR_CODE (-(int)GetLastError())

int open_com(int port_number, HANDLE *p_result)
{
	HANDLE com_port = INVALID_HANDLE_VALUE;
	char port_name[] = {
		'\\',
		'\\',
		'.',
		'\\',
		'C',
		'O',
		'M',
		'0',
		0
	};
	DCB port_dcb = {sizeof(DCB)};
	COMMTIMEOUTS port_timeouts = {MAXDWORD, MAXDWORD, 1000, 0, 0 };
	port_name[countof(port_name) - 2] += port_number;
	com_port = CreateFileA(
		port_name,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (com_port == INVALID_HANDLE_VALUE) return ERROR_CODE;
	if (!BuildCommDCBA("baud=4800 parity=N data=8 stop=1", &port_dcb)) return ERROR_CODE;
	if (!SetCommState(com_port, &port_dcb)) return ERROR_CODE;
	if (!SetCommTimeouts(com_port, &port_timeouts)) return ERROR_CODE;
	if (!SetupComm(com_port, 1024, 1024)) return ERROR_CODE;
	*p_result = com_port;
	return 0;
}

int write_com(HANDLE com_port, int length, BYTE *buffer)
{
	DWORD res_length;
	if (!WriteFile(com_port, buffer, length, &res_length, NULL)) return ERROR_CODE;
	syncro_delay(COUNTER_WRITE_DELAY);
	return res_length;
}

int write_com_cstr(HANDLE com_port, const char* cstr)
{
	printf("sending to handle %p string <%s>\n", com_port, cstr);
	return write_com(com_port, strlen(cstr), (BYTE*)cstr);
}

int read_com(HANDLE com_port, int length, BYTE *buffer)
{
	DWORD res_length;
	if (!ReadFile(com_port, buffer, length, &res_length, NULL)) return ERROR_CODE;
	return res_length;
}
int close_com(HANDLE com_port)
{
	return 0;
}

/*
 * Задержка выполнения на указанное число миллисекунд с целью синхронизации
 */
void syncro_delay(int milliseconds)
{
	Sleep(milliseconds);
}
