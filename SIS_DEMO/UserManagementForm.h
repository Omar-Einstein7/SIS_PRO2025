#pragma once

#include "DataManager.h"
#include "AddEditUserForm.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class UserManagementForm : public System::Windows::Forms::Form
    {
    private:
        // Modern UI Colors
        Color primaryColor = Color::FromArgb(45, 52, 54);
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        Color cardColor = Color::White;

    public:
        UserManagementForm(void)
        {
            InitializeComponent();
            SetupDataGridView();
            ApplyModernTheme();
            LoadUsers();
        }

    private:
        void LoadUsers() {
            try {
                // Clear existing data
                dataGridViewUsers->Rows->Clear();

                // Get users from database
                auto users = SIS::DataManager::GetAllUsers();
                
                for each (auto user in users) {
                    dataGridViewUsers->Rows->Add(
                        user->UserId,
                        user->UserName,
                        user->UserType,
                        "Edit",
                        "Delete"
                    );
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading users: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void ApplyModernTheme() {
            this->BackColor = bgColor;
            
            // Form styling
            this->Text = "User Management - SIS";
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            
            // Button styling
            btnAddUser->FlatStyle = FlatStyle::Flat;
            btnAddUser->BackColor = accentColor;
            btnAddUser->ForeColor = Color::White;
            btnAddUser->FlatAppearance->BorderSize = 0;
            btnAddUser->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            btnAddUser->Cursor = Cursors::Hand;

            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->BackColor = Color::FromArgb(214, 48, 49);
            btnClose->ForeColor = Color::White;
            btnClose->FlatAppearance->BorderSize = 0;
            btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            btnClose->Cursor = Cursors::Hand;

            // DataGridView styling
            dataGridViewUsers->BackgroundColor = Color::White;
            dataGridViewUsers->BorderStyle = BorderStyle::None;
            dataGridViewUsers->DefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            dataGridViewUsers->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            dataGridViewUsers->EnableHeadersVisualStyles = false;
            dataGridViewUsers->ColumnHeadersDefaultCellStyle->BackColor = primaryColor;
            dataGridViewUsers->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
        }

    protected:
        ~UserManagementForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: 
        System::Windows::Forms::DataGridView^ dataGridViewUsers;
        System::Windows::Forms::Button^ btnAddUser;
        System::Windows::Forms::Button^ btnClose;
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->dataGridViewUsers = (gcnew System::Windows::Forms::DataGridView());
            this->btnAddUser = (gcnew System::Windows::Forms::Button());
            this->btnClose = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewUsers))->BeginInit();
            this->SuspendLayout();
            // 
            // dataGridViewUsers
            // 
            this->dataGridViewUsers->AllowUserToAddRows = false;
            this->dataGridViewUsers->AllowUserToDeleteRows = false;
            this->dataGridViewUsers->AllowUserToResizeRows = false;
            this->dataGridViewUsers->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->dataGridViewUsers->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridViewUsers->Location = System::Drawing::Point(20, 20);
            this->dataGridViewUsers->Name = L"dataGridViewUsers";
            this->dataGridViewUsers->ReadOnly = true;
            this->dataGridViewUsers->RowHeadersVisible = false;
            this->dataGridViewUsers->Size = System::Drawing::Size(760, 400);
            this->dataGridViewUsers->TabIndex = 0;
            this->dataGridViewUsers->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &UserManagementForm::dataGridViewUsers_CellContentClick);
            // 
            // btnAddUser
            // 
            this->btnAddUser->Location = System::Drawing::Point(20, 440);
            this->btnAddUser->Name = L"btnAddUser";
            this->btnAddUser->Size = System::Drawing::Size(120, 40);
            this->btnAddUser->TabIndex = 1;
            this->btnAddUser->Text = L"ADD USER";
            this->btnAddUser->UseVisualStyleBackColor = true;
            this->btnAddUser->Click += gcnew System::EventHandler(this, &UserManagementForm::btnAddUser_Click);
            // 
            // btnClose
            // 
            this->btnClose->Location = System::Drawing::Point(660, 440);
            this->btnClose->Name = L"btnClose";
            this->btnClose->Size = System::Drawing::Size(120, 40);
            this->btnClose->TabIndex = 2;
            this->btnClose->Text = L"CLOSE";
            this->btnClose->UseVisualStyleBackColor = true;
            this->btnClose->Click += gcnew System::EventHandler(this, &UserManagementForm::btnClose_Click);
            // 
            // UserManagementForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(800, 500);
            this->Controls->Add(this->btnClose);
            this->Controls->Add(this->btnAddUser);
            this->Controls->Add(this->dataGridViewUsers);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"UserManagementForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"User Management";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewUsers))->EndInit();
            this->ResumeLayout(false);

        }

    private:
        System::Void btnAddUser_Click(System::Object^ sender, System::EventArgs^ e) {
            AddEditUserForm^ form = gcnew AddEditUserForm();
            if (form->ShowDialog() == Windows::Forms::DialogResult::OK) {
                LoadUsers(); // Refresh the list
            }
        }

        System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }

        System::Void dataGridViewUsers_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
            if (e->RowIndex >= 0 && e->ColumnIndex >= 0) {
                String^ columnName = dataGridViewUsers->Columns[e->ColumnIndex]->Name;
                int userId = safe_cast<int>(dataGridViewUsers->Rows[e->RowIndex]->Cells["UserId"]->Value);
                String^ userName = safe_cast<String^>(dataGridViewUsers->Rows[e->RowIndex]->Cells["UserName"]->Value);
                String^ userType = safe_cast<String^>(dataGridViewUsers->Rows[e->RowIndex]->Cells["UserType"]->Value);

                if (columnName == "Edit") {
                    AddEditUserForm^ form = gcnew AddEditUserForm(userId, userName, userType);
                    if (form->ShowDialog() == Windows::Forms::DialogResult::OK) {
                        LoadUsers(); // Refresh the list
                    }
                }
                else if (columnName == "Delete") {
                    if (MessageBox::Show("Are you sure you want to delete user '" + userName + "'?", "Confirm Delete", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == Windows::Forms::DialogResult::Yes) {
                        if (SIS::DataManager::DeleteUser(userId)) {
                            MessageBox::Show("User deleted successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                            LoadUsers(); // Refresh the list
                        }
                        else {
                            MessageBox::Show("Failed to delete user.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        }
                    }
                }
            }
        }

        // Initialize DataGridView columns
        void SetupDataGridView() {
            dataGridViewUsers->Columns->Clear();

            // Add columns
            dataGridViewUsers->Columns->Add("UserId", "User ID");
            dataGridViewUsers->Columns->Add("UserName", "Username");
            dataGridViewUsers->Columns->Add("UserType", "User Type");
            
            // Add action buttons
            DataGridViewButtonColumn^ editColumn = gcnew DataGridViewButtonColumn();
            editColumn->Name = "Edit";
            editColumn->HeaderText = "";
            editColumn->Text = "Edit";
            editColumn->UseColumnTextForButtonValue = true;
            dataGridViewUsers->Columns->Add(editColumn);

            DataGridViewButtonColumn^ deleteColumn = gcnew DataGridViewButtonColumn();
            deleteColumn->Name = "Delete";
            deleteColumn->HeaderText = "";
            deleteColumn->Text = "Delete";
            deleteColumn->UseColumnTextForButtonValue = true;
            dataGridViewUsers->Columns->Add(deleteColumn);

            // Set column widths
            dataGridViewUsers->Columns["UserId"]->Width = 80;
            dataGridViewUsers->Columns["UserName"]->Width = 200;
            dataGridViewUsers->Columns["UserType"]->Width = 150;
            dataGridViewUsers->Columns["Edit"]->Width = 60;
            dataGridViewUsers->Columns["Delete"]->Width = 60;
        }
    };
}