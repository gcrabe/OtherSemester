#pragma once

namespace Graphics_Task2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
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
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
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
			this->Text = L"Task 2";
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
				 graphics->Clear(Color::DarkGray);

				 Pen ^pen = Pens::Black;

				 //graphics->DrawLine(Pens::Red, Point(240, 0), Point(240, 180));
				 //graphics->DrawLine(Pens::Red, Point(0, 180), Point(240, 180));

				 int houseWidth = 130;
				 int houseHeight = 150;
				 
				 Rectangle house = Rectangle(80, 10, houseWidth, houseHeight);
				 graphics->DrawRectangle(pen, house);

				 int sandboxWidth = 40;
				 int sandboxHeight = 5;

				 Rectangle sandbox = Rectangle(20, 155, sandboxWidth, sandboxHeight);
				 graphics->DrawRectangle(pen, sandbox);

				 Point pillarTop = Point(40, 140);
				 Point pillarDown = Point(40, 155);
				 graphics->DrawLine(pen, pillarTop, pillarDown);

				 Point triangleLeft = Point(20, 140);
				 Point triangleRight = Point(60, 140);
				 Point triangleTop = Point(40, 130);

				 graphics->DrawLine(pen, triangleLeft, triangleRight);
				 graphics->DrawLine(pen, triangleLeft, triangleTop);
				 graphics->DrawLine(pen, triangleRight, triangleTop);

				 int doorWidth = 10;
				 int doorHeight = 30;

				 array<Rectangle> ^doors = {
											Rectangle(140, 130, doorWidth, doorHeight), Rectangle(150, 130, doorWidth, doorHeight),
											Rectangle(100, 120, doorWidth, doorHeight), Rectangle(180, 120, doorWidth, doorHeight)
										};
				 
				 graphics->DrawRectangles(pen, doors);

				 int windowWidth = 10;
				 int windowHeight = 20;

				 array<Rectangle> ^windows = {
												Rectangle(100, 20, windowWidth, windowHeight),
												Rectangle(140, 20, windowWidth, windowHeight),
												Rectangle(180, 20, windowWidth, windowHeight),
												Rectangle(100, 70, windowWidth, windowHeight),
												Rectangle(140, 70, windowWidth, windowHeight),
												Rectangle(180, 70, windowWidth, windowHeight)
											};

				 graphics->DrawRectangles(pen, windows);

				 int balconyWidth = 30;
				 int balconyHeight = 10;

				 array<Rectangle> ^balconies = {
												Rectangle(90, 40, balconyWidth, balconyHeight),
												Rectangle(130, 40, balconyWidth, balconyHeight),
												Rectangle(170, 40, balconyWidth, balconyHeight),
												Rectangle(90, 90, balconyWidth, balconyHeight),
												Rectangle(130, 90, balconyWidth, balconyHeight),
												Rectangle(170, 90, balconyWidth, balconyHeight)
											};

				 graphics->DrawRectangles(pen, balconies);
			 }
	};
}

