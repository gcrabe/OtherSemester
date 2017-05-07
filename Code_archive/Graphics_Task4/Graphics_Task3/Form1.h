#pragma once

namespace Graphics_Task3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	
	private: System::ComponentModel::Container ^components;
	
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;
	
	private: System::Collections::Generic::List<t_line> lines;

	private: float left, right, top, bottom;
	
	private: float Wcx, Wcy, Wx, Wy;
	private: float Vcx, Vcy, Vx, Vy;

	private: bool drawNames;

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
			this->btnOpen->Location = System::Drawing::Point(197, 12);
			this->btnOpen->MinimumSize = System::Drawing::Size(5, 5);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 25);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"Открыть";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->btnOpen);
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(75, 75);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->ResumeLayout(false);
		}
#pragma endregion

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e){
				 Graphics ^graphics = e->Graphics;
				 graphics->Clear(Color::Gray);

				 Pen ^blackPen = gcnew Pen(Color::Black);
				 blackPen->Width = 1;

				 Pen ^rectPen = gcnew Pen(Color::Red);
				 rectPen->Width = 1;

				 graphics->DrawRectangle(rectPen, Wcx, top, Wx, Wy);

				 //////////////////////////
				 t_matrix Reform, Temp;
				 t_matrix CentralSystemFs, CentralSystemSc;
				 t_matrix SymReform, SymTemp;

				 t_move(0, - (float) Form::ClientRectangle.Height / 2.0f, CentralSystemFs);
				 t_move(0, (float) Form::ClientRectangle.Height / 2.0f, CentralSystemSc);
						
				 t_unit(Reform);
				 t_reflection_horizontal(SymReform);

				 t_times_matrix_to_matrix(SymReform, CentralSystemFs, SymTemp);
				 t_times_matrix_to_matrix(CentralSystemSc, SymTemp, Reform);
				  
				 t_times_matrix_to_matrix(Reform, ETransform, Temp);
				 t_set(Temp, ETransform);
				 //////////////////////////

				 int linesCount = lines.Count;

				 for (int i = 0; i < linesCount; i++)
				 {
					 t_vector fs;
					 t_vector sc;

					 t_point_to_vector(lines[i].start, fs);
					 t_point_to_vector(lines[i].end, sc);

					 t_vector tFs;
					 t_vector tSc;

					 t_times_matrix_to_vector(ETransform, fs, tFs);
					 t_times_matrix_to_vector(ETransform, sc, tSc);

					 t_point drawStart, drawEnd;

					 t_vector_to_point(tFs, drawStart);
					 t_vector_to_point(tSc, drawEnd);

					 graphics->DrawLine(blackPen, drawStart.x, drawStart.y, drawEnd.x, drawEnd.y);
				 }

				 //FILE *fileDebug = fopen("graphicsDebug.txt", "wt");
				 //fprintf(fileDebug, "%.2f %.2f %.2f %.2f", Wcx, top, Wx, Wy);
			 }

	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Vx, oldWy = Wy; 

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;

				 t_matrix RszScale;
				 t_matrix RszMovFs, RszMovSc;

				 t_scale_xy(Wx / oldWx, Wy / oldWy, RszScale);
				 t_move(Wcx, top, RszMovFs);
				 t_move(Wcx, top, RszMovSc);
				 
				 t_matrix MovRef, Ref, TmpRef;
				 
				 t_times_matrix_to_matrix(RszMovSc, RszScale, MovRef);
				 t_times_matrix_to_matrix(MovRef, RszMovFs, Ref);
				 t_times_matrix_to_matrix(Ref, ETransform, MovRef);
				 
				 t_set(MovRef, ETransform);

				 this->Refresh();
			 }

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 lines.Clear();
				 t_unit(ETransform);

				 left = 50;
				 top = 50;
				 right = 50;
				 bottom = 50;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;

				 drawNames = false;
			 }

	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 wchar_t fileName[1024];

					 for (int i = 0; i < openFileDialog->FileName->Length; i++)
						 fileName[i] = openFileDialog->FileName[i];

					 fileName[openFileDialog->FileName->Length] = '\0';
				 
					 std::ifstream inStream;
					 inStream.open(fileName);

					 bool loadSize = false;

					 if (inStream.is_open())
					 {
						 lines.Clear();

						 t_unit(ETransform);
						 
						 std::string str;
						 getline(inStream, str);

						 while (inStream)
						 {
							 if (str.find_first_not_of(" \t\r\n") != std::string::npos && str[0] != '#')
							 {
								 std::stringstream strStream(str);
								 
								 if(!loadSize)
								 {
									 float vcx, vcy, vx, vy;
									 strStream >> vcx >> vcy >> vx >> vy;
									 
									 this->Vcx = vcx;
									 this->Vcy = vcy;
									 this->Vx = vx;
									 this->Vy = vy;
									 
									 loadSize = true;
									 
									 getline(inStream, str);
									 continue;
								 }
								 
								 t_line tempLine;

								 strStream >> tempLine.start.x >> tempLine.start.y >> tempLine.end.x >> tempLine.end.y;

								 std::string lineName;
								 strStream >>lineName;

								 tempLine.name = gcnew String(lineName.c_str());

								 lines.Add(tempLine);
							 }

							 getline(inStream, str);
						 }
					 }

					 t_frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, ETransform);
					 this->Refresh();
				 }
			 }

	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 t_matrix Reform;
				 t_matrix Temp;

				 t_matrix CentralSystemFs;
				 t_matrix CentralSystemSc;

				 t_matrix SymReform;
				 t_matrix SymTemp;

				 switch	(e->KeyCode)
				 {
				 case Keys::S :
					 t_move(0, -1, Reform);
					 break;
				 case Keys::W :
					 t_move(0, 1, Reform);
					 break;
				 case Keys::A : 
					 t_move(-1, 0, Reform);
					 break;
				 case Keys::D : 
					 t_move(1, 0, Reform);
					 break;

				 case Keys::G :
					 t_move(0, -5, Reform);
					 break;
				 case Keys::T :
					 t_move(0, 5, Reform);
					 break;
				 case Keys::F : 
					 t_move(-5, 0, Reform);
					 break;
				 case Keys::H : 
					 t_move(5, 0, Reform);
					 break;

				 case Keys::E : 
					 t_rotate(0.05f, Reform);
					 break;
				 case Keys::Q : 
					 t_rotate(-0.05f, Reform);
					 break;
				 
				 case Keys::X : 
					 t_scale(1.1f, Reform);
					 break;
				 case Keys::Z :
					 t_scale(1.0f / 1.1f, Reform);
					 break;

				 case Keys::U : 
					 {
						 t_move(- (float) Form::ClientRectangle.Width / 2.0f, 0, CentralSystemFs);
						 t_move((float) Form::ClientRectangle.Width / 2.0f, 0, CentralSystemSc);

						 t_unit(Reform);
						 t_reflection_vertical(SymReform);

						 t_times_matrix_to_matrix(SymReform, CentralSystemFs, SymTemp);
						 t_times_matrix_to_matrix(CentralSystemSc, SymTemp, Reform);

						 break;
					 }
				 case Keys::J :
					 {
						 t_move(0, - (float) Form::ClientRectangle.Height / 2.0f, CentralSystemFs);
						 t_move(0, (float) Form::ClientRectangle.Height / 2.0f, CentralSystemSc);
						
						 t_unit(Reform);
						 t_reflection_horizontal(SymReform);

						 t_times_matrix_to_matrix(SymReform, CentralSystemFs, SymTemp);
						 t_times_matrix_to_matrix(CentralSystemSc, SymTemp, Reform);

						 break;
					 }

				case Keys::R :
					 {
						 t_move(- (float) Form::ClientRectangle.Width / 2.0f, - (float) Form::ClientRectangle.Height / 2.0f, CentralSystemFs);
						 t_move((float) Form::ClientRectangle.Width / 2.0f, (float) Form::ClientRectangle.Height / 2.0f, CentralSystemSc);
						 
						 t_unit(Reform);
						 t_rotate(-0.05f, SymReform);

						 t_times_matrix_to_matrix(SymReform, CentralSystemFs, SymTemp);
						 t_times_matrix_to_matrix(CentralSystemSc, SymTemp, Reform);

						 break;
					 }
				case Keys::Y :
					 {
						 t_move(- (float) Form::ClientRectangle.Width / 2.0f, - (float) Form::ClientRectangle.Height / 2.0f, CentralSystemFs);
						 t_move((float) Form::ClientRectangle.Width / 2.0f, (float) Form::ClientRectangle.Height / 2.0f, CentralSystemSc);
						
						 t_unit(Reform);
						 t_rotate(0.05f, SymReform);

						 t_times_matrix_to_matrix(SymReform, CentralSystemFs, SymTemp);
						 t_times_matrix_to_matrix(CentralSystemSc, SymTemp, Reform);

						 break;
					 }

				case Keys::C :
					 {
						 t_move(- (float) Form::ClientRectangle.Width / 2.0f, - (float) Form::ClientRectangle.Height / 2.0f, CentralSystemFs);
						 t_move((float) Form::ClientRectangle.Width / 2.0f, (float) Form::ClientRectangle.Height /  2.0f, CentralSystemSc);
						
						 t_unit(Reform);
						 t_scale(1.0f / 1.1f, SymReform);

						 t_times_matrix_to_matrix(SymReform, CentralSystemFs, SymTemp);
						 t_times_matrix_to_matrix(CentralSystemSc, SymTemp, Reform);

						 break;
					 }
				case Keys::V :
					 {
						 t_move(- (float) Form::ClientRectangle.Width / 2.0f, - (float) Form::ClientRectangle.Height / 2.0f, CentralSystemFs);
						 t_move((float) Form::ClientRectangle.Width / 2.0f, (float) Form::ClientRectangle.Height /  2.0f, CentralSystemSc);
						
						 t_unit(Reform);
						 t_scale(1.1f, SymReform);

						 t_times_matrix_to_matrix(SymReform, CentralSystemFs, SymTemp);
						 t_times_matrix_to_matrix(CentralSystemSc, SymTemp, Reform);

						 break;
					 }

				case Keys::I :
					 {
						 t_move(- (float) Form::ClientRectangle.Width / 2.0f, 0, CentralSystemFs);
						 t_move((float) Form::ClientRectangle.Width / 2.0f, 0, CentralSystemSc);
						
						 t_unit(Reform);
						 t_scale(1.0 / 1.1f, SymReform);

						 t_times_matrix_to_matrix(SymReform, CentralSystemFs, SymTemp);
						 t_times_matrix_to_matrix(CentralSystemSc, SymTemp, Reform);

						 break;
					 }
				case Keys::O :
					 {
						 t_move(- (float) Form::ClientRectangle.Width / 2.0f, 0, CentralSystemFs);
						 t_move((float) Form::ClientRectangle.Width / 2.0f, 0, CentralSystemSc);
						
						 t_unit(Reform);
						 t_scale(1.1f, SymReform);

						 t_times_matrix_to_matrix(SymReform, CentralSystemFs, SymTemp);
						 t_times_matrix_to_matrix(CentralSystemSc, SymTemp, Reform);

						 break;
					 }
					 case Keys::K :
					 {
						 t_move(0, - (float) Form::ClientRectangle.Height / 2.0f, CentralSystemFs);
						 t_move(0, (float) Form::ClientRectangle.Height /  2.0f, CentralSystemSc);
						
						 t_unit(Reform);
						 t_scale(1.0f / 1.1f, SymReform);

						 t_times_matrix_to_matrix(SymReform, CentralSystemFs, SymTemp);
						 t_times_matrix_to_matrix(CentralSystemSc, SymTemp, Reform);

						 break;
					 }
				case Keys::L :
					 {
						 t_move(0, - (float) Form::ClientRectangle.Height / 2.0f, CentralSystemFs);
						 t_move(0, (float) Form::ClientRectangle.Height /  2.0f, CentralSystemSc);
						
						 t_unit(Reform);
						 t_scale(1.1f, SymReform);

						 t_times_matrix_to_matrix(SymReform, CentralSystemFs, SymTemp);
						 t_times_matrix_to_matrix(CentralSystemSc, SymTemp, Reform);

						 break;
					 }

				case Keys::Escape :
					{
						t_frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, ETransform);
						t_unit(Reform);
						break;
					}

				case Keys::P :
					{
						drawNames = !drawNames;
						t_unit(Reform);
						break;
					}

				 default : 
					 t_unit(Reform);
				 }

				 t_times_matrix_to_matrix(Reform, ETransform, Temp);
				 t_set(Temp, ETransform);

				 this->Refresh();
			 }
	};
}

