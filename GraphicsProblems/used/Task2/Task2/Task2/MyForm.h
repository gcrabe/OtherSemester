#pragma once

namespace Task2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(824, 441);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}

		//Width cell
		const int w = 10;
	private: void DrawGrid(Graphics^ g, Rectangle rect)
	{
		Pen^ line = gcnew Pen(Color::Gray);
		//Vert
		for (int i = 0; i < rect.Width;i+=w)
		{
			g->DrawLine(line, i, 0, i, rect.Height);
		}
		//Horiz
		for (int i = 0; i < rect.Height; i += w)
		{
			g->DrawLine(line, 0, i, rect.Width, i);
		}
	}
#pragma endregion
	private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		Graphics^ g = e->Graphics;
		g->Clear(Color::White);
		Rectangle rect = Form::ClientRectangle;
		Pen^ blackPen = gcnew Pen(Color::Black);
		DrawGrid(g,rect);
		blackPen->Width = 2;
		//1
		g->DrawLine(blackPen, w * 2, w * 16, w * 6, w * 16);
		//2
		g->DrawLine(blackPen, w * 6, w * 16, w * 5, w * 17);
		//3
		g->DrawLine(blackPen, w * 5, w * 17, w * 8, w * 17);
		//4
		g->DrawLine(blackPen, w * 8, w * 17, w * 10, w * 16);
		//5
		g->DrawLine(blackPen, w * 10, w * 16, w * 11, w * 15);
		//6
		g->DrawLine(blackPen, w * 11, w * 15, w * 13, w * 15);
		//7
		g->DrawLine(blackPen, w * 13, w * 15, w * 15, w * 16);
		//8
		g->DrawLine(blackPen, w * 15, w * 16, w * 23, w * 16);
		//9
		g->DrawLine(blackPen, w * 23, w * 16, w * 26, w * 15);
		//10
		g->DrawLine(blackPen, w * 26, w * 15, w * 31, w * 15);
		//11
		g->DrawLine(blackPen, w * 31, w * 15, w * 33, w * 14);
		//12
		g->DrawLine(blackPen, w * 33, w * 14, w * 36, w * 14);
		//13
		g->DrawLine(blackPen, w * 36, w * 14, w * 36, w * 12);
		//14
		g->DrawLine(blackPen, w * 36, w * 12, w * 35, w * 11);
		//15
		g->DrawLine(blackPen, w * 35, w * 11, w * 34, w * 11);
		//16
		g->DrawLine(blackPen, w * 34, w * 11, w * 35, w * 12);
		//17
		g->DrawLine(blackPen, w * 34, w * 11, w * 32, w * 12);
		//18
		g->DrawLine(blackPen, w * 32, w * 12, w * 14, w * 12);
		//19
		g->DrawLine(blackPen, w * 14, w * 12, w * 15, w * 13);
		//20
		g->DrawLine(blackPen, w * 14, w * 12, w * 13, w * 14);
		//21
		g->DrawLine(blackPen, w * 13, w * 14, w * 15, w * 14);
		//22
		g->DrawLine(blackPen, w * 13, w * 14, w * 13, w * 15);
		//23
		g->DrawLine(blackPen, w * 14, w * 12, w * 12, w * 11);
		//24
		g->DrawLine(blackPen, w * 12, w * 11, w * 12, w * 9);
		//25
		g->DrawLine(blackPen, w * 12, w * 9, w * 11, w * 7);
		//26
		g->DrawLine(blackPen, w * 11, w * 7, w * 10, w * 6);
		//27
		g->DrawLine(blackPen, w * 10, w * 6, w * 9, w * 7);
		//28
		g->DrawLine(blackPen, w * 9, w * 7, w * 9, w * 8);
		//29
		g->DrawLine(blackPen, w * 8, w * 7, w * 10, w * 9);
		//30
		g->DrawLine(blackPen, w * 10, w * 9, w * 11, w * 11);
		//31
		g->DrawLine(blackPen, w * 11, w * 11, w * 11, w * 12);
		//32
		g->DrawLine(blackPen, w * 11, w * 12, w * 10, w * 11);
		//33
		g->DrawLine(blackPen, w * 10, w * 11, w * 8, w * 10);
		//34
		g->DrawLine(blackPen, w * 8, w * 10, w * 7, w * 9);
		//35
		g->DrawLine(blackPen, w * 7, w * 9, w * 7, w * 8);
		//36
		g->DrawLine(blackPen, w * 8, w * 7, w * 7, w * 7);
		//37
		g->DrawLine(blackPen, w * 7, w * 7, w * 2, w * 12);
		//38
		g->DrawLine(blackPen, w * 2, w * 12, w * 2, w * 13);
		//39
		g->DrawLine(blackPen, w * 2, w * 13, w * 3, w * 14);
		//40
		g->DrawLine(blackPen, w * 3, w * 14, w * 5, w * 13);
		//41
		g->DrawLine(blackPen, w * 5, w * 13, w * 10, w * 13);
		//42
		g->DrawLine(blackPen, w * 10, w * 13, w * 12, w * 11);
		//43
		g->DrawLine(blackPen, w * 10, w * 13, w * 10, w * 14);
		//44
		g->DrawLine(blackPen, w * 10, w * 14, w * 11, w * 15);
		//45
		g->DrawLine(blackPen, w * 8, w * 13, w * 6, w * 14);
		//46
		g->DrawLine(blackPen, w * 6, w * 14, w * 5, w * 14);
		//47
		g->DrawLine(blackPen, w * 5, w * 14, w * 3, w * 15);
		//48
		g->DrawLine(blackPen, w * 3, w * 15, w * 2, w * 16);
		//49
		g->DrawLine(blackPen, w * 13, w * 10, w * 12, w * 8);
		//50
		g->DrawLine(blackPen, w * 12, w * 8, w * 12, w * 6);
		//51
		g->DrawLine(blackPen, w * 15, w * 9, w * 13, w * 7);
		//52
		g->DrawLine(blackPen, w * 13, w * 7, w * 13, w * 5);
		//53
		g->DrawLine(blackPen, w * 14, w * 8, w * 14, w * 6);
		//54
		g->DrawLine(blackPen, w * 14, w * 6, w * 15, w * 5);
		//55
		g->DrawLine(blackPen, w * 15, w * 5, w * 17, w * 7);
		//56
		g->DrawLine(blackPen, w * 16, w * 7, w * 17, w * 8);
		//57
		g->DrawLine(blackPen, w * 15, w * 5, w * 16, w * 5);
		//58
		g->DrawLine(blackPen, w * 16, w * 5, w * 18, w * 6);
		//59
		g->DrawLine(blackPen, w * 18, w * 6, w * 20, w * 5);
		//60
		g->DrawLine(blackPen, w * 20, w * 5, w * 22, w * 5);
		//61
		g->DrawLine(blackPen, w * 22, w * 5, w * 21, w * 4);
		//62
		g->DrawLine(blackPen, w * 23, w * 5, w * 22, w * 4);
		//63
		g->DrawLine(blackPen, w * 23, w * 5, w * 23, w * 4);
		//64
		g->DrawLine(blackPen, w * 24, w * 5, w * 24, w * 4);
		//65
		g->DrawLine(blackPen, w * 24, w * 5, w * 26, w * 5);
		//66
		g->DrawLine(blackPen, w * 26, w * 5, w * 28, w * 6);
		//67
		g->DrawLine(blackPen, w * 28, w * 6, w * 29, w * 6);
		//68
		g->DrawLine(blackPen, w * 29, w * 6, w * 31, w * 4);
		//69
		g->DrawLine(blackPen, w * 31, w * 4, w * 30, w * 6);
		//70
		g->DrawLine(blackPen, w * 30, w * 6, w * 30, w * 7);
		//71
		g->DrawLine(blackPen, w * 30, w * 7, w * 32, w * 9);
		//72
		g->DrawLine(blackPen, w * 32, w * 9, w * 32, w * 5);
		//73
		g->DrawLine(blackPen, w * 32, w * 5, w * 31, w * 4);
		//74
		g->DrawLine(blackPen, w * 32, w * 8, w * 34, w * 7);
		//75
		g->DrawLine(blackPen, w * 34, w * 7, w * 35, w * 5);
		//76
		g->DrawLine(blackPen, w * 34, w * 8, w * 35, w * 6);
		//77
		g->DrawLine(blackPen, w * 34, w * 8, w * 33, w * 9);
		//78
		g->DrawLine(blackPen, w * 34, w * 9, w * 36, w * 7);
		//79
		g->DrawLine(blackPen, w * 35, w * 9, w * 37, w * 8);
		//80
		g->DrawLine(blackPen, w * 36, w * 9, w * 38, w * 10);
		//81
		g->DrawLine(blackPen, w * 37, w * 10, w * 38, w * 11);
		//82
		g->DrawLine(blackPen, w * 37, w * 10, w * 36, w * 10);
		//83
		g->DrawLine(blackPen, w * 36, w * 10, w * 37, w * 12);
		//84
		g->DrawLine(blackPen, w * 17, w * 9, w * 19, w * 9);
		//85
		g->DrawLine(blackPen, w * 18, w * 9, w * 18, w * 10);
		//86
		g->DrawLine(blackPen, w * 18, w * 10, w * 19, w * 11);
		//87
		g->DrawLine(blackPen, w * 19, w * 11, w * 21, w * 11+w/2);
		//88
		g->DrawLine(blackPen, w * 21, w * 11 + w / 2, w * 22, w * 11);
		//89
		g->DrawLine(blackPen, w * 22, w * 11, w * 23, w * 10);
		//90
		g->DrawLine(blackPen, w * 23, w * 10, w * 24, w * 11);
		//91
		g->DrawLine(blackPen, w * 24, w * 11, w * 25, w * 11);
		//92
		g->DrawLine(blackPen, w * 25, w * 11, w * 27, w * 10);
		//93
		g->DrawLine(blackPen, w * 27, w * 10, w * 28, w * 9);
		//94
		g->DrawLine(blackPen, w * 27, w * 9, w * 29, w * 9);
		//95
		g->DrawLine(blackPen, w * 23, w * 10, w * 23, w * 9);
		//96
		g->DrawLine(blackPen, w * 22, w * 9, w * 24, w * 9);
		//97
		g->DrawLine(blackPen, w * 22, w * 9, w * 22, w * 8);
		//98
		g->DrawLine(blackPen, w * 24, w * 9, w * 24, w * 8);
		//99
		g->DrawLine(blackPen, w * 22, w * 8, w * 24, w * 8);
		//100
		g->DrawLine(blackPen, w * 22, w * 7, w * 22+w/2, w * 7+w/2);
		//101
		g->DrawLine(blackPen, w * 22, w * 7, w * 22 + w / 2, w * 7 - w / 2);
		//102
		g->DrawLine(blackPen, w * 22 + w / 2, w * 7 + w / 2, w * 23 + w / 2, w * 6 + w / 2);
		//103
		g->DrawLine(blackPen, w * 22 + w / 2, w * 7 - w / 2, w * 23 + w / 2, w * 8 - w / 2);
		//104
		g->DrawLine(blackPen, w * 23 + w / 2, w * 8 - w / 2, w * 24, w * 7);
		//105
		g->DrawLine(blackPen, w * 24, w * 7, w * 24-w/2, w * 7-w/2);
		//106
		g->DrawLine(blackPen, w * 22, w * 5+w/2, w * 22-w/2, w * 6);
		//107
		g->DrawLine(blackPen, w * 23, w * 5 + w / 2, w * 24, w * 6);
		//108
		g->DrawLine(blackPen, w * 21, w * 3, w * 21, w * 2);
		//109
		g->DrawLine(blackPen, w * 21, w * 2, w * 22, w * 1);
		//110
		g->DrawLine(blackPen, w * 23, w * 1, w * 24, w * 3);
		//111
		g->DrawLine(blackPen, w * 15, w * 7, w * 16, w * 9);
	}
	private: System::Void MyForm_Resize(System::Object^  sender, System::EventArgs^  e) {
		this->Refresh();
	}
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
};
}
