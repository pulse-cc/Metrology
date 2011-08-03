#include "stdafx.h"
#include "Calibrator.h"

static Calibrator *pC = new Calibrator();

CALIBRATOR_API Calibrator *getCalibrator(void)
{
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
	m_U = Volt;
	// send to device
	return m_U;
}

uint Calibrator::setFrequency(uint Hz)
{
	m_F = Hz;
	// send to device
	return m_F;
}

bool Calibrator::setOutput(bool State)
{
	m_state = State;
	// send to device
	return m_state;
}
