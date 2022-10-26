#include "framework.h"
#include "resource1.h"
#include "toolbar.h"
#include "resource.h"
#include <commctrl.h>

void Toolbar::OnCreate(HWND hWnd, HINSTANCE hInst)
{
    TBBUTTON tbb[4]; 

    ZeroMemory(tbb, sizeof(tbb));
    tbb[0].iBitmap = 0; 
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = TBSTYLE_BUTTON; 
    tbb[0].idCommand = ID_TOOL_POINT; 

    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = ID_TOOL_LINE;

    tbb[2].iBitmap = 2;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_TOOL_RECT;

    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_TOOL_ELLIPSE;

    SendMessage(hwndToolBar, TB_ADDBUTTONS, 4, (LPARAM)&tbb);

    hwndToolBar = CreateToolbarEx(hWnd, //батьківське вікно
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP |
        TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR, //ID дочірнього вікна Toolbar
        4,
        hInst,
        IDB_BITMAP1,
        tbb, //масив опису кнопок
        4, //кількість кнопок
        24, 24, 24, 24, //розташування та розміри
        sizeof(TBBUTTON));
};

//---обробник повідомлення WM_SIZE---
void Toolbar::OnSize(HWND hWnd)
{
    RECT rc, rw;
    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc);        //нові розміри головного вікна
        GetWindowRect(hwndToolBar, &rw); //нам потрібно знати висоту Toolbar
        MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
    }
}

// Зміна натиснутої кнопки
void Toolbar::PressBtn(HWND hWnd, LPARAM lParam)
{
    if (oldlParam)
    {
        SendMessage(hwndToolBar, TB_PRESSBUTTON, oldlParam, 0); 
    }
    SendMessage(hwndToolBar, TB_PRESSBUTTON, lParam, 1);
    oldlParam = lParam;
}

void Toolbar::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LPNMHDR pnmh = (LPNMHDR)lParam;

    if (pnmh->code == TTN_NEEDTEXT)
    {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom)
        {

        case ID_TOOL_POINT:
            lstrcpy(lpttt->szText, L"Крапка");
            break;

        case ID_TOOL_LINE:
            lstrcpy(lpttt->szText, L"Лінія");
            break;

        case ID_TOOL_RECT:
            lstrcpy(lpttt->szText, L"Прямокутник");
            break;

        case ID_TOOL_ELLIPSE:
            lstrcpy(lpttt->szText, L"Еліпс");
            break;

        default: lstrcpy(lpttt->szText, L"Щось невідоме");
        }
    }
}
