#pragma once
#include "editor.h"
#include "shape.h"

#define MY_SHAPE_ARRAY_SIZE 124

class ShapeEditor : public Editor {
protected:
	POINT pt;
	HMENU hMenu, hSubMenu;
	static Shape** pcshape;
	int index = 0;
	bool isPainting = false;
	void getIndex();
	virtual void createShape() = 0;
public:
	void OnLBdown(HWND);
	void OnLBup(HWND); 
	virtual void OnMouseMove(HWND) = 0;
	void OnPaint(HWND);
	virtual void OnInitMenuPopup(HWND, WPARAM) = 0;
};

class PointEditor : public ShapeEditor {
	void createShape();
	void OnMouseMove(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class LineEditor : public ShapeEditor {
	void createShape();
	void OnMouseMove(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class RectEditor : public ShapeEditor {
	void createShape();
	void OnMouseMove(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class EllipseEditor : public ShapeEditor {
	void createShape();
	void OnMouseMove(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};