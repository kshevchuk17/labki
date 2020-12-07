#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <Windows.h>
using namespace std;
struct book
{
	char Name[30];
	int year;
	int number_of_pages;
}hook;
HANDLE myFile;
DWORD n;
int main()
{
	
	setlocale(LC_ALL, "russian");
	int number;
	myFile = CreateFile(
		L"C:\\Users\\kiril\\source\\repos\\Laba1\\Laba1\\library.dat", // Имя файла
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (myFile == INVALID_HANDLE_VALUE)
		cout << "Error"; // Файла не существует
	else
		cout << " File is opened\n"; // Файл открыт
	while (ReadFile(myFile, &hook, sizeof(hook), &n, NULL) && n != 0) 
	{
		cout << hook.Name << " " << hook.number_of_pages << " " << hook.year << endl;
	};
	cout << "Bведите номер структуры, которую хотите изменить" << endl;
	int k;
	cin >> k;
	


	//SetFilePointer(myFile, 0, 0, FILE_BEGIN);
	CloseHandle(myFile);
	
	STARTUPINFO StartupInfo;
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof(StartupInfo);
	PROCESS_INFORMATION ProcInfo;
	ZeroMemory(&ProcInfo, sizeof(ProcInfo));
	
	wchar_t daughter[200], t[5];
	wcscpy(daughter, L"C:\\Users\\kiril\\source\\repos\\Dproc\\Debug\\Dproc.exe ");
	swprintf_s(t, L"%d", k);
	wcscat(daughter, t);
	wcout << wstring(daughter) << endl;


	//wchar_t name2[] = L"Dproc.exe"; не работает
	if (!CreateProcess(NULL, daughter, NULL, NULL, FALSE, 0,
		NULL, NULL, &StartupInfo, &ProcInfo)) return 0;

	WaitForSingleObject(ProcInfo.hProcess, INFINITE);
	CloseHandle(ProcInfo.hProcess);
	CloseHandle(ProcInfo.hThread);
	//CloseHandle(myFile);
}
