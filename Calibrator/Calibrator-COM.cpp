#include "stdafx.h"
#include "Calibrator.h"

static Calibrator *pC = new Calibrator();

CALIBRATOR_API Calibrator *getCalibrator(void)
{
	char sendStr[255];
	BYTE buffer[255];
	sprintf(sendStr, "C\r\n");
	memcpy(&buffer,&sendStr,sizeof(sendStr));
	//послали
	sprintf(sendStr, "MI\r\n");
	memcpy(&buffer,&sendStr,sizeof(sendStr));
	//послали
	return pC;
}

Calibrator::Calibrator()
{
	printf("Creating calibrator\n");
}

Calibrator::~Calibrator()
{
}

double Calibrator::setVoltage(double Volt)
{
	char sendStr[255];
	BYTE buffer[255];
	sprintf(sendStr, "S%f\r\n",Volt);
	memcpy(&buffer,&sendStr,sizeof(sendStr));
	//printf("%X%X%X%X\n",buffer[0],buffer[1],buffer[2],buffer[3]);
	//послали
	LSleep(100);
	m_U = Volt;
	// send to device
	return m_U;
}

uint Calibrator::setFrequency(uint Hz)
{
	char sendStr[255];
	BYTE buffer[255];
	sprintf(sendStr, "FH%d\r\n",Hz);
	memcpy(&buffer,&sendStr,sizeof(sendStr));
	//послали
	LSleep(100);
	m_F = Hz;
	// send to device
	return m_F;
}

bool Calibrator::setOutput(bool State)
{
	char sendStr[255];
	BYTE buffer[255];
	if(State){
		sprintf(sendStr, "O1\r\n");
	}
	else{
		sprintf(sendStr, "O0\r\n");
	}
	memcpy(&buffer,&sendStr,sizeof(sendStr));
	//послали
	LSleep(100);
	m_state = State;
	// send to device
	return m_state;
}
