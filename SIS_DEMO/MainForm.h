#pragma once


#include "AdminForm.h"
#include "StudentForm.h"
#include "ProfForm.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    private:
        Color primaryColor = Color::FromArgb(45, 52, 54);
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        System::Windows::Forms::Panel^ pnlCard;
        System::Windows::Forms::Label^ lblWelcome;
        System::Windows::Forms::Label^ lblSubtitle;

    public:
        MainForm(void)
        {
            InitializeComponent();
            ApplyModernTheme();

            // TODO: replace placeholders below with your actual DB credentials
            SIS::DataManager::Configure(
                gcnew System::String("localhost"),
                gcnew System::String("root"),
                gcnew System::String("root"),
                gcnew System::String("sis_db"),
                3306
            );

            if (!SIS::DataManager::TestConnection()) {
                MessageBox::Show("Failed to connect to MySQL using the configured credentials.\nPlease check host/user/password/database and network access.",
                                 "Database Connection Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            else {
                // Connection successful, run schema fixes if needed
                //SIS::DataManager::CreateNewSchema();
            }
        }

    private:
        void ApplyModernTheme() {
            this->BackColor = bgColor;
            
            lblWelcome->Font = gcnew System::Drawing::Font(L"Segoe UI", 24, FontStyle::Bold);
            lblWelcome->ForeColor = primaryColor;
            
            lblSubtitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
            lblSubtitle->ForeColor = Color::FromArgb(99, 110, 114);

            array<Button^>^ buttons = { btnAdmin, btnProfessor, btnStudent };
            for each (Button^ btn in buttons) {
                btn->FlatStyle = FlatStyle::Flat;
                btn->BackColor = primaryColor;
                btn->ForeColor = Color::White;
                btn->FlatAppearance->BorderSize = 0;
                btn->Font = gcnew System::Drawing::Font(L"Segoe UI", 11, FontStyle::Bold);
                btn->Cursor = Cursors::Hand;
                btn->Size = System::Drawing::Size(250, 50);
            }

            btnExit->FlatStyle = FlatStyle::Flat;
            btnExit->BackColor = Color::Transparent;
            btnExit->ForeColor = Color::FromArgb(214, 48, 49);
            btnExit->FlatAppearance->BorderSize = 1;
            btnExit->FlatAppearance->BorderColor = Color::FromArgb(214, 48, 49);
            btnExit->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            btnExit->Size = System::Drawing::Size(100, 35);
        }

    protected:
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Button^ btnAdmin;
    private: System::Windows::Forms::Button^ btnProfessor;
    private: System::Windows::Forms::Button^ btnStudent;
    private: System::Windows::Forms::Button^ btnExit;

    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->btnAdmin = (gcnew System::Windows::Forms::Button());
               this->btnProfessor = (gcnew System::Windows::Forms::Button());
               this->btnStudent = (gcnew System::Windows::Forms::Button());
               this->btnExit = (gcnew System::Windows::Forms::Button());
               this->pnlCard = (gcnew System::Windows::Forms::Panel());
               this->lblWelcome = (gcnew System::Windows::Forms::Label());
               this->lblSubtitle = (gcnew System::Windows::Forms::Label());
               this->pnlCard->SuspendLayout();
               this->SuspendLayout();

               // pnlCard
               this->pnlCard->BackColor = System::Drawing::Color::White;
               this->pnlCard->Controls->Add(this->lblWelcome);
               this->pnlCard->Controls->Add(this->lblSubtitle);
               this->pnlCard->Controls->Add(this->btnAdmin);
               this->pnlCard->Controls->Add(this->btnProfessor);
               this->pnlCard->Controls->Add(this->btnStudent);
               this->pnlCard->Location = System::Drawing::Point(50, 50);
               this->pnlCard->Name = L"pnlCard";
               this->pnlCard->Size = System::Drawing::Size(400, 450);
               this->pnlCard->TabIndex = 0;

               // lblWelcome
               this->lblWelcome->AutoSize = true;
               this->lblWelcome->Location = System::Drawing::Point(40, 40);
               this->lblWelcome->Name = L"lblWelcome";
               this->lblWelcome->Size = System::Drawing::Size(320, 45);
               this->lblWelcome->TabIndex = 0;
               this->lblWelcome->Text = L"University SIS";
               this->lblWelcome->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

               // lblSubtitle
               this->lblSubtitle->AutoSize = true;
               this->lblSubtitle->Location = System::Drawing::Point(40, 90);
               this->lblSubtitle->Name = L"lblSubtitle";
               this->lblSubtitle->Size = System::Drawing::Size(320, 20);
               this->lblSubtitle->TabIndex = 1;
               this->lblSubtitle->Text = L"Please select a portal to continue";
               this->lblSubtitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

               // btnAdmin
               this->btnAdmin->Location = System::Drawing::Point(75, 150);
               this->btnAdmin->Name = L"btnAdmin";
               this->btnAdmin->Size = System::Drawing::Size(250, 50);
               this->btnAdmin->TabIndex = 2;
               this->btnAdmin->Text = L"Admin Portal";
               this->btnAdmin->Click += gcnew System::EventHandler(this, &MainForm::btnAdmin_Click);

               // btnProfessor
               this->btnProfessor->Location = System::Drawing::Point(75, 220);
               this->btnProfessor->Name = L"btnProfessor";
               this->btnProfessor->Size = System::Drawing::Size(250, 50);
               this->btnProfessor->TabIndex = 3;
               this->btnProfessor->Text = L"Professor Portal";
               this->btnProfessor->Click += gcnew System::EventHandler(this, &MainForm::btnProfessor_Click);

               // btnStudent
               this->btnStudent->Location = System::Drawing::Point(75, 290);
               this->btnStudent->Name = L"btnStudent";
               this->btnStudent->Size = System::Drawing::Size(250, 50);
               this->btnStudent->TabIndex = 4;
               this->btnStudent->Text = L"Student Portal";
               this->btnStudent->Click += gcnew System::EventHandler(this, &MainForm::btnStudent_Click);

               // btnExit
               this->btnExit->Location = System::Drawing::Point(200, 520);
               this->btnExit->Name = L"btnExit";
               this->btnExit->Size = System::Drawing::Size(100, 35);
               this->btnExit->TabIndex = 5;
               this->btnExit->Text = L"Exit System";
               this->btnExit->Click += gcnew System::EventHandler(this, &MainForm::btnExit_Click);

               // MainForm
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->ClientSize = System::Drawing::Size(500, 600);
               this->Controls->Add(this->pnlCard);
               this->Controls->Add(this->btnExit);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
               this->MaximizeBox = false;
               this->Name = L"MainForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"University SIS";
               this->pnlCard->ResumeLayout(false);
               this->pnlCard->PerformLayout();
               this->ResumeLayout(false);
           }
#pragma endregion

    private: System::Void btnAdmin_Click(System::Object^ sender, System::EventArgs^ e) {
        AdminForm^ f = gcnew AdminForm();
        f->ShowDialog();
    }

    private: System::Void btnProfessor_Click(System::Object^ sender, System::EventArgs^ e) {
        ProfForm^ f = gcnew ProfForm();
        f->ShowDialog();
    }

    private: System::Void btnStudent_Click(System::Object^ sender, System::EventArgs^ e) {
        StudentForm^ f = gcnew StudentForm();
        f->ShowDialog();
    }

    private: System::Void btnExit_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }
   
};
}
