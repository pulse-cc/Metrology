// Calibrator.cpp: ���������� ���������������� ������� ��� ���������� DLL.
//

#include "stdafx.h"
#include "Calibrator.h"


// ������ ���������������� ����������
CALIBRATOR_API int nCalibrator=0;

// ������ ���������������� �������.
CALIBRATOR_API int fnCalibrator(void)
{
	return 42;
}

// ����������� ��� ����������������� ������.
// ��. ����������� ������ � Calibrator.h
CCalibrator::CCalibrator()
{
	return;
}
