#include "stdafx.h"
#include "Calibrator.h"

static Calibrator *pC = new Calibrator();

CALIBRATOR_API Calibrator *getCalibrator(void)
{
	return pC;
}

Calibrator::Calibrator()
{
	printf("Creating VIRTUAL calibrator\n");
	setBarrier(0);
	setVoltage(0);
	setFrequency(0);
}

Calibrator::~Calibrator()
{
}

double Calibrator::setVoltage(double Volt)
{
	m_U = Volt;
	LSleep(100);
	return m_U;
}

uint Calibrator::setFrequency(uint Hz)
{
	m_F = Hz;
	LSleep(100);
	return m_F;
}

bool Calibrator::setOutput(bool State)
{
	m_state = State;
	LSleep(100);
	return m_state;
}
void Calibrator::setBarrier(double Umax)
{
	if (Umax > 1000.) {
		fprintf(stderr, "Too high voltage %lf\n", Umax);
		exit(1);
	}
}