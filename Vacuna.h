#pragma once
#include "Entidad.h"
#include <iostream>
using namespace System::Drawing;

class Vacuna : public Entidad {
private:
	char direccion;
	int indiceW, indiceH;

public:
	
	Vacuna(int x, int y, int W, int H, char tecla)
		: Entidad(W, H, x, y, 30, 30), direccion(tecla), indiceW(0), indiceH(0) {
	}

	~Vacuna() {}

	void dibujar(Graphics^ gr, Bitmap^ bmp) override {
		gr->DrawImage(bmp, x, y, (W * 0.03), (H * 0.03));
	}

	void mover(Graphics^ gr) override {
		if (direccion == 'S' && y + H * 0.03 <= gr->VisibleClipBounds.Height)
			y += dy;
		else if (direccion == 'W' && y >= 0)
			y -= dy;
		else if (direccion == 'A' && x >= 0)
			x -= dx;
		else if (direccion == 'D' && x + W * 0.03 < gr->VisibleClipBounds.Width)
			x += dx;
	}

	
	Rectangle getRectangle() override {
		return Rectangle(x, y, (int)(W * 0.03), (int)(H * 0.06));
	}

	int getW() { return (int)(W * 0.03); }
	int getH() { return (int)(H * 0.03); }

	void setDireccion(char d) { direccion = d; }
	char getDireccion() const { return direccion; }
};
