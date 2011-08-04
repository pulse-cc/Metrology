#include "stdafx.h"
#include "math.h"
#include "PCL_Static.h"
#include "Voltmeter.h"
#include "Calibrator.h"


static Voltmeter *pVRef = new Voltmeter(Voltmeter::REFERENCE);
static Voltmeter *pVVer = new Voltmeter(Voltmeter::VERIFIED);
static Calibrator *pC = getCalibrator();



typedef struct {
	double A, B, C;
} data_t;

#define _(X) (((data_t*)m_data)->X)
	
Voltmeter::Voltmeter(Purpose Which)
{
	printf("Creating voltmeter of purpose %d\n", Which);
	m_data = new(data_t);
	_(A) = 0.01;
	_(B) = 0.9876;
	_(C) = 0.1234;
}

Voltmeter::~Voltmeter()
{
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
	return _(A) * log(pC->getVoltage()) + _(B) * abs(sin((double)pC->getFrequency())) + _(C);
}
