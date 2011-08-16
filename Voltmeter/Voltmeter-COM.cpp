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
	DeviceType dt;
	cstr dn;
	if (Which == REFERENCE) {
		dt = VOLTM_REF;
		dn = "VOLTM_REF";
	}
	else if (Which == VERIFIED) {
		dt = VOLTM_VER;
		dn = "VOLTM_VER";
	}
	else {
		fprintf(stderr, "Unexpected volmeter purpose %d", Which);
		exit(1);
	}
	m_data = new(data_t);
	open_com(dt, &_(HPORT));
	write_com_cstr(_(HPORT), "SYST:REM" EOS);
	write_com_cstr(_(HPORT), "DISP:TEXT \"");
	write_com_cstr(_(HPORT),  dn);
	write_com_cstr(_(HPORT), "\"" EOS);
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
	fprintf(stderr, "Unexpected volmeter purpose %d", Which);
	exit(1);
	return 0;
}

double Voltmeter::getVoltage()
{
	char buf[20] = "abcdefghijklmnopq";
	write_com_cstr(_(HPORT), "MEAS?" EOS);
	syncro_delay(500);
	read_com(_(HPORT), 7, (BYTE*)&buf[0]);
	buf[7] = 0;
	write_com_cstr(_(HPORT), "DISP:TEXT \"");
	write_com_cstr(_(HPORT),  buf);
	write_com_cstr(_(HPORT), "\"" EOS);
	double result = LParseDbl(buf);
	printf("Measured %lf\n", result);
	return result;
}
