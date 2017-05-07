#pragma once


namespace task3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
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
	private: System::Collections::Generic::List<line> lines;
			 System::Collections::Generic::List<polygon^> polygons;
			 System::Collections::Generic::List<polygon3D^> polygons3D;
			 System::Collections::Generic::List<System::Drawing::Color> colors;
			 System::Drawing::Color currentColor;	
			 point3D eye, center, up, BASE_EYE, BASE_CENTER, BASE_UP;
			 float fovy, near, far, BASE_FOVY, BASE_NEAR, BASE_FAR, aspect, aspect1;
			 float left, right, top, bottom, Wcx, Wcy, Wx, Wy, Vcx, Vcy, Vx, Vy, alpha;
			 bool drawNames, prOrtho;
			 System::Windows::Forms::OpenFileDialog^  openFileDialog;
			 System::Windows::Forms::Button^  btnOpen;
			 #define PI 3.14159265  

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
			this->btnOpen->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnOpen->Location = System::Drawing::Point(698, 11);
			this->btnOpen->Margin = System::Windows::Forms::Padding(2);
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
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(784, 441);
			this->Controls->Add(this->btnOpen);
			this->KeyPreview = true;
			this->Margin = System::Windows::Forms::Padding(2);
			this->MinimumSize = System::Drawing::Size(304, 251);
			this->Name = L"Form1";
			this->ShowIcon = false;
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 left = 50;
				 right = 50;
				 top = 50;
				 bottom = 50;
				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;
				 unit3D(T);
				 polygons3D.Clear();
				 drawNames = false;
				 prOrtho = true;
				 aspect1 = Wx / Wy;
				 alpha = 5.0 * PI / 180.0;
			 }
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Bitmap^ image1 = gcnew Bitmap( this->ClientRectangle.Width , this->ClientRectangle.Height );
				 Graphics^ g = Graphics::FromImage(image1); 
				 System::Drawing::Pen^ drawPen = gcnew Pen(currentColor);
				 drawPen->Width = 1;

				 mat3D U, V, temp, R;
				 if (BASE_EYE.x != 0) {
					 unit3D(V);
					 unit3D(U);
					 unit3D(temp);
					 unit3D(R);
					 LookAt(eye, center, up, V);
					 if (prOrtho) {
						 float Vx, Vy;
						 Vy = std::tan( fovy / 2 ) * 2 * near;
						 Vx = aspect1 * Vy;
						 Ortho(Vx, Vy, near, far, U);
					 } else {
						 Perspective(fovy, aspect1, near, far, U);
					 }
					 times3D(U, V, temp);
					 times3D(temp, T, R);
				 }
				 mat F;
				 unit(F);
				 frame(2.0, 2.0, -1.0, -1.0, Wx, Wy, Wcx, Wcy, F);
				 g->DrawRectangle(drawPen, Wcx, top, Wx, Wy);
				 point min, max;
				 min.x = left;
				 min.y = top;
				 max.x = 	System::Windows::Forms::Form::ClientRectangle.Width - right;
				 max.y = System::Windows::Forms::Form::ClientRectangle.Height - bottom;
				 System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 8);
				 SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);
				 drawPen->Width = 2;
				 for (int i = 0; i < polygons3D.Count; i++) { 
					 polygon3D^ p = polygons3D[i];
					 polygon^ TempP = gcnew polygon(0);
					 drawPen->Color = colors[i];
					 point a, b;
					 for (int j = 0; j < p->Count; j++) {
						 vec3D A, B;
						 point2vec3D(p[j], A);
						 timesMatVec3D(R, A, B);
						 point3D B2;
						 vec2point3D(B, B2);
						 point B2_2D;
						 setTo2D(B2, B2_2D);
						 point B3;
						 vec vec_B3, vec_B2_2D;
						 point2vec(B2_2D, vec_B2_2D);
						 timesMatVec(F, vec_B2_2D, vec_B3);
						 vec2point(vec_B3, B3);
						 TempP->Add(B3);
					 }
					 TempP = Pclip(TempP, min, max);
					 if (TempP->Count != 0) {
						 a = TempP[TempP->Count - 1];
						 for (int j = 0; j < TempP->Count; j++) {
							 b = TempP[j];
							 g ->DrawLine(drawPen, a.x, a.y, b.x, b.y);
							 a = TempP[j];
						 }
					 }
				 }
				 g = e->Graphics;
				 g->DrawImage(image1,0,0);
				 delete image1;

			 }
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK){
					 unit3D(T);
					 currentColor = Color::Black;
					 wchar_t fileName[1024];
					 for (int i = 0; i < openFileDialog->FileName->Length; i++)
						 fileName[i] = openFileDialog->FileName[i];
					 fileName[openFileDialog->FileName->Length] = '\0'; 

					 std::ifstream in;
					 in.open(fileName);
					 if (in.is_open()) { 
						 lines.Clear(); 
						 std::string str;
						 getline (in, str);
						 while (in) { 
							 if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) { 
								 std::stringstream s(str);
								 std::string cmd;
								 bool ISFIRST_LOOKAT = true, ISFIRST_SCREEN = true;
								 s >> cmd;
								 if ( cmd == "triangle" ) {
									 polygon3D^ P = gcnew polygon3D(0);
									 for (int i = 0; i < 3; i++) {
										 point3D temp;
										 s >> temp.x >> temp.y >> temp.z;
										 P->Add(temp);
									 }
									 polygons3D.Add(P);
									 colors.Add(currentColor);
								 }
								 else if ( cmd == "color" ) {
									 int R, G, B;
									 s >> R >> G >> B;
									 currentColor = Color::FromArgb(R, G, B);
								 }
								 else if ( cmd == "lookat" ) {
									 float eyex, eyey, eyez;
									 s >> eyex >> eyey >> eyez;
									 eye = point3D(eyex, eyey, eyez);
									 float centerx, centery, centerz;
									 s >> centerx >> centery >> centerz;
									 center = point3D(centerx, centery, centerz);
									 float upx, upy, upz;
									 s >> upx >> upy >> upz;
									 up = point3D(upx, upy, upz);
									 if (ISFIRST_LOOKAT) {
										 BASE_EYE = eye;
										 BASE_CENTER = center;
										 BASE_UP = up;
										 ISFIRST_LOOKAT= false;
									 }
								 }
								 else if (cmd == "screen") {
									 int _fovy, _near, _far;
									 s >> _fovy >> _near >> _far;
									 fovy = _fovy * PI / 180.0;
									 near = _near;
									 far = _far;
									 if (ISFIRST_SCREEN) {
										 BASE_FOVY = fovy;
										 BASE_NEAR = near;
										 BASE_FAR = far;
										 ISFIRST_SCREEN = false;
									 }
								 }
							 }
							 getline (in, str);
						 }
					 }
					 LookAt(BASE_CENTER, BASE_EYE, BASE_UP, T);
					 vec3D vec_BASE_EYE, vec_BASE_EYE_2;
					 point3D temp_eye;
					 point2vec3D(BASE_EYE, vec_BASE_EYE);
					 timesMatVec3D(T, vec_BASE_EYE, vec_BASE_EYE_2);
					 vec2point3D(vec_BASE_EYE_2, temp_eye);
					 eye = temp_eye;
					 up = point3D(0, 1, 0);
					 center = point3D(0, 0, 0);
					 this->Refresh();
				 }
			 }
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 Rectangle rect = Form::ClientRectangle;
				 mat3D R, T1;
				 switch(e->KeyCode){
					 case Keys::W :rotate3D(point3D(1, 0, 0), alpha, R);break;
					 case Keys::S :rotate3D(point3D(1, 0, 0), -alpha, R);break;
					 case Keys::A :rotate3D(point3D(0, 1, 0), alpha, R);break;
					 case Keys::D :rotate3D(point3D(0, 1, 0), -alpha, R);break;
					 case Keys::E :rotate3D(point3D(0, 0, 1), alpha, R);break;
					 case Keys::Q :rotate3D(point3D(0, 0, 1), -alpha, R);break;	
					 case Keys::X :near += 2;unit3D(R);break;
					 case Keys::Z :near -= 2;unit3D(R);break;
					 case Keys::C :if (fovy < PI - PI / 180.0)fovy += PI / 180.0;unit3D(R);break;
					 case Keys::V :if (fovy > PI / 180.0)fovy -= PI / 180.0;unit3D(R);break;
					 case Keys::L :alpha *= 1.1;unit3D(R);break;
					 case Keys::O :alpha /= 1.1;unit3D(R);break;
					 case Keys::P :prOrtho = !prOrtho;unit3D(R);break;
					 case Keys::Escape :fovy = BASE_FOVY;near = BASE_NEAR;far = BASE_FAR;unit3D(R);unit3D(T);LookAt (BASE_CENTER, BASE_EYE, BASE_UP, T);break;
					 default :unit3D(R);
				 }
				 times3D(R,T,T1);
				 set3D(T1, T);
				 this->Refresh();
			 }

	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx, oldWy = Wy;
				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;
				 this->Refresh();
			 }
	};
}

