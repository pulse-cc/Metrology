// ����������� ���� ���� ifdef - ��� ����������� ����� �������� ��������, ���������� ��������� 
// �������� �� ��������� DLL. ��� ����� ������ DLL �������������� � �������������� ������� CALIBRATOR_EXPORTS,
// � ��������� ������. ���� ������ �� ������ ���� ��������� � �����-���� �������
// ������������ ������ DLL. ��������� ����� ����� ������ ������, ��� �������� ����� �������� ������ ����, ����� 
// ������� CALIBRATOR_API ��� ��������������� �� DLL, ����� ��� ������ DLL ����� �������,
// ������������ ������ ��������, ��� ����������������.
#ifdef CALIBRATOR_EXPORTS
#define CALIBRATOR_API __declspec(dllexport)
#else
#define CALIBRATOR_API __declspec(dllimport)
#endif

// ���� ����� ������������� �� Calibrator.dll
class CALIBRATOR_API CCalibrator {
public:
	CCalibrator(void);
	// TODO: �������� ����� ���� ������.
};

extern CALIBRATOR_API int nCalibrator;

CALIBRATOR_API int fnCalibrator(void);
