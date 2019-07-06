// task3.cpp: главный файл проекта.

#include "stdafx.h"
#include <fstream>
#include <cmath>
#include <sstream>
#include "Transform.h"
#include "PClip.h"
#include "MyForm.h"

using namespace task3;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Включение визуальных эффектов Windows XP до создания каких-либо элементов управления
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Создание главного окна и его запуск
	Application::Run(gcnew Form1());
	return 0;
}
