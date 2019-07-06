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
				System::Collections::Generic::List<line> lines;				bool drawName;
				float left, right, top, bottom;
				float Wcx, Wcy, Wx, Wy;
				float Vcx, Vcy, Vx, Vy;				float minY,maxY;				float minX,maxX;
#pragma endregion
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		Graphics^ g = e->Graphics;
		g->Clear(Color::White);
		Pen^ blackPen = gcnew Pen(Color::Black);
		Pen^ rectPen = gcnew Pen(Color::Red);
		Rectangle rect = System::Drawing::Rectangle(left, top,Wx, Wy);
		blackPen->Width = 3;
		System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 10);
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);	
		Pen^ netPen = gcnew Pen(Color::Gray);
		//int width=20;
		//for(int i=0;i<Wx;i+=width)
		//{
		//	g->DrawLine(netPen,i,0,i,(int)Wy);
		//}
		//for(int i=0;i<Wy;i+=width)
		//{
		//	g->DrawLine(netPen,0,i,(int)Wx,i);
		//}
		for (int i = 0; i < matrices.size(); i++) 		{			mat С;
			times(T, matrices[i], С);
			g->Transform = gcnew System::Drawing::Drawing2D::Matrix(С[0][0], С[1][0],
				С[0][1], С[1][1],
				С[0][2], С[1][2]);			DrawFigure(g,blackPen);		}
		
	}
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 
		float oldWx = Wx, oldWy = Wy;
		mat R, T1;
		Wcx = 0;
		Wcy = 0;
		Wx = Form::ClientRectangle.Width-1;
		Wy = Form::ClientRectangle.Height-1;
		//Wx=60;
		//Wy=40;
		ZoomResize(Wx/oldWx, 0, 0, R, T, T1, false);
		ZoomResize(Wy / oldWy, 0, 0, R, T, T1, true);
		ZoomResize(Wx/oldWx, 0, 0, R, backupT, T1, false);
		ZoomResize(Wy / oldWy, 0, 0, R, backupT, T1, true);
		this->Refresh();
			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				
		left = 50, right = 50, top = 50, bottom = 50;
		Wcx = 0;
		Wcy = 0;
		Wx = Form::ClientRectangle.Width-1;
		//Wx=60;
		Wy = Form::ClientRectangle.Height-1;
		//Wy=40;
		drawName = true;
		//Vcx=0;
		//Vcy=0;
		//Vx=60;
		//Vy=40;
		drawName = true;
		unit(T);
		unit(backupT);
		minY=1e9;
		maxY=1e-9;
		minX=1e9;
		maxX=1e-9;
		//frameIcon(Vcx, Vcy, Vx, Vy, Wcx, Wcy, Wx, Wy, T);
		LoadPicture();
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
							else if ( cmd == "figure" ) {
								matrices.push_back(K);
							}
							else if ( cmd == "pushTransform" ) {
								matStack.push(K);
							}
							else if ( cmd == "popTransform" ) {
								K = matStack.top();
								matStack.pop();
							}
							else if ( cmd == "translate" ) {
								int Tx;
								int Ty;
								s>>Tx>>Ty;
								mat C, C1;
								move(Tx,Ty,C);
								times(K,C,C1);
								K=C1;
							}
							else if ( cmd == "scale" ) {
								float z;
								s>>z;
								mat C, C1;
								unit(C);
								Zoom(z,C);
								times(K, C, C1);
								K = C1;
							}
							else if ( cmd == "rotate" ) {
								float Phi;
								s >> Phi;
								float pi = 3.1415926535;
								float PhiR = Phi * (pi / 180);
								mat C, C1;
								unit(C);
								Rotate(PhiR, C,true);
								times(K, C, C1);
								K = C1;
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
					 System::String^ file="C:/Users/Aleksandr/Documents/Visual Studio 2010/Projects/Task6/Task6/picture.txt";
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

