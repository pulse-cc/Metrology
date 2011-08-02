// Inspector.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "PCL_Static.h"
#include "Voltmeter.h"

int _tmain(int argc, _TCHAR* argv[])
{
	LString suka("yana");
	printf("Suka %s\n", (cstr)suka);
	getVoltmeter(Voltmeter::REFERENCE);
	getVoltmeter(Voltmeter::Purpose(666));
	return 0;
}

