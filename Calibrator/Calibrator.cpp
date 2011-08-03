#include "stdafx.h"
#include "Calibrator.h"
#include "PCL_Static.h"


Calibrator *pC = new Calibrator();


CALIBRATOR_API Calibrator *getCalibrator(void)
{
	return pC;
}


Calibrator::Calibrator()
{
	return;
}

Calibrator::~Calibrator()
{
	return;
}