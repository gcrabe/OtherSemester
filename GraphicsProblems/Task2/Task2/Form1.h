#pragma once

namespace Task2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(240, 180);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 this->Refresh();
			 }

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics ^graphics = e->Graphics;
				 graphics->Clear(Color::Gray);

				 /*Pen ^optionPen = gcnew Pen(Color::Red);
				 optionPen->Width = 1;
				 graphics->DrawLine(optionPen, 0, 0, 240, 180);*/

				 Pen ^pen = gcnew Pen(Color::Black);
				 pen->Width = 1;

				 //mashroom
				 graphics->DrawLine(pen, 20, 140, 40, 130);
				 graphics->DrawLine(pen, 40, 130, 60, 140);
				 graphics->DrawLine(pen, 20, 140, 60, 140);
				 graphics->DrawLine(pen, 40, 140, 40, 155);
				 graphics->DrawLine(pen, 20, 155, 60, 155);
				 graphics->DrawLine(pen, 20, 160, 60, 160);
				 graphics->DrawLine(pen, 20, 155, 20, 160);
				 graphics->DrawLine(pen, 60, 155, 60, 160);

				 //house:basics
				 graphics->DrawLine(pen, 80, 10, 210, 10);
				 graphics->DrawLine(pen, 80, 10, 80, 160);
				 graphics->DrawLine(pen, 210, 10, 210, 160);
				 graphics->DrawLine(pen, 80, 160, 210, 160);

				 //left low window
				 graphics->DrawLine(pen, 100, 150, 110, 150);
				 graphics->DrawLine(pen, 110, 150, 110, 120);
				 graphics->DrawLine(pen, 110, 120, 100, 120);
				 graphics->DrawLine(pen, 100, 120, 100, 150);
				 
				 //right low window
				 graphics->DrawLine(pen, 180, 150, 190, 150);
				 graphics->DrawLine(pen, 190, 150, 190, 120);
			 	 graphics->DrawLine(pen, 190, 120, 180, 120);
				 graphics->DrawLine(pen, 180, 120, 180, 150);
				 
				 //doors
				 graphics->DrawLine(pen, 140, 160, 140, 130);
			 	 graphics->DrawLine(pen, 140, 130, 160, 130);
				 graphics->DrawLine(pen, 160, 130, 160, 160);
				 graphics->DrawLine(pen, 150, 160, 150, 130);

				 //top balcons
				 graphics->DrawLine(pen, 90, 50, 90, 40);
				 graphics->DrawLine(pen, 90, 40, 120, 40);
				 graphics->DrawLine(pen, 120, 40, 120, 50);
				 graphics->DrawLine(pen, 120, 50, 90, 50);
				 graphics->DrawLine(pen, 130, 50, 130, 40);
				 graphics->DrawLine(pen, 130, 40, 160, 40);
				 graphics->DrawLine(pen, 160, 40, 160, 50);
				 graphics->DrawLine(pen, 160, 50, 130, 50);
				 graphics->DrawLine(pen, 170, 50, 170, 40);
				 graphics->DrawLine(pen, 170, 40, 200, 40);
				 graphics->DrawLine(pen, 200, 40, 200, 50);
				 graphics->DrawLine(pen, 200, 50, 170, 50);
				 
				 //middle balcons
				 graphics->DrawLine(pen, 90, 100, 90, 90);
				 graphics->DrawLine(pen, 90, 90, 120, 90);
				 graphics->DrawLine(pen, 120, 90, 120, 100);
				 graphics->DrawLine(pen, 120, 100, 90, 100);
				 graphics->DrawLine(pen, 130, 100, 130, 90);
				 graphics->DrawLine(pen, 130, 90, 160, 90);
				 graphics->DrawLine(pen, 160, 90, 160, 100);
				 graphics->DrawLine(pen, 160, 100, 130, 100);
				 graphics->DrawLine(pen, 170, 100, 170, 90);
				 graphics->DrawLine(pen, 170, 90, 200, 90);
				 graphics->DrawLine(pen, 200, 90, 200, 100);
				 graphics->DrawLine(pen, 200, 100, 170, 100);

				 //top windows
				 graphics->DrawLine(pen, 100, 20, 110, 20);
				 graphics->DrawLine(pen, 110, 20, 110, 40);
				 graphics->DrawLine(pen, 110, 40, 100, 40);
				 graphics->DrawLine(pen, 100, 40, 100, 20);
				 graphics->DrawLine(pen, 140, 20, 150, 20);
				 graphics->DrawLine(pen, 150, 20, 150, 40);
				 graphics->DrawLine(pen, 150, 40, 140, 40);
				 graphics->DrawLine(pen, 140, 40, 140, 20);
				 graphics->DrawLine(pen, 180, 20, 190, 20);
				 graphics->DrawLine(pen, 190, 20, 190, 40);
				 graphics->DrawLine(pen, 190, 40, 180, 40);
				 graphics->DrawLine(pen, 180, 40, 180, 20);

				 //middle windows
				 graphics->DrawLine(pen, 100, 70, 110, 70);
				 graphics->DrawLine(pen, 110, 70, 110, 90);
				 graphics->DrawLine(pen, 110, 90, 100, 90);
				 graphics->DrawLine(pen, 100, 90, 100, 70);
				 graphics->DrawLine(pen, 140, 70, 150, 70);
				 graphics->DrawLine(pen, 150, 70, 150, 90);
				 graphics->DrawLine(pen, 150, 90, 140, 90);
				 graphics->DrawLine(pen, 140, 90, 140, 70);
				 graphics->DrawLine(pen, 180, 70, 190, 70);
				 graphics->DrawLine(pen, 190, 70, 190, 90);
				 graphics->DrawLine(pen, 190, 90, 180, 90);
				 graphics->DrawLine(pen, 180, 90, 180, 70);
			 }
	};
}

