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

CALIBRATOR_API Calibrator *getCalibrator(void)
{
	return pC;
}

Calibrator::Calibrator()
{
	m_data = new(data_t);
	open_com(CALIBRATOR, &_(HPORT));
	write_com_cstr(_(HPORT), "C" EOS);
	LSleep(3500);
	write_com_cstr(_(HPORT), "MI" EOS);
	write_com_cstr(_(HPORT), "O0" EOS);
	m_state = false;
	m_F = 0;
	m_U = 0.L;
	printf("Creating COM1 calibrator\n");
}

Calibrator::~Calibrator()
{
	close_com(_(HPORT));
	delete m_data;
}

void Calibrator::setBarrier(double Umax)
{
	if (Umax > 1000.) {
		fprintf(stderr, "Too high voltage %lf\n", Umax);
		exit(1);
	}
	else if (Umax > 200.) {
		write_com_cstr(_(HPORT), "RI5" EOS);
	}
	else if (Umax > 20.) {
		write_com_cstr(_(HPORT), "RI4" EOS);
	}
	else if (Umax > 2.) {
		write_com_cstr(_(HPORT), "RI3" EOS);
	}
	else if (Umax > 0.2) {
		write_com_cstr(_(HPORT), "RI2" EOS);
	}
	else if (Umax > 0.02) {
		write_com_cstr(_(HPORT), "RI1" EOS);
	}
	else {
		write_com_cstr(_(HPORT), "RI0" EOS);
	}
}

double Calibrator::setVoltage(double Volt)
{
	if (m_U == Volt) return m_U;
	m_U = Volt;
	write_com_cstr(_(HPORT), LFormat("S%lf" EOS, m_U));
	return m_U;
}

uint Calibrator::setFrequency(uint Hz)
{
	if (m_F == Hz) return m_F;
	m_F = Hz;
	write_com_cstr(_(HPORT), LFormat("FH%d" EOS, m_F));
	return m_F;
}

bool Calibrator::setOutput(bool State)
{
	if (m_state == State) return m_state;
	m_state = State;
	if (m_state) {
		write_com_cstr(_(HPORT), "O1" EOS);
	}
	else {
		write_com_cstr(_(HPORT), "O0" EOS);
	}
	return m_state;
}
