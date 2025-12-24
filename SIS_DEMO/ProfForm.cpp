#include "ProfForm.h"
#include "EnterGradesForm.h"
#include "GradesListForm.h"
#include "TakeAttendanceForm.h"

using namespace SISDEMO;
using namespace System;
using namespace System::Windows::Forms;

System::Void ProfForm::btnEnterGrades_Click(System::Object^ sender, System::EventArgs^ e)
{
    try {
        EnterGradesForm^ f = gcnew EnterGradesForm(this->profId);
        f->ShowDialog();
    }
    catch (Exception^ ex) {
        MessageBox::Show(String::Format("Failed to open Enter Grades: {0}", ex->ToString()),
            "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void ProfForm::btnViewGrades_Click(System::Object^ sender, System::EventArgs^ e)
{
    try {
        GradesListForm^ f = gcnew GradesListForm(this->profId);
        f->ShowDialog();
    }
    catch (Exception^ ex) {
        MessageBox::Show(String::Format("Failed to open View Grades: {0}", ex->ToString()),
            "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void ProfForm::btnAttendance_Click(System::Object^ sender, System::EventArgs^ e)
{
    try {
        TakeAttendanceForm^ f = gcnew TakeAttendanceForm(this->profId);
        f->ShowDialog();
    }
    catch (Exception^ ex) {
        MessageBox::Show(String::Format("Failed to open Attendance: {0}", ex->ToString()),
            "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}


