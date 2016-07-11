#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <CommCtrl.h>
#include "student.h"



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

enum {
    STATIC_ID = 1,
    EDIT_ID
};

int WINAPI WinMain (HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
    HINSTANCE hInst;

    const char g_szClassName[] = "myWindowClass";

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Windows hometask",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
        NULL, NULL, hInstance, NULL);






    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hEdit, hStatic;
    static char buf[100];
    char str[100] = "Hello";
    student_t students[5];
            int index = -1;
            students[0] = student_new ("Ruslan", "Hadyniak", 25, 4.6);
            students[1] = student_new ("Vlad", "Sorochynskyi", 17, 4.1);
            students[2] = student_new ("Sasha", "Pischela", 18, 4.0);
            students[3] = student_new ("Helen", "Avramenko", 31, 3.6);
            students[4] = student_new ("Viktor", "Legeza", 55, 5.0);


    switch(msg)
    {
        case WM_CREATE:
            hStatic = CreateWindowEx(0,
                              WC_STATIC,
                              "Label",
                              WS_CHILD | WS_VISIBLE,
                              50, 50, 400, 400,
                              hwnd,
                              (HMENU)STATIC_ID,
                              hwnd,
                              NULL);
            SetWindowText(hStatic, TEXT("Info"));



            hEdit = CreateWindowEx(0,
                              WC_EDIT,
                              "Write index here (from 1 to 5)",
                              WS_CHILD | WS_VISIBLE | WS_BORDER,
                              50, 20, 300, 23,
                              hwnd,
                              (HMENU)EDIT_ID,
                              hwnd,
                              NULL);
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:

            PostQuitMessage(0);
        break;
        case WM_COMMAND:
            if((HIWORD(wParam) == EN_CHANGE) &&  // notification
               (LOWORD(wParam) == EDIT_ID)) {    // your edit control ID
                HWND hEdit = GetDlgItem(hwnd, EDIT_ID);
                GetWindowText(hEdit, buf, sizeof(buf));


            int index = -1;


                index = atoi(buf);
                if (index >= 1 && index <= 5) {
                    //printf("Student\nName: %s %s\nAge: %i\nAverage score: %2f\n",
                    //students[index - 1]->name, students[index - 1]->surname, students[index - 1]->age, students[index - 1]->score);
                    SetWindowText(hStatic, TEXT(student_toString(students[index - 1])));
                }
                else
                    SetWindowText(hStatic, TEXT("Error, no such index\nYou can only write index from 1 to 5"));
            }
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    for (int i = 0; i < 5; i++)
                student_free(students[i]);
    return 0;
}

