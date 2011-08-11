#ifndef COMSUPPORT_H
#define COMSUPPORT_H

/* 
 *  Дмитрий Обувалин
 *
 *  $Id$
 */

#include <Windows.h>

typedef enum {EMPTY, CALIBRATOR, VOLTM_REF, VOLTM_VER} DeviceType;

int open_com(DeviceType device, HANDLE *p_result);
int write_com(HANDLE com_port, int length, BYTE *buffer);
int write_com_cstr(HANDLE com_port, const char* cstr);
int read_com(HANDLE com_port, int length, BYTE *buffer);
int close_com(HANDLE com_port);

void syncro_delay(int milliseconds);

#define EOS "\x0d\x0a"

#endif
