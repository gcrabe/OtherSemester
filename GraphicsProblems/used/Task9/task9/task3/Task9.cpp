// task3.cpp: ������� ���� �������.

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
	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// �������� �������� ���� � ��� ������
	Application::Run(gcnew Form1());
	return 0;
}
