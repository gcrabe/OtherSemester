#include "Transform.h"
#include "Function.h"
#include <ctime>
#include <fstream>
#include <sstream>
#include "MyForm.h"
#include <omp.h>

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
