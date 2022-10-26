#include "shape_editor.h"
#include "shape.h"
#include "resource.h"

Shape** ShapeEditor::pcshape = new Shape * [MY_SHAPE_ARRAY_SIZE] {};

void ShapeEditor::OnLBdown(HWND hWnd) {
	isPainting = true;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	getIndex();
	createShape();
	pcshape[index]->setEnd(pt.x, pt.y);
	pcshape[index]->setStart(pt.x, pt.y);
};

void ShapeEditor::OnLBup(HWND hWnd) {
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	pcshape[index]->setEnd(pt.x, pt.y);
	InvalidateRect(hWnd, NULL, TRUE);
	isPainting = false;
};

void ShapeEditor::getIndex() {
	for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++)
		if (!pcshape[i]) {
			index = i;
			break;
		}
};

void ShapeEditor::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++)
		if (pcshape[i])
			pcshape[i]->Show(hdc);
		else break;
	EndPaint(hWnd, &ps);
}

void PointEditor::createShape() {
	pcshape[index] = new PointShape;
};

void LineEditor::createShape() {
	pcshape[index] = new LineShape;
};

void RectEditor::createShape() {
	pcshape[index] = new RectShape;
};

void EllipseEditor::createShape() {
	pcshape[index] = new EllipseShape;
};

void PointEditor::OnMouseMove(HWND hWnd) {}

void PointEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParam == hSubMenu)
	{
		CheckMenuItem(hSubMenu, ID_POINT, MF_CHECKED);
		CheckMenuItem(hSubMenu, ID_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, ID_RECT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, ID_ELLIPSE, MF_UNCHECKED);
	}
}

void LineEditor::OnMouseMove(HWND hWnd) {
	if (!isPainting) return;

	HPEN hPenOld, hPen;
	HDC hdc;
	hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, pcshape[index]->getXS1(), pcshape[index]->getYS1(), NULL);
	LineTo(hdc, pcshape[index]->getXS2(), pcshape[index]->getYS2());

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	pcshape[index]->setEnd(pt.x, pt.y);

	MoveToEx(hdc, pcshape[index]->getXS1(), pcshape[index]->getYS1(), NULL);
	LineTo(hdc, pcshape[index]->getXS2(), pcshape[index]->getYS2());

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void LineEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParam == hSubMenu)
	{
		CheckMenuItem(hSubMenu, ID_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, ID_LINE, MF_CHECKED);
		CheckMenuItem(hSubMenu, ID_RECT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, ID_ELLIPSE, MF_UNCHECKED);
	}
}

void RectEditor::OnMouseMove(HWND hWnd) {
	if (!isPainting) return;
	HPEN hPenOld, hPen;
	HDC hdc;
	hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);

	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, pcshape[index]->getXS1(), pcshape[index]->getYS1(), pcshape[index]->getXS2(), pcshape[index]->getYS2());

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	pcshape[index]->setEnd(pt.x, pt.y);
	Rectangle(hdc, pcshape[index]->getXS1(), pcshape[index]->getYS1(), pcshape[index]->getXS2(), pcshape[index]->getYS2());

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void RectEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParam == hSubMenu)
	{
		CheckMenuItem(hSubMenu, ID_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, ID_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, ID_RECT, MF_CHECKED);
		CheckMenuItem(hSubMenu, ID_ELLIPSE, MF_UNCHECKED);
	}
}

void EllipseEditor::OnMouseMove(HWND hWnd) {
	if (!isPainting) return;
	HPEN hPenOld, hPen;
	HDC hdc;
	hdc = GetDC(hWnd);

	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	long xStart = pcshape[index]->getXS2() - (2 * (pcshape[index]->getXS2() - pcshape[index]->getXS1()));
	long yStart = pcshape[index]->getYS2() - (2 * (pcshape[index]->getYS2() - pcshape[index]->getYS1()));
	Ellipse(hdc, xStart, yStart, pcshape[index]->getXS2(), pcshape[index]->getYS2());

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	pcshape[index]->setEnd(pt.x, pt.y);
	xStart = pcshape[index]->getXS2() - (2 * (pcshape[index]->getXS2() - pcshape[index]->getXS1()));
	yStart = pcshape[index]->getYS2() - (2 * (pcshape[index]->getYS2() - pcshape[index]->getYS1()));
	Ellipse(hdc, xStart, yStart, pcshape[index]->getXS2(), pcshape[index]->getYS2());

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void EllipseEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParam == hSubMenu)
	{
		CheckMenuItem(hSubMenu, ID_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, ID_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, ID_RECT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, ID_ELLIPSE, MF_CHECKED);
	}
}