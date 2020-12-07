#include <Windows.h>
#include <iostream>
#include <cstring>

using namespace std;
int value1 = 0, value2 = 0, value3 = 0;
volatile int n;
HANDLE hTh1, hTh2, hTh3;

DWORD WINAPI thread_1()
{
	while (true)
	{
		value1++;
		Sleep(100);
	}

	return 0;
}

DWORD WINAPI thread_2()
{
	while (true)
	{
		value2++;
		Sleep(300);
	}

	return 0;
}

DWORD WINAPI thread_3()
{
	while (true)
	{
		value3++;
		Sleep(600);
	}

	return 0;
}



int main()
{
	int threads_number = 3, max, close1 = 0, close2 = 0, close3 = 0;
	HANDLE hThreadManager;
	DWORD IDThread1, IDThread2, IDThread3, IDThreadManager;



	if ((hTh1 = CreateThread(NULL, 	0, (LPTHREAD_START_ROUTINE)thread_1, NULL, 0, &IDThread1)) == NULL)
	{
		int error = GetLastError();
		cerr << "There is an error while hTh1 thread creating: " << error << endl;
		return error;
	}

	if ((hTh2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_2, NULL, 0, &IDThread2)) == NULL)
	{
		int error = GetLastError();
		cerr << "There is an error while hTh2 thread creating: " << error << endl;
		return error;
	}

	if ((hTh3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_3, NULL, 0, &IDThread3)) == NULL)
	{
		int error = GetLastError();
		cerr << "There is an error while hTh3 thread creating: " << error << endl;
		return error;
	}




	char resp;
	do {
		cout << "'q' Terminate threads" << endl;
		cout << "'w' Write keys" << endl;
		cout << "'s' To clear the biggest value" << endl;
		cin >> resp;
		cin.clear();
		system("cls");

		switch (resp)
		{
		case 'w':
			cout << "value1 = " << value1 << endl;
			cout << "value2 = " << value2 << endl;
			cout << "value3 = " << value3 << endl;
			break;
		case 's':
			max = value2;
			if (value1 > value2)
			{
				max = value1;
			}
			if (value3 > max)
			{
				max = value3;
			}
			if (value1 == max)
			{
				TerminateThread(hTh1, 0);
				close1 = CloseHandle(hTh1);
				cout << "thread_hTh1 was closes" << endl;
			}
			else if (value2 == max)
			{
				TerminateThread(hTh2, 0);
				close2 = CloseHandle(hTh2);
				cout << "thread_hTh2 was closed" << endl;
			}
			else
			{
				TerminateThread(hTh3, 0);
				close3 = CloseHandle(hTh3);
				cout << "thread_hTh3 was closed" << endl;
			}
			break;
		default:
			break;
		}
	} while (resp != 'q');

	
	
	if (close1 != 1) CloseHandle(hTh1);
	if (close2 != 1) CloseHandle(hTh2);
	if (close3 != 1) CloseHandle(hTh3);
	

	return 0;
}
