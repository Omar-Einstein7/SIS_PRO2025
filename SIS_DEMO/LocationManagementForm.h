#pragma once

#include "DataManager.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class LocationManagementForm : public System::Windows::Forms::Form
    {
    private:
        Color primaryColor = Color::FromArgb(45, 52, 54);
        Color accentColor = Color::FromArgb(9, 132, 227);
        
        System::Windows::Forms::DataGridView^ dgvLocations;
        System::Windows::Forms::TextBox^ txtName;
        System::Windows::Forms::NumericUpDown^ numCapacity;
        System::Windows::Forms::ComboBox^ cmbType;
        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnDelete;
        System::Windows::Forms::Label^ lblTitle;

    public:
        LocationManagementForm(void)
        {
            InitializeComponent();
            LoadLocations();
        }

    protected:
        ~LocationManagementForm()
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
            this->dgvLocations = (gcnew System::Windows::Forms::DataGridView());
            this->txtName = (gcnew System::Windows::Forms::TextBox());
            this->numCapacity = (gcnew System::Windows::Forms::NumericUpDown());
            this->cmbType = (gcnew System::Windows::Forms::ComboBox());
            this->btnAdd = (gcnew System::Windows::Forms::Button());
            this->btnDelete = (gcnew System::Windows::Forms::Button());
            this->lblTitle = (gcnew System::Windows::Forms::Label());

            ((System::ComponentModel::ISupportInitialize^)(this->dgvLocations))->BeginInit();
            ((System::ComponentModel::ISupportInitialize^)(this->numCapacity))->BeginInit();
            this->SuspendLayout();

            // lblTitle
            this->lblTitle->AutoSize = true;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16));
            this->lblTitle->ForeColor = primaryColor;
            this->lblTitle->Location = System::Drawing::Point(20, 20);
            this->lblTitle->Text = L"Location Management (Halls & Labs)";

            // dgvLocations
            this->dgvLocations->AllowUserToAddRows = false;
            this->dgvLocations->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvLocations->BackgroundColor = Color::White;
            this->dgvLocations->BorderStyle = BorderStyle::None;
            this->dgvLocations->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dgvLocations->Location = System::Drawing::Point(20, 70);
            this->dgvLocations->Name = L"dgvLocations";
            this->dgvLocations->ReadOnly = true;
            this->dgvLocations->RowHeadersVisible = false;
            this->dgvLocations->Size = System::Drawing::Size(740, 300);
            this->dgvLocations->SelectionMode = DataGridViewSelectionMode::FullRowSelect;

            // Input fields
            CreateLabel("Name:", 20, 390);
            this->txtName->Location = System::Drawing::Point(20, 415);
            this->txtName->Size = System::Drawing::Size(200, 25);

            CreateLabel("Type:", 240, 390);
            this->cmbType->Location = System::Drawing::Point(240, 415);
            this->cmbType->Size = System::Drawing::Size(120, 25);
            this->cmbType->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbType->Items->AddRange(gcnew array<Object^>{ "Hall", "Lab" });
            this->cmbType->SelectedIndex = 0;

            CreateLabel("Capacity:", 380, 390);
            this->numCapacity->Location = System::Drawing::Point(380, 415);
            this->numCapacity->Size = System::Drawing::Size(100, 25);
            this->numCapacity->Maximum = Decimal(1000);
            this->numCapacity->Value = Decimal(50);

            // Buttons
            this->btnAdd->Location = System::Drawing::Point(500, 410);
            this->btnAdd->Size = System::Drawing::Size(120, 35);
            this->btnAdd->Text = L"Add Location";
            this->btnAdd->FlatStyle = FlatStyle::Flat;
            this->btnAdd->BackColor = accentColor;
            this->btnAdd->ForeColor = Color::White;
            this->btnAdd->Click += gcnew System::EventHandler(this, &LocationManagementForm::btnAdd_Click);

            this->btnDelete->Location = System::Drawing::Point(630, 410);
            this->btnDelete->Size = System::Drawing::Size(120, 35);
            this->btnDelete->Text = L"Delete Selected";
            this->btnDelete->FlatStyle = FlatStyle::Flat;
            this->btnDelete->BackColor = Color::FromArgb(214, 48, 49);
            this->btnDelete->ForeColor = Color::White;
            this->btnDelete->Click += gcnew System::EventHandler(this, &LocationManagementForm::btnDelete_Click);

            // Form
            this->ClientSize = System::Drawing::Size(780, 480);
            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->dgvLocations);
            this->Controls->Add(this->txtName);
            this->Controls->Add(this->cmbType);
            this->Controls->Add(this->numCapacity);
            this->Controls->Add(this->btnAdd);
            this->Controls->Add(this->btnDelete);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->StartPosition = FormStartPosition::CenterParent;
            this->Text = L"Location Management";

            ((System::ComponentModel::ISupportInitialize^)(this->dgvLocations))->EndInit();
            ((System::ComponentModel::ISupportInitialize^)(this->numCapacity))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void CreateLabel(String^ text, int x, int y) {
            Label^ lbl = gcnew Label();
            lbl->Text = text;
            lbl->Location = System::Drawing::Point(x, y);
            lbl->AutoSize = true;
            lbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            this->Controls->Add(lbl);
        }

        void LoadLocations() {
            dgvLocations->Columns->Clear();
            dgvLocations->Columns->Add("ID", "Location ID");
            dgvLocations->Columns->Add("Type", "Type");
            dgvLocations->Columns->Add("Name", "Name");

            List<String^>^ locs = SIS::DataManager::ReadAllLocationsSimple();
            for each (String^ s in locs) {
                // format: "id,type - name"
                array<String^>^ parts = s->Split(',');
                if (parts->Length == 2) {
                    String^ id = parts[0];
                    array<String^>^ subparts = parts[1]->Split(gcnew array<String^>{" - "}, StringSplitOptions::None);
                    if (subparts->Length == 2) {
                        dgvLocations->Rows->Add(id, subparts[0]->Trim(), subparts[1]->Trim());
                    }
                }
            }
        }

        System::Void btnAdd_Click(Object^ sender, EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(txtName->Text)) {
                MessageBox::Show("Please enter a name.", "Validation Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            bool success = false;
            String^ type = cmbType->SelectedItem->ToString();
            int cap = (int)numCapacity->Value;

            if (type == "Hall") {
                success = SIS::DataManager::AddLectureHall(txtName->Text, cap);
            } else {
                success = SIS::DataManager::AddLaboratory(txtName->Text, cap);
            }

            if (success) {
                MessageBox::Show(type + " added successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                txtName->Clear();
                LoadLocations();
            } else {
                MessageBox::Show("Failed to add location.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void btnDelete_Click(Object^ sender, EventArgs^ e) {
            if (dgvLocations->SelectedRows->Count == 0) return;

            if (MessageBox::Show("Are you sure you want to delete this location?", "Confirm Delete", 
                MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
                
                int id = Int32::Parse(dgvLocations->SelectedRows[0]->Cells["ID"]->Value->ToString());
                if (SIS::DataManager::DeleteLocation(id)) {
                    MessageBox::Show("Location deleted successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    LoadLocations();
                } else {
                    MessageBox::Show("Failed to delete location. It might be in use in the schedule.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }
    };
}