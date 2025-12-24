#pragma once

#include "DataManager.h"
#include "ScheduleForm.h"
#include "AcademicCalendarForm.h"
#include "AttendanceForm.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class StudentProfileForm : public System::Windows::Forms::Form
    {
    private:
        int studentId;
        Color primaryColor = Color::FromArgb(45, 52, 54);
        Color accentColor = Color::FromArgb(9, 132, 227);
        
        System::Windows::Forms::Label^ lblName;
        System::Windows::Forms::Label^ lblEmail;
        System::Windows::Forms::Label^ lblPhone;
        System::Windows::Forms::Label^ lblFaculty;
        System::Windows::Forms::Label^ lblDept;
        System::Windows::Forms::Label^ lblLevel;
        
        System::Windows::Forms::Button^ btnSchedule;
        System::Windows::Forms::Button^ btnCalendar;
        System::Windows::Forms::Button^ btnAttendance;

    public:
        StudentProfileForm(int sid)
        {
            this->studentId = sid;
            InitializeComponent();
            LoadStudentData();
        }

    protected:
        ~StudentProfileForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->lblName = (gcnew System::Windows::Forms::Label());
            this->lblEmail = (gcnew System::Windows::Forms::Label());
            this->lblPhone = (gcnew System::Windows::Forms::Label());
            this->lblFaculty = (gcnew System::Windows::Forms::Label());
            this->lblDept = (gcnew System::Windows::Forms::Label());
            this->lblLevel = (gcnew System::Windows::Forms::Label());
            
            this->btnSchedule = (gcnew System::Windows::Forms::Button());
            this->btnCalendar = (gcnew System::Windows::Forms::Button());
            this->btnAttendance = (gcnew System::Windows::Forms::Button());
            
            this->SuspendLayout();

            // Labels
            int startY = 30;
            array<Label^>^ labels = { lblName, lblEmail, lblPhone, lblFaculty, lblDept, lblLevel };
            for each (Label^ lbl in labels) {
                lbl->AutoSize = true;
                lbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 12);
                lbl->ForeColor = primaryColor;
                lbl->Location = System::Drawing::Point(30, startY);
                startY += 40;
                this->Controls->Add(lbl);
            }

            // Buttons
            this->btnSchedule->Text = L"View My Schedule";
            this->btnSchedule->Location = System::Drawing::Point(30, 300);
            this->btnSchedule->Size = System::Drawing::Size(200, 45);
            this->btnSchedule->Click += gcnew System::EventHandler(this, &StudentProfileForm::btnSchedule_Click);

            this->btnCalendar->Text = L"Academic Calendar";
            this->btnCalendar->Location = System::Drawing::Point(250, 300);
            this->btnCalendar->Size = System::Drawing::Size(200, 45);
            this->btnCalendar->Click += gcnew System::EventHandler(this, &StudentProfileForm::btnCalendar_Click);

            this->btnAttendance->Text = L"Attendance History";
            this->btnAttendance->Location = System::Drawing::Point(470, 300);
            this->btnAttendance->Size = System::Drawing::Size(200, 45);
            this->btnAttendance->Click += gcnew System::EventHandler(this, &StudentProfileForm::btnAttendance_Click);

            array<Button^>^ buttons = { btnSchedule, btnCalendar, btnAttendance };
            for each (Button^ btn in buttons) {
                btn->FlatStyle = FlatStyle::Flat;
                btn->BackColor = accentColor;
                btn->ForeColor = Color::White;
                btn->FlatAppearance->BorderSize = 0;
                btn->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
                btn->Cursor = Cursors::Hand;
                this->Controls->Add(btn);
            }

            // StudentProfileForm
            this->BackColor = Color::White;
            this->ClientSize = System::Drawing::Size(700, 400);
            this->Name = L"StudentProfileForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"Student Profile";
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void LoadStudentData() {
            String^ data = SIS::DataManager::GetStudentDetails(this->studentId);
            if (data != nullptr) {
                array<String^>^ p = data->Split('|');
                if (p->Length >= 7) {
                    lblName->Text = "Name: " + p[0];
                    lblEmail->Text = "Email: " + p[1];
                    lblPhone->Text = "Phone: " + p[2];
                    lblFaculty->Text = "Faculty: " + p[4];
                    lblDept->Text = "Department: " + p[5];
                    lblLevel->Text = "Academic Level: " + p[6];
                }
            }
        }

        private: System::Void btnSchedule_Click(System::Object^ sender, System::EventArgs^ e) {
            ScheduleForm^ f = gcnew ScheduleForm(this->studentId);
            f->ShowDialog();
        }

        private: System::Void btnCalendar_Click(System::Object^ sender, System::EventArgs^ e) {
            AcademicCalendarForm^ f = gcnew AcademicCalendarForm();
            f->ShowDialog();
        }

        private: System::Void btnAttendance_Click(System::Object^ sender, System::EventArgs^ e) {
            AttendanceForm^ f = gcnew AttendanceForm(this->studentId);
            f->ShowDialog();
        }
    };
}
