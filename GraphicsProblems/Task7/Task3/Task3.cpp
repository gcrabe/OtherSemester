// Task3.cpp: ������� ���� �������.

#include "stdafx.h"

#include <array>
#include <fstream>
#include <sstream>	
#include <stack>

#include "Transform.h"
#include "Form1.h"

using namespace Task3;

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
