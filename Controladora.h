#pragma once
#include "Enfermo.h"
#include "Paciente.h"
#include "Vacuna.h"
#include "Enfermera.h"
#include <vector>
#include <ctime>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace std;

class Controladora {
private:
	Enfermera* enfermera;
	vector<Enfermo*> enfermos;
	vector<Paciente*> pacientes;
	vector<Vacuna*> vacunas;

	int vidas;
	int contador;
	int curados;
	int vacunasRecolectadas;
	bool gameOver;

public:
	Controladora(Bitmap^ bmpEnfermera, Bitmap^ bmpEnfermo) {
		srand(time(NULL));
		enfermera = new Enfermera(bmpEnfermera->Width / 3, bmpEnfermera->Height / 4);
		vidas = 3;
		contador = 300;
		curados = 0;
		vacunasRecolectadas = 0;
		gameOver = false;

		// Generar entre 5 y 7 enfermos y vacunas
		int cantidad = rand() % 3 + 5;
		for (int i = 0; i < cantidad; ++i) {
			int x = rand() % 800 + 50;
			enfermos.push_back(new Enfermo(bmpEnfermo->Width / 3, bmpEnfermo->Height / 4, x));
			vacunas.push_back(new Vacuna(rand() % 800 + 50, rand() % 400 + 50, 500, 900, ' '));
		}
	}

	~Controladora() {
		delete enfermera;
		for (auto e : enfermos) delete e;
		for (auto p : pacientes) delete p;
		for (auto v : vacunas) delete v;
	}

	void moverJugador(Graphics^ gr, char tecla) {
		if (!gameOver)
			enfermera->mover(gr, tecla);
	}

	bool disparar() {
		if (!gameOver && vacunasRecolectadas > 0) {
			int x = enfermera->getX();
			int y = enfermera->getY();
			char dir = enfermera->getDireccion();

			vacunas.push_back(new Vacuna(x, y, 500, 900, dir));
			vacunasRecolectadas--;
			return true;
		}
		return false;
	}

	void jugar(Graphics^ gr, Bitmap^ bmpEnfermera, Bitmap^ bmpEnfermo, Bitmap^ bmpPaciente, Bitmap^ bmpVacuna, Timer^ timer) {
		if (gameOver) return;

		contador--;
		if (contador <= 0) {
			timer->Stop();
			gameOver = true;
			MessageBox::Show("¡Game Over! Tiempo agotado");
			return;
		}

		// Enfermos
		for (auto e : enfermos) {
			e->mover(gr);
			e->dibujar(gr, bmpEnfermo);
		}

		// Pacientes
		for (auto p : pacientes) {
			p->mover(gr);
			p->dibujar(gr, bmpPaciente);
		}

		// Vacunas
		for (auto v : vacunas) {
			if (v->getVisibilidad()) {
				v->mover(gr);
				v->dibujar(gr, bmpVacuna);
			}
		}

		// Enfermera
		enfermera->dibujar(gr, bmpEnfermera);
		Rectangle rEnfermera = enfermera->getRectangle();

		// Recolectar vacunas
		for (auto v : vacunas) {
			if (v->getVisibilidad() && v->getDireccion() == ' ' && rEnfermera.IntersectsWith(v->getRectangle())) {
				v->setVisibilidad(false);
				vacunasRecolectadas++;
			}
		}

		// Colisión con enfermos
		for (int i = 0; i < enfermos.size(); ++i) {
			if (rEnfermera.IntersectsWith(enfermos[i]->getRectangle())) {
				vidas--;
				enfermera->setPosicion(70, 70);
				if (vidas <= 0) {
					timer->Stop();
					gameOver = true;
					MessageBox::Show("VIRUS EXTREMO");
				}
				break;
			}
		}

		// Colisión de vacuna con enfermo
		for (int i = 0; i < vacunas.size(); ++i) {
			Vacuna* v = vacunas[i];
			if (!v->getVisibilidad() || v->getDireccion() == ' ') continue;

			for (int j = 0; j < enfermos.size(); ++j) {
				if (v->getRectangle().IntersectsWith(enfermos[j]->getRectangle())) {
					Paciente* nuevoPaciente = new Paciente(enfermos[j]->getW(), enfermos[j]->getH(), enfermos[j]->getX());
					pacientes.push_back(nuevoPaciente);

					delete enfermos[j];
					enfermos.erase(enfermos.begin() + j);

					v->setVisibilidad(false);
					curados++;
					break;
				}
			}
		}
		if (enfermos.empty()) {
			timer->Stop();
			gameOver = true;
			MessageBox::Show("MISION CUMPLIDA!");
		}
	}
	int getVidasRestantes() { return vidas; }
	int tiempoContador() { return contador; }
	int getCurados() { return curados; }
	int getVacunasRecolectadas() { return vacunasRecolectadas; }

};
