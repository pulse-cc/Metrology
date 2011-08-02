// Calibrator.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "Calibrator.h"


// Пример экспортированной переменной
CALIBRATOR_API int nCalibrator=0;

// Пример экспортированной функции.
CALIBRATOR_API int fnCalibrator(void)
{
	return 42;
}

// Конструктор для экспортированного класса.
// см. определение класса в Calibrator.h
CCalibrator::CCalibrator()
{
	return;
}
