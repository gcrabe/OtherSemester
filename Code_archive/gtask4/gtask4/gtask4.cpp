// gtask4.cpp: ������� ���� �������.

#include "stdafx.h"
#include <sstream>
#include <fstream>
#include "Transform.h"
#include "Clip.h"
#include "Form1.h"

using namespace gtask4;

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
