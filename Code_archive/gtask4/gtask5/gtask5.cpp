// gtask5.cpp: ������� ���� �������.

#include "stdafx.h"
#include "Transform.h"
#include "Function.h"
#include <ctime>
#include <fstream>
#include <sstream>
#include "Form1.h"

using namespace gtask5;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// �������� �������� ���� � ��� ������
	Application::Run(gcnew Form1());
	return 0;
}
