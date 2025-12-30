#pragma once
#include "Controladora.h"

namespace Virus {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form {
	public:
		MyForm(void) {
			InitializeComponent();
			gr = this->CreateGraphics();
			buffer = BufferedGraphicsManager::Current->Allocate(gr, this->ClientRectangle);

			bmpEnfermera = gcnew Bitmap("Imagenes\\Enfermera.jpeg");
			bmpEnfermo = gcnew Bitmap("Imagenes\\Enfermo.jpeg");
			bmpPaciente = gcnew Bitmap("Imagenes\\Paciente.jpeg");
			bmpVacuna = gcnew Bitmap("Imagenes\\Vacuna.jpeg");
			fondo = gcnew Bitmap("Imagenes\\mundo.png");

			controladora = new Controladora(bmpEnfermera, bmpEnfermo);
		}

	protected:
		~MyForm() {
			if (components) delete components;
		}

	private:
		System::ComponentModel::IContainer^ components;
		System::Windows::Forms::Timer^ timer1;

		Graphics^ gr;
		BufferedGraphics^ buffer;
		Bitmap^ fondo;
		Bitmap^ bmpEnfermera;
		Bitmap^ bmpEnfermo;
		Bitmap^ bmpPaciente;
		Bitmap^ bmpVacuna;

		Controladora* controladora;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void) {
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 100;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1177, 639);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->ResumeLayout(false);
		}
#pragma endregion

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		buffer->Graphics->DrawImage(fondo, 0, 0, fondo->Width * 0.8, fondo->Height * 0.7);

		controladora->jugar(buffer->Graphics, bmpEnfermera, bmpEnfermo, bmpPaciente, bmpVacuna, timer1);

		System::Drawing::Font^ fuente = gcnew System::Drawing::Font("Arial", 14, System::Drawing::FontStyle::Bold);
		SolidBrush^ brocha = gcnew SolidBrush(Color::White);

		buffer->Graphics->DrawString("Vidas: " + controladora->getVidasRestantes().ToString(), fuente, brocha, 10, 10);
		buffer->Graphics->DrawString("Tiempo: " + controladora->tiempoContador().ToString(), fuente, brocha, 10, 30);
		buffer->Graphics->DrawString("Curados: " + controladora->getCurados().ToString(), fuente, brocha, 10, 50);
		buffer->Graphics->DrawString("Vacunas: " + controladora->getVacunasRecolectadas().ToString(), fuente, brocha, 10, 70);


		buffer->Render(gr);
	}

	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::A:controladora->moverJugador(buffer->Graphics, 'A');break;
		case Keys::D:controladora->moverJugador(buffer->Graphics, 'D');break;
		case Keys::W:controladora->moverJugador(buffer->Graphics, 'W');break;
		case Keys::S:controladora->moverJugador(buffer->Graphics, 'S');break;

		case Keys::V:
			if (!controladora->disparar()) {
				MessageBox::Show("No tiene vacunas disponibles.");
			}
			break;

		case Keys::Enter:
			MessageBox::Show("Enfermos curados: " + controladora->getCurados().ToString());
			break;
		}
	}
	};
}
