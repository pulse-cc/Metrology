// Inspector.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "PCL_Static.h"
#include "Calibrator.h"
#include "Voltmeter.h"
#include "SafeCalibrator.h"

int _tmain(int argc, _TCHAR* argv[])
{
	LString suka("yana");
	printf("Suka %s\n", (cstr)suka);
	Calibrator *pC = getCalibrator();
	Voltmeter *pV = getVoltmeter(Voltmeter::REFERENCE);
	double U = 300., step = 10.;
	uint F = 1000;
	
	for (uint i = 0; i < 10; i++) {
		//if (U != runUpExact(U,F,pC)) LTerminate("Calibrator runUpExact(U,F,pC) dead\n");
		runUpExact(U,F,pC);
		printf("Cal. U=%lf\tThermo EMF=%lf\n", U, pV->getVoltage());
		U += step;
	}
	//getVoltmeter(Voltmeter::Purpose(666));
	return 0;
}

