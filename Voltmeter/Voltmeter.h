// Приведенный ниже блок ifdef - это стандартный метод создания макросов, упрощающий процедуру 
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа VOLTMETER_EXPORTS,
// в командной строке. Этот символ не должен быть определен в каком-либо проекте
// использующем данную DLL. Благодаря этому любой другой проект, чьи исходные файлы включают данный файл, видит 
// функции VOLTMETER_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifdef VOLTMETER_EXPORTS
#define VOLTMETER_API __declspec(dllexport)
#else
#define VOLTMETER_API __declspec(dllimport)
#endif

// Этот класс экспортирован из Voltmeter.dll
class Voltmeter {
public:
	enum Purpose {EMPTY, REFERENCE, VERIFIED}; 
	Voltmeter(Purpose Which);
	virtual ~Voltmeter();
};

VOLTMETER_API Voltmeter *getVoltmeter(Voltmeter::Purpose Which);
