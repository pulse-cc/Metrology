#include "StdAfx.h"
#include "SafeCalibrator.h"
#include <math.h>


double runUpExact(double Voltage, uint Frequency, Calibrator *pC)
{
	
	const double k = 0.3333333333333333;
	const double minThreshold = 0.001;
	double Uout;
	
	if(pC->getFrequency() != Frequency){ //���������� �� 0 ���� ���������� �������
		pC->setOutput(0);
		pC->setVoltage(0);
		pC->setFrequency(Frequency);
	}
	if(Voltage*pC->getVoltage()<0){ // ���������� �� 0 ���� ��������� ���� ����������
		pC->setOutput(0);
		pC->setVoltage(0); 
	}
	if(!pC->getOutput())
		pC->setOutput(1);
	
	Uout = pC->getVoltage();
	//setVoltage(Uout);
	
	while(fabs((Voltage-Uout)*k)>minThreshold) // ������ ���� �� ��������� ����������� �����
	{
		//LSleep(100); // �������� 100 ����������
		
		pC->setVoltage(Uout); // ������������� ���������� �� ������ �����������
		//printf("runUPExact -> %1f\n",pC->getVoltage());
		if(fabs((Voltage-Uout)*k)<100)
			Uout+=((Voltage-Uout)*k);
		else
			Uout+=((Voltage-Uout)*0.1);
	}
	//LSleep(100);
	pC->setVoltage(Voltage);
	return pC->getVoltage();
}
