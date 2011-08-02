// ����������� ���� ���� ifdef - ��� ����������� ����� �������� ��������, ���������� ��������� 
// �������� �� ��������� DLL. ��� ����� ������ DLL �������������� � �������������� ������� VOLTMETER_EXPORTS,
// � ��������� ������. ���� ������ �� ������ ���� ��������� � �����-���� �������
// ������������ ������ DLL. ��������� ����� ����� ������ ������, ��� �������� ����� �������� ������ ����, ����� 
// ������� VOLTMETER_API ��� ��������������� �� DLL, ����� ��� ������ DLL ����� �������,
// ������������ ������ ��������, ��� ����������������.
#ifdef VOLTMETER_EXPORTS
#define VOLTMETER_API __declspec(dllexport)
#else
#define VOLTMETER_API __declspec(dllimport)
#endif

// ���� ����� ������������� �� Voltmeter.dll
class Voltmeter {
public:
	enum Purpose {EMPTY, REFERENCE, VERIFIED}; 
	Voltmeter(Purpose Which);
	virtual ~Voltmeter();
};

VOLTMETER_API Voltmeter *getVoltmeter(Voltmeter::Purpose Which);
