// Projcet:         Bassi_S21_023_WS_10
// Author:          Jaiveer Bassi
// Date:            February 11, 2021
// Purpose:         Retrieve text from an edit control
//                  Set the text property of the static control
//                  Declare and use the TCHAR data type
//                  Convert TCHAR arrays to string objects
//                  Convert string objects to TCHAR arrays
//

#include "framework.h"
#include "Bassi_S21_023_WS_10.h"
#include <iostream>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hWnd_Show;                        // Show button
HWND hWnd_Input1;                       // edit control
HWND hWnd_Input2;                       // edit control
HWND hWnd_TOTAL;
HWND hWnd_Output;                      // output label
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BASSIS21023WS10, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BASSIS21023WS10));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BASSIS21023WS10));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+0);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BASSIS21023WS10);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 260, 235, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case BN_CLICKED:
                if (LOWORD(lParam) == (WORD)hWnd_Show)
                {
                    TCHAR szInput1[100];
                    TCHAR szInput2[100];
                    string strInput1;
                    string strInput2;
                    string strInputTotal;
                    strInputTotal = strInput1 + strInput2;
                    TCHAR szOutput[100];
                    size_t pReturnValue;
                   

                    SendMessage(
                        hWnd_Input1,
                        WM_GETTEXT,
                        100,
                        LPARAM(szInput1)
                    );
                    SendMessage(
                        hWnd_Input2,
                        WM_GETTEXT,
                        100,
                        LPARAM(szInput2)
                    );

                    strInput1.assign(
                        &szInput1[0],
                        &szInput1[_tcslen(szInput1)]
                    );
                    strInput2.assign(
                        &szInput2[0],
                        &szInput2[_tcslen(szInput2)]
                    );
                    strInputTotal = strInput1 + strInput2;
                    mbstowcs_s(
                        &pReturnValue,
                        szOutput,
                        100,
                        strInputTotal.c_str(),
                        100);
                    SendMessage(
                        hWnd_Output,
                        WM_SETTEXT,
                        NULL,
                        LPARAM(szOutput));
                }

                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_CREATE:

        // create prompt
        CreateWindow(                 // prompt
            TEXT("STATIC"),            // label
            TEXT("Enter text:"),       // display
            WS_VISIBLE | WS_CHILD,     // options
            10, 10, 75, 20,            // xy xy
            hWnd, NULL, NULL, NULL);   // parent
       ///////////////////////////////////////////
        CreateWindow(                  // prompt
            TEXT("STATIC"),            // label
            TEXT("Enter text:"),       // display
            WS_VISIBLE | WS_CHILD,     // options
            10, 50, 75, 20,            // xy xy
            hWnd, NULL, NULL, NULL);   // parent

        // create input
        hWnd_Input1 = CreateWindow(             // input
            TEXT("EDIT"),                       // edit control
            TEXT(""),                           // empty
            WS_VISIBLE | WS_CHILD |             // options
            WS_BORDER | ES_AUTOHSCROLL,
            110, 10, 100, 20,                   // xy xy
            hWnd, NULL, NULL, NULL);            // parent
        hWnd_Input2 = CreateWindow(              // input
            TEXT("EDIT"),                       // edit control
            TEXT(""),                           // empty
            WS_VISIBLE | WS_CHILD |             // options
            WS_BORDER | ES_AUTOHSCROLL,
            110, 50, 100, 20,                   // xy xy
            hWnd, NULL, NULL, NULL);            // parent
         // create output
        hWnd_Output = CreateWindow(            // output
            TEXT("STATIC"),                     // label
            TEXT(""),                           // empty
            WS_VISIBLE | WS_CHILD |             // options
            WS_BORDER,                          // border to show limits
            40, 85, 170, 20,                    // xy xy
            hWnd, NULL, NULL, NULL);            // parent

         // create show button
        hWnd_Show = CreateWindow(              // Show button
            TEXT("BUTTON"),                     // button control
            TEXT("Append"),                       // label
            WS_VISIBLE | WS_CHILD |             // options
            BS_DEFPUSHBUTTON,
            70, 125, 90, 30,                    // xy xy
            hWnd, NULL, NULL, NULL);            // parent

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
