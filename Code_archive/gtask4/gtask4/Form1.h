#pragma once

#define _max(a, b) (a > b ? a : b)
#define _min(a, b) (a < b ? a : b)

namespace gtask4 {

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
		System::Collections::Generic::List<line>lines;
	private:
		System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private:
		System::Windows::Forms::Button^  btnOpen;
	
	private: float left, right, top, bottom;
	private: float Wcx, Wcy, Wx, Wy;
	private: float Vcx, Vcy, Vx, Vy;

	private: float maxXVal, minXVal;
	private: float maxYVal, minYVal;
	
	private: bool drawName;

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
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->DefaultExt = L"txt";
			this->openFileDialog->FileName = L"openFileDialog1";
			this->openFileDialog->Filter = L"Текстовый докумет (*.txt)|*.txt|Все файлы (*.*)|*.*";
			this->openFileDialog->Title = L"Открыть файл";
			// 
			// btnOpen
			// 
			this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnOpen->Location = System::Drawing::Point(697, 12);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"Открыть";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 441);
			this->Controls->Add(this->btnOpen);
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(300, 300);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->ResumeLayout(false);
		}
#pragma endregion

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		lines.Clear();
		unit(T);
		
		left = 50;
		right = 50;
		top = 50;
		bottom = 50;
		
		Wcx = left;
		Wcy = Form::ClientRectangle.Height - bottom;
		Wx = Form::ClientRectangle.Width - left - right;
		Wy = Form::ClientRectangle.Height - top - bottom;

		drawName = false;

	}
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		Graphics^ g = e->Graphics;
		g->Clear(Color::White);

		Pen^ blackPen = gcnew Pen(Color::Black);
		blackPen->Width = 4;
		
		Pen^ rectPen = gcnew Pen(Color::Red);
		g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);
		
		System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 10);
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);	

		for (int i = 0; i < lines.Count;i++)
		{
			vec A, B;

			point2vec(lines[i].start, A);
			point2vec(lines[i].end, B);

			vec A1, B1;

			timesMatVec(T, A, A1);
			timesMatVec(T, B, B1);

			if (i == 0)
			{
				maxXVal = _max(A1[0], B1[0]);
				minXVal = _min(A1[0], B1[0]);
				maxYVal = _max(A1[1], B1[1]);
				minYVal = _min(A1[1], B1[1]);
			}
			else
			{
				maxXVal = _max(maxXVal, _max(A1[0], B1[0]));
				minXVal = _min(minXVal, _min(A1[0], B1[0]));
				maxYVal = _max(maxYVal, _max(A1[1], B1[1]));
				minYVal = _min(minYVal, _min(A1[1], B1[1]));
			}
			
			point a, b;
			point c, d;

			vec2point(A1, a);
			vec2point(B1, b);

			c.x = left;
			c.y = top;
			d.x = Form::ClientRectangle.Width - right;
			d.y = Form::ClientRectangle.Height - top;

			if (Clip(a, b, c, d))
			{
				g->DrawLine(blackPen, a.x, a.y, b.x, b.y);

				if (drawName)
				{
					g->DrawString(lines[i].name, drawFont, drawBrush, 
									System::Math::Min(a.x, b.x) + abs(b.x - a.x) / 2,
									System::Math::Min(a.y, b.y) + abs(b.y - a.y) / 2 - 20);
				}
			}
		}
	}
	
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
		float oldWx = Wx;
		float oldWy = Wy;

		mat R, T1;

		Wcx = left;
		Wcy = Form::ClientRectangle.Height - bottom;
		Wx = Form::ClientRectangle.Width - left - right;
		Wy = Form::ClientRectangle.Height - top - bottom;

		ZoomResize(Wx / oldWx, top, left, R, T, T1, false);
		ZoomResize(Wy / oldWy, top, left, R, T, T1, true);

		this->Refresh();
	}
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			wchar_t fileName[1024];

			for (int i = 0; i < openFileDialog->FileName->Length;i++)
				fileName[i] = openFileDialog->FileName[i];

			fileName[openFileDialog->FileName->Length] = '\0';

			std::ifstream in;
			in.open(fileName);

			if (in.is_open())
			{
				lines.Clear();
				unit(T);

				std::string str;
				point a;
				
				in >> a.x >> a.y;
				Vcx = a.x;
				Vcy = a.y;

				in >> a.x >> a.y;
				Vx = a.x;
				Vy = a.y;

				frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
				getline(in, str);

				while (in)
				{
					if (str.find_first_not_of(" \t\r\n") != std::string::npos && str[0] != '#')
					{
						std::stringstream s(str);
						line l;
						s >> l.start.x >> l.start.y >> l.end.x >> l.end.y;

						std::string linename;
						s >> linename;
						
						l.name = gcnew String(linename.c_str());
						lines.Add(l);
					}
					
					getline(in, str);
				}
			}

			this->Refresh();
		}
	}
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		mat R, T1;

		switch (e->KeyCode)
		{
			case Keys::W: 
				move(0, -1, R); 
				break;
			case Keys::T: 
				move(0, -10, R); 
				break;
			case Keys::S: 
				move(0, 1, R); 
				break;
			case Keys::G: 
				move(0, 10, R); 
				break;
			case Keys::A: 
				move(-1, 0, R); 
				break;
			case Keys::F: 
				move(-10, 0, R); 
				break;
			case Keys::D: 
				move(1, 0, R); 
				break;
			case Keys::H: 
				move(10, 0, R); 
				break;
			case Keys::E: 
				Rotate(0.05f, R, false); 
				break;
			case Keys::Q: 
				Rotate(0.05f, R, true); 
				break;
			case Keys::X: 
				Zoom(1.1, R); 
				break;
			case Keys::Z: 
				Zoom(1 / 1.1, R); 
				break;
			case Keys::J: 
				RepresentationCenter(R, Form::ClientRectangle.Width, Form::ClientRectangle.Height, true); 
				break;
			case Keys::U: 
				RepresentationCenter(R, Form::ClientRectangle.Width, Form::ClientRectangle.Height, false); 
				break;
			case Keys::R: 
				RotateAboutCenter(0.05f, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, true);  
				break;
			case Keys::Y: 
				RotateAboutCenter(0.05f, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, false);  
				break;
			case Keys::C: 
				ZoomAboutCenter(1.1, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1); 
				break;
			case Keys::V: 
				ZoomAboutCenter(1 / 1.1, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1); 
				break;
			case Keys::I: 
				ZoomAboutAxes(1 / 1.1, 0, Form::ClientRectangle.Width, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, false); 
				break;
			case Keys::O: 
				ZoomAboutAxes(1.1, 0, Form::ClientRectangle.Width, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, false); 
				break;
			case Keys::K:
				ZoomAboutAxes(1 / 1.1, 0, Form::ClientRectangle.Height, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, true); 
				break;
			case Keys::L:
				ZoomAboutAxes(1.1, 0, Form::ClientRectangle.Height, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, true); 
				break;
			case Keys::Escape: 
				OriginalState(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx,Wcy,R, T, T1); 
				break;
			case Keys::N: 
				ShowNorm(minYVal, maxYVal, R, T, T1);
				break;
			case Keys::P: 
				drawName = !drawName;
				//unit(R); 
				break;
			default:
				unit(R);
		}

		times(R, T, T1);
		set(T1,T);

		this->Refresh();
	}
	
	};
}

