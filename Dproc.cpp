#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>
using namespace std;
struct book
{
    char Name[30];
    int year;
    int number_of_pages;
}hook[20];

DWORD n;
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "russian");
    HANDLE myFile;

    myFile = CreateFile(
        L"C:\\Users\\kiril\\source\\repos\\Laba1\\Laba1\\library.dat", // Имя файла
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (myFile == INVALID_HANDLE_VALUE)
        cout << "Error\n"; // Файла не существует
    else
        cout << " File is opened\n"; // Файл открыт
    int i = 0;
    SetFilePointer(myFile, 0, 0, FILE_BEGIN);
    while (ReadFile(myFile, &hook[i], sizeof(hook[i]), &n, NULL) && n != 0)
    {
        cout << hook[i].Name << " " << hook[i].number_of_pages << " " << hook[i].year << endl;
        i++;
    };
    stringstream convert(argv[1]);
    int number;
    convert >> number;
    for (int j = 0; j < i; j++)
    {
       
            if (number == j)
            {
                cout << "Перезапишите поля строки" << j << endl;
                cout << "название книги:" << endl;
                cin >> hook[j].Name;
                cout << "кол-во страниц:" << endl;
                cin >> hook[j].number_of_pages;
                cout << "год написания:" << endl;
                cin >> hook[j].year;
            }
       
    }
    
    CloseHandle(myFile);
   
    myFile = CreateFile(
        L"C:\\Users\\kiril\\source\\repos\\Laba1\\Laba1\\library.dat", // Имя файла
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (myFile == INVALID_HANDLE_VALUE)
        cout << "Error"; // Файла не существует
    else
        cout << " File is opened\n"; // Файл открыт
    for (int j = 0; j < i; j++) WriteFile(myFile, &hook[j], sizeof(hook[j]), &n, NULL);
    cout << "Well done" << endl;
}

