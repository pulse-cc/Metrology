// Приведенный ниже блок ifdef - это стандартный метод создания макросов, упрощающий процедуру 
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа CALIBRATOR_EXPORTS,
// в командной строке. Этот символ не должен быть определен в каком-либо проекте
// использующем данную DLL. Благодаря этому любой другой проект, чьи исходные файлы включают данный файл, видит 
// функции CALIBRATOR_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifdef CALIBRATOR_EXPORTS
#define CALIBRATOR_API __declspec(dllexport)
#else
#define CALIBRATOR_API __declspec(dllimport)
#endif

// Этот класс экспортирован из Calibrator.dll
class CALIBRATOR_API CCalibrator {
public:
	CCalibrator(void);
	// TODO: Добавьте здесь свои методы.
};

extern CALIBRATOR_API int nCalibrator;

CALIBRATOR_API int fnCalibrator(void);
