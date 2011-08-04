#include "StdAfx.h"
#include "SafeCalibrator.h"
#include <math.h>

SafeCalibrator::SafeCalibrator(void)
{
}


SafeCalibrator::~SafeCalibrator(void)
{
}

double SafeCalibrator::runUpExact(double Voltage, uint Frequency)
{
	
	const double k = 0.3333333333333333;
	const double minThreshold = 0.0000001;
	double Uout;
	setOutput(0);
	if(getFrequency() != Frequency) //���������� �� 0 ���� ���������� �������
		setVoltage(0);
	if(Voltage*getVoltage()<0) // ���������� �� 0 ���� ��������� ���� ����������
		setVoltage(0); 
	setFrequency(Frequency);
	Uout = getVoltage();
	//setVoltage(Uout);
	
	setOutput(1);
	while(fabs((Voltage-Uout)*k)>minThreshold) // ������ ���� �� ��������� ����������� �����
	{
		Sleep(100); // �������� 100 ����������
		setVoltage(Uout); // ������������� ���������� �� ������ �����������
		printf("runUPExact -> %1f\n",getVoltage());
		if(fabs((Voltage-Uout)*k)<100)
			Uout+=((Voltage-Uout)*k);
		else
			Uout+=((Voltage-Uout)*0.1);
	}
	return 0;
}

SafeCalibrator* getSafeCalibrator()
{
	static SafeCalibrator *pcal = new SafeCalibrator();
	return pcal;
}