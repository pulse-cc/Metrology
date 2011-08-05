#include "stdafx.h"
#include "Calibrator.h"

static Calibrator *pC = new Calibrator();

CALIBRATOR_API Calibrator *getCalibrator(void)
{
	LSleep(100);
	return pC;
}

Calibrator::Calibrator()
{
	printf("Creating calibrator\n");
}

Calibrator::~Calibrator()
{
}

double Calibrator::setVoltage(double Volt)
{
	LSleep(100);
	m_U = Volt;
	// send to device
	return m_U;
}

uint Calibrator::setFrequency(uint Hz)
{
	LSleep(100);
	m_F = Hz;
	// send to device
	return m_F;
}

bool Calibrator::setOutput(bool State)
{
	LSleep(100);
	m_state = State;
	// send to device
	return m_state;
}
