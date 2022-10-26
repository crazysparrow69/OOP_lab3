#include "framework.h"
#include "ShapeObjectsEditor.h"
#include "shape.h"
#include "editor.h"
#include "shape_editor.h"

ShapeEditor* pse = NULL;
ShapeObjectsEditor::ShapeObjectsEditor(void) {}
ShapeObjectsEditor::~ShapeObjectsEditor() {}

void ShapeObjectsEditor::StartPointEditor(HWND hWnd) {
	if (pse) delete pse;
	pse = new PointEditor;
}

void ShapeObjectsEditor::StartLineEditor(HWND hWnd) {
	if (pse) delete pse;
	pse = new LineEditor;
}

void ShapeObjectsEditor::StartRectEditor(HWND hWnd) {
	if (pse) delete pse;
	pse = new RectEditor;
}

void ShapeObjectsEditor::StartEllipseEditor(HWND hWnd) {
	if (pse) delete pse;
	pse = new EllipseEditor;
}

void ShapeObjectsEditor::OnLBdown(HWND hWnd) {
	if (pse) pse->OnLBdown(hWnd);
}

void ShapeObjectsEditor::OnLBup(HWND hWnd) {
	if (pse) pse->OnLBup(hWnd);
}

void ShapeObjectsEditor::OnMouseMove(HWND hWnd) {
	if (pse) pse->OnMouseMove(hWnd);
}

void ShapeObjectsEditor::OnPaint(HWND hWnd) {
	if (pse) pse->OnPaint(hWnd);
}

void ShapeObjectsEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam) {
	if (pse) pse->OnInitMenuPopup(hWnd, wParam);
}