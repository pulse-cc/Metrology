// Inspector.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "PCL_Static.h"
#include "Calibrator.h"
#include "Voltmeter.h"

int _tmain(int argc, _TCHAR* argv[])
{
	LString suka("yana");
	printf("Suka %s\n", (cstr)suka);
	Calibrator *pC = getCalibrator();
	Voltmeter *pV = getVoltmeter(Voltmeter::REFERENCE);
	double U = 300., step = 10.;
	for (uint i = 0; i < 10; i++) {
		if (U != pC->setVoltage(U)) LTerminate("Calibrator pC->setVoltage(U) dead\n");
		printf("Cal. U=%lf\tThermo EMF=%lf\n", U, pV->getVoltage());
		U += step;
	}
	//getVoltmeter(Voltmeter::Purpose(666));
	return 0;
}

