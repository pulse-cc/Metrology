// Inspector.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "PCL_Static.h"
#include "Calibrator.h"
#include "Voltmeter.h"
#include "SafeCalibrator.h"
#include <math.h>
#include <stdlib.h>

//int _tmain(int argc, _TCHAR* argv[])
int main(int argc, char *argv[])
{
	LString suka("yana");
	//printf("Suka %s\n", (cstr)suka);
	Calibrator *pC = getCalibrator();
	Voltmeter *pV = getVoltmeter(Voltmeter::REFERENCE);
	double Umax = 0., U = 0., step = 0., E1 = 0., E2 = 0., k = 0.1;
	const double minThreshold = 0.0000001;
	uint F = 0, i = 0, ccount = 0;
	bool typeOfCalc = 0;
	//char *command[4] = {"Umax","U","F","Eref"};
	// Umax = 0 volt U = 0 volt F = 0 Hz Eref = 0.0 volt
	// Umax=0 - обязательны параметр нужен для того, чтобы мы не установили напряжение больше порога
	// если передается параметр Eref=0.1 - то устанавливаем эдс, возвращаем U
	// елси не передается параметр Eref=0.0 - то устанавливаем U и возвращаем эдс
	// for example U = 10 F = 1000 Umax = 20 Eref = 0.508185
	i = 1;
	ccount = 0;
	while(i<argc){
		suka = argv[i];
		if(suka.FindStr("Umax")){
			i++;
			suka = argv[i];
			if(suka.FindStr("=")){
				i++;
				suka = argv[i];
				if(!(Umax = atof(suka))){
					printf("Umax is null\n");
					return 1;
				}
			}
			printf("Umax -> %f\n",Umax);
		}
		if(suka.FindStr("U")){
			i++;
			suka = argv[i];
			if(suka.FindStr("=")){
				i++;
				suka = argv[i];
				if(!(U = atof(suka))){
					printf("U is null\n");
					return 1;
				}
			}
			printf("U -> %f\n",U);
		}
		if(suka.FindStr("F")){
			i++;
			suka = argv[i];
			if(suka.FindStr("=")){
				i++;
				suka = argv[i];
				F = atoi(suka);
			}
			printf("F -> %d\n",F);
		}
		if(suka.FindStr("Eref")){
			i++;
			suka = argv[i];
			if(suka.FindStr("=")){
				i++;
				suka = argv[i];
				if(!(E1 = atof(suka))){
					typeOfCalc = 0;
					printf("Eref is null\n");
				}
				else{
					typeOfCalc = 1;
					printf("Eref is not null\n");
				}
				
			}
			printf("Eref -> %f\n",E1);
		}
		i++;
	}
	if(Umax == 0){
		printf("Umax is null\n");
		return 1;
	}
	if(U == 0){
		printf("U is null\n");
		return 1;
	}
	if(U>Umax){
		printf("danger damage device U>Umax\n");
		return 1;
	}
		////////////////////////////////////
	if(!typeOfCalc){
		pC->setOutput(0);
		pC->setVoltage(0);
		runUpExact(U, F, pC);
		E1 = pV->getVoltage();
		printf("set voltage -> %2f V | set frequency -> %d Hz | thermo EMF -> %1f\n", U, F, E1);
	}
	else{
		step = U*k;
		U;
		while(fabs(step)>minThreshold)
		{
		
			if(U>Umax){
				printf("danger damage device U>Umax\n");
				return 1;
			}
			runUpExact(U, F, pC);
			E2 = pV->getVoltage();
			printf("set voltage -> %2f V | set frequency -> %d Hz | thermo EMF -> %1f\n", U, F, E2);

			U += step; // этот способ нахождения оказался быстрее всех
			if(E1<E2&&step>0||E1>E2&&step<0){
				step = step*(-k);
			}

		}
	}
	
	return 0;
}

