#pragma once
 
// remove heavy includes from header so designer won't load DB/other form code
// #include "EnterGradesForm.h"   // moved to .cpp
// #include "GradesListForm.h"    // moved to .cpp

#include "DataManager.h"

namespace SISDEMO {

    // forward-declare other managed forms so header is lightweight for the designer
    ref class EnterGradesForm;
    ref class GradesListForm;
    ref class TakeAttendanceForm;

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class ProfForm : public System::Windows::Forms::Form
    {
    private:
        int profId;
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
        ProfForm(int id)
        {
            InitializeComponent();
            this->profId = SIS::DataManager::GetProfessorIdByUserId(id);
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
            
            // Get all students and courses for this professor (including those without grades)
            System::Collections::Generic::List<System::String^>^ students = SIS::DataManager::ReadStudentsByProfessor(this->profId);
            System::Collections::Generic::List<System::String^>^ courses = SIS::DataManager::ReadCoursesByProfessor(this->profId);

            pnlContent->Controls->Add(CreateStatCard("My Students", students->Count.ToString(), 0));
            pnlContent->Controls->Add(CreateStatCard("My Courses", courses->Count.ToString(), 1));
        }

    private:
        void ApplyModernTheme() {
            this->BackColor = bgColor;
            
            array<Button^>^ buttons = { btnEnterGrades, btnAttendance, btnViewGrades, btnClose };
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
        ~ProfForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Button^ btnEnterGrades;
    private: System::Windows::Forms::Button^ btnAttendance;
    private: System::Windows::Forms::Button^ btnViewGrades;
    private: System::Windows::Forms::Button^ btnClose;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->pnlSidebar = (gcnew System::Windows::Forms::Panel());
               this->pnlHeader = (gcnew System::Windows::Forms::Panel());
               this->pnlContent = (gcnew System::Windows::Forms::Panel());
               this->lblDashboard = (gcnew System::Windows::Forms::Label());
               this->lblWelcome = (gcnew System::Windows::Forms::Label());
               this->btnEnterGrades = (gcnew System::Windows::Forms::Button());
               this->btnAttendance = (gcnew System::Windows::Forms::Button());
               this->btnViewGrades = (gcnew System::Windows::Forms::Button());
               this->btnClose = (gcnew System::Windows::Forms::Button());
               this->pnlSidebar->SuspendLayout();
               this->pnlHeader->SuspendLayout();
               this->SuspendLayout();
               // 
               // pnlSidebar
               // 
               this->pnlSidebar->BackColor = this->sidebarColor;
               this->pnlSidebar->Controls->Add(this->btnClose);
               this->pnlSidebar->Controls->Add(this->btnViewGrades);
               this->pnlSidebar->Controls->Add(this->btnAttendance);
               this->pnlSidebar->Controls->Add(this->btnEnterGrades);
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
               this->lblDashboard->Text = L"Professor Dashboard";
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
               this->lblWelcome->Text = L"Welcome back, Professor";
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
               // btnEnterGrades
               // 
               this->btnEnterGrades->Location = System::Drawing::Point(0, 100);
               this->btnEnterGrades->Name = L"btnEnterGrades";
               this->btnEnterGrades->Size = System::Drawing::Size(250, 50);
               this->btnEnterGrades->TabIndex = 0;
               this->btnEnterGrades->Text = L"Enter Grades";
               this->btnEnterGrades->Click += gcnew System::EventHandler(this, &ProfForm::btnEnterGrades_Click);
               // 
               // btnAttendance
               // 
               this->btnAttendance->Location = System::Drawing::Point(0, 150);
               this->btnAttendance->Name = L"btnAttendance";
               this->btnAttendance->Size = System::Drawing::Size(250, 50);
               this->btnAttendance->TabIndex = 1;
               this->btnAttendance->Text = L"Attendance";
               this->btnAttendance->Click += gcnew System::EventHandler(this, &ProfForm::btnAttendance_Click);
               // 
               // btnViewGrades
               // 
               this->btnViewGrades->Location = System::Drawing::Point(0, 200);
               this->btnViewGrades->Name = L"btnViewGrades";
               this->btnViewGrades->Size = System::Drawing::Size(250, 50);
               this->btnViewGrades->TabIndex = 2;
               this->btnViewGrades->Text = L"View Grades";
               this->btnViewGrades->Click += gcnew System::EventHandler(this, &ProfForm::btnViewGrades_Click);
               // 
               // btnClose
               // 
               this->btnClose->Dock = System::Windows::Forms::DockStyle::Bottom;
               this->btnClose->Location = System::Drawing::Point(0, 650);
               this->btnClose->Name = L"btnClose";
               this->btnClose->Size = System::Drawing::Size(250, 50);
               this->btnClose->TabIndex = 3;
               this->btnClose->Text = L"Logout";
               this->btnClose->Click += gcnew System::EventHandler(this, &ProfForm::btnClose_Click);
               // 
               // ProfForm
               // 
               this->ClientSize = System::Drawing::Size(1000, 700);
               this->Controls->Add(this->pnlContent);
               this->Controls->Add(this->pnlHeader);
               this->Controls->Add(this->pnlSidebar);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
               this->MaximizeBox = false;
               this->Name = L"ProfForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Professor Portal";
               this->pnlSidebar->ResumeLayout(false);
               this->pnlHeader->ResumeLayout(false);
               this->pnlHeader->PerformLayout();
               this->ResumeLayout(false);
           }

           // keep signatures only in header � implementations moved to .cpp
    private: System::Void btnEnterGrades_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnAttendance_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnViewGrades_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
        if (MessageBox::Show("Are you sure you want to logout?", "Logout", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
            this->Close();
        }
    }
    };
}
