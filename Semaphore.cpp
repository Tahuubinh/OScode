#include <windows.h>
#include <stdio.h>
int x = 0, y = 1;
HANDLE S1, S2;
void T1(){
    while(1){
        WaitForSingleObject(S1,INFINITE);
        x = y + 1;
        ReleaseSemaphore(S2,1,NULL);
        printf("%4d",x);
    }
}
void T2(){
    while(1){
        y = 2;
        y = 2 * y;
        ReleaseSemaphore(S1,1,NULL);
        WaitForSingleObject(S2,INFINITE);
    }
}
int main(){
    HANDLE h1, h2;
    DWORD ThreadId;
    S1 = CreateSemaphore( NULL,0, 1,NULL);
    S2 = CreateSemaphore( NULL,0, 1,NULL);
    h1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)T1, NULL,0,&ThreadId);
    h2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)T2, NULL,0,&ThreadId);
    WaitForSingleObject(h1,INFINITE);
    WaitForSingleObject(h2,INFINITE);
    system("pause");
    return 0;
}