#pragma once

#include "DataManager.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class RegisterCourseForm : public System::Windows::Forms::Form
    {
    private:
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        Color primaryColor = Color::FromArgb(45, 52, 54);
        System::Windows::Forms::Panel^ pnlCard;
        System::Windows::Forms::Label^ lblTitle;

    public:
        RegisterCourseForm(void)
        {
            InitializeComponent();
            ApplyModernTheme();
        }

    private:
        void ApplyModernTheme() {
            this->BackColor = bgColor;
            
            lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, FontStyle::Bold);
            lblTitle->ForeColor = primaryColor;

            array<Label^>^ labels = { lblCourseCode, lblName, lblCredits };
            for each (Label^ lbl in labels) {
                lbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
                lbl->ForeColor = Color::FromArgb(99, 110, 114);
            }

            array<TextBox^>^ texts = { txtCourseCode, txtName, txtCredits };
            for each (TextBox^ txt in texts) {
                txt->BorderStyle = BorderStyle::FixedSingle;
                txt->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            }

            btnSave->FlatStyle = FlatStyle::Flat;
            btnSave->BackColor = accentColor;
            btnSave->ForeColor = Color::White;
            btnSave->FlatAppearance->BorderSize = 0;
            btnSave->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);

            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->BackColor = Color::FromArgb(189, 195, 199);
            btnClose->ForeColor = Color::White;
            btnClose->FlatAppearance->BorderSize = 0;
            btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
        }

    protected:
        ~RegisterCourseForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Label^ lblCourseCode;
    private: System::Windows::Forms::Label^ lblName;
    private: System::Windows::Forms::Label^ lblCredits;
    private: System::Windows::Forms::TextBox^ txtCourseCode;
    private: System::Windows::Forms::TextBox^ txtName;
    private: System::Windows::Forms::TextBox^ txtCredits;
    private: System::Windows::Forms::Button^ btnSave;
    private: System::Windows::Forms::Button^ btnClose;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->lblCourseCode = (gcnew System::Windows::Forms::Label());
               this->lblName = (gcnew System::Windows::Forms::Label());
               this->lblCredits = (gcnew System::Windows::Forms::Label());
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->txtCourseCode = (gcnew System::Windows::Forms::TextBox());
               this->txtName = (gcnew System::Windows::Forms::TextBox());
               this->txtCredits = (gcnew System::Windows::Forms::TextBox());
               this->pnlCard = (gcnew System::Windows::Forms::Panel());
               this->btnSave = (gcnew System::Windows::Forms::Button());
               this->btnClose = (gcnew System::Windows::Forms::Button());
               this->pnlCard->SuspendLayout();
               this->SuspendLayout();

               // lblTitle
               this->lblTitle->AutoSize = true;
               this->lblTitle->Location = System::Drawing::Point(30, 20);
               this->lblTitle->Name = L"lblTitle";
               this->lblTitle->Size = System::Drawing::Size(200, 30);
               this->lblTitle->TabIndex = 0;
               this->lblTitle->Text = L"Course Registration";

               // pnlCard
               this->pnlCard->BackColor = System::Drawing::Color::White;
               this->pnlCard->Controls->Add(this->lblCourseCode);
               this->pnlCard->Controls->Add(this->txtCourseCode);
               this->pnlCard->Controls->Add(this->lblName);
               this->pnlCard->Controls->Add(this->txtName);
               this->pnlCard->Controls->Add(this->lblCredits);
               this->pnlCard->Controls->Add(this->txtCredits);
               this->pnlCard->Location = System::Drawing::Point(30, 70);
               this->pnlCard->Name = L"pnlCard";
               this->pnlCard->Size = System::Drawing::Size(360, 220);
               this->pnlCard->TabIndex = 1;

               int labelX = 20, textX = 140, y = 20, spacing = 40;

               this->lblCourseCode->Location = System::Drawing::Point(labelX, y);
               this->lblCourseCode->Text = L"Course Code:";
               this->txtCourseCode->Location = System::Drawing::Point(textX, y);
               this->txtCourseCode->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblName->Location = System::Drawing::Point(labelX, y);
               this->lblName->Text = L"Course Name:";
               this->txtName->Location = System::Drawing::Point(textX, y);
               this->txtName->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblCredits->Location = System::Drawing::Point(labelX, y);
               this->lblCredits->Text = L"Credits:";
               this->txtCredits->Location = System::Drawing::Point(textX, y);
               this->txtCredits->Size = System::Drawing::Size(200, 22);

               // btnSave
               this->btnSave->Location = System::Drawing::Point(210, 310);
               this->btnSave->Size = System::Drawing::Size(100, 35);
               this->btnSave->TabIndex = 2;
               this->btnSave->Text = L"Save Course";
               this->btnSave->Click += gcnew System::EventHandler(this, &RegisterCourseForm::btnSave_Click);

               // btnClose
               this->btnClose->Location = System::Drawing::Point(320, 310);
               this->btnClose->Size = System::Drawing::Size(70, 35);
               this->btnClose->TabIndex = 3;
               this->btnClose->Text = L"Close";
               this->btnClose->Click += gcnew System::EventHandler(this, &RegisterCourseForm::btnClose_Click);

               this->ClientSize = System::Drawing::Size(420, 370);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->pnlCard);
               this->Controls->Add(this->btnSave);
               this->Controls->Add(this->btnClose);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->MaximizeBox = false;
               this->Name = L"RegisterCourseForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               this->Text = L"Register Course";
               this->pnlCard->ResumeLayout(false);
               this->pnlCard->PerformLayout();
               this->ResumeLayout(false);
               this->PerformLayout();
           }

    private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            String^ code = this->txtCourseCode->Text;
            String^ name = this->txtName->Text;
            String^ desc = "No description"; // Default or add field
            String^ type = "Mandatory"; // Default or add field
            int maxDegree = 100; // Default or add field
            double credits = Double::Parse(this->txtCredits->Text);
            
            if (String::IsNullOrWhiteSpace(code) || String::IsNullOrWhiteSpace(name)) { 
                MessageBox::Show("Code and Name required", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning); 
                return; 
            }
            SIS::DataManager::AddCourse(code, name, desc, type, maxDegree, credits);
            MessageBox::Show("Course saved.", "Saved", MessageBoxButtons::OK, MessageBoxIcon::Information); 
            this->Close();
        }
        catch (FormatException^) { MessageBox::Show("Invalid numeric fields.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning); }
        catch (Exception^ ex) { MessageBox::Show(String::Format("Error: {0}", ex->Message), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error); }
    }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) { this->Close(); }
    };
}
