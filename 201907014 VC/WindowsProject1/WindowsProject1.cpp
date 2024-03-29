﻿// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject1.h"
#include <stdlib.h>
#include <time.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
int mtime;
RECT pbody, obody, pleg, oleg, parm, oarm;
RECT health, ohealth, hit, ohit;
WPARAM wparam;
BOOL g, h, w, up, two, three, ai;
static HBITMAP standbit;
static HBITMAP punchbit;
static HBITMAP kickbit;
static HBITMAP ostandbit;
static HBITMAP opunchbit;
static HBITMAP okickbit;
static HBITMAP ko;

HPEN vis, invis;
HBRUSH bvis, binvis;

//캐릭터 모양, 메뉴

void drawbitmap(HDC hdc, int x, int y, HBITMAP hbitmap) {
    HDC MemDC;
    HBITMAP oldbitmap;
    int bx, by;
    BITMAP bitmap;

    MemDC = CreateCompatibleDC(hdc);
    oldbitmap = (HBITMAP)SelectObject(MemDC, hbitmap);

    GetObject(hbitmap, sizeof(BITMAP), &bitmap);
    bx = bitmap.bmWidth;
    by = bitmap.bmHeight;

    BitBlt(hdc, x, y, bx, by, MemDC, 0, 0, SRCCOPY);
    SelectObject(MemDC, oldbitmap);
    DeleteDC(MemDC);
}

DWORD WINAPI punch(LPVOID param) {  
    HWND hWnd = (HWND)param;
    parm.right += 100;
    HDC hdc;
    hdc = GetDC(hWnd);
    drawbitmap(hdc, pbody.left, pbody.top, punchbit);
    if (IntersectRect(&ohit, &parm, &obody)) {
        ohealth.left += rand() % 100;
        if (ohealth.left >= 1400){
            KillTimer(hWnd, 1);
            MessageBox(hWnd, L"1P 승리", L"게임 끝", MB_OK); 
        }
    }

    Sleep(90);
    parm.right -= 100;
    InvalidateRect(hWnd, NULL, true);
    ReleaseDC(hWnd, hdc);
    ExitThread(0);
    return 0;
}
DWORD WINAPI kick(LPVOID param) {
    HWND hWnd = (HWND)param;
    HDC hdc;
    hdc = GetDC(hWnd);
    drawbitmap(hdc, pbody.left, pbody.top, kickbit);
    pleg.right += 180;
    if (IntersectRect(&ohit, &pleg, &oleg)) {
        ohealth.left += rand() % 70;
        if (ohealth.left >= 1400) {
            KillTimer(hWnd, 1);
            MessageBox(hWnd, L"1P 승리", L"게임 끝", MB_OK);
        }
    }
    Sleep(90);
    pleg.right -= 180;
    InvalidateRect(hWnd, NULL, true);
    ReleaseDC(hWnd, hdc);
    ExitThread(0);
    return 0;
}
DWORD WINAPI opunch(LPVOID param) {
    HWND hWnd = (HWND)param;
    HDC hdc;
    hdc = GetDC(hWnd);
    drawbitmap(hdc, obody.left - 100, obody.top, opunchbit);
    oarm.left -= 100;
    if (IntersectRect(&hit, &oarm, &pbody)) {
        health.right -= rand() % 100;
        if (health.right <= 10) {
            KillTimer(hWnd, 1);
            MessageBox(hWnd, L"2P 승리", L"게임 끝", MB_OK);
        }  
    }
    Sleep(90);
    oarm.left += 100;
    InvalidateRect(hWnd, NULL, true);
    ReleaseDC(hWnd, hdc);
    ExitThread(0);
    return 0;
}
DWORD WINAPI okick(LPVOID param) {
    HWND hWnd = (HWND)param;
    HDC hdc;
    hdc = GetDC(hWnd);
    drawbitmap(hdc, obody.left - 180, obody.top, okickbit);
    oleg.left -= 180;
    if (IntersectRect(&hit, &oleg, &pleg)) {
        health.right -= rand() % 70;
        if (health.right <= 10) {
            KillTimer(hWnd, 1);
            MessageBox(hWnd, L"2P 승리", L"게임 끝", MB_OK);
        }
    }
    Sleep(90);
    oleg.left += 180;
    InvalidateRect(hWnd, NULL, true);
    ReleaseDC(hWnd, hdc);
    ExitThread(0);
    return 0;
}


HANDLE hdl[10000] = { NULL, };
int idx = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case solo:
                SetTimer(hWnd, 1, mtime, NULL);
                break;
            case duo:
                KillTimer(hWnd, 1);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_TIMER:
    {

        if (wParam == 1) {
            int x = rand() % 4 + 1;
            if (x == 1) {
                mtime = rand() % 50;
                KillTimer(hWnd, 1);
                SetTimer(hWnd, 1, mtime, NULL);
                if (obody.left > pbody.right) {
                    obody.left -= 25;
                    obody.right -= 25;
                    oarm.left -= 25;
                    oarm.right -= 25;
                    oleg.left -= 25;
                    oleg.right -= 25;
                    InvalidateRect(hWnd, NULL, true);
                }
            }
            else if (x == 2) {
                mtime = rand() % 90;
                KillTimer(hWnd, 1);
                SetTimer(hWnd, 1, mtime, NULL);
                if (obody.left > pbody.right && obody.right < 1400) {
                    obody.left += 25;
                    obody.right += 25;
                    oarm.left += 25;
                    oarm.right += 25;
                    oleg.left += 25;
                    oleg.right += 25;
                    InvalidateRect(hWnd, NULL, true);
                }
            }
            else if (x == 3) {
                mtime = rand() % 60 + 90;
                KillTimer(hWnd, 1);
                SetTimer(hWnd, 1, mtime, NULL);
                DWORD tid = 0;
                if(obody.left < pbody.right + 70)
                hdl[idx++] = CreateThread(NULL, 0, opunch, hWnd, 0, &tid);
            }
            else if (x == 4) {
                mtime = rand() % 60 + 90;
                KillTimer(hWnd, 1);
                SetTimer(hWnd, 1, mtime, NULL);
                DWORD tid = 0;
                if (obody.left < pbody.right + 120)
                hdl[idx++] = CreateThread(NULL, 0, okick, hWnd, 0, &tid);
            }
        }
    }
    break;
    case WM_CREATE:

    {
        punchbit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
        opunchbit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
        standbit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));
        ostandbit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
        kickbit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
        okickbit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
        ko = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7));
        srand((unsigned int)time(NULL));

        health.left = 10;
        health.top = 10;
        health.right = 640;
        health.bottom = 35;

        ohealth.left = 770;
        ohealth.top = 10;
        ohealth.right = 1400;
        ohealth.bottom = 35;

        pbody.top = 220;
        pbody.left = 10;
        pbody.right = 110;
        pbody.bottom = 450;

        parm.top = pbody.top + 30;
        parm.bottom = pbody.bottom - 50;
        parm.left = pbody.left + 30;
        parm.right = pbody.right - 30;

        pleg.top = pbody.bottom;
        pleg.bottom = pleg.top + 250;
        pleg.left = pbody.left + 30;
        pleg.right = pbody.right - 30;

        obody.left = 1300;
        obody.top = 220;
        obody.right = 1400;
        obody.bottom = 450;

        oarm.top = obody.top + 30;
        oarm.bottom = obody.bottom - 50;
        oarm.left = obody.left + 30;
        oarm.right = obody.right - 30;

        oleg.top = obody.bottom;
        oleg.bottom = oleg.top + 250;
        oleg.left = obody.left + 30;
        oleg.right = obody.right - 30;

        

    }
    break;
    case WM_KEYDOWN:
    {
        // 키 값에 따라 처리를 수행
        switch (wParam)
        {
            // 왼쪽 방향키 입력
        case VK_LEFT:
            obody.left -= 25;
            obody.right -= 25;
            oarm.left -= 25;
            oarm.right -= 25;
            oleg.left -= 25;
            oleg.right -= 25;
            break;
            // 오른쪽 방향키 입력
        case VK_RIGHT:
            obody.left += 25;
            obody.right += 25;
            oarm.left += 25;
            oarm.right += 25;
            oleg.left += 25;
            oleg.right += 25;
            break;
        case 0x41: //a
            pbody.left -= 25;
            pbody.right -= 25;
            parm.left -= 25;
            parm.right -= 25;
            pleg.left -= 25;
            pleg.right -= 25;
            break;
        case 0x44: //d
            pbody.left += 25;
            pbody.right += 25;
            parm.left += 25;
            parm.right += 25;
            pleg.left += 25;
            pleg.right += 25;
            break;
        case 0x47: //g
        {     
                DWORD tid = 0;
                wparam = wParam;
                if (g || health.right <= 10)
                    break;
                hdl[idx++] = CreateThread(NULL, 0, punch, hWnd, 0, &tid);
                g = true;
        }
            break;
        case 0x48: //h
        {
            DWORD tid = 0;
            wparam = wParam;
            if (h || health.right <= 10)
                break;
            hdl[idx++] = CreateThread(NULL, 0, kick, hWnd, 0, &tid);
            h = true;
        }
            break;
        case VK_NUMPAD2: //2
        {     
                DWORD tid = 0;
                wparam = wParam;
                if (two || ohealth.left >= 1400)
                    break;
                hdl[idx++] = CreateThread(NULL, 0, opunch, hWnd, 0, &tid);
                two = true;
        }
        break;
        case VK_NUMPAD3: //3
        {
            DWORD tid = 0;
            wparam = wParam;
            if (three || ohealth.left >= 1400)
                break;
            hdl[idx++] = CreateThread(NULL, 0, okick, hWnd, 0, &tid);
            three = true;
        }
        break;
        }
            // 위쪽 방향키 입력
        /*case VK_UP:
            g_rect.top -= 10;
            g_rect.bottom -= 10;
            break;

            // 아래쪽 방향키 입력
        case VK_DOWN:
            g_rect.top += 10;
            g_rect.bottom += 10;
            break;
        }
        */
    
        // 그라운드 범위 확인 및 좌표 재설정
        if (pbody.left < 10)
        {
            pbody.left = 10;
            pbody.right = 110;
            parm.left = pbody.left + 30;
            parm.right = pbody.right - 30;
            pleg.left = pbody.left + 30;
            pleg.right = pbody.right - 30;
        }

        if (pbody.right > 1400)
        {
            pbody.left = 1300;
            pbody.right = 1400;
            parm.left = pbody.left + 30;
            parm.right = pbody.right - 30;
            pleg.left = pbody.left + 30;
            pleg.right = pbody.right - 30;
        }
        if (obody.left < 10)
        {
            obody.left = 10;
            obody.right = 110;
            oarm.left = obody.left + 30;
            oarm.right = obody.right - 30;
            oleg.left = obody.left + 30;
            oleg.right = obody.right - 30;
        }

        if (obody.right > 1400)
        {
            obody.left = 1300;
            obody.right = 1400;
            oarm.left = obody.left + 30;
            oarm.right = obody.right - 30;
            oleg.left = obody.left + 30;
            oleg.right = obody.right - 30;
        }
        if (pbody.right > obody.left)
        {
            pbody.right = obody.left;
            pbody.left = pbody.right - 100;
            obody.right = obody.left + 100;
            parm.left = pbody.left + 30;
            parm.right = pbody.right - 30;
            pleg.left = pbody.left + 30;
            pleg.right = pbody.right - 30;
            oarm.left = obody.left + 30;
            oarm.right = obody.right - 30;
            oleg.left = obody.left + 30;
            oleg.right = obody.right - 30;
        }


        


        // 변경된 좌표 값이 적용된 그림을 그리도록 화면 무효화를 요청
        InvalidateRect(hWnd, NULL, true);
        }
    break;
    case WM_KEYUP:
    {
        switch (wParam)
        {
        case 0x47:
        {
            g = false;
        }
        break;
        case 0x48:
        {
            h = false;
        }
        break;
        case VK_NUMPAD2:
        {
            two = false;
        }
        break;
        case VK_NUMPAD3:
        {
            three = false;
        }
        break;
        case 0x57:
        {
            w = false;
        }
        break;
        }
        break;
    }
        
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            Rectangle(hdc, health.left, health.top, health.right, health.bottom);
            Rectangle(hdc, ohealth.left, ohealth.top, ohealth.right, ohealth.bottom);
            if (health.right <= 10) {
                drawbitmap(hdc, pbody.left, pbody.top, ko);
            }
            else {
                drawbitmap(hdc, pbody.left, pbody.top, standbit);
            }
            if (ohealth.left >= 1400) {
                drawbitmap(hdc, obody.left, obody.top, ko);
            }
            else{
                drawbitmap(hdc, obody.left, obody.top, ostandbit);
            }
            vis = (HPEN)SelectObject(hdc, invis);
            bvis = (HBRUSH)(SelectObject(hdc, binvis));
            SelectObject(hdc, invis);
            SelectObject(hdc, GetStockObject(NULL_PEN));
            SelectObject(hdc, binvis);
            SelectObject(hdc, GetStockObject(NULL_BRUSH));

            Rectangle(hdc, pbody.left, pbody.top, pbody.right, pbody.bottom);
            Rectangle(hdc, obody.left, obody.top, obody.right, obody.bottom);
            Rectangle(hdc, pleg.left, pleg.top, pleg.right, pleg.bottom);
            Rectangle(hdc, parm.left, parm.top, parm.right, parm.bottom);
            Rectangle(hdc, oleg.left, oleg.top, oleg.right, oleg.bottom);
            Rectangle(hdc, oarm.left, oarm.top, oarm.right, oarm.bottom);

            DeleteObject(SelectObject(hdc, vis));
            DeleteObject(SelectObject(hdc, invis));
            DeleteObject(SelectObject(hdc, bvis));
            DeleteObject(SelectObject(hdc, binvis));
            

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
