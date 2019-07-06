#pragma once

namespace Task3 {

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

	private: bool drawName;
	private: float left, right, top, bottom;
	private: float Wcx, Wcy, Wx, Wy;
	private: float Vcx, Vcy, Vx, Vy;
	private: float maxXVal, minXVal, maxYVal, minYVal;
	private: System::Collections::Generic::List<line> lines;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;
	private: System::Collections::Generic::List<polygon^> polygons;
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
			this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
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

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics ^graphics = e->Graphics;
				 graphics->Clear(Color::White);

				 Pen ^blackPen = gcnew Pen(Color::Black);
				 blackPen->Width = 2;

				 Pen ^rectPen = gcnew Pen(Color::Red);
				 Rectangle rect = System::Drawing::Rectangle(left, top, Wx, Wy);

				 //Pen^ netPen = gcnew Pen(Color::Gray);

				 System::Drawing::Font ^drawFont = gcnew System::Drawing::Font("Arial", 10);
				 SolidBrush ^drawBrush = gcnew SolidBrush(Color::Black);	

				 for (int i = 0; i < polygons.Count; i++) 
				 {
					 point pmin,pmax;
					 pmin.x = left;
					 pmin.y = top;
					 pmax.x = Form::ClientRectangle.Width-right;
					 pmax.y = Form::ClientRectangle.Height-bottom;

					 polygon^ p = Pclip(ConvertP(polygons[i],T),pmin,pmax);

					 point a, b, c;

					 /*vec A, B, A1, B1;
					 point2vec(p[p->Count - 1], A);
					 timesMatVec(T, A, A1);
					 vec2point(A1, a);*/

					 if(p->Count>0)
					 {
					 	 a=p[p->Count - 1];
					 }
					 for (int j = 0; j < p->Count; j++)
					 {

						/*point2vec(p[j], B);
						timesMatVec(T, B, B1);
						vec2point(B1, b);*/

						 b=p[j];
						 graphics->DrawLine(blackPen, a.x, a.y, b.x, b.y);
						 a = b;
					 }
				 }
			 }

	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx, oldWy = Wy;
				 mat R, T1;

				 //Wcx = 0;
				 //Wcy = 0;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;
				 
				 scaleResize(Wx / oldWx, top, left, R, T, T1, false);
				 scaleResize(Wy / oldWy, top, left, R, T, T1, true);

				 scaleResize(Wx / oldWx, top, left, R, backupT, T1, false);
				 scaleResize(Wy / oldWy, top, left, R, backupT, T1, true);

				 this->Refresh();
			 }

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 left = right = top = bottom = 50;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height-bottom;
				 Wx = Form::ClientRectangle.Width-left-right;
				 Wy = Form::ClientRectangle.Height-top-bottom;
		
				 drawName = false;

				 unit(T);
				 unit(backupT);
				 
				 minYVal = 1e9;
				 maxYVal = 1e-9;
				 minXVal = 1e9;
				 maxXVal = 1e-9;
				 
				 polygons.Clear();

				 //LoadPicture();
			 }

	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) 
				 {
					 wchar_t fileName[1024];

					 for (int i = 0; i < openFileDialog->FileName->Length; i++) 
					 {
						fileName[i] = openFileDialog->FileName[i];
					 }

					 fileName[openFileDialog->FileName->Length] = '\0';

					 std::fstream in;
					 in.open(fileName);

					 if (in.is_open()) {
						 matrices.clear();
						 std::stack<mat> matStack;

						 mat K;
						 unit(K);
						 unit(T);

						 std::string str;
						 getline(in, str);

						 while (in) 
						 {
								 if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) 
								 {
									 std::stringstream s(str);
									 std::string cmd;
									 s >> cmd;

									 if ( cmd == "frame" ) {
										 int Vcx, Vcy, Vx, Vy;
										 s >> Vcx >> Vcy >> Vx >> Vy;

										 frameIcon(0, 0, Vx, Vy, Wcx, Wcy, Wx, Wy, T);
										 backupT = T;
									 } else if ( cmd == "polygon" ) {
										 int numpoint;
										 s >> numpoint;

										 polygon^ P = gcnew polygon(0);
										 for (int i = 0; i < numpoint; i++) 
										 {
											 point p;
											 s >> p.x >> p.y;

											 P->Add(p);
										 }

										 polygons.Add(P);
									 }
								 }

								 getline(in, str);
							}
					 }

					 this->Refresh();
				 }
			 }

	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 mat R, T1;
				 unit(R);
				 unit(T1);

				 switch (e->KeyCode) 
				 {
				 case Keys::W :
					 {
						 move(0, -1, R);
						 break;
					 }
				 case Keys::S :
					 {
						 move(0, 1, R);
						 break;
					 }
				 case Keys::A :
					 {
						 move(-1, 0, R);
						 break;
					 }
				 case Keys::D :
					 {
						 move(1, 0, R);
						 break;
					 }

				 case Keys::T :
					 {
						 move(0, -5, R);
						 break;
					 }
				 case Keys::G :
					 {
						 move(0, 5, R);
						 break;
					 }
				 case Keys::F :
					 {
						 move(-5, 0, R);
						 break;
					 }
				 case Keys::H :
					 {
						 move(5, 0, R);
						 break;
					 }

				 case Keys::E :
					 {
						 rotate(0.05, R, false);
						 break;
					 }
				 case Keys::Q :
					 {
						 rotate(0.05, R, true);
						 break;
					 }

				 case Keys::X :
					 {
						 scale(1.1, R);
						 break;
					 }
				 case Keys::Z :
					 {
						 scale(1 / 1.1, R);
						 break;
					 }

				 case Keys::J : 
					 {
						 reflect(R, Form::ClientRectangle.Width, Form::ClientRectangle.Height, false);
						 break;
					 }
				 case Keys::U :
					 {
						 reflect(R, Form::ClientRectangle.Width, Form::ClientRectangle.Height, true);
						 break;
					 }

				 case Keys::R :
					 {
						 rotateCenter(0.05, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, false);
						 break;
					 }
				 case Keys::Y :
					 {
						 rotateCenter(0.05, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, true);
						 break;
					 }

				 case Keys::C :
					 {
						 scaleCenter(1.1, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1);
						 break;
					 }
				 case Keys::V :
					 {
						 scaleCenter(1 / 1.1, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1);
						 break;
					 }

				 case Keys::I :
					 {
						 scaleAxes(1.1, 0, Form::ClientRectangle.Width, Form::ClientRectangle.Width, 
									Form::ClientRectangle.Height, R, T, T1, false);
						 break;
					 }
				 case Keys::O :
					 {
						 scaleAxes(1 / 1.1, 0, Form::ClientRectangle.Width, Form::ClientRectangle.Width,
									Form::ClientRectangle.Height, R, T, T1, false);
						 break;
					 }
				 case Keys::K :
					 {
						 scaleAxes(1.1, 0, Form::ClientRectangle.Width, Form::ClientRectangle.Width, 
									Form::ClientRectangle.Height, R, T, T1, true);
						 break;
					 }
				 case Keys::L :
					 {
						 scaleAxes(1 / 1.1, 0, Form::ClientRectangle.Width, Form::ClientRectangle.Width, 
									Form::ClientRectangle.Height, R, T, T1, true);
						 break;
					 }

				 case Keys::Escape :
					 {
						 unit(T);
						 T = backupT;
						 break;
					 }

				 case Keys::P :
					 {
						 drawName = !drawName;
						 unit(R);
						 break;
					 }

				 default :
					 {
						 unit(R);
					 }
				 }

				 times(R, T, T1);
				 set(T1, T);

				 this->Refresh();
			 }

	private: System::Void DrawFigure(Graphics^ g, Pen^ pen) {
			float cx = minXVal + (maxXVal - minXVal) / 2.0;
			float cy = minYVal + (maxYVal - minYVal) / 2.0;
			
			for (int i = 0; i < lines.Count; i++)
			{
				g->DrawLine(pen, lines[i].start.x, lines[i].start.y, lines[i].end.x, lines[i].end.y);
			}
		}

	private: System::Void LoadPicture() {
		wchar_t fileName[1024];
		System::String^ file="C:/picture2.txt";

		for (int i = 0; i < file->Length; i++)
		{
			fileName[i] = file[i];
		}

		fileName[file->Length] = '\0';

		std::ifstream in;
		in.open(fileName);
		
		if (in.is_open()) 
		{
			lines.Clear();

			std::string str;
			getline(in, str);

			while (in) 
			{
				if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
						std::stringstream s(str);
						line l;
						s >> l.start.x >> l.start.y >> l.end.x >> l.end.y;

						minYVal=System::Math::Min(minYVal,System::Math::Min(l.start.y,l.end.y));
						maxYVal=System::Math::Max(maxYVal,System::Math::Max(l.start.y,l.end.y));
						minXVal=System::Math::Min(minXVal,System::Math::Min(l.start.x,l.end.x));
						maxXVal=System::Math::Max(maxXVal,System::Math::Max(l.start.x,l.end.x));
						
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
};
}

