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
class VOLTMETER_API CVoltmeter {
public:
	CVoltmeter(void);
	// TODO: �������� ����� ���� ������.
};

extern VOLTMETER_API int nVoltmeter;

VOLTMETER_API int fnVoltmeter(void);
