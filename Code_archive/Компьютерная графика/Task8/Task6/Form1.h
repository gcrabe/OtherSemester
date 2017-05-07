#pragma once

namespace Task6 {

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
	private: System::Windows::Forms::Button^  btnOpen;
	protected: 
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;



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
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// btnOpen
			// 
			this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnOpen->Location = System::Drawing::Point(697, 13);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"Open";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"openFileDialog";
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
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->ResumeLayout(false);

		}
		private:
				System::Collections::Generic::List<line> lines;				System::Collections::Generic::List<polygon^> polygons;				System::Collections::Generic::List<clr^> colors;				bool drawName;
				float left, right, top, bottom;
				float Wcx, Wcy, Wx, Wy;
				float Vcx, Vcy, Vx, Vy;				float minY,maxY;				float minX,maxX;
#pragma endregion
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		//Graphics^ g = e->Graphics;
		Bitmap^ image1 = gcnew Bitmap( this->ClientRectangle.Width, this->ClientRectangle.Height);
		Graphics^ g = Graphics::FromImage(image1);

		g->Clear(Color::White);
		Pen^ rectPen = gcnew Pen(Color::Red);
		Rectangle rect = System::Drawing::Rectangle(left, top, Wx, Wy);
		System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 10);
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);	
		Pen^ netPen = gcnew Pen(Color::Gray);
		g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);
		for (int i = 0; i < polygons.Count; i++) {
			Pen^ drawPen = gcnew Pen(Color::FromArgb(colors[i][0], colors[i][1], colors[i][2]));
			drawPen->Width = 3;
			point pmin,pmax;
			pmin.x = left;
			pmin.y = top;
			pmax.x = Form::ClientRectangle.Width-right;
			pmax.y = Form::ClientRectangle.Height-bottom;
			polygon^ p = Pclip(ConvertP(polygons[i],T),pmin,pmax);
			//polygon^ p=polygons[i];
			//polygon^ p=ConvertP(polygons[i],T);
			Pfill(p,image1,Color::FromArgb(colors[i][0], colors[i][1], colors[i][2]));
			/*
			point a, b, c;
			vec A, B, A1, B1;
			if(p->Count>0){
			point2vec(p[p->Count - 1], A);
			}
			timesMatVec(T, A, A1);
			vec2point(A1, a);
			if(p->Count>0)
			{
				a=p[p->Count - 1];
			}
			for (int j = 0; j < p->Count; j++){
				point2vec(p[j], B);
				timesMatVec(T, B, B1);
				vec2point(B1, b);
				b=p[j];
				g ->DrawLine(drawPen, a.x, a.y, b.x, b.y);
				a = b;
			}*/
		}
		g = e->Graphics;
		g->DrawImage(image1,0,0);
		delete image1;
	}
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 
		float oldWx = Wx, oldWy = Wy;
		mat R, T1;
		Wx = Form::ClientRectangle.Width-left-right;
		Wy = Form::ClientRectangle.Height-top-bottom;
		//Wx=60;
		//Wy=40;
		ZoomResize(Wx/oldWx, top, left, R, T, T1, false);
		ZoomResize(Wy / oldWy, top, left, R, T, T1, true);
		ZoomResize(Wx/oldWx, top, left, R, backupT, T1, false);
		ZoomResize(Wy / oldWy, top, left, R, backupT, T1, true);
		this->Refresh();
			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				
		left = 50, right = 50, top = 50, bottom = 50;
		Wcx = left;
		Wcy = Form::ClientRectangle.Height-bottom;
		Wx = Form::ClientRectangle.Width-left-right;
		Wy = Form::ClientRectangle.Height-top-bottom;
		drawName = true;
		drawName = true;
		unit(T);
		unit(backupT);
		minY=1e9;
		maxY=1e-9;
		minX=1e9;
		maxX=1e-9;
		polygons.Clear();
		colors.Clear();
		//LoadPicture();
			 }
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
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
				matrices.clear();
				std::stack<mat> matStack;
				mat K; unit(K);
				unit(T);
				std::string str;
				getline(in, str);
				while (in) {
						if ((str.find_first_not_of(" \t\r\n") != std::string::npos)
							&& (str[0] != '#')) {
							std::stringstream s(str);
							std::string cmd;
							s >> cmd;
							if ( cmd == "frame" ) {
								int Vcx;
								int Vcy;
								int Vx;
								int Vy;
								s>>Vcx>>Vcy>>Vx>>Vy;
								frameIcon(0,0,Vx,Vy,Wcx,Wcy,Wx,Wy,T);
								backupT=T;
							}
							else if ( cmd == "polygon" ) {
								int numpoint;
								s >> numpoint;
								polygon^ P = gcnew polygon(0);
								for (int i = 0; i<numpoint; i++) {
									point p;
									s >> p.x >> p.y;
									P->Add(p);
								}
								polygons.Add(P);
							}
							else{
								if(cmd == "color"){
									clr^ c = gcnew clr(0);
									for (int i = 0; i<3; i++) {
										int color;
										s>>color;
										c->Add(color);
									}
									colors.Add(c);
								}
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
		case Keys::Escape: unit(T);/*frameIcon(0,0,Vx,Vy,Wcx,Wcy,Wx,Wy,T);*/T=backupT; break;
		default:unit(R);
		}
		times(R, T, T1);
		set(T1,T);
		this->Refresh();
		 }
		 private: System::Void DrawFigure(Graphics^ g, Pen^ pen){
					  float cx=minX+(maxX-minX)/2.0;
					  float cy=minY+(maxY-minY)/2.0;
					  for (int i = 0; i < lines.Count; i++)
					  {
						  g->DrawLine(pen, lines[i].start.x, lines[i].start.y, lines[i].end.x, lines[i].end.y);
					  }
				  }
		private: System::Void LoadPicture()
				 {
					 wchar_t fileName[1024];
					 System::String^ file="D:/Универ/6 семестр/Компьютерная графика/Task7/Task6/picture.txt";
					 for (int i = 0; i < file->Length;i++)
					 {
						 fileName[i] = file[i];
					 }
					 fileName[file->Length] = '\0';
					 std::ifstream in;
					 in.open(fileName);
					 if (in.is_open()) {
						 lines.Clear();
						 std::string str;
						 getline(in, str);
						 while (in) {
							 if ((str.find_first_not_of(" \t\r\n") != std::string::npos)
								 && (str[0] != '#')) {
									 std::stringstream s(str);
									 line l;
									 s >> l.start.x >> l.start.y >> l.end.x >> l.end.y;
									 minY=System::Math::Min(minY,System::Math::Min(l.start.y,l.end.y));
									 maxY=System::Math::Max(maxY,System::Math::Max(l.start.y,l.end.y));
									 minX=System::Math::Min(minX,System::Math::Min(l.start.x,l.end.x));
									 maxX=System::Math::Max(maxX,System::Math::Max(l.start.x,l.end.x));
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
private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

