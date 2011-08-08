/* -*- mode: C; coding: cp1251 -*-
 *
 *  Протокольный стек Zigbee
 *
 *  (C) Институт сетевых технологий, 2006
 *
 *  Набор счетчиков электроэнергии
 *  Реализация для инструментальной машины под Win32
 *
 *  Дмитрий Обувалин <dymon@its.nnov.ru>
 *
 *  $Id: common-win32.c,v 1.3 2006/11/22 18:05:59 dymon Exp $
 */

#include "stack/zapl.h"

#include "counter/decimal.h"
#include "counter/common.h"

#define ERROR_CODE -(int)GetLastError()

HANDLE com_port = INVALID_HANDLE_VALUE;
/*
 * Процедуры для работы RS-485.
 * Закрытие COM порта не требуется, т.к. нормального выхода не предусмотрено
 */
int open_com(int port_number)
{
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
    port_name[COUNT_OF(port_name) - 2] += port_number;
    com_port = CreateFile(
        port_name,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (com_port == INVALID_HANDLE_VALUE) return ERROR_CODE;
    if (!BuildCommDCB("baud=4800 parity=N data=8 stop=1", &port_dcb)) return ERROR_CODE;
    if (!SetCommState(com_port, &port_dcb)) return ERROR_CODE;
    if (!SetCommTimeouts(com_port, &port_timeouts)) return ERROR_CODE;
    if (!SetupComm(com_port, 1024, 1024)) return ERROR_CODE;
    return 0;
}

int write_com(int length, BYTE *buffer)
{
    DWORD res_length;
    if (!WriteFile(com_port, buffer, length, &res_length, NULL)) return ERROR_CODE;
    syncro_delay(COUNTER_WRITE_DELAY);
    return res_length;
}

int read_com(int length, BYTE *buffer)
{
    DWORD res_length;
    if (!ReadFile(com_port, buffer, length, &res_length, NULL)) return ERROR_CODE;
    return res_length;
}

/*
 * Задержка выполнения на указанное число миллисекунд с целью синхронизации
 */
void syncro_delay(int milliseconds)
{
    Sleep(milliseconds);
}
