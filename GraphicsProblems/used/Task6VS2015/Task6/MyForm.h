#pragma once
#include<vector>
#include <ctime>
namespace Task3 {

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
		System::Collections::Generic::List<line>lines;
		bool drawName;
		float left, right, top, bottom;
		float Wcx, Wcy, Wx, Wy;
		float Vcx, Vcy, Vx, Vy;

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;


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
			this->btnOpen->Click += gcnew System::EventHandler(this, &MyForm::btnOpen_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 441);
			this->Controls->Add(this->btnOpen);
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(300, 300);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		lines.Clear();
		unit(T);
		left = 50, right = 50, top = 50, bottom = 50;
		Wcx = left;
		Wcy = Form::ClientRectangle.Height - bottom;
		Wx = Form::ClientRectangle.Width - left - right;
		Wy = Form::ClientRectangle.Height - top - bottom;
		drawName = true;

	}
	private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		Graphics^ g = e->Graphics;
		g->Clear(Color::White);
		Pen^ blackPen = gcnew Pen(Color::Black);
		Pen^ rectPen = gcnew Pen(Color::Red);
		Rectangle rect = System::Drawing::Rectangle(Wcx, top, Wx, Wy);
		g->DrawRectangle(rectPen, rect);
		g->Clip = gcnew System::Drawing::Region(rect);
		blackPen->Width = 3;
		System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 10);
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);	

		g->Transform=gcnew System::Drawing::Drawing2D::Matrix(T[0][0], T[1][0],T[0][1], T[1][1],T[0][2], T[1][2]);
		for (int i = 0; i < lines.Count; i++)
		{
			g->DrawLine(blackPen, lines[i].start.x, lines[i].start.y, lines[i].end.x, lines[i].end.y);
		}
	}

	private: System::Void MyForm_Resize(System::Object^  sender, System::EventArgs^  e) {
		float oldWx = Wx, oldWy = Wy;
		mat R, T1;
		Wcx = left;
		Wcy = Form::ClientRectangle.Height - bottom;
		Wx = Form::ClientRectangle.Width - left - right;
		Wy = Form::ClientRectangle.Height - top - bottom;
		ZoomResize(Wx/oldWx, top, left, R, T, T1, false);
		ZoomResize(Wy / oldWy, top, left, R, T, T1, true);
		this->Refresh();
	}
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
		//this->openFileDialog->ShowDialog();
		if (this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			wchar_t fileName[1024];
			for (int i = 0; i < openFileDialog->FileName->Length;i++)
			{
				fileName[i] = openFileDialog->FileName[i];
			}
			fileName[openFileDialog->FileName->Length] = '\0';
			std::ifstream in;
			in.open(fileName);
			if (in.is_open()) {
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
				while (in) {
						if ((str.find_first_not_of(" \t\r\n") != std::string::npos)
							&& (str[0] != '#')) {
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
	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		mat R, T1;
		switch (e->KeyCode)
		{
		case Keys::W: move(0, -1, R); break;
		case Keys::T: move(0, -10, R); break;
		case Keys::S: move(0, 1, R); break;
		case Keys::G: move(0, 10, R); break;
		case Keys::A: move(-1, 0, R); break;
		case Keys::F: move(-10, 0, R); break;
		case Keys::D: move(1, 0, R); break;
		case Keys::H: move(10, 0, R); break;
		case Keys::E: Rotate(0.05f, R, false); break;
		case Keys::Q: Rotate(0.05f, R, true); break;
		case Keys::X: Zoom(1.1, R); break;
		case Keys::Z: Zoom(1 / 1.1, R); break;
		case Keys::J: RepresentationCentre(R, Form::ClientRectangle.Width, Form::ClientRectangle.Height, true); break;
		case Keys::U: RepresentationCentre(R, Form::ClientRectangle.Width, Form::ClientRectangle.Height, false); break;
		case Keys::R: RotateAboutCentre(0.05f, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, true);  break;
		case Keys::Y: RotateAboutCentre(0.05f, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, false);  break;
		case Keys::C: ZoomAboutCentre(1.1, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1); break;
		case Keys::V: ZoomAboutCentre(1 / 1.1, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1); break;
		case Keys::I: ZoomAboutAxes(1 / 1.1, 0, Form::ClientRectangle.Width, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, false); break;
		case Keys::O: ZoomAboutAxes(1.1, 0, Form::ClientRectangle.Width, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, false); break;
		case Keys::K:ZoomAboutAxes(1 / 1.1, 0, Form::ClientRectangle.Height, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, true); break;
		case Keys::L:ZoomAboutAxes(1.1, 0, Form::ClientRectangle.Height, Form::ClientRectangle.Width, Form::ClientRectangle.Height, R, T, T1, true); break;
		case Keys::Escape: OriginalState(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx,Wcy,R, T, T1); break;
		case Keys::P: drawName = !drawName;unit(R); break;
		default:unit(R);
		}
		times(R, T, T1);
		set(T1,T);
		this->Refresh();
	}
	private: System::Void Transform(){

	}
};
}
