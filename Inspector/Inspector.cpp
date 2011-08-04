// Inspector.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "PCL_Static.h"
#include "Calibrator.h"
#include "Voltmeter.h"
#include "SafeCalibrator.h"
#include <math.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//LString suka("yana");
	//printf("Suka %s\n", (cstr)suka);
	Calibrator *pC = getCalibrator();
	Voltmeter *pV = getVoltmeter(Voltmeter::REFERENCE);
	double U = 10., U2 = 0., step = 0., E1 = 0., E2 = 0., k = 0.1;
	const double minThreshold = 0.0000001;
	uint F = 1000, i = 0;
	////////////////////////////////////
	pC->setOutput(0);
	pC->setVoltage(0);
	runUpExact(U, F, pC);
	E1 = pV->getVoltage();
	printf("set voltage -> %2f V | set frequency -> %d Hz | thermo EMF -> %1f\n", U, F, E1);
	///////////////////////////////////

	F = 0;
	//runUpExact(U, F, pC);
	//E2 = pV->getVoltage();
	//printf("set voltage -> %2f V | set frequency -> %d Hz | thermo EMF -> %1f\n", U, F, E2);
	step = U*k;
	U2 = U;
	while(fabs(step)>minThreshold)
	{
		

		runUpExact(U2, F, pC);
		//printf("U2 -> %f\n", U2);
		E2 = pV->getVoltage();
		printf("set voltage -> %2f V | set frequency -> %d Hz | thermo EMF -> %1f\n", U2, F, E2);
		//U2 += U2*(E1/E2)*(E1-E2);
		//U2 = U2*(E1/E2);
		//U2 = (U2 * E1)/E2;
		U2 += step; // этот способ нахождения оказался быстрее всех
		if(E1<E2&&step>0||E1>E2&&step<0){
			step = step*(-k);
		}
		/*if(E1>E2&&step<0){
			step = step*(-k);
		}*/
		
		//i++;
	}


	/*for (uint i = 0; i < 10; i++) {
		//if (U != runUpExact(U,F,pC)) LTerminate("Calibrator runUpExact(U,F,pC) dead\n");
		runUpExact(U,F,pC);
		printf("Cal. U=%lf\tThermo EMF=%lf\n", U, pV->getVoltage());
		U += step;
	}*/
	//getVoltmeter(Voltmeter::Purpose(666));
	return 0;
}

