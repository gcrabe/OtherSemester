// Graphics_Task3.cpp: ������� ���� �������.

#include "stdafx.h"

#include <fstream>
#include <sstream>
#include <cstdio>

#include "Transform.h"
#include "Clip.h"
#include "Form1.h"

using namespace Graphics_Task3;

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