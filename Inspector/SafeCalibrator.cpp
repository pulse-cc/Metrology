#include "StdAfx.h"
#include "SafeCalibrator.h"
#include <math.h>


double runUpExact(double Voltage, uint Frequency, Calibrator *pC)
{
	double Uout = pC->getVoltage();
	double delta = fabs(Voltage - Uout) * 0.25;
	double barrier = fabs(Voltage - Uout) * 0.02;
	const double Umax = 290;
	const double k = 0.3333333333333333;
	const double k2 = 0.1;

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

	while (fabs(Voltage - Uout) > barrier) { // ������ ���� �� ��������� ����������� �����
		if (fabs(Voltage - Uout) < delta) {
			Uout += ((Voltage - Uout) * k);
		}
		else {
			Uout += ((Voltage - Uout) * k2);
		}
		pC->setVoltage(Uout); // ������������� ���������� �� ������ �����������
	}

	return pC->setVoltage(Voltage);
}
