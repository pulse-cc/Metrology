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
	printf("Creating VIRTUAL voltmeter of purpose %d\n", Which);
	m_data = new(data_t);
	double LRandomFromTo(double From, double To);
	_(A) = LRandomFromTo(0.001, 0.01);
	_(B) = LRandomFromTo(0.01, 1);
	_(C) = LRandomFromTo(0.01, 0.9);
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
	return _(A) * pC->getVoltage() + _(B) * abs(sin((double)pC->getFrequency())*0.01) + _(C);
}
