#pragma once

namespace Task5 {

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

	private: 
		System::Collections::Generic::List<line>lines;
	private: bool drawName;
	private: point X, addX;
	private: int l, r;
	private: double left, right, top, bottom;
	private: double Wcx, Wcy, Wx, Wy;
	private: double Vcx, Vcy, Vx, Vy;
	private: point minW, maxW;
	private: int L, K;
	private: 
		System::Windows::Forms::OpenFileDialog^  openFileDialog;
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
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->DefaultExt = L"txt";
			this->openFileDialog->FileName = L"openFileDialog1";
			this->openFileDialog->Filter = L"��������� ������� (*.txt)|*.txt|��� ����� (*.*)|*.*";
			this->openFileDialog->Title = L"������� ����";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 461);
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

				 l = 0, r = 0;
				 left = 50, right = 50, top = 50, bottom = 50;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;

				 Vcx = 0;
				 Vcy = 0;
				 Vx = 784;
				 Vy = 461;

				 drawName = true;

				 unit(T);
				 unit(T2);
				 unit(TCoo);
				 unit(TPoint);

				 frame(Vx, Vy, Vcx + Vx / 2.0, Vcy + Vy / 2.0, Wx, Wy, Wcx, Wcy, T);
				 frame(Vx, Vy, Vcx + Vx / 2.0, Vcy + Vy / 2.0, Wx, Wy, Wcx, Wcy, T2);

				 L = 10;
				 K = 10;

				 minW.x = left;
				 minW.y = top;
				 maxW.x = Form::ClientRectangle.Width - right;
				 maxW.y = Form::ClientRectangle.Height - top;
				 
				 X.x = Vx;
				 X.y = 0;
				 
				 addX.x = 0;
				 addX.y = 0;
			 }

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics^ g = e->Graphics;
				 g->Clear(Color::White);

				 Pen^ blackPen = gcnew Pen(Color::Black);
				 Pen^ colorNet = gcnew Pen(Color::Gray);
				 Pen^ rectPen = gcnew Pen(Color::DarkGray);

				 g->DrawRectangle(rectPen, (float)Wcx, (float)top, (float)Wx, (float)Wy);
				 blackPen->Width = 3;
				 colorNet->Width = 0.5;

				 System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 8);
				 SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);	

				 int count = 0;
				 for (double i = - Vx / 2.0 + ((double)Vx) / ((double)(L + 1)); count < L + 1; i += ((double)Vx) / ((double)(L+1)), count++) {
					 point p1,p2;
					 point a, b;

					 p1.x = i;
					 p1.y = -Vy / 2;
					 p2.x = i;
					 p2.y = Vy/2;
					 
					 a = ConvertPoint(T2,p1);
					 b = ConvertPoint(T2, p2);
					 
					 if (Clip(a, b, minW, maxW)) {
						 g->DrawLine(colorNet, (float)a.x, (float)a.y, (float)b.x, (float)b.y);
						 g->DrawString(ConvertPoint(TCoo, p2).x.ToString("F"), drawFont, drawBrush, b.x, b.y - 15);
					 }
				 }

				 count = 0;
				 for (double i = - Vy / 2.0 + ((double)Vy) / ((double)(K + 1)); count < K; i += ((double)Vy) / ((double)(K + 1)), count++) {
					 point p1,p2;
					 point a, b;

					 p1.x = -Vx / 2;
					 p1.y = i;
					 p2.x = Vx/2;
					 p2.y = i;
					 
					 a = ConvertPoint(T2, p1);
					 b = ConvertPoint(T2, p2);
					 
					 if (Clip(a, b, minW, maxW)) {
						 g->DrawLine(colorNet, (float)a.x, (float)a.y, (float)b.x, (float)b.y);
						 g->DrawString(ConvertPoint(TCoo, p1).y.ToString("F"), drawFont, drawBrush, a.x, a.y - 15);
					 }
				 }

				 double pl = 0.1;
				 for (double x = - (ConvertPoint(TPoint, X).x / 2.0) + System::Math::Min(l, 0);
						x <= ConvertPoint(TPoint, X).x / 2.0 + System::Math::Max(r, 0); x += pl) {
					 point p1,p2;
					 point a, b;
					 
					 p1.x = x;
					 p1.y = F(x);
					 p2.x = x + pl;
					 p2.y = F(x + pl);
					 
					 a = ConvertPoint(T,p1);
					 b = ConvertPoint(T, p2);
					 
					 if (FExist(p1.x) && FExist(p2.x) && Clip(a, b, minW, maxW)) {
						 g->DrawLine(blackPen, (float)a.x, (float)a.y, (float)b.x, (float)b.y);
					 }
				 }
			 }

	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 mat R, T1, RCoo, RPoint;

				 unit(R);
				 unit(RCoo);
				 unit(RPoint);

				 switch (e->KeyCode)
				 {
					 case Keys::W: 
						 {
							 move(0, -1, R);
							 move(0, -1, RCoo); 
							 break;
						 }
					 case Keys::T: 
						 {
							 move(0, -5, R);
							 move(0, -5, RCoo);
							 break;
						 }
					 case Keys::S: 
						 {
							 move(0, 1, R); 
							 move(0, 1, RCoo); 
							 break;
						 }
					 case Keys::G: 
						 {
							 move(0, 5, R); 
							 move(0, 5, RCoo); 
							 break;
						 }
					 case Keys::A: 
						 {
							 move(-1, 0, R); 
							 move(1, 0, RCoo); 
							 r += 3; 
							 l += 3; 
							 break;
						 }
					 case Keys::F: 
						 {
							 move(-5, 0, R); 
							 move(5, 0, RCoo); 
							 r += 15;
							 l+=15; 
							 break;
						 }
					 case Keys::D: 
						 {
							 move(1, 0, R); 
							 move(-1, 0, RCoo); 
							 l -= 3; 
							 r -= 3; 
							 break;
						 }
					 case Keys::H:
						 {
							 move(5, 0, R);
							 move(-5, 0, RCoo); 
							 l -= 15; 
							 r -= 15; 
							 break;
						 }
					 case Keys::E: 
						 {
							L=System::Math::Max(L-1,0);
							break;
						 }
					 case Keys::Q: 
						 {
							L++; 
							break;
						 }
					 case Keys::Z: 
						 {
							K++; 
							break;
						 }
					 case Keys::C: 
						 {
							K = System::Math::Max(K - 1, 0); 
							break;
						 }
					 case Keys::I:
						 {
							scaleAxesDr(1 / 1.1, 0, Form::ClientRectangle.Width, 
								Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, false); 

							scaleAxes(1.1, 0, 0, RCoo, TCoo, T1, false);
							scaleAxes(1.1, 0, 0, RPoint, TPoint, T1, false); 
							break;
						 }
					 case Keys::O:
						 {
							scaleAxesDr(1.1, 0, Form::ClientRectangle.Width, 
								Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, false);

							scaleAxes(1 / 1.1, 0, 0, RCoo, TCoo, T1, false);
							scaleAxes(1 / 1.1, 0, 0, RPoint, TPoint, T1, false);
							break;
						 }
					 case Keys::K:
						 {
							scaleAxesDr(1 / 1.1, 0, Form::ClientRectangle.Height, 
								Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, true);

							scaleAxes(1.1, 0, 0, RCoo, TCoo, T1, true);
							scaleAxes(1.1, 0, 0, RPoint, TPoint, T1, true);
							break;
						 }
					 case Keys::L:
						 {
							scaleAxesDr(1.1, 0, Form::ClientRectangle.Height,
								Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, true);

							scaleAxes(1 / 1.1, 0, 0, RCoo, TCoo, T1, true);
							scaleAxes(1 / 1.1, 0, 0, RPoint, TPoint, T1, true);
							break;
						 }
					 case Keys::Escape:
						 {
							originalState(Vx, Vy, Vcx + Vx / 2, Vcy + Vy / 2, Wx, Wy, Wcx, Wcy, R, T, T1);
							originalState(Vx, Vy, Vcx + Vx / 2, Vcy + Vy / 2, Wx, Wy, Wcx, Wcy, R, T2, T1);
							unit(TCoo); 
							unit(TPoint);
							l = 0;
							r = 0;
							break;
						 }
					 default:
						 {
							unit(R);
						 }
				 }

				 times(R, T, T1);
				 set(T1,T);

				 unit(T1);
				 times(RCoo, TCoo, T1);
				 set(T1, TCoo);

				 unit(T1);
				 times(RPoint, TPoint, T1);
				 set(T1, TPoint);

				 this->Refresh();
			 }

	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 double oldWx = Wx, oldWy = Wy;
				 mat R, T1;
				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;

				 scaleResize(Wx / oldWx, top, left, R, T, T1, false);
				 scaleResize(Wy / oldWy, top, left, R, T, T1, true);
				 scaleResize(Wx / oldWx, top, left, R, T2, T1, false);
				 scaleResize(Wy / oldWy, top, left, R, T2, T1, true);

				 minW.x = left;
				 minW.y = top;
				 maxW.x = Form::ClientRectangle.Width - right;
				 maxW.y = Form::ClientRectangle.Height - top;

				 this->Refresh();
			 }
	};
}

