#include "lab3.h"
#include <windows.h>
#include <iostream>

#define MAX_SEM_COUNT 10
#define THREADCOUNT 12

HANDLE ghSemaphoreA, ghSemaphoreB, ghSemaphoreC, mutex;
HANDLE aThread[THREADCOUNT];
DWORD ThreadID;

DWORD WINAPI ThB(LPVOID); //1
DWORD WINAPI ThC(LPVOID); //2
DWORD WINAPI ThD(LPVOID); //3
DWORD WINAPI ThE(LPVOID); //4
DWORD WINAPI ThF(LPVOID); //5
DWORD WINAPI ThG(LPVOID); //6
DWORD WINAPI ThH(LPVOID); //7
DWORD WINAPI ThI(LPVOID); //8
DWORD WINAPI ThK(LPVOID); //9
DWORD WINAPI ThM(LPVOID); //10
DWORD WINAPI ThN(LPVOID); //11

int a, b, c, d, e;


//
// lab3 code should be located here!
//


unsigned int lab3_thread_graph_id() 
{
    return 2;
}

const char* lab3_unsynchronized_threads()
{
    return "bcde";
}

const char* lab3_sequential_threads()
{
    return "ikm";
}

DWORD WINAPI ThA(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "a" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI ThB(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "b" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    //waiting for A to end
    WaitForSingleObject(aThread[0], INFINITE);
    CloseHandle(aThread[0]);
    //start C, D, E threads
    aThread[2] = CreateThread(NULL, 0, ThC, NULL, 0, &ThreadID);
    if (aThread[2] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }
    aThread[3] = CreateThread(NULL, 0, ThD, NULL, 0, &ThreadID);
    if (aThread[3] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }
    aThread[4] = CreateThread(NULL, 0, ThE, NULL, 0, &ThreadID);
    if (aThread[4] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }
    //continue thread
    a=0;
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "b" << std::flush;
        a++;
        ReleaseMutex(mutex);
        computation();
    }
    //waiting last to end
    WaitForSingleObject(aThread[4], INFINITE);
    CloseHandle(aThread[4]);
    return 0;
}

DWORD WINAPI ThC(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "c" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    do {computation();} while (a!=3);
    return 0;
}

DWORD WINAPI ThD(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "d" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    WaitForSingleObject(aThread[2] , INFINITE);
    CloseHandle(aThread[2]);
    return 0;
}

DWORD WINAPI ThE(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "e" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    //waiting for D to end
    WaitForSingleObject(aThread[3], INFINITE);
    CloseHandle(aThread[3]);
    //start F, G, H, I threads
    aThread[5] = CreateThread(NULL, 0, ThF, NULL, 0, &ThreadID);
    if (aThread[5] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }
    aThread[6] = CreateThread(NULL, 0, ThG, NULL, 0, &ThreadID);
    if (aThread[6] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }
    aThread[7] = CreateThread(NULL, 0, ThH, NULL, 0, &ThreadID);
    if (aThread[7] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }
    aThread[8] = CreateThread(NULL, 0, ThI, NULL, 0, &ThreadID);
    if (aThread[8] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }
    //continue thread
    b=0;
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout  << "e" << std::flush;
        b++;
        ReleaseMutex(mutex);
        computation();
    }
    //waiting for I to end
    WaitForSingleObject(aThread[8], INFINITE);
    CloseHandle(aThread[8]);
    return 0;
}

DWORD WINAPI ThF(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "f" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI ThG(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "g" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    WaitForSingleObject(aThread[5], INFINITE);
    CloseHandle(aThread[5]);
    return 0;
}

DWORD WINAPI ThH(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "h" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    WaitForSingleObject(aThread[6], INFINITE);
    CloseHandle(aThread[6]);
    return 0;
}

DWORD WINAPI ThI(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "i" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    do {computation();} while (b!=3);
    //waiting for H to end
    WaitForSingleObject(aThread[7], INFINITE);
    CloseHandle(aThread[7]);
    //start K, M threads
    aThread[9] = CreateThread(NULL, 0, ThK, NULL, 0, &ThreadID);
    if (aThread[9] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }
    aThread[10] = CreateThread(NULL, 0, ThM, NULL, 0, &ThreadID);
    if (aThread[10] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }
    //continue thread
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghSemaphoreA, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "i" << std::flush;
        ReleaseMutex(mutex);
        ReleaseSemaphore(ghSemaphoreB, 1, NULL);
        computation();
    }
    //waiting for I to end
    WaitForSingleObject(aThread[9], INFINITE);
    CloseHandle(aThread[9]);
    return 0;
}

DWORD WINAPI ThM(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghSemaphoreC, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "m" << std::flush;
        ReleaseMutex(mutex);
        ReleaseSemaphore(ghSemaphoreA, 1, NULL);
        computation();
    }
    return 0;
}

DWORD WINAPI ThK(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghSemaphoreB, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "k" << std::flush;
        ReleaseMutex(mutex);
        ReleaseSemaphore(ghSemaphoreC, 1, NULL);
        computation();
    }
    WaitForSingleObject(aThread[10], INFINITE);
    CloseHandle(aThread[10]);
    aThread[11] = CreateThread(NULL, 0, ThN, NULL, 0, &ThreadID);
    if (aThread[11] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }
    WaitForSingleObject(aThread[11], INFINITE);
    CloseHandle(aThread[11]);
    return 0;
}

DWORD WINAPI ThN(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << "n" << std::flush;
        ReleaseMutex(mutex);
        computation();
    }
    return 0;
}

int lab3_init()
{
    ghSemaphoreA = CreateSemaphore(
       NULL,           // default security attributes // аттрибуты безопасности по умолчанию
       1,  // initial count               // начальное значение счетчика
       MAX_SEM_COUNT,  // maximum count               // максимаьлное значение счетчика
       NULL); 
    ghSemaphoreB = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    ghSemaphoreC = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    mutex = CreateMutex(NULL, FALSE, NULL);
    aThread[0] = CreateThread(NULL, 0, ThA, NULL, 0, &ThreadID);
    if (aThread[0] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }
    aThread[1] = CreateThread(NULL, 0, ThB, NULL, 0, &ThreadID);
    if (aThread[1] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }
    WaitForSingleObject(aThread[1], INFINITE);
    CloseHandle(aThread[1]);
    CloseHandle(ghSemaphoreA);
    CloseHandle(ghSemaphoreB);
    CloseHandle(ghSemaphoreC);
    CloseHandle(mutex);
    // ...
    return 0;
}
