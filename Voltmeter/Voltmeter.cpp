#include "stdafx.h"
#include "math.h"
#include "PCL_Static.h"
// Do not move or remove: this is required for PCL static objects allocating
static const LRoot LAppRoot(0);

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
	if (Which == REFERENCE) {
		printf("Creating REFERENCE VIRTUAL voltmeter\n");
		m_data = new(data_t);
		_(A) = 0.05;
		_(B) = 0.33;
		_(C) = 0.7;
	}
	else if (Which == VERIFIED) {
		printf("Creating VERIFIED VIRTUAL voltmeter\n");
		m_data = new(data_t);
		_(A) = LRandomFromTo(0.001, 0.01);
		_(B) = LRandomFromTo(0.01, 1.);
		_(C) = LRandomFromTo(0.01, 0.9);
	}
	else {
		fprintf(stderr, "Unknown voltmeter purpose %d\n", Which);
		exit(1);
	}
}

Voltmeter::~Voltmeter()
{
	delete m_data;
}

VOLTMETER_API Voltmeter *getVoltmeter(Voltmeter::Purpose Which)
{
	if (Which == Voltmeter::REFERENCE) return pVRef;
	if (Which == Voltmeter::VERIFIED) return pVVer;
	fprintf(stderr, "Unknown voltmeter purpose %d\n", Which);
	exit(1);
	return 0;
}

double Voltmeter::getVoltage()
{
	return _(A) * pC->getVoltage() + _(B) * abs(sin((double)pC->getFrequency())*0.01) + _(C);
}
