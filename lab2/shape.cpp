#include "framework.h"
#include "shape.h"

HBRUSH hBrush, hBrushOld;

void Shape::setStart(long x, long y)
{
	xs1 = x;
	ys1 = y;
}

void Shape::setEnd(long x, long y)
{
	xs2 = x;
	ys2 = y;
}

long Shape::getXS1()
{
	return xs1;
}

long Shape::getXS2()
{
	return xs2;
}

long Shape::getYS1()
{
	return ys1;
}

long Shape::getYS2()
{
	return ys2;
}

void PointShape::Show(HDC hdc) {
	SetPixel(hdc, xs2, ys2, 0x00000000);
	SetPixel(hdc, xs2 - 1, ys2, 0x00000000);
	SetPixel(hdc, xs2 + 1, ys2, 0x00000000);
	SetPixel(hdc, xs2, ys2 - 1, 0x00000000);
	SetPixel(hdc, xs2, ys2 + 1, 0x00000000);
	SetPixel(hdc, xs2 - 1, ys2 - 1, 0x00000000);
	SetPixel(hdc, xs2 + 1, ys2 - 1, 0x00000000);
	SetPixel(hdc, xs2 - 1, ys2 + 1, 0x00000000);
	SetPixel(hdc, xs2 + 1, ys2 + 1, 0x00000000);
}

void LineShape::Show(HDC hdc) {
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
}

void RectShape::Show(HDC hdc) {
	hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	hBrushOld = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

	Rectangle(hdc, xs1, ys1, xs2, ys2);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void EllipseShape::Show(HDC hdc) {
	hBrush = (HBRUSH)CreateSolidBrush(RGB(220, 220, 220));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	long newXS1 = xs2 - (2 * (xs2 - xs1));
	long newYS1 = ys2 - (2 * (ys2 - ys1));
	Ellipse(hdc, newXS1, newYS1, xs2, ys2);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}