#pragma once

class Shape {
protected:
	long xs1, ys1, xs2, ys2;
public:
	virtual void Show(HDC) = 0;
	void setStart(long x, long y);
	void setEnd(long x, long y);
	long getXS1(), getXS2(), getYS1(), getYS2();
};

class PointShape : public Shape {
public:
	void Show(HDC);
};

class LineShape : public Shape {
public:
	void Show(HDC);
};

class RectShape : public Shape {
public:
	void Show(HDC);
};

class EllipseShape : public Shape {
public:
	void Show(HDC);
};

