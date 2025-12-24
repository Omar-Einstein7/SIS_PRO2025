#pragma once

#include "DataManager.h"
#include "AdminForm.h"
#include "ProfForm.h"
#include "StudentForm.h"

namespace SISDEMO {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class LoginForm : public System::Windows::Forms::Form
	{
    private:
        // Modern UI Colors
        Color primaryColor = Color::FromArgb(45, 52, 54);    // Dark Charcoal
        Color accentColor = Color::FromArgb(9, 132, 227);   // Blue
        Color bgColor = Color::FromArgb(245, 246, 250);     // Light Gray
        Color cardColor = Color::White;

           Color textColor = Color::FromArgb(45, 52, 54);

	public:
		LoginForm(void)
		{
			InitializeComponent();
            ApplyModernTheme();
            try {
                // Try connecting with no password first (common for local dev)
                SIS::DataManager::Configure("localhost", "root", "root", "sis_db", 3306);
                SIS::DataManager::EnsureDatabaseInitialized();
            } catch (Exception^ firstEx) {
                // If it fails (likely Access Denied), try 'root' password
                try {
                    SIS::DataManager::Configure("localhost", "root", "root", "sis_db", 3306);
                    SIS::DataManager::EnsureDatabaseInitialized();
                } catch (Exception^ secondEx) {
                    // Both failed. Show a helpful message.
                    String^ msg = "Could not connect to MySQL server.\n\n" +
                                 "Attempts:\n" +
                                 "1. root@localhost (no password): " + firstEx->Message + "\n" +
                                 "2. root@localhost (password 'root'): " + secondEx->Message + "\n\n" +
                                 "Please ensure MySQL is running and the credentials are correct.";
                    MessageBox::Show(msg, "Database Connection Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
		}

    private:
        void ApplyModernTheme() {
            this->BackColor = bgColor;
            
            // Title Styling
            lblTitle->ForeColor = accentColor;
            lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 22, FontStyle::Bold);
            
            // Labels
            System::Drawing::Font^ labelFont = gcnew System::Drawing::Font(L"Segoe UI", 10);
            Color labelColor = Color::FromArgb(99, 110, 114);
            
            lblUser->Font = labelFont;
            lblPass->Font = labelFont;
            
            lblUser->ForeColor = labelColor;
            lblPass->ForeColor = labelColor;

            // Buttons
            btnLogin->FlatStyle = FlatStyle::Flat;
            btnLogin->BackColor = accentColor;
            btnLogin->ForeColor = Color::White;
            btnLogin->FlatAppearance->BorderSize = 0;
            btnLogin->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            btnLogin->Cursor = Cursors::Hand;

            btnExit->FlatStyle = FlatStyle::Flat;
            btnExit->BackColor = Color::FromArgb(214, 48, 49); // Red
            btnExit->ForeColor = Color::White;
            btnExit->FlatAppearance->BorderSize = 0;
            btnExit->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            btnExit->Cursor = Cursors::Hand;

            // Inputs
            txtUser->BorderStyle = BorderStyle::FixedSingle;
            txtPass->BorderStyle = BorderStyle::FixedSingle;
        }

	protected:
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: 
        System::Windows::Forms::Panel^ pnlCard;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblUser;
        System::Windows::Forms::TextBox^ txtUser;
        System::Windows::Forms::Label^ lblPass;
        System::Windows::Forms::TextBox^ txtPass;
        System::Windows::Forms::Button^ btnLogin;
        System::Windows::Forms::Button^ btnExit;
    private: System::ComponentModel::IContainer^ components;



#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
            this->pnlCard = (gcnew System::Windows::Forms::Panel());
            this->btnExit = (gcnew System::Windows::Forms::Button());
            this->btnLogin = (gcnew System::Windows::Forms::Button());
            this->txtPass = (gcnew System::Windows::Forms::TextBox());
            this->lblPass = (gcnew System::Windows::Forms::Label());
            this->txtUser = (gcnew System::Windows::Forms::TextBox());
            this->lblUser = (gcnew System::Windows::Forms::Label());
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->pnlCard->SuspendLayout();
            this->SuspendLayout();
            // 
            // pnlCard
            // 
            this->pnlCard->BackColor = System::Drawing::Color::White;
            this->pnlCard->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
            this->pnlCard->Controls->Add(this->btnExit);
            this->pnlCard->Controls->Add(this->btnLogin);
            this->pnlCard->Controls->Add(this->txtPass);
            this->pnlCard->Controls->Add(this->lblPass);
            this->pnlCard->Controls->Add(this->txtUser);
            this->pnlCard->Controls->Add(this->lblUser);
            this->pnlCard->Controls->Add(this->lblTitle);
            this->pnlCard->Location = System::Drawing::Point(225, 75);
            this->pnlCard->Name = L"pnlCard";
            this->pnlCard->Size = System::Drawing::Size(350, 400);
            this->pnlCard->TabIndex = 0;
            // 
            // btnExit
            // 
            this->btnExit->Location = System::Drawing::Point(35, 290);
            this->btnExit->Name = L"btnExit";
            this->btnExit->Size = System::Drawing::Size(280, 40);
            this->btnExit->TabIndex = 4;
            this->btnExit->Text = L"EXIT";
            this->btnExit->UseVisualStyleBackColor = true;
            this->btnExit->Click += gcnew System::EventHandler(this, &LoginForm::btnExit_Click);
            // 
            // btnLogin
            // 
            this->btnLogin->Location = System::Drawing::Point(35, 240);
            this->btnLogin->Name = L"btnLogin";
            this->btnLogin->Size = System::Drawing::Size(280, 40);
            this->btnLogin->TabIndex = 3;
            this->btnLogin->Text = L"LOGIN";
            this->btnLogin->UseVisualStyleBackColor = true;
            this->btnLogin->Click += gcnew System::EventHandler(this, &LoginForm::btnLogin_Click);
            // 
            // txtPass
            // 
            this->txtPass->Location = System::Drawing::Point(35, 190);
            this->txtPass->Name = L"txtPass";
            this->txtPass->PasswordChar = '*';
            this->txtPass->Size = System::Drawing::Size(280, 20);
            this->txtPass->TabIndex = 2;
            // 
            // lblPass
            // 
            this->lblPass->Location = System::Drawing::Point(35, 165);
            this->lblPass->Name = L"lblPass";
            this->lblPass->Size = System::Drawing::Size(280, 23);
            this->lblPass->TabIndex = 5;
            this->lblPass->Text = L"Password";
            // 
            // txtUser
            // 
            this->txtUser->Location = System::Drawing::Point(35, 125);
            this->txtUser->Name = L"txtUser";
            this->txtUser->Size = System::Drawing::Size(280, 20);
            this->txtUser->TabIndex = 1;
            // 
            // lblUser
            // 
            this->lblUser->Location = System::Drawing::Point(35, 100);
            this->lblUser->Name = L"lblUser";
            this->lblUser->Size = System::Drawing::Size(280, 23);
            this->lblUser->TabIndex = 6;
            this->lblUser->Text = L"Username";
            // 
            // lblTitle
            // 
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 22, System::Drawing::FontStyle::Bold));
            this->lblTitle->Location = System::Drawing::Point(0, 30);
            this->lblTitle->Name = L"lblTitle";
            this->lblTitle->Size = System::Drawing::Size(350, 50);
            this->lblTitle->TabIndex = 0;
            this->lblTitle->Text = L"UNIVERSITY SIS";
            this->lblTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // LoginForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
            this->ClientSize = System::Drawing::Size(800, 600);
            this->Controls->Add(this->pnlCard);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->MaximizeBox = false;
            this->Name = L"LoginForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"SIS - Login";
            this->pnlCard->ResumeLayout(false);
            this->pnlCard->PerformLayout();
            this->ResumeLayout(false);

        }
#pragma endregion

    private: 
        System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e) {
            String^ user = txtUser->Text;
            String^ pass = txtPass->Text;

            if (String::IsNullOrWhiteSpace(user) || String::IsNullOrWhiteSpace(pass)) {
                MessageBox::Show("Please enter username and password.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            String^ result = nullptr;
                try {
                    result = SIS::DataManager::Login(user, pass);
                } catch (Exception^ ex) {
                    MessageBox::Show("Login error: " + ex->Message, "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }

                if (result != nullptr) {
                // Login successful
                array<String^>^ parts = result->Split('|');
                String^ userId = parts[0];
                String^ userType = parts[1];

                MessageBox::Show("Welcome! You are logged in as " + userType, "Login Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

                this->Hide();
                int id = Int32::Parse(userId);
                String^ typeLower = userType->ToLower();
                if (typeLower == "admin") {
                    AdminForm^ adminForm = gcnew AdminForm();
                    adminForm->ShowDialog();
                }
                else if (typeLower == "professor") {
                    ProfForm^ profForm = gcnew ProfForm(id);
                    profForm->ShowDialog();
                }
                else if (typeLower == "student") {
                    StudentForm^ studentForm = gcnew StudentForm(id);
                    studentForm->ShowDialog();
                }
                
                // Show login form again after logout
                txtUser->Text = "";
                txtPass->Text = "";
                this->Show();
            }
            else {
                MessageBox::Show("Invalid username or password.", "Login Failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void btnExit_Click(System::Object^ sender, System::EventArgs^ e) {
            Application::Exit();
        }
	};
}
