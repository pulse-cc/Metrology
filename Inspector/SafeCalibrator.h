#ifndef __SAFECALIBRATOR_H__
#define __SAFECALIBRATOR_H__

#include "calibrator.h"
#include "PCL_Static.h"
class SafeCalibrator :
	public Calibrator
{
public:
	SafeCalibrator(void);
	~SafeCalibrator(void);
	double runUpExact(double Voltage, uint Frequency);
};


SafeCalibrator* getSafeCalibrator();

#endif