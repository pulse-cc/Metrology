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

	if (pC->getFrequency() != Frequency) { //сбрасываем на 0 если изменилась частота
		pC->setOutput(0);
		Uout = pC->setVoltage(0);
		pC->setFrequency(Frequency);
	}
	else if (!Frequency) if (Voltage * pC->getVoltage() < 0) { // сбрасываем на 0 если изменился знак напряжения
		pC->setOutput(0);
		Uout = pC->setVoltage(0); 
	}
	if (!pC->getOutput()) pC->setOutput(1);

	while (fabs((Voltage - Uout) * k) > minThreshold) { // крутим пока не достигнут минимальный порог
		if (fabs(Voltage - Uout) < Umax) {
			Uout += ((Voltage - Uout) * k);
		}
		else {
			Uout += ((Voltage - Uout) * k2);
		}
		pC->setVoltage(Uout); // устанавливает напряжение на выходе калибратора
	}

	return pC->setVoltage(Voltage);
}
