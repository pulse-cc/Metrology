#include "stdafx.h"
#include "math.h"
#include "PCL_Static.h"
#include "Voltmeter.h"
#include "Calibrator.h"

extern "C" {
#	include "..\com-support.h"
}

static Voltmeter *pVRef = new Voltmeter(Voltmeter::REFERENCE);
static Voltmeter *pVVer = new Voltmeter(Voltmeter::VERIFIED);
static Calibrator *pC = getCalibrator();

typedef struct {
	HANDLE HPORT;
} data_t;
#define _(X) (((data_t*)m_data)->X)
	
Voltmeter::Voltmeter(Purpose Which)
{
	m_data = new(data_t);
	open_com(Which + 1, &_(HPORT));
	printf("Creating COM%d voltmeter\n", Which + 1);
}

Voltmeter::~Voltmeter()
{
	close_com(_(HPORT));
	delete m_data;
}

VOLTMETER_API Voltmeter *getVoltmeter(Voltmeter::Purpose Which)
{
	if (Which == Voltmeter::REFERENCE) return pVRef;
	if (Which == Voltmeter::VERIFIED) return pVVer;
	LException abort(ZShow);
	abort.Signal(LFormat("Wrong voltmeter purpose code %d\n", Which));
	LTerminate("Metrology abort during votmeter initialization");
	return 0;
}

double Voltmeter::getVoltage()
{
	return -0.5;
}
