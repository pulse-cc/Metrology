#ifndef __CALIBRATOR_H__
#define __CALIBRATOR_H__
#include "PCL_Static.h"

#ifdef CALIBRATOR_EXPORTS
#define CALIBRATOR_API __declspec(dllexport)
#else
#define CALIBRATOR_API __declspec(dllimport)
#endif


class CALIBRATOR_API Calibrator {
	double m_U;
	uint m_F;
	bool m_state;
	pvoid m_data;

public:
	Calibrator(void);
	virtual ~Calibrator();

	double setVoltage(double Volt);
	uint setFrequency(uint Hz);
	bool setOutput(bool State);

	double getVoltage() {return m_U;};
	uint getFrequency() {return m_F;};
	bool getOutput() {return m_state;};
};


CALIBRATOR_API Calibrator *getCalibrator();

#endif