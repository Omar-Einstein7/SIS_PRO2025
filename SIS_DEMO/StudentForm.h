#pragma once

#include "StudentGradesViewForm.h"
#include "StudentPaymentsViewForm.h"
#include "StudentRegisteredCoursesForm.h"
#include "StudentProfileForm.h"
#include "ScheduleForm.h"
#include "AttendanceForm.h"
#include "AcademicCalendarForm.h"
#include "DataManager.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class StudentForm : public System::Windows::Forms::Form
    {
    private:
        int studentId;
        // Modern UI Colors
        Color sidebarColor = Color::FromArgb(45, 52, 54);
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        System::Windows::Forms::Panel^ pnlSidebar;
        System::Windows::Forms::Panel^ pnlHeader;
        System::Windows::Forms::Panel^ pnlContent;
        System::Windows::Forms::Label^ lblDashboard;
        System::Windows::Forms::Label^ lblWelcome;

    public:
        StudentForm(int id)
        {
            InitializeComponent();
            this->studentId = SIS::DataManager::GetStudentIdByUserId(id);
            ApplyModernTheme();
            LoadDashboard();
        }

    private:
        System::Windows::Forms::Panel^ CreateStatCard(System::String^ title, System::String^ value, int index) {
            System::Windows::Forms::Panel^ card = gcnew System::Windows::Forms::Panel();
            card->Size = System::Drawing::Size(200, 120);
            card->Location = System::Drawing::Point(30 + (index * 230), 30);
            card->BackColor = System::Drawing::Color::White;
            card->BorderStyle = System::Windows::Forms::BorderStyle::None;

            System::Windows::Forms::Label^ lblVal = gcnew System::Windows::Forms::Label();
            lblVal->Text = value;
            lblVal->Font = gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold);
            lblVal->ForeColor = accentColor;
            lblVal->AutoSize = true;
            lblVal->Location = System::Drawing::Point(20, 20);

            System::Windows::Forms::Label^ lblTit = gcnew System::Windows::Forms::Label();
            lblTit->Text = title;
            lblTit->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
            lblTit->ForeColor = System::Drawing::Color::Gray;
            lblTit->AutoSize = true;
            lblTit->Location = System::Drawing::Point(20, 70);

            card->Controls->Add(lblVal);
            card->Controls->Add(lblTit);
            return card;
        }

        void LoadDashboard() {
            pnlContent->Controls->Clear();
            
            System::Collections::Generic::List<System::String^>^ regs = SIS::DataManager::ReadRegistrationsForStudent(this->studentId);
            
            pnlContent->Controls->Add(CreateStatCard("My Courses", regs->Count.ToString(), 0));
            pnlContent->Controls->Add(CreateStatCard("Academic Status", "Active", 1));
        }

    private:
        void ApplyModernTheme() {
            this->BackColor = bgColor;
            
            array<Button^>^ buttons = { btnProfile, btnCourses, btnGrades, btnPayments, btnSchedule, btnAttendance, btnCalendar, btnClose };
            for each (Button^ btn in buttons) {
                btn->FlatStyle = FlatStyle::Flat;
                btn->BackColor = sidebarColor;
                btn->ForeColor = Color::White;
                btn->FlatAppearance->BorderSize = 0;
                btn->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
                btn->Cursor = Cursors::Hand;
                btn->TextAlign = ContentAlignment::MiddleLeft;
                btn->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
            }

            btnClose->BackColor = Color::FromArgb(214, 48, 49);
            btnClose->TextAlign = ContentAlignment::MiddleCenter;
            btnClose->Padding = System::Windows::Forms::Padding(0);
        }

    protected:
        ~StudentForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Button^ btnProfile;
    private: System::Windows::Forms::Button^ btnCourses;
    private: System::Windows::Forms::Button^ btnGrades;
    private: System::Windows::Forms::Button^ btnPayments;
    private: System::Windows::Forms::Button^ btnSchedule;
    private: System::Windows::Forms::Button^ btnAttendance;
    private: System::Windows::Forms::Button^ btnCalendar;
    private: System::Windows::Forms::Button^ btnClose;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->pnlSidebar = (gcnew System::Windows::Forms::Panel());
               this->pnlHeader = (gcnew System::Windows::Forms::Panel());
               this->pnlContent = (gcnew System::Windows::Forms::Panel());
               this->lblDashboard = (gcnew System::Windows::Forms::Label());
               this->lblWelcome = (gcnew System::Windows::Forms::Label());
               this->btnProfile = (gcnew System::Windows::Forms::Button());
               this->btnCourses = (gcnew System::Windows::Forms::Button());
               this->btnGrades = (gcnew System::Windows::Forms::Button());
               this->btnPayments = (gcnew System::Windows::Forms::Button());
               this->btnSchedule = (gcnew System::Windows::Forms::Button());
               this->btnAttendance = (gcnew System::Windows::Forms::Button());
               this->btnCalendar = (gcnew System::Windows::Forms::Button());
               this->btnClose = (gcnew System::Windows::Forms::Button());
               this->pnlSidebar->SuspendLayout();
               this->pnlHeader->SuspendLayout();
               this->SuspendLayout();
               // 
               // pnlSidebar
               // 
               this->pnlSidebar->BackColor = this->sidebarColor;
               this->pnlSidebar->Controls->Add(this->btnClose);
               this->pnlSidebar->Controls->Add(this->btnCalendar);
               this->pnlSidebar->Controls->Add(this->btnAttendance);
               this->pnlSidebar->Controls->Add(this->btnSchedule);
               this->pnlSidebar->Controls->Add(this->btnPayments);
               this->pnlSidebar->Controls->Add(this->btnGrades);
               this->pnlSidebar->Controls->Add(this->btnCourses);
               this->pnlSidebar->Controls->Add(this->btnProfile);
               this->pnlSidebar->Dock = System::Windows::Forms::DockStyle::Left;
               this->pnlSidebar->Location = System::Drawing::Point(0, 0);
               this->pnlSidebar->Name = L"pnlSidebar";
               this->pnlSidebar->Size = System::Drawing::Size(250, 700);
               this->pnlSidebar->TabIndex = 0;
               // 
               // btnSchedule
               // 
               this->btnSchedule->Location = System::Drawing::Point(0, 300);
               this->btnSchedule->Name = L"btnSchedule";
               this->btnSchedule->Size = System::Drawing::Size(250, 50);
               this->btnSchedule->TabIndex = 5;
               this->btnSchedule->Text = L"My Schedule";
               this->btnSchedule->Click += gcnew System::EventHandler(this, &StudentForm::btnSchedule_Click);
               // 
               // btnAttendance
               // 
               this->btnAttendance->Location = System::Drawing::Point(0, 350);
               this->btnAttendance->Name = L"btnAttendance";
               this->btnAttendance->Size = System::Drawing::Size(250, 50);
               this->btnAttendance->TabIndex = 6;
               this->btnAttendance->Text = L"My Attendance";
               this->btnAttendance->Click += gcnew System::EventHandler(this, &StudentForm::btnAttendance_Click);
               // 
               // btnCalendar
               // 
               this->btnCalendar->Location = System::Drawing::Point(0, 400);
               this->btnCalendar->Name = L"btnCalendar";
               this->btnCalendar->Size = System::Drawing::Size(250, 50);
               this->btnCalendar->TabIndex = 7;
               this->btnCalendar->Text = L"Academic Calendar";
               this->btnCalendar->Click += gcnew System::EventHandler(this, &StudentForm::btnCalendar_Click);
               // 
               // pnlHeader
               // 
               this->pnlHeader->BackColor = System::Drawing::Color::White;
               this->pnlHeader->Controls->Add(this->lblWelcome);
               this->pnlHeader->Controls->Add(this->lblDashboard);
               this->pnlHeader->Dock = System::Windows::Forms::DockStyle::Top;
               this->pnlHeader->Location = System::Drawing::Point(250, 0);
               this->pnlHeader->Name = L"pnlHeader";
               this->pnlHeader->Size = System::Drawing::Size(750, 80);
               this->pnlHeader->TabIndex = 1;
               // 
               // lblDashboard
               // 
               this->lblDashboard->AutoSize = true;
               this->lblDashboard->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 18, System::Drawing::FontStyle::Bold));
               this->lblDashboard->ForeColor = this->sidebarColor;
               this->lblDashboard->Location = System::Drawing::Point(20, 23);
               this->lblDashboard->Name = L"lblDashboard";
               this->lblDashboard->Size = System::Drawing::Size(210, 32);
               this->lblDashboard->TabIndex = 0;
               this->lblDashboard->Text = L"Student Dashboard";
               // 
               // lblWelcome
               // 
               this->lblWelcome->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
               this->lblWelcome->AutoSize = true;
               this->lblWelcome->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
               this->lblWelcome->ForeColor = System::Drawing::Color::Gray;
               this->lblWelcome->Location = System::Drawing::Point(580, 32);
               this->lblWelcome->Name = L"lblWelcome";
               this->lblWelcome->Size = System::Drawing::Size(150, 19);
               this->lblWelcome->TabIndex = 1;
               this->lblWelcome->Text = L"Welcome back, Student";
               // 
               // pnlContent
               // 
               this->pnlContent->Dock = System::Windows::Forms::DockStyle::Fill;
               this->pnlContent->Location = System::Drawing::Point(250, 80);
               this->pnlContent->Name = L"pnlContent";
               this->pnlContent->Padding = System::Windows::Forms::Padding(30);
               this->pnlContent->Size = System::Drawing::Size(750, 620);
               this->pnlContent->TabIndex = 2;
               // 
               // btnProfile
               // 
               this->btnProfile->Location = System::Drawing::Point(0, 100);
               this->btnProfile->Name = L"btnProfile";
               this->btnProfile->Size = System::Drawing::Size(250, 50);
               this->btnProfile->TabIndex = 0;
               this->btnProfile->Text = L"View Profile";
               this->btnProfile->Click += gcnew System::EventHandler(this, &StudentForm::btnProfile_Click);
               // 
               // btnCourses
               // 
               this->btnCourses->Location = System::Drawing::Point(0, 150);
               this->btnCourses->Name = L"btnCourses";
               this->btnCourses->Size = System::Drawing::Size(250, 50);
               this->btnCourses->TabIndex = 1;
               this->btnCourses->Text = L"Registered Courses";
               this->btnCourses->Click += gcnew System::EventHandler(this, &StudentForm::btnCourses_Click);
               // 
               // btnGrades
               // 
               this->btnGrades->Location = System::Drawing::Point(0, 200);
               this->btnGrades->Name = L"btnGrades";
               this->btnGrades->Size = System::Drawing::Size(250, 50);
               this->btnGrades->TabIndex = 2;
               this->btnGrades->Text = L"View Grades & GPA";
               this->btnGrades->Click += gcnew System::EventHandler(this, &StudentForm::btnGrades_Click);
               // 
               // btnPayments
               // 
               this->btnPayments->Location = System::Drawing::Point(0, 250);
               this->btnPayments->Name = L"btnPayments";
               this->btnPayments->Size = System::Drawing::Size(250, 50);
               this->btnPayments->TabIndex = 3;
               this->btnPayments->Text = L"View Payment Status";
               this->btnPayments->Click += gcnew System::EventHandler(this, &StudentForm::btnPayments_Click);
               // 
               // btnClose
               // 
               this->btnClose->Dock = System::Windows::Forms::DockStyle::Bottom;
               this->btnClose->Location = System::Drawing::Point(0, 650);
               this->btnClose->Name = L"btnClose";
               this->btnClose->Size = System::Drawing::Size(250, 50);
               this->btnClose->TabIndex = 4;
               this->btnClose->Text = L"Logout";
               this->btnClose->Click += gcnew System::EventHandler(this, &StudentForm::btnClose_Click);
               // 
               // StudentForm
               // 
               this->ClientSize = System::Drawing::Size(1000, 700);
               this->Controls->Add(this->pnlContent);
               this->Controls->Add(this->pnlHeader);
               this->Controls->Add(this->pnlSidebar);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
               this->MaximizeBox = false;
               this->Name = L"StudentForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Student Portal";
               this->pnlSidebar->ResumeLayout(false);
               this->pnlHeader->ResumeLayout(false);
               this->pnlHeader->PerformLayout();
               this->ResumeLayout(false);
           }

    private: System::Void btnProfile_Click(System::Object^ sender, System::EventArgs^ e) {
        StudentProfileForm^ f = gcnew StudentProfileForm(this->studentId);
        f->ShowDialog();
    }

    private: System::Void btnCourses_Click(System::Object^ sender, System::EventArgs^ e) {
        StudentRegisteredCoursesForm^ f = gcnew StudentRegisteredCoursesForm(this->studentId);
        f->ShowDialog();
    }

    private: System::Void btnGrades_Click(System::Object^ sender, System::EventArgs^ e) {
        StudentGradesViewForm^ f = gcnew StudentGradesViewForm(this->studentId);
        f->ShowDialog();
    }

    private: System::Void btnPayments_Click(System::Object^ sender, System::EventArgs^ e) {
        StudentPaymentsViewForm^ f = gcnew StudentPaymentsViewForm(this->studentId);
        f->ShowDialog();
    }

    private: System::Void btnSchedule_Click(System::Object^ sender, System::EventArgs^ e) {
        ScheduleForm^ f = gcnew ScheduleForm(this->studentId);
        f->ShowDialog();
    }

    private: System::Void btnAttendance_Click(System::Object^ sender, System::EventArgs^ e) {
        AttendanceForm^ f = gcnew AttendanceForm(this->studentId);
        f->ShowDialog();
    }

    private: System::Void btnCalendar_Click(System::Object^ sender, System::EventArgs^ e) {
        AcademicCalendarForm^ f = gcnew AcademicCalendarForm();
        f->ShowDialog();
    }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
        if (MessageBox::Show("Are you sure you want to logout?", "Logout", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
            this->Close();
        }
    }
    };
}
