//#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include<vector>
#include "Transform.h"
#include <ctime>
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Task3::MyForm form;
	Application::Run(%form);
}
