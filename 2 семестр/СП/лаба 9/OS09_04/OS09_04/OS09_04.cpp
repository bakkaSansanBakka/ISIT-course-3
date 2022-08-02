#include <windows.h>
#include <iostream>
using namespace std;

BOOL printWatchRowFileTxt(LPWSTR FileName, DWORD mlsec) {
    try {
        HANDLE file = CreateFile(
            FileName,
            GENERIC_WRITE | GENERIC_READ,
            NULL,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        if (file == INVALID_HANDLE_VALUE) throw "open file failed\n";
        else cout << "open file successful" << endl;

        DWORD size = GetFileSize(file, NULL);

        CloseHandle(file);

        HANDLE dwChangeHandle = FindFirstChangeNotification((LPWSTR)L"E:\\3 курс\\2 семестр\\Системное программирование\\лаба 1", FALSE, FILE_NOTIFY_CHANGE_SIZE);
        if (dwChangeHandle == INVALID_HANDLE_VALUE) throw "find first change failed";
        
        cout << "start change notification" << endl;

        DWORD dwWaitStatus = WaitForSingleObject(dwChangeHandle, mlsec);

        if (dwWaitStatus == WAIT_OBJECT_0)
        {
            cout << "Some changes" << endl;

            FindCloseChangeNotification(dwChangeHandle);
            HANDLE file2;
            while (true)
            {
                file2 = CreateFile(FileName, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                if (file2 != INVALID_HANDLE_VALUE) break;
            }
            if (size < GetFileSize(file2, NULL)) cout << "Added strings" << endl;
            else cout << "Deleted strings" << endl;
            CloseHandle(file2);
        }
    }
    catch (const char* error_message) {
        cout << "Error: " << error_message;

        return false;
    }
    return true;
}

int main()
{
    const wchar_t* fileName = L"E:\\3 курс\\2 семестр\\Системное программирование\\лаба 1\\OS09_01.txt";
    DWORD mlsec = 60000;

    printWatchRowFileTxt((LPWSTR)fileName, mlsec);

    return 0;
}