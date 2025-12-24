#pragma once

#include "DataManager.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class AddEditUserForm : public System::Windows::Forms::Form
    {
    private:
        int userId;
        bool isEditMode;

        // Modern UI Colors
        Color primaryColor = Color::FromArgb(45, 52, 54);
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);

    public:
        // Constructor for adding new user
        AddEditUserForm(void)
        {
            isEditMode = false;
            userId = -1;
            InitializeComponent();
            ApplyModernTheme();
            this->Text = "Add New User";
        }

        // Constructor for editing existing user
        AddEditUserForm(int userId, String^ userName, String^ userType)
        {
            isEditMode = true;
            this->userId = userId;
            InitializeComponent();
            ApplyModernTheme();

            // Populate fields
            txtUserId->Text = userId.ToString();
            txtUserId->Enabled = false; // Cannot change ID of existing user
            txtUsername->Text = userName;
            cmbUserType->SelectedItem = userType;

            this->Text = "Edit User";
        }

    private:
        void ApplyModernTheme() {
            this->BackColor = bgColor;

            // Form styling
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->MinimizeBox = false;

            // Button styling
            btnSave->FlatStyle = FlatStyle::Flat;
            btnSave->BackColor = accentColor;
            btnSave->ForeColor = Color::White;
            btnSave->FlatAppearance->BorderSize = 0;
            btnSave->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            btnSave->Cursor = Cursors::Hand;

            btnCancel->FlatStyle = FlatStyle::Flat;
            btnCancel->BackColor = Color::FromArgb(99, 110, 114);
            btnCancel->ForeColor = Color::White;
            btnCancel->FlatAppearance->BorderSize = 0;
            btnCancel->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            btnCancel->Cursor = Cursors::Hand;

            // Label styling
            System::Drawing::Font^ labelFont = gcnew System::Drawing::Font(L"Segoe UI", 10);
            Color labelColor = Color::FromArgb(99, 110, 114);

            lblUserId->Font = labelFont;
            lblUsername->Font = labelFont;
            lblPassword->Font = labelFont;
            lblUserType->Font = labelFont;

            lblUserId->ForeColor = labelColor;
            lblUsername->ForeColor = labelColor;
            lblPassword->ForeColor = labelColor;
            lblUserType->ForeColor = labelColor;

            // Input styling
            txtUserId->BorderStyle = BorderStyle::FixedSingle;
            txtUsername->BorderStyle = BorderStyle::FixedSingle;
            txtPassword->BorderStyle = BorderStyle::FixedSingle;
            cmbUserType->FlatStyle = FlatStyle::Flat;
        }

    protected:
        ~AddEditUserForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ lblUserId;
        System::Windows::Forms::TextBox^ txtUserId;
        System::Windows::Forms::Label^ lblUsername;
        System::Windows::Forms::TextBox^ txtUsername;
        System::Windows::Forms::Label^ lblPassword;
        System::Windows::Forms::TextBox^ txtPassword;
        System::Windows::Forms::Label^ lblUserType;
        System::Windows::Forms::ComboBox^ cmbUserType;
        System::Windows::Forms::Button^ btnSave;
        System::Windows::Forms::Button^ btnCancel;
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->lblUserId = (gcnew System::Windows::Forms::Label());
            this->txtUserId = (gcnew System::Windows::Forms::TextBox());
            this->lblUsername = (gcnew System::Windows::Forms::Label());
            this->txtUsername = (gcnew System::Windows::Forms::TextBox());
            this->lblPassword = (gcnew System::Windows::Forms::Label());
            this->txtPassword = (gcnew System::Windows::Forms::TextBox());
            this->lblUserType = (gcnew System::Windows::Forms::Label());
            this->cmbUserType = (gcnew System::Windows::Forms::ComboBox());
            this->btnSave = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // lblUserId
            // 
            this->lblUserId->Location = System::Drawing::Point(30, 20);
            this->lblUserId->Name = L"lblUserId";
            this->lblUserId->Size = System::Drawing::Size(200, 20);
            this->lblUserId->TabIndex = 10;
            this->lblUserId->Text = L"User ID:";
            // 
            // txtUserId
            // 
            this->txtUserId->Location = System::Drawing::Point(30, 40);
            this->txtUserId->Name = L"txtUserId";
            this->txtUserId->Size = System::Drawing::Size(300, 20);
            this->txtUserId->TabIndex = 0;
            // 
            // lblUsername
            // 
            this->lblUsername->Location = System::Drawing::Point(30, 70);
            this->lblUsername->Name = L"lblUsername";
            this->lblUsername->Size = System::Drawing::Size(200, 20);
            this->lblUsername->TabIndex = 11;
            this->lblUsername->Text = L"Username:";
            // 
            // txtUsername
            // 
            this->txtUsername->Location = System::Drawing::Point(30, 90);
            this->txtUsername->Name = L"txtUsername";
            this->txtUsername->Size = System::Drawing::Size(300, 20);
            this->txtUsername->TabIndex = 1;
            // 
            // lblPassword
            // 
            this->lblPassword->Location = System::Drawing::Point(30, 120);
            this->lblPassword->Name = L"lblPassword";
            this->lblPassword->Size = System::Drawing::Size(200, 20);
            this->lblPassword->TabIndex = 12;
            this->lblPassword->Text = L"Password:";
            // 
            // txtPassword
            // 
            this->txtPassword->Location = System::Drawing::Point(30, 140);
            this->txtPassword->Name = L"txtPassword";
            this->txtPassword->Size = System::Drawing::Size(300, 20);
            this->txtPassword->TabIndex = 2;
            this->txtPassword->PasswordChar = '*';
            // 
            // lblUserType
            // 
            this->lblUserType->Location = System::Drawing::Point(30, 170);
            this->lblUserType->Name = L"lblUserType";
            this->lblUserType->Size = System::Drawing::Size(200, 20);
            this->lblUserType->TabIndex = 13;
            this->lblUserType->Text = L"User Type:";
            // 
            // cmbUserType
            // 
            this->cmbUserType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cmbUserType->FormattingEnabled = true;
            this->cmbUserType->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Admin", L"Professor", L"Student" });
            this->cmbUserType->Location = System::Drawing::Point(30, 190);
            this->cmbUserType->Name = L"cmbUserType";
            this->cmbUserType->Size = System::Drawing::Size(300, 21);
            this->cmbUserType->TabIndex = 3;
            // 
            // btnSave
            // 
            this->btnSave->Location = System::Drawing::Point(30, 230);
            this->btnSave->Name = L"btnSave";
            this->btnSave->Size = System::Drawing::Size(140, 40);
            this->btnSave->TabIndex = 4;
            this->btnSave->Text = L"SAVE";
            this->btnSave->UseVisualStyleBackColor = true;
            this->btnSave->Click += gcnew System::EventHandler(this, &AddEditUserForm::btnSave_Click);
            // 
            // btnCancel
            // 
            this->btnCancel->Location = System::Drawing::Point(190, 230);
            this->btnCancel->Name = L"btnCancel";
            this->btnCancel->Size = System::Drawing::Size(140, 40);
            this->btnCancel->TabIndex = 5;
            this->btnCancel->Text = L"CANCEL";
            this->btnCancel->UseVisualStyleBackColor = true;
            this->btnCancel->Click += gcnew System::EventHandler(this, &AddEditUserForm::btnCancel_Click);
            // 
            // AddEditUserForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(360, 300);
            this->Controls->Add(this->txtUserId);
            this->Controls->Add(this->lblUserId);
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->btnSave);
            this->Controls->Add(this->cmbUserType);
            this->Controls->Add(this->lblUserType);
            this->Controls->Add(this->txtPassword);
            this->Controls->Add(this->lblPassword);
            this->Controls->Add(this->txtUsername);
            this->Controls->Add(this->lblUsername);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"AddEditUserForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Add User";
            this->ResumeLayout(false);
            this->PerformLayout();
        }

    private:
        System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
            String^ username = txtUsername->Text;
            String^ password = txtPassword->Text;
            String^ userType = cmbUserType->SelectedItem != nullptr ? cmbUserType->SelectedItem->ToString() : "";

            // Validation
            int newUserId = -1;
            if (!isEditMode) {
                if (String::IsNullOrWhiteSpace(txtUserId->Text)) {
                    MessageBox::Show("Please enter a User ID.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }
                if (!Int32::TryParse(txtUserId->Text, newUserId)) {
                    MessageBox::Show("User ID must be a number.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }
            }

            if (String::IsNullOrWhiteSpace(username)) {
                MessageBox::Show("Please enter a username.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (!isEditMode && String::IsNullOrWhiteSpace(password)) {
                MessageBox::Show("Please enter a password.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (String::IsNullOrWhiteSpace(userType)) {
                MessageBox::Show("Please select a user type.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            bool success = false;

            if (isEditMode) {
                // Update existing user
                if (String::IsNullOrWhiteSpace(password)) {
                    // Update without changing password
                    success = SIS::DataManager::UpdateUser(userId, username, userType);
                }
                else {
                    // Update with new password
                    success = SIS::DataManager::UpdateUser(userId, username, password, userType);
                }
            }
            else {
                // Add new user
                success = SIS::DataManager::AddUser(newUserId, username, password, userType);
            }

            if (success) {
                MessageBox::Show("User " + (isEditMode ? "updated" : "added") + " successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                this->DialogResult = Windows::Forms::DialogResult::OK;
                this->Close();
            }
            else {
                MessageBox::Show("Failed to " + (isEditMode ? "update" : "add") + " user. The User ID might already exist.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
            this->DialogResult = Windows::Forms::DialogResult::Cancel;
            this->Close();
        }
    };
}