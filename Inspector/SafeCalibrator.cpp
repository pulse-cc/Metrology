#include "StdAfx.h"
#include "SafeCalibrator.h"
#include <math.h>


double runUpExact(double Voltage, uint Frequency, Calibrator *pC)
{
	const double Umax = 290;
	const double k = 0.3333333333333333;
	const double k2 = 0.1;
	const double minThreshold = 0.05;
	double Uout = pC->getVoltage();

	if (pC->getFrequency() != Frequency) { //���������� �� 0 ���� ���������� �������
		pC->setOutput(0);
		Uout = pC->setVoltage(0);
		pC->setFrequency(Frequency);
	}
	else if (!Frequency) if (Voltage * pC->getVoltage() < 0) { // ���������� �� 0 ���� ��������� ���� ����������
		pC->setOutput(0);
		Uout = pC->setVoltage(0); 
	}
	if (!pC->getOutput()) pC->setOutput(1);

	while (fabs((Voltage - Uout) * k) > minThreshold) { // ������ ���� �� ��������� ����������� �����
		if (fabs(Voltage - Uout) < Umax) {
			Uout += ((Voltage - Uout) * k);
		}
		else {
			Uout += ((Voltage - Uout) * k2);
		}
		pC->setVoltage(Uout); // ������������� ���������� �� ������ �����������
	}

	return pC->setVoltage(Voltage);
}
