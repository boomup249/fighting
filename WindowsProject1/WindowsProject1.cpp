// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject1.h"

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
int p_l, p_r, p_t, p_b, o_l, o_r, o_t, o_b;
int p_legl, p_legr, p_legt, p_legb, o_legl, o_legr, o_legt, o_legb;
int p_arml, p_armr, p_armt, p_armb, o_arml, o_armr, o_armt, o_armb;
WPARAM wparam;
BOOL g, h, w, up, two, three;

DWORD WINAPI punch(LPVOID param) {
    HWND hWnd = (HWND)param;
    int armr;
    HDC hdc;
    hdc = GetDC(hWnd);
    armr = p_armr + 100;
    Rectangle(hdc, p_arml, p_armt, armr, p_armb);
    Sleep(90);
    InvalidateRect(hWnd, NULL, true);
    Rectangle(hdc, p_arml, p_armt, p_armr, p_armb);
    ReleaseDC(hWnd, hdc);
    ExitThread(0);
    return 0;
}
DWORD WINAPI kick(LPVOID param) {
    HWND hWnd = (HWND)param;
    int legr;
    HDC hdc;
    hdc = GetDC(hWnd);
    legr = p_legr + 180;
    Rectangle(hdc, p_legl, p_legt, legr, p_legb);
    Sleep(90);
    InvalidateRect(hWnd, NULL, true);
    Rectangle(hdc, p_legl, p_legt, p_legr, p_legb);
    ReleaseDC(hWnd, hdc);
    ExitThread(0);
    return 0;
}
DWORD WINAPI opunch(LPVOID param) {
    HWND hWnd = (HWND)param;
    int arml;
    HDC hdc;
    hdc = GetDC(hWnd);
    arml = o_arml - 100;
    Rectangle(hdc, arml, o_armt, o_armr, o_armb);
    Sleep(90);
    InvalidateRect(hWnd, NULL, true);
    Rectangle(hdc, o_arml, o_armt, o_armr, o_armb);
    ReleaseDC(hWnd, hdc);
    ExitThread(0);
    return 0;
}
DWORD WINAPI okick(LPVOID param) {
    HWND hWnd = (HWND)param;
    int legl;
    HDC hdc;
    hdc = GetDC(hWnd);
    legl = o_legl - 180;
    Rectangle(hdc, legl, o_legt, o_legr, o_legb);
    Sleep(90);
    InvalidateRect(hWnd, NULL, true);
    Rectangle(hdc, o_legl, o_legt, o_legr, o_legb);
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
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_CREATE:
    {


        p_t = 220;
        p_l = 10;
        p_r = 110;
        p_b = 450;

        p_armt = p_t + 30;
        p_armb = p_b - 50;
        p_arml = p_l + 30;
        p_armr = p_r - 30;

        p_legt = p_b;
        p_legb = p_legt + 250;
        p_legl = p_l + 30;
        p_legr = p_r - 30;

        o_l = 1300;
        o_t = 220;
        o_r = 1400;
        o_b = 450;

        o_armt = o_t + 30;
        o_armb = o_b - 50;
        o_arml = o_l + 30;
        o_armr = o_r - 30;

        o_legt = o_b;
        o_legb = o_legt + 250;
        o_legl = o_l + 30;
        o_legr = o_r - 30;


    }
    break;
    case WM_KEYDOWN:
    {
        // 키 값에 따라 처리를 수행
        switch (wParam)
        {
            // 왼쪽 방향키 입력
        case VK_LEFT:
            o_l -= 25;
            o_r -= 25;
            o_arml -= 25;
            o_armr -= 25;
            o_legl -= 25;
            o_legr -= 25;
            break;
            // 오른쪽 방향키 입력
        case VK_RIGHT:
            o_l += 25;
            o_r += 25;
            o_arml += 25;
            o_armr += 25;
            o_legl += 25;
            o_legr += 25;
            break;
        case 0x41:
            p_l -= 25;
            p_r -= 25;
            p_arml -= 25;
            p_armr -= 25;
            p_legl -= 25;
            p_legr -= 25;
            break;
        case 0x44:
            p_l += 25;
            p_r += 25;
            p_arml += 25;
            p_armr += 25;
            p_legl += 25;
            p_legr += 25;
            break;
        case 0x47:
        {     
                DWORD tid = 0;
                wparam = wParam;
                if (g)
                    break;
                hdl[idx++] = CreateThread(NULL, 0, punch, hWnd, 0, &tid);
                g = true;
        }
            break;
        case 0x48:
        {
            DWORD tid = 0;
            wparam = wParam;
            if (h)
                break;
            hdl[idx++] = CreateThread(NULL, 0, kick, hWnd, 0, &tid);
            h = true;
        }
            break;
        case 0x62:
        {     
                DWORD tid = 0;
                wparam = wParam;
                if (h)
                    break;
                hdl[idx++] = CreateThread(NULL, 0, opunch, hWnd, 0, &tid);
                two = true;
        }
        break;
        case 0x63:
        {
            DWORD tid = 0;
            wparam = wParam;
            if (h)
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
        if (p_l < 10)
        {
            p_l = 10;
            p_r = 110;
            p_arml = p_l + 30;
            p_armr = p_r - 30;
            p_legl = p_l + 30;
            p_legr = p_r - 30;
        }

        if (p_r > 1400)
        {
            p_l = 1300;
            p_r = 1400;
            p_arml = p_l + 30;
            p_armr = p_r - 30;
            p_legl = p_l + 30;
            p_legr = p_r - 30;
        }
        if (o_l < 10)
        {
            o_l = 10;
            o_r = 110;
            o_arml = o_l + 30;
            o_armr = o_r - 30;
            o_legl = o_l + 30;
            o_legr = o_r - 30;
        }

        if (o_r > 1400)
        {
            o_l = 1300;
            o_r = 1400;
            o_arml = o_l + 30;
            o_armr = o_r - 30;
            o_legl = o_l + 30;
            o_legr = o_r - 30;
        }
        if (p_r > o_l)
        {
            p_r = o_l;
            p_l = p_r - 100;
            o_r = o_l + 100;
            p_arml = p_l + 30;
            p_armr = p_r - 30;
            p_legl = p_l + 30;
            p_legr = p_r - 30;
            o_arml = o_l + 30;
            o_armr = o_r - 30;
            o_legl = o_l + 30;
            o_legr = o_r - 30;
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
        }
    case 0x62:
    {
        two = false;
    }
    break;
    case 0x63:
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
        
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            Rectangle(hdc, p_l, p_t, p_r, p_b);
            Rectangle(hdc, o_l, o_t, o_r, o_b);
            Rectangle(hdc, p_legl, p_legt, p_legr, p_legb);
            Rectangle(hdc, p_arml, p_armt, p_armr, p_armb);
            Rectangle(hdc, o_legl, o_legt, o_legr, o_legb);
            Rectangle(hdc, o_arml, o_armt, o_armr, o_armb);
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
