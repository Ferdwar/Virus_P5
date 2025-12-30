#pragma once
#include <iostream>
using namespace System::Drawing;

class Entidad {
protected:
	int x, y;
	int dx, dy;
	int W, H;
	bool visibilidad;

public:
	Entidad(int W, int H, int x = 0, int y = 0, int dx = 0, int dy = 0)
		: W(W), H(H), x(x), y(y), dx(dx), dy(dy), visibilidad(true) {
	}

	virtual ~Entidad() {}

	int getX() const { return x; }
	int getY() const { return y; }
	int getDX() const { return dx; }
	int getDY() const { return dy; }
	int getW() const { return W; }
	int getH() const { return H; }
	void setVisibilidad(bool v) { visibilidad = v; }
	bool getVisibilidad() const { return visibilidad; }

	virtual Rectangle getRectangle() {
		return Rectangle(x, y, W, H);
	}

	virtual void mover(Graphics^ gr) = 0;
	virtual void dibujar(Graphics^ gr, Bitmap^ bmp) = 0;
};