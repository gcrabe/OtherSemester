#pragma once

namespace Task3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
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
	private:
		/// <summary>
		/// ��������� ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ������������ ����� ��� ��������� ������������ - �� ���������
		/// ���������� ������� ������ ��� ������ ��������� ����.
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
			this->openFileDialog->Filter = L"��������� ����� (*.txt)|*.txt|��� ����� (*.*)|*.*";
			this->openFileDialog->Title = L"������� ����";
			// 
			// btnOpen
			// 
			this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnOpen->Location = System::Drawing::Point(697, 12);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"�������";
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
				 graphics->Clear(Color::Gray);

				 Pen ^blackPen = gcnew Pen(Color::Black);
				 blackPen->Width = 2;

				 Pen ^rectPen = gcnew Pen(Color::Red);
				 graphics->DrawRectangle(rectPen, Wcx, top, Wx, Wy);

				 System::Drawing::Font ^drawFont = gcnew System::Drawing::Font("Arial", 10);
				 SolidBrush ^drawBrush = gcnew SolidBrush(Color::Black);	

				 for (int i = 0; i < lines.Count; i++) 
				 {
					 vec A, B;
					 point2vec(lines[i].start, A);
					 point2vec(lines[i].end, B);

					 vec A1, B1;
					 timesMatVec(T, A, A1);
					 timesMatVec(T, B, B1);
					 if (i == 0)
					 {
						 maxXVal = System::Math::Max(A1[0], B1[0]);
						 minXVal = System::Math::Min(A1[0], B1[0]);
						 maxYVal = System::Math::Max(A1[1], B1[1]);
						 minYVal = System::Math::Min(A1[1], B1[1]);
					 }
					 else
					 {
						 maxXVal = System::Math::Max(maxXVal, System::Math::Max(A1[0], B1[0]));
						 minXVal = System::Math::Min(minXVal, System::Math::Min(A1[0], B1[0]));
						 maxYVal = System::Math::Max(maxYVal, System::Math::Max(A1[1], B1[1]));
						 minYVal = System::Math::Min(minYVal, System::Math::Min(A1[1], B1[1]));
					 }
				 
				 	 point a, b;
				 	 vec2point(A1, a);
				 	 vec2point(B1, b);

					 point c, d;
					 c.x = left;
					 c.y = top;
					 d.x = Form::ClientRectangle.Width - right;
					 d.y = Form::ClientRectangle.Height - top;
				 	 
					 if (Clip(a, b, c, d)) 
					 {
						 graphics->DrawLine(blackPen, a.x, a.y, b.x, b.y);

						 if (drawName) 
						 {
							 float strX = System::Math::Min(a.x, b.x) + abs(b.x - a.x) / 2;
							 float strY = System::Math::Min(a.y, b.y) + abs(b.y - a.y) / 2 - 20;

							 //graphics->DrawString(lines[i].name, drawFont, drawBrush, strX, strY);
						 }
					 }
				 }
			 }

	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx, oldWy = Wy;
				 mat R, T1;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;
				 
				 scaleResize(Wx / oldWx, top, left, R, T, T1, false);
				 scaleResize(Wy / oldWy, top, left, R, T, T1, true);

				 this->Refresh();
			 }

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 lines.Clear();
				 unit(T);

				 left = right = top = bottom = 50;
				 maxXVal = minXVal = maxYVal = minYVal = 0;
				 
				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;
				 
				 drawName = false;
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
						lines.Clear();
						unit(T);

						point a, b;
						
						in >> a.x >> a.y;
						Vcx = a.x;
						Vcy = a.y;

						in >> b.x >> b.y;
						Vx = b.x;
						Vy = b.y;

						frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);

						std::string str;
						getline(in, str);

						while (in) 
						{
							if (str.find_first_not_of(" \t\r\n") != std::string::npos && str[0] != '#') 
							{
								std::stringstream s(str);
								line l;

								s >> l.start.x >> l.start.y >> l.end.x >> l.end.y;

								std::string lineName;
								s >> lineName;

								l.name = gcnew String(lineName.c_str());

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
						 originalState(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx,Wcy,R, T, T1);
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
};
}

