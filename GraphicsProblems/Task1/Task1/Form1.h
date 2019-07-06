#pragma once

namespace Task1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
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
		/// Освободить все используемые ресурсы.
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
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
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
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->ResumeLayout(false);

		}

#pragma endregion
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics ^g = e->Graphics;
				 g->Clear(Color::Aquamarine);

				 Rectangle rect = Form::ClientRectangle;
				 Rectangle smallRect;

				 Pen ^redPen = gcnew Pen(Color::Red);
				 redPen->Width = 4;

				 g->DrawLine(redPen, 0, 0, rect.Width, rect.Height);

				 Pen ^bluePen = gcnew Pen(Color::Blue);
				 bluePen->Width = 10;

				 g->DrawLine(bluePen, 50, 70, rect.Width, 80);

				 System::Drawing::Font ^drawFont = gcnew System::Drawing::Font("Arial", 10);
				 SolidBrush ^drawBrush = gcnew SolidBrush(Color::Black);

				 g->DrawString("Надпись на форме", drawFont, drawBrush, 40, 100);
			 }

	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 this->Refresh();
			 }
	};
}

