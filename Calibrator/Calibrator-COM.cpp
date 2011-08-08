#include "stdafx.h"
#include "Calibrator.h"

extern "C" {
#	include "..\com-support.h"
}

static Calibrator *pC = new Calibrator();

typedef struct {
	HANDLE HPORT;
} data_t;
#define _(X) (((data_t*)m_data)->X)

#define EOS "\x0d\x0a"

CALIBRATOR_API Calibrator *getCalibrator(void)
{
	return pC;
}

Calibrator::Calibrator()
{
	m_data = new(data_t);
	open_com(1, &_(HPORT));
	write_com_cstr(_(HPORT), "C" EOS);
	write_com_cstr(_(HPORT), "MI" EOS);
	printf("Creating COM1 calibrator\n");
}

Calibrator::~Calibrator()
{
	close_com(_(HPORT));
	delete m_data;
}

double Calibrator::setVoltage(double Volt)
{
	m_U = Volt;
	write_com_cstr(_(HPORT), LFormat("S%lf" EOS, m_U));
	return m_U;
}

uint Calibrator::setFrequency(uint Hz)
{
	m_F = Hz;
	write_com_cstr(_(HPORT), LFormat("FH%d" EOS, m_F));
	return m_F;
}

bool Calibrator::setOutput(bool State)
{
	m_state = State;
	if (m_state) {
		write_com_cstr(_(HPORT), "O1" EOS);
	}
	else {
		write_com_cstr(_(HPORT), "O0" EOS);
	}
	return m_state;
}
