#pragma once

#include "DataManager.h"
#include <msclr/marshal_cppstd.h>

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class PaymentForm : public System::Windows::Forms::Form
    {
    private:
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        Color primaryColor = Color::FromArgb(45, 52, 54);
        System::Windows::Forms::Panel^ pnlCard;
        System::Windows::Forms::Label^ lblTitle;

    public:
        PaymentForm(void)
        {
            InitializeComponent();
            ApplyModernTheme();
            LoadMetaData();
        }

    private:
        void LoadMetaData() {
            this->cmbStudent->Items->Clear();
            List<String^>^ students = SIS::DataManager::ReadAllStudents();
            for each (String^ s in students) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) this->cmbStudent->Items->Add(p[0] + " - " + p[1]);
            }

            this->cmbSemester->Items->Clear();
            List<String^>^ semesters = SIS::DataManager::ReadAllSemesters();
            for each (String^ s in semesters) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) this->cmbSemester->Items->Add(p[0] + " - " + p[1]);
            }

            if (this->cmbStudent->Items->Count > 0) this->cmbStudent->SelectedIndex = 0;
            if (this->cmbSemester->Items->Count > 0) this->cmbSemester->SelectedIndex = 0;
        }

        int GetIdFromCombo(ComboBox^ cmb) {
            if (cmb->SelectedIndex == -1) return -1;
            String^ s = cmb->SelectedItem->ToString();
            return Int32::Parse(s->Split(' ')[0]);
        }

    private:
        void ApplyModernTheme() {
            this->BackColor = bgColor;
            
            lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, FontStyle::Bold);
            lblTitle->ForeColor = primaryColor;

            array<Label^>^ labels = { lblStudentID, lblSemesterID, lblAmount, lblTotalAmount, lblStatus };
            for each (Label^ lbl in labels) {
                lbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
                lbl->ForeColor = Color::FromArgb(99, 110, 114);
            }

            array<TextBox^>^ texts = { txtAmount, txtTotalAmount };
            for each (TextBox^ txt in texts) {
                txt->BorderStyle = BorderStyle::FixedSingle;
                txt->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            }

            cmbStatus->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            cmbStudent->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            cmbSemester->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);

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
        ~PaymentForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Label^ lblStudentID;
    private: System::Windows::Forms::Label^ lblSemesterID;
    private: System::Windows::Forms::Label^ lblAmount;
    private: System::Windows::Forms::Label^ lblTotalAmount;
    private: System::Windows::Forms::Label^ lblStatus;
    private: System::Windows::Forms::ComboBox^ cmbStudent;
    private: System::Windows::Forms::ComboBox^ cmbSemester;
    private: System::Windows::Forms::TextBox^ txtAmount;
    private: System::Windows::Forms::TextBox^ txtTotalAmount;
    private: System::Windows::Forms::ComboBox^ cmbStatus;
    private: System::Windows::Forms::Button^ btnSave;
    private: System::Windows::Forms::Button^ btnClose;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->lblStudentID = (gcnew System::Windows::Forms::Label());
               this->lblSemesterID = (gcnew System::Windows::Forms::Label());
               this->lblAmount = (gcnew System::Windows::Forms::Label());
               this->lblTotalAmount = (gcnew System::Windows::Forms::Label());
               this->lblStatus = (gcnew System::Windows::Forms::Label());
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->cmbStudent = (gcnew System::Windows::Forms::ComboBox());
               this->cmbSemester = (gcnew System::Windows::Forms::ComboBox());
               this->txtAmount = (gcnew System::Windows::Forms::TextBox());
               this->txtTotalAmount = (gcnew System::Windows::Forms::TextBox());
               this->cmbStatus = (gcnew System::Windows::Forms::ComboBox());
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
               this->lblTitle->Text = L"Payment Details";

               // pnlCard
               this->pnlCard->BackColor = System::Drawing::Color::White;
               this->pnlCard->Controls->Add(this->lblStudentID);
               this->pnlCard->Controls->Add(this->cmbStudent);
               this->pnlCard->Controls->Add(this->lblSemesterID);
               this->pnlCard->Controls->Add(this->cmbSemester);
               this->pnlCard->Controls->Add(this->lblTotalAmount);
               this->pnlCard->Controls->Add(this->txtTotalAmount);
               this->pnlCard->Controls->Add(this->lblAmount);
               this->pnlCard->Controls->Add(this->txtAmount);
               this->pnlCard->Controls->Add(this->lblStatus);
               this->pnlCard->Controls->Add(this->cmbStatus);
               this->pnlCard->Location = System::Drawing::Point(30, 70);
               this->pnlCard->Name = L"pnlCard";
               this->pnlCard->Size = System::Drawing::Size(360, 260);
               this->pnlCard->TabIndex = 1;

               int labelX = 20, textX = 140, y = 20, spacing = 45;

               this->lblStudentID->Location = System::Drawing::Point(labelX, y);
               this->lblStudentID->Text = L"Student:";
               this->cmbStudent->Location = System::Drawing::Point(textX, y);
               this->cmbStudent->Size = System::Drawing::Size(200, 22);
               this->cmbStudent->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList; y += spacing;

               this->lblSemesterID->Location = System::Drawing::Point(labelX, y);
               this->lblSemesterID->Text = L"Semester:";
               this->cmbSemester->Location = System::Drawing::Point(textX, y);
               this->cmbSemester->Size = System::Drawing::Size(200, 22);
               this->cmbSemester->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList; y += spacing;

               this->lblTotalAmount->Location = System::Drawing::Point(labelX, y);
               this->lblTotalAmount->Text = L"Total Amount:";
               this->txtTotalAmount->Location = System::Drawing::Point(textX, y);
               this->txtTotalAmount->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblAmount->Location = System::Drawing::Point(labelX, y);
               this->lblAmount->Text = L"Paid Amount:";
               this->txtAmount->Location = System::Drawing::Point(textX, y);
               this->txtAmount->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblStatus->Location = System::Drawing::Point(labelX, y);
               this->lblStatus->Text = L"Status:";
               this->cmbStatus->Location = System::Drawing::Point(textX, y);
               this->cmbStatus->Size = System::Drawing::Size(200, 22);
               this->cmbStatus->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
               this->cmbStatus->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Paid", L"Pending", L"Failed" });
               this->cmbStatus->SelectedIndex = 0;

               // btnSave
               this->btnSave->Location = System::Drawing::Point(210, 350);
               this->btnSave->Size = System::Drawing::Size(100, 35);
               this->btnSave->TabIndex = 2;
               this->btnSave->Text = L"Save Payment";
               this->btnSave->Click += gcnew System::EventHandler(this, &PaymentForm::btnSave_Click);

               // btnClose
               this->btnClose->Location = System::Drawing::Point(320, 350);
               this->btnClose->Size = System::Drawing::Size(70, 35);
               this->btnClose->TabIndex = 3;
               this->btnClose->Text = L"Close";
               this->btnClose->Click += gcnew System::EventHandler(this, &PaymentForm::btnClose_Click);

               this->ClientSize = System::Drawing::Size(420, 410);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->pnlCard);
               this->Controls->Add(this->btnSave);
               this->Controls->Add(this->btnClose);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->MaximizeBox = false;
               this->Name = L"PaymentForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               this->Text = L"Payment Management";
               this->pnlCard->ResumeLayout(false);
               this->pnlCard->PerformLayout();
               this->ResumeLayout(false);
               this->PerformLayout();
           }

    private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            int sid = GetIdFromCombo(this->cmbStudent);
            int semId = GetIdFromCombo(this->cmbSemester);
            double paidAmount = Double::Parse(this->txtAmount->Text);
            double totalAmount = Double::Parse(this->txtTotalAmount->Text);
            String^ status = this->cmbStatus->Text;

            if (sid == -1 || semId == -1) {
                MessageBox::Show("Please select Student and Semester.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            bool ok = SIS::DataManager::AddPayment(sid, semId, paidAmount, totalAmount, status);
            if (ok) {
                MessageBox::Show("Payment saved successfully.", "Saved", MessageBoxButtons::OK, MessageBoxIcon::Information);
                this->Close();
            }
            else {
                MessageBox::Show("Failed to save payment.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
        catch (FormatException^) {
            MessageBox::Show("Please enter valid numeric values for Amount.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
        catch (Exception^ ex) {
            MessageBox::Show(String::Format("Unexpected error: {0}", ex->Message), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }
    };
}
