#include "stdafx.h"
#include "PCL_Static.h"
#include "Voltmeter.h"

Voltmeter *pVRef = new Voltmeter(Voltmeter::REFERENCE);
Voltmeter *pVVer = new Voltmeter(Voltmeter::VERIFIED);

Voltmeter::Voltmeter(Purpose Which) {
	printf("Creating voltmeter of purpose %d\n", Which);
}

Voltmeter::~Voltmeter() {
}

VOLTMETER_API Voltmeter *getVoltmeter(Voltmeter::Purpose Which) {
	if (Which == Voltmeter::REFERENCE) return pVRef;
	if (Which == Voltmeter::VERIFIED) return pVVer;
	LException abort(ZShow);
	abort.Signal(LFormat("Wrong voltmeter purpose code %d\n", Which));
	LTerminate("Metrology abort during votmeter initialization");
	return 0;
}
