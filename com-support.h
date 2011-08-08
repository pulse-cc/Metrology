#ifndef COMSUPPORT_H
#define COMSUPPORT_H

/* 
 *  Дмитрий Обувалин
 *
 *  $Id$
 */

#include <Windows.h>

int open_com(int port_number, HANDLE *p_result);
int write_com(HANDLE com_port, int length, BYTE *buffer);
int write_com_cstr(HANDLE com_port, const char* cstr);
int read_com(HANDLE com_port, int length, BYTE *buffer);
int close_com(HANDLE com_port);

void syncro_delay(int milliseconds);

#endif
