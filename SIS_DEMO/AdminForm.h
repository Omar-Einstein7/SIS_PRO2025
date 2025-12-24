#pragma once

#include "RegisterStudentForm.h"
#include "PaymentForm.h"
#include "PaymentsListForm.h"
#include "StudentsListForm.h"
#include "RegisterCourseForm.h"
#include "AssignCourseForm.h"
#include "UserManagementForm.h"
#include "AcademicCalendarForm.h"
#include "FacultiesManagementForm.h"
#include "DepartmentsManagementForm.h"
#include "NewsManagementForm.h"
#include "DataManager.h"


namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class AdminForm : public System::Windows::Forms::Form
    {
    private:
        // Modern UI Colors
        Color sidebarColor = Color::FromArgb(45, 52, 54);
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        Color btnHoverColor = Color::FromArgb(55, 62, 64);
        System::Windows::Forms::Panel^ pnlSidebar;
        System::Windows::Forms::Panel^ pnlHeader;
        System::Windows::Forms::Panel^ pnlContent;
        System::Windows::Forms::Label^ lblDashboard;
        System::Windows::Forms::Label^ lblWelcome;

    public:
        AdminForm(void)
        {
            InitializeComponent();
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
            
            int students = SIS::DataManager::GetStudentCount();
            int courses = SIS::DataManager::GetCourseCount();
            int instructors = SIS::DataManager::GetInstructorCount();

            // Create 3 stat cards
            pnlContent->Controls->Add(CreateStatCard("Total Students", students.ToString(), 0));
            pnlContent->Controls->Add(CreateStatCard("Total Courses", courses.ToString(), 1));
            pnlContent->Controls->Add(CreateStatCard("Total Instructors", instructors.ToString(), 2));
        }

    private:
        void ApplyModernTheme() {
            this->BackColor = bgColor;
            
            array<Button^>^ buttons = { 
                btnRegisterStudent, btnPaymentMgmt, btnViewStudents, 
                btnRegisterCourse, btnAssignCourse, btnViewPayments, 
                btnUserManagement, btnFaculties, btnDepartments,
                btnAcademicCalendar, btnNews, btnClose 
            };

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
        ~AdminForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Button^ btnRegisterStudent;
    private: System::Windows::Forms::Button^ btnPaymentMgmt;
    private: System::Windows::Forms::Button^ btnViewStudents;

    private: System::Windows::Forms::Button^ btnRegisterCourse;
    private: System::Windows::Forms::Button^ btnAssignCourse;
    private: System::Windows::Forms::Button^ btnViewPayments;
    private: System::Windows::Forms::Button^ btnUserManagement;
    private: System::Windows::Forms::Button^ btnFaculties;
    private: System::Windows::Forms::Button^ btnDepartments;
    private: System::Windows::Forms::Button^ btnAcademicCalendar;
    private: System::Windows::Forms::Button^ btnNews;
    private: System::Windows::Forms::Button^ btnClose;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->pnlSidebar = (gcnew System::Windows::Forms::Panel());
               this->pnlHeader = (gcnew System::Windows::Forms::Panel());
               this->pnlContent = (gcnew System::Windows::Forms::Panel());
               this->lblDashboard = (gcnew System::Windows::Forms::Label());
               this->lblWelcome = (gcnew System::Windows::Forms::Label());
               this->btnRegisterStudent = (gcnew System::Windows::Forms::Button());
               this->btnPaymentMgmt = (gcnew System::Windows::Forms::Button());
               this->btnViewStudents = (gcnew System::Windows::Forms::Button());
               this->btnViewPayments = (gcnew System::Windows::Forms::Button());
               this->btnRegisterCourse = (gcnew System::Windows::Forms::Button());
               this->btnAssignCourse = (gcnew System::Windows::Forms::Button());
               this->btnUserManagement = (gcnew System::Windows::Forms::Button());
               this->btnFaculties = (gcnew System::Windows::Forms::Button());
               this->btnDepartments = (gcnew System::Windows::Forms::Button());
               this->btnAcademicCalendar = (gcnew System::Windows::Forms::Button());
               this->btnNews = (gcnew System::Windows::Forms::Button());
               this->btnClose = (gcnew System::Windows::Forms::Button());
               this->pnlSidebar->SuspendLayout();
               this->pnlHeader->SuspendLayout();
               this->SuspendLayout();
               // 
               // pnlSidebar
               // 
               this->pnlSidebar->BackColor = this->sidebarColor;
               this->pnlSidebar->Controls->Add(this->btnClose);
               this->pnlSidebar->Controls->Add(this->btnNews);
               this->pnlSidebar->Controls->Add(this->btnAcademicCalendar);
               this->pnlSidebar->Controls->Add(this->btnDepartments);
               this->pnlSidebar->Controls->Add(this->btnFaculties);
               this->pnlSidebar->Controls->Add(this->btnUserManagement);
               this->pnlSidebar->Controls->Add(this->btnViewPayments);
               this->pnlSidebar->Controls->Add(this->btnAssignCourse);
               this->pnlSidebar->Controls->Add(this->btnRegisterCourse);
               this->pnlSidebar->Controls->Add(this->btnViewStudents);
               this->pnlSidebar->Controls->Add(this->btnPaymentMgmt);
               this->pnlSidebar->Controls->Add(this->btnRegisterStudent);
               this->pnlSidebar->Dock = System::Windows::Forms::DockStyle::Left;
               this->pnlSidebar->Location = System::Drawing::Point(0, 0);
               this->pnlSidebar->Name = L"pnlSidebar";
               this->pnlSidebar->Size = System::Drawing::Size(250, 700);
               this->pnlSidebar->TabIndex = 0;
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
               this->lblDashboard->Text = L"Admin Dashboard";
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
               this->lblWelcome->Text = L"Welcome back, Admin";
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
               // btnRegisterStudent
               // 
               this->btnRegisterStudent->Location = System::Drawing::Point(0, 100);
               this->btnRegisterStudent->Name = L"btnRegisterStudent";
               this->btnRegisterStudent->Size = System::Drawing::Size(250, 50);
               this->btnRegisterStudent->TabIndex = 0;
               this->btnRegisterStudent->Text = L"Register Student";
               this->btnRegisterStudent->Click += gcnew System::EventHandler(this, &AdminForm::btnRegisterStudent_Click);
               // 
               // btnPaymentMgmt
               // 
               this->btnPaymentMgmt->Location = System::Drawing::Point(0, 150);
               this->btnPaymentMgmt->Name = L"btnPaymentMgmt";
               this->btnPaymentMgmt->Size = System::Drawing::Size(250, 50);
               this->btnPaymentMgmt->TabIndex = 1;
               this->btnPaymentMgmt->Text = L"Payment Management";
               this->btnPaymentMgmt->Click += gcnew System::EventHandler(this, &AdminForm::btnPaymentMgmt_Click);
               // 
               // btnViewStudents
               // 
               this->btnViewStudents->Location = System::Drawing::Point(0, 200);
               this->btnViewStudents->Name = L"btnViewStudents";
               this->btnViewStudents->Size = System::Drawing::Size(250, 50);
               this->btnViewStudents->TabIndex = 2;
               this->btnViewStudents->Text = L"View Students";
               this->btnViewStudents->Click += gcnew System::EventHandler(this, &AdminForm::btnViewStudents_Click);
               // 
               // btnRegisterCourse
               // 
               this->btnRegisterCourse->Location = System::Drawing::Point(0, 250);
               this->btnRegisterCourse->Name = L"btnRegisterCourse";
               this->btnRegisterCourse->Size = System::Drawing::Size(250, 50);
               this->btnRegisterCourse->TabIndex = 3;
               this->btnRegisterCourse->Text = L"Register Course";
               this->btnRegisterCourse->Click += gcnew System::EventHandler(this, &AdminForm::btnRegisterCourse_Click);
               // 
               // btnAssignCourse
               // 
               this->btnAssignCourse->Location = System::Drawing::Point(0, 300);
               this->btnAssignCourse->Name = L"btnAssignCourse";
               this->btnAssignCourse->Size = System::Drawing::Size(250, 50);
               this->btnAssignCourse->TabIndex = 4;
               this->btnAssignCourse->Text = L"Assign to Course";
               this->btnAssignCourse->Click += gcnew System::EventHandler(this, &AdminForm::btnAssignCourse_Click);
               // 
               // btnViewPayments
               // 
               this->btnViewPayments->Location = System::Drawing::Point(0, 350);
               this->btnViewPayments->Name = L"btnViewPayments";
               this->btnViewPayments->Size = System::Drawing::Size(250, 50);
               this->btnViewPayments->TabIndex = 5;
               this->btnViewPayments->Text = L"View Payments";
               this->btnViewPayments->Click += gcnew System::EventHandler(this, &AdminForm::btnViewPayments_Click);
               // 
               // btnUserManagement
               // 
               this->btnUserManagement->Location = System::Drawing::Point(0, 400);
               this->btnUserManagement->Name = L"btnUserManagement";
               this->btnUserManagement->Size = System::Drawing::Size(250, 50);
               this->btnUserManagement->TabIndex = 6;
               this->btnUserManagement->Text = L"User Management";
               this->btnUserManagement->Click += gcnew System::EventHandler(this, &AdminForm::btnUserManagement_Click);
               // 
               // btnFaculties
               // 
               this->btnFaculties->Location = System::Drawing::Point(0, 450);
               this->btnFaculties->Name = L"btnFaculties";
               this->btnFaculties->Size = System::Drawing::Size(250, 50);
               this->btnFaculties->TabIndex = 8;
               this->btnFaculties->Text = L"Faculties";
               this->btnFaculties->Click += gcnew System::EventHandler(this, &AdminForm::btnFaculties_Click);
               // 
               // btnDepartments
               // 
               this->btnDepartments->Location = System::Drawing::Point(0, 500);
               this->btnDepartments->Name = L"btnDepartments";
               this->btnDepartments->Size = System::Drawing::Size(250, 50);
               this->btnDepartments->TabIndex = 9;
               this->btnDepartments->Text = L"Departments";
               this->btnDepartments->Click += gcnew System::EventHandler(this, &AdminForm::btnDepartments_Click);
               // 
               // btnAcademicCalendar
               // 
               this->btnAcademicCalendar->Location = System::Drawing::Point(0, 550);
               this->btnAcademicCalendar->Name = L"btnAcademicCalendar";
               this->btnAcademicCalendar->Size = System::Drawing::Size(250, 50);
               this->btnAcademicCalendar->TabIndex = 10;
               this->btnAcademicCalendar->Text = L"Academic Calendar";
               this->btnAcademicCalendar->Click += gcnew System::EventHandler(this, &AdminForm::btnAcademicCalendar_Click);
               // 
               // btnNews
               // 
               this->btnNews->Location = System::Drawing::Point(0, 600);
               this->btnNews->Name = L"btnNews";
               this->btnNews->Size = System::Drawing::Size(250, 50);
               this->btnNews->TabIndex = 11;
               this->btnNews->Text = L"News Management";
               this->btnNews->Click += gcnew System::EventHandler(this, &AdminForm::btnNews_Click);
               // 
               // btnClose
               // 
               this->btnClose->Dock = System::Windows::Forms::DockStyle::Bottom;
               this->btnClose->Location = System::Drawing::Point(0, 700);
               this->btnClose->Name = L"btnClose";
               this->btnClose->Size = System::Drawing::Size(250, 50);
               this->btnClose->TabIndex = 7;
               this->btnClose->Text = L"Logout";
               this->btnClose->Click += gcnew System::EventHandler(this, &AdminForm::btnClose_Click);
               // 
               // AdminForm
               // 
               this->ClientSize = System::Drawing::Size(1000, 700);
               this->Controls->Add(this->pnlContent);
               this->Controls->Add(this->pnlHeader);
               this->Controls->Add(this->pnlSidebar);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
               this->MaximizeBox = false;
               this->Name = L"AdminForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Admin Portal";
               this->pnlSidebar->ResumeLayout(false);
               this->pnlHeader->ResumeLayout(false);
               this->pnlHeader->PerformLayout();
               this->ResumeLayout(false);

           }

    private: System::Void btnRegisterStudent_Click(System::Object^ sender, System::EventArgs^ e) {
        RegisterStudentForm^ f = gcnew RegisterStudentForm();
        f->ShowDialog();
    }

    private: System::Void btnPaymentMgmt_Click(System::Object^ sender, System::EventArgs^ e) {
        PaymentForm^ f = gcnew PaymentForm();
        f->ShowDialog();
    }

    private: System::Void btnViewStudents_Click(System::Object^ sender, System::EventArgs^ e) {
        StudentsListForm^ f = gcnew StudentsListForm();
        f->ShowDialog();
    }

    private: System::Void btnViewPayments_Click(System::Object^ sender, System::EventArgs^ e) {
        PaymentsListForm^ f = gcnew PaymentsListForm();
        f->ShowDialog();
    }

    private: System::Void btnRegisterCourse_Click(System::Object^ sender, System::EventArgs^ e) {
        RegisterCourseForm^ f = gcnew RegisterCourseForm();
        f->ShowDialog();
    }

    private: System::Void btnAssignCourse_Click(System::Object^ sender, System::EventArgs^ e) {
        AssignCourseForm^ f = gcnew AssignCourseForm();
        f->ShowDialog();
    }

    private: System::Void btnUserManagement_Click(System::Object^ sender, System::EventArgs^ e) {
        UserManagementForm^ f = gcnew UserManagementForm();
        f->ShowDialog();
    }

    private: System::Void btnFaculties_Click(System::Object^ sender, System::EventArgs^ e) {
        FacultiesManagementForm^ f = gcnew FacultiesManagementForm();
        f->ShowDialog();
    }

    private: System::Void btnDepartments_Click(System::Object^ sender, System::EventArgs^ e) {
        DepartmentsManagementForm^ f = gcnew DepartmentsManagementForm();
        f->ShowDialog();
    }

    private: System::Void btnAcademicCalendar_Click(System::Object^ sender, System::EventArgs^ e) {
        AcademicCalendarForm^ f = gcnew AcademicCalendarForm();
        f->ShowDialog();
    }

    private: System::Void btnNews_Click(System::Object^ sender, System::EventArgs^ e) {
        NewsManagementForm^ f = gcnew NewsManagementForm();
        f->ShowDialog();
    }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
        if (MessageBox::Show("Are you sure you want to logout?", "Logout", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
            this->Close();
        }
    }
    };
}
