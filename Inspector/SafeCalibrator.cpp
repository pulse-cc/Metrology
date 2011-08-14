#include "StdAfx.h"
#include "SafeCalibrator.h"
#include <math.h>


double runUpExact(double Voltage, uint Frequency, Calibrator *pC)
{
	double Uout = pC->getVoltage();
	double barrier = fabs(Voltage - Uout) * 0.03;

	if (pC->getFrequency() != Frequency) {
		pC->setOutput(0);
		Uout = pC->setVoltage(0);
		pC->setFrequency(Frequency);
	}
	else if (!Frequency) if (Voltage * pC->getVoltage() < 0) {
		pC->setOutput(0);
		Uout = pC->setVoltage(0); 
	}
	if (!pC->getOutput()) pC->setOutput(1);

	double kk = 0.1;
	while (fabs(Voltage - Uout) > barrier) {
		Uout += ((Voltage - Uout) * kk);
		kk += 0.1;
		pC->setVoltage(Uout);
	}

	return pC->setVoltage(Voltage);
}
