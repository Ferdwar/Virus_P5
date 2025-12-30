#pragma once
#include "Entidad.h"
#include <iostream>
using namespace System::Drawing;

class Enfermo : public Entidad {
private:
	int indiceW, indiceH;
	int direccion; // 1 = horizontal, 2 = vertical

public:
	Enfermo(int W, int H, int posX)
		: Entidad(W, H, posX, rand() % 300 + 50,
			(rand() % 2 == 0 ? 5 : -5),
			(rand() % 2 == 0 ? 5 : -5)) {

		direccion = (rand() % 2 == 0 ? 1 : 2);
		indiceW = 0;
		indiceH = 0;
	}

	void mover(Graphics^ gr) override {
		if (!visibilidad) return;

		if (direccion == 1) { // horizontal
			if (x + W > gr->VisibleClipBounds.Width || x < 0)
				dx *= -1;

			indiceH = (dx > 0) ? 2 : 1;
			x += dx;
		}
		else { // vertical
			if (y + H > gr->VisibleClipBounds.Height || y < 0)
				dy *= -1;

			indiceH = (dy > 0) ? 0 : 3;
			y += dy;
		}

		indiceW = (indiceW + 1) % 4;
	}

	void dibujar(Graphics^ gr, Bitmap^ bmp) override {
		if (!visibilidad) return;

		Rectangle src = Rectangle(indiceW * W, indiceH * H, W, H);
		Rectangle dest = Rectangle(x, y, W, H);
		gr->DrawImage(bmp, dest, src, GraphicsUnit::Pixel);
	}
};
