//����� ����������� ������� �������


#include <Windows.h>
#include <iostream>
#include <time.h>

const int n = 10;
volatile int arr[n];
HANDLE hSemaphore;

using namespace std;

DWORD WINAPI fThread1(LPVOID)
{

	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() * 500 / (RAND_MAX)+0;
		cout << "arr[" << i << "] = " << arr[i] << endl;
		ReleaseSemaphore(hSemaphore, 2, NULL);
		Sleep(500);
	}
	return 0;
}

DWORD WINAPI fThread2(LPVOID)
{
	int min = arr[0];
	for (int i = 0; i < n; i++)
	{
		WaitForSingleObject(hSemaphore, INFINITE);
		if (arr[i] < min)
			min = arr[i];
		Sleep(500);
	}

	cout << "min value = " << min << endl;

	return 0;
}

DWORD WINAPI fThread3(LPVOID)
{
	int max = arr[0];
	for (int i = 0; i < n; i++)
	{
		WaitForSingleObject(hSemaphore, INFINITE);
		if (arr[i] > max)
			max = arr[i];
		Sleep(500);
	}

	cout << "max value = " << max << endl;

	return 0;
}

int main()
{
	HANDLE hThread1, hThread2, hThread3;
	DWORD dwIDThread1, dwIDThread2, dwIDThread3;

	hSemaphore = CreateSemaphore(NULL, 0, n, NULL);
	if (hSemaphore == NULL)
	{
		int iErrorCode = GetLastError();
		cerr << "Error while semaphore creating. Error code: " << iErrorCode << endl;
		return iErrorCode;
	}

	hThread1 = CreateThread(NULL, 0, fThread1, NULL, 0, &dwIDThread1);
	if (hThread1 == NULL)
	{
		int iErrorCode = GetLastError();
		cerr << "Error while consumer thread creating. Error code: " << iErrorCode << endl;
		return iErrorCode;
	}

	hThread2 = CreateThread(NULL, 0, fThread2, NULL, 0, &dwIDThread2);
	if (hThread2 == NULL)
	{
		int iErrorCode = GetLastError();
		cerr << "Error while producer thread creating. Error code: " << iErrorCode << endl;
		return iErrorCode;
	}

	hThread3 = CreateThread(NULL, 0, fThread3, NULL, 0, &dwIDThread3);
	if (hThread3 == NULL)
	{
		int iErrorCode = GetLastError();
		cerr << "Error while producer thread creating. Error code: " << iErrorCode << endl;
		return iErrorCode;
	}

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);
	WaitForSingleObject(hThread3, INFINITE);
	CloseHandle(hSemaphore);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	CloseHandle(hThread3);

	return 0;
}