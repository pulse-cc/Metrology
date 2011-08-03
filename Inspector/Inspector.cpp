// Inspector.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

#include "PCL_Static.h"
#include "Voltmeter.h"
#include "Calibrator.h"

int _tmain(int argc, _TCHAR* argv[])
{
	LString suka("yana");
	printf("Suka %s\n", (cstr)suka);
	getVoltmeter(Voltmeter::REFERENCE);
	getVoltmeter(Voltmeter::Purpose(666));
	getCalibrator();
	return 0;
}

