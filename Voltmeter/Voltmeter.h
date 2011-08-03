#ifndef  __VOLTMETER_H__
#define  __VOLTMETER_H__

#ifdef VOLTMETER_EXPORTS
#define VOLTMETER_API __declspec(dllexport)
#else
#define VOLTMETER_API __declspec(dllimport)
#endif

class VOLTMETER_API Voltmeter {
	pvoid m_data;
public:
	enum Purpose {EMPTY, REFERENCE, VERIFIED}; 
	Voltmeter(Purpose Which);
	virtual ~Voltmeter();
	double getVoltage();
};

VOLTMETER_API Voltmeter *getVoltmeter(Voltmeter::Purpose Which);

#endif