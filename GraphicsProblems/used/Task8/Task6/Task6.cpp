// Task6.cpp: ������� ���� �������.

#include "stdafx.h"
#include <array>
#include <stack>
#include <fstream>
#include <sstream>
#include <vector>
#include "Transform.h"
#include "Form1.h"

using namespace Task6;

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
