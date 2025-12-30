#pragma once
#include <iostream>
#include "Entidad.h"
using namespace System::Drawing;

class Enfermera : public Entidad {
private:
	int indiceW, indiceH;
	char direccion;

public:
	Enfermera(int W, int H)
		: Entidad(W, H, 70, 70, 15, 15), indiceW(0), indiceH(0), direccion('S') {
	}

	void mover(Graphics^ gr, char tecla) {
		switch (tecla) {
		case 'A':
			if (x > 0) {
				indiceH = 1;
				x -= dx;
				direccion = 'A';
			}
			break;
		case 'D':
			if (x + W < gr->VisibleClipBounds.Width) {
				indiceH = 2;
				x += dx;
				direccion = 'D';
			}
			break;
		case 'W':
			if (y > 0) {
				indiceH = 3;
				y -= dy;
				direccion = 'W';
			}
			break;
		case 'S':
			if (y + H < gr->VisibleClipBounds.Height) {
				indiceH = 0;
				y += dy;
				direccion = 'S';
			}
			break;
		}

		indiceW = (indiceW + 1) % 4;
	}

	void mover(Graphics^ gr) override {}

	void dibujar(Graphics^ gr, Bitmap^ bmp) override {
		Rectangle porcionMostrar = Rectangle(indiceW * W, indiceH * H, W, H);
		Rectangle zoom = Rectangle(x, y, W, H);
		gr->DrawImage(bmp, zoom, porcionMostrar, GraphicsUnit::Pixel);
	}

	// Métodos que faltaban
	char getDireccion() const {
		return direccion;
	}

	void setPosicion(int nuevoX, int nuevoY) {
		x = nuevoX;
		y = nuevoY;
	}
};
