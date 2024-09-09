#include "MyForm.h" // ?ây là tên file header c?a form chính

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // T?o m?t th? hi?n c?a form chính và hi?n th? nó
    Project1test::MyForm form;
    Application::Run(% form);

    return 0;
}
