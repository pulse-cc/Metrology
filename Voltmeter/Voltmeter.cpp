// Voltmeter.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "Voltmeter.h"


// Пример экспортированной переменной
VOLTMETER_API int nVoltmeter=0;

// Пример экспортированной функции.
VOLTMETER_API int fnVoltmeter(void)
{
	return 42;
}

// Конструктор для экспортированного класса.
// см. определение класса в Voltmeter.h
CVoltmeter::CVoltmeter()
{
	return;
}
