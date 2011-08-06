// Inspector.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "PCL_Static.h"
#include "Calibrator.h"
#include "Voltmeter.h"
#include "SafeCalibrator.h"
#include <math.h>
#include <stdlib.h>

const double EPSILON = 1e-15;

LString getValue(cstr Key, cstr Chunk)
{
	LString head, tail, errout(" ");
	LSplit(Chunk, "=", head, tail);
	if (head != Key) return errout;
	return tail;
}

struct {
	cstr key;
	bool seen, req;
} arg[] = {
	{"Umax", false, true},
	{"U", false, true},
	{"F", false, true},
	{"Eref", false, false},
};

//int _tmain(int argc, _TCHAR* argv[])
uint main(uint argc, cstr argv[])
{
	LString typeOfCalc;
	Calibrator *pC = getCalibrator();
	Voltmeter *pV = getVoltmeter(Voltmeter::REFERENCE);
	double Umax = 0., U = 0., step = 0., E1 = 0., E2 = 0., k = 0.1;
	const double minThreshold = 0.0000001;
	uint F = 0, i = 0, j = 0, ccount = 0;
	//char *command[4] = {"Umax","U","F","Eref"};
	// Umax = 0 volt U = 0 volt F = 0 Hz Eref = 0.0 volt
	// Umax=0 - обязательны параметр нужен для того, чтобы мы не установили напряжение больше порога
	// если передается параметр Eref - то устанавливаем эдс, возвращаем U
	// елси не передается параметр Eref - то устанавливаем U и возвращаем эдс
	// for example U = 10 F = 1000 Umax = 20 Eref = 0.508185
	typeOfCalc = argv[1];
	if (typeOfCalc == "fix") {
		arg[3].seen = true;
	}
	else if (typeOfCalc == "equ") {
		arg[3].req = true;
	}
	else {
		fprintf(stderr, "Wrong command: %s\n", argv[1]);
		exit(1);
	}
	for (i = 2; i < argc; i++) {
		bool good = false;
		for (j = 0; j < countof(arg); j++) {
			LString res = getValue(arg[j].key, argv[i]);
			if (res == " ") continue;
			good = true;
			if (arg[j].seen) {
				fprintf(stderr, "Duplicate or prohibited: %s\n", arg[j].key);
				exit(1);
			}
			switch (j) {
			case 0:  Umax = LParseDbl(res); break;
			case 1:  U = LParseDbl(res); break;
			case 2:  F = LParseInt(res); break;
			case 3:  E1 = LParseDbl(res); break;
			}
			printf("%d=%s\n", j, (cstr)res);
			arg[j].seen = true;
		}
		if (!good) {
			fprintf(stderr, "Unexpected: %s\n", argv[i]);
			exit(1);
		}
	}
	for (j = 0; j < countof(arg); j++) {
		if (arg[j].req) if (!arg[j].seen) {
			fprintf(stderr, "Required but not seen: %s\n", arg[j].key);
			exit(1);
		}
	}
	if (Umax <= 0.) {
		fprintf(stderr, "Invalid Umax: %lf\n", Umax);
		exit(1);
	}
	if (typeOfCalc == "fix") if (fabs(U) < EPSILON) {
		fprintf(stderr, "Invalid U: %lf\n", Umax);
		exit(1);
	}
	printf("Umax=%lf U=%lf F=%d Eref=%lf\n", Umax, U, F, E1);
	if (typeOfCalc == "fix"){
		pC->setOutput(0);
		pC->setVoltage(0);
		runUpExact(U, F, pC);
		E1 = pV->getVoltage();
		printf("set voltage -> %2f V | set frequency -> %d Hz | thermo EMF -> %1f\n", U, F, E1);
	}
	else {
		step = U*k;
		while (fabs(step) > minThreshold) {
			if (Umax <= U) {
				fprintf(stderr, "U is greater than Umax\n");
				exit(1);
			}
			runUpExact(U, F, pC);
			E2 = pV->getVoltage();
			printf("set voltage -> %2f V | set frequency -> %d Hz | thermo EMF -> %1f\n", U, F, E2);

			U += step; // этот способ нахождения оказался быстрее всех
			if (E1 < E2 && step > 0 || E1 > E2 && step < 0) {
				step *= (-k);
			}
		}
	}
	return 0;
}

