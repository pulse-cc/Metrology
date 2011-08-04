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
	//Calibrator *pC = getCalibrator();
	SafeCalibrator *pSC = getSafeCalibrator();
	Voltmeter *pV = getVoltmeter(Voltmeter::REFERENCE);
	double U = 300., step = 10.;
	uint F = 0;
	pSC->runUpExact(10,10);
	printf("Thermo EMF -> %1f\n",pV->getVoltage());
	//pSC->runUpExact(200,10);
	//printf("%1f\n",pV->getVoltage());
	/*for (uint i = 0; i < 10; i++) {
		if (U != pSC->runUpExact(U,F)) LTerminate("Calibrator pSC->runUpExact(U,F) dead\n");
		printf("Cal. U=%lf\tThermo EMF=%lf\n", U, pV->getVoltage());
		U += step;
	}*/
	//getVoltmeter(Voltmeter::Purpose(666));
	return 0;
}

