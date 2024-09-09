//#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <chrono> // Include thư viện này để sử dụng cho việc xử lý dữ liệu nhập/ra
//#include "MaHoavaGiaiMa.cpp"
//#include "MaHoavaGiaiMa.cpp"
#include <msclr/marshal_cppstd.h>
// Bạn cũng cần include thư viện của OpenFileDialog
#include <Windows.h>

namespace Project1test {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;
	//using namespace System::Convert;
	using namespace System::IO; // Include thư viện này để sử dụng cho việc đọc tệp tin
	using namespace std;
	using namespace std::chrono;
	int dodai = 0;

	int initial_permutation[64] =
	{
		58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7
	};

	// Initial permutation table for key
	int initial_key_permutation[56] =
	{
		57, 49, 41, 33, 25, 17, 9, 1,
		58, 50, 42, 34, 26, 18, 10, 2,
		59, 51, 43, 35, 27, 19, 11, 3,
		60, 52, 44, 36, 63, 55, 47, 39,
		31, 23, 15, 7, 62, 54, 46, 38,
		30, 22, 14, 6, 61, 53, 45, 37,
		29, 21, 13, 5, 28, 20, 12, 4
	};

	// Expansion table for key
	int key_expansion[48] =
	{
		32, 1, 2, 3, 4, 5, 4, 5,
		6, 7, 8, 9, 8, 9, 10, 11,
		12, 13, 12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21, 20, 21,
		22, 23, 24, 25, 24, 25, 26, 27,
		28, 29, 28, 29, 30, 31, 32, 1
	};

	// Substitution boxes
	int substitution_boxes[8][4][16] =
	{
		{
			14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
			0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
			4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
			15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
		},
		{
			15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
			3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
			0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
			13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
		},
		{
			10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
			13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
			13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
			1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
		},
		{
			7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
			13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
			10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
			3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
		},
		{
			2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
			14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
			4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
			11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
		},
		{
			12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
			10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
			9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
			4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
		},
		{
			4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
			13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
			1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
			6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
		},
		{
			13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
			1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
			7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
			2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
		}
	};

	// Permutation table for expanding 32-bit R to 48 bits
	int expansion_table[48] =
	{
		32, 1, 2, 3, 4, 5, 4, 5,
		6, 7, 8, 9, 8, 9, 10, 11,
		12, 13, 12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21, 20, 21,
		22, 23, 24, 25, 24, 25, 26, 27,
		28, 29, 28, 29, 30, 31, 32, 1
	};

	// Permutation table after S-box substitution
	int permutation_tab[32] =
	{
		16, 7, 20, 21, 29, 12, 28, 17,
		1, 15, 23, 26, 5, 18, 31, 10,
		2, 8, 24, 14, 32, 27, 3, 9,
		19, 13, 30, 6, 22, 11, 4, 25
	};

	// Final permutation (Inverse of initial permutation)
	int inverse_permutation[64] =
	{
		40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41, 9, 49, 17, 57, 25
	};
	public delegate void DataEnteredEventHandler(String^ data, String^ key);

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

		// Sự kiện DataEntered để truyền dữ liệu về class main
		event DataEnteredEventHandler^ DataEntered;

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Button^ button3;
		System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::TextBox^ textBox1;

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::RichTextBox^ richTextBox2;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::RichTextBox^ richTextBox3;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::ComponentModel::IContainer^ components;





#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			   this->button4 = (gcnew System::Windows::Forms::Button());
			   this->richTextBox3 = (gcnew System::Windows::Forms::RichTextBox());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   this->SuspendLayout();
			   // 
			   // button3
			   // 
			   this->button3->Location = System::Drawing::Point(20, 122);
			   this->button3->Margin = System::Windows::Forms::Padding(4);
			   this->button3->Name = L"button3";
			   this->button3->Size = System::Drawing::Size(100, 28);
			   this->button3->TabIndex = 7;
			   this->button3->Text = L"Chọn file";
			   this->button3->UseVisualStyleBackColor = true;
			   this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			   // 
			   // richTextBox1
			   // 
			   this->richTextBox1->Location = System::Drawing::Point(20, 191);
			   this->richTextBox1->Margin = System::Windows::Forms::Padding(4);
			   this->richTextBox1->Name = L"richTextBox1";
			   this->richTextBox1->Size = System::Drawing::Size(484, 237);
			   this->richTextBox1->TabIndex = 8;
			   this->richTextBox1->Text = L"";
			   this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::richTextBox1_TextChanged);
			   // 
			   // textBox1
			   // 
			   this->textBox1->Location = System::Drawing::Point(20, 52);
			   this->textBox1->Margin = System::Windows::Forms::Padding(4);
			   this->textBox1->Multiline = true;
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(359, 28);
			   this->textBox1->TabIndex = 9;
			   this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			   // 
			   // button1
			   // 
			   this->button1->Location = System::Drawing::Point(397, 52);
			   this->button1->Margin = System::Windows::Forms::Padding(4);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(108, 28);
			   this->button1->TabIndex = 11;
			   this->button1->Text = L"Ngẫu nhiên";
			   this->button1->UseVisualStyleBackColor = true;
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(16, 32);
			   this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(116, 16);
			   this->label1->TabIndex = 12;
			   this->label1->Text = L"Nhập khóa tại đây";
			   this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(165, 128);
			   this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(27, 16);
			   this->label2->TabIndex = 17;
			   this->label2->Text = L"null";
			   this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			   // 
			   // button2
			   // 
			   this->button2->Location = System::Drawing::Point(397, 468);
			   this->button2->Margin = System::Windows::Forms::Padding(4);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(108, 38);
			   this->button2->TabIndex = 18;
			   this->button2->Text = L"Mã hóa";
			   this->button2->UseVisualStyleBackColor = true;
			   this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			   // 
			   // richTextBox2
			   // 
			   this->richTextBox2->Location = System::Drawing::Point(580, 52);
			   this->richTextBox2->Margin = System::Windows::Forms::Padding(4);
			   this->richTextBox2->Name = L"richTextBox2";
			   this->richTextBox2->Size = System::Drawing::Size(473, 190);
			   this->richTextBox2->TabIndex = 19;
			   this->richTextBox2->Text = L"";
			   this->richTextBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::richTextBox2_TextChanged);
			   // 
			   // button4
			   // 
			   this->button4->Location = System::Drawing::Point(1085, 204);
			   this->button4->Margin = System::Windows::Forms::Padding(4);
			   this->button4->Name = L"button4";
			   this->button4->Size = System::Drawing::Size(108, 38);
			   this->button4->TabIndex = 20;
			   this->button4->Text = L"Giải mã";
			   this->button4->UseVisualStyleBackColor = true;
			   this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			   // 
			   // richTextBox3
			   // 
			   this->richTextBox3->Location = System::Drawing::Point(580, 309);
			   this->richTextBox3->Margin = System::Windows::Forms::Padding(4);
			   this->richTextBox3->Name = L"richTextBox3";
			   this->richTextBox3->Size = System::Drawing::Size(473, 196);
			   this->richTextBox3->TabIndex = 21;
			   this->richTextBox3->Text = L"";
			   this->richTextBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::richTextBox3_TextChanged);
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Location = System::Drawing::Point(1075, 52);
			   this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(111, 16);
			   this->label3->TabIndex = 22;
			   this->label3->Text = L"Thời gian mã hóa";
			   this->label3->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			   // 
			   // textBox2
			   // 
			   this->textBox2->Location = System::Drawing::Point(1075, 84);
			   this->textBox2->Margin = System::Windows::Forms::Padding(4);
			   this->textBox2->Name = L"textBox2";
			   this->textBox2->Size = System::Drawing::Size(118, 22);
			   this->textBox2->TabIndex = 23;
			   this->textBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
			   // 
			   // textBox3
			   // 
			   this->textBox3->Location = System::Drawing::Point(1075, 340);
			   this->textBox3->Margin = System::Windows::Forms::Padding(4);
			   this->textBox3->Name = L"textBox3";
			   this->textBox3->Size = System::Drawing::Size(118, 22);
			   this->textBox3->TabIndex = 25;
			   this->textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Location = System::Drawing::Point(1075, 308);
			   this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(110, 16);
			   this->label4->TabIndex = 24;
			   this->label4->Text = L"Thời gian giải mã";
			   // 
			   // label5
			   // 
			   this->label5->AutoSize = true;
			   this->label5->Location = System::Drawing::Point(1101, 122);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(92, 16);
			   this->label5->TabIndex = 26;
			   this->label5->Text = L"microseconds";
			   this->label5->Click += gcnew System::EventHandler(this, &MyForm::label5_Click);
			   // 
			   // label6
			   // 
			   this->label6->AutoSize = true;
			   this->label6->Location = System::Drawing::Point(1101, 379);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(92, 16);
			   this->label6->TabIndex = 27;
			   this->label6->Text = L"microseconds";
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1224, 558);
			   this->Controls->Add(this->label6);
			   this->Controls->Add(this->label5);
			   this->Controls->Add(this->textBox3);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->textBox2);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->richTextBox3);
			   this->Controls->Add(this->button4);
			   this->Controls->Add(this->richTextBox2);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->richTextBox1);
			   this->Controls->Add(this->button3);
			   this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

	private:
		System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {}

		System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
			OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();

			openFileDialog1->Title = "Chọn một tệp tin";
			openFileDialog1->InitialDirectory = "c:\\";
			openFileDialog1->Filter = "Tất cả các tệp tin (*.*)|*.*";
			openFileDialog1->RestoreDirectory = true;

			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				String^ filePath = openFileDialog1->FileName;

				// Kiểm tra xem tệp tin tồn tại trước khi đọc
				if (File::Exists(filePath)) {
					try {
						StreamReader^ sr = gcnew StreamReader(filePath);
						richTextBox1->Text = sr->ReadToEnd();
						sr->Close();

						label2->Text = System::IO::Path::GetFileName(filePath);
					}
					catch (Exception^ ex) {
						MessageBox::Show("Không thể đọc tệp tin: " + ex->Message, "Lỗi", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
				else {
					MessageBox::Show("Tệp tin không tồn tại!", "Lỗi", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}

		System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {

		}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {


	}
		   /*
		   */
		   string padToMultipleOf64(string input)
		   {
			   int remainder = input.length() % 64;
			   int padding_length = (remainder == 0) ? 64 : (64 - remainder);
			   // Thêm một ký tự '1' đầu tiên
			   input += '1';
			   // Thêm các ký tự '0' vào cuối
			   input.append(padding_length - 1, ' ');
			   return input;
		   }
		   string stringToBinary(string input)
		   {
			   string binary_string = "";
			   for (char& c : input)
			   {
				   binary_string += bitset<8>(c).to_string();
			   }
			   return binary_string;
		   }

		   // Function to permute the input according to a permutation table
		   string permute(string input, int* permutation_table, int table_size)
		   {
			   string permuted = "";
			   for (int i = 0; i < table_size; ++i)
			   {
				   permuted += input[permutation_table[i] - 1];
			   }
			   return permuted;
		   }

		   // Function to do a circular left shift by a specified number of positions
		   string circularLeftShift(string key_chunk, int shift)
		   {
			   string shifted = "";
			   for (std::string::size_type i = shift; i < key_chunk.size(); ++i)
			   {
				   shifted += key_chunk[i];
			   }
			   for (int i = 0; i < shift; ++i)
			   {
				   shifted += key_chunk[i];
			   }
			   return shifted;
		   }

		   // Function to perform XOR operation on two strings
		   string XOR(string a, string b)
		   {
			   string result = "";
			   for (std::string::size_type i = 0; i < a.size(); ++i)
			   {
				   result += (a[i] == b[i]) ? '0' : '1';
			   }
			   return result;
		   }

		   // Function to generate round keys
		   void generateRoundKeys(string key, string* round_keys)
		   {
			   key = permute(key, initial_key_permutation, 56);
			   string left = key.substr(0, 28);
			   string right = key.substr(28, 28);
			   for (int i = 0; i < 16; ++i)
			   {
				   if (i == 0 || i == 1 || i == 8 || i == 15)
				   {
					   left = circularLeftShift(left, 1);
					   right = circularLeftShift(right, 1);
				   }
				   else
				   {
					   left = circularLeftShift(left, 2);
					   right = circularLeftShift(right, 2);
				   }
				   string combined_key = left + right;
				   round_keys[i] = permute(combined_key, key_expansion, 48);
			   }
		   }

		   // Function to apply S-box substitution
		   string applySBox(string input)
		   {
			   string result = "";
			   for (int i = 0; i < 8; ++i)
			   {
				   int row = stoi(input.substr(i * 6, 1) + input.substr(i * 6 + 5, 1), nullptr, 2);
				   int col = stoi(input.substr(i * 6 + 1, 4), nullptr, 2);
				   result += bitset<4>(substitution_boxes[i][row][col]).to_string();
			   }
			   return result;
		   }

		   // Function to perform DES encryption on a 64-bit block
		   string encryptBlock(string block, string* round_keys)
		   {
			   block = permute(block, initial_permutation, 64);
			   string left = block.substr(0, 32);
			   string right = block.substr(32, 32);
			   for (int i = 0; i < 16; ++i)
			   {
				   string expanded_right = permute(right, expansion_table, 48);
				   string xored = XOR(expanded_right, round_keys[i]);
				   string substituted = applySBox(xored);
				   string permuted = permute(substituted, permutation_tab, 32);
				   string temp = left;
				   left = right;
				   right = XOR(temp, permuted);
			   }
			   string combined = right + left;
			   string ciphertext = permute(combined, inverse_permutation, 64);
			   return ciphertext;
		   }

		   // Function to perform DES encryption on a string of any length
		   string DES_Encrypt(string plaintext, string key)
		   {
			   // Pad the plaintext to a multiple of 64 bits
			   plaintext = padToMultipleOf64(plaintext);
			   // Convert key and plaintext to binary
			   key = stringToBinary(key);
			   plaintext = stringToBinary(plaintext);
			   // Generate round keys
			   string round_keys[16];
			   generateRoundKeys(key, round_keys);
			   // Encrypt each 64-bit block of plaintext
			   string ciphertext = "";
			   for (std::string::size_type i = 0; i < plaintext.length(); i += 64)
			   {
				   string block = plaintext.substr(i, 64);
				   ciphertext += encryptBlock(block, round_keys);
			   }
			   return ciphertext;
		   }


		   //tesst
		   string removePadding(string plaintext)
		   {
			   // Tìm vị trí cuối cùng của '1' trong plaintext
			   size_t last_one = plaintext.find_last_of('1');
			   // Trả về phần của chuỗi không chứa padding
			   return plaintext.substr(0, last_one + 1);
		   }

		   string binaryToString(string binary)
		   {
			   // Loại bỏ các ký tự số 0 thừa
			   //binary = removePadding(binary);

			   string text = "";
			   // Lặp qua từng byte của chuỗi nhị phân (mỗi byte có 8 bit)
			   for (size_t i = 0; i < binary.length(); i += 8)
			   {
				   string byte = binary.substr(i, 8); // Lấy 8 bit
				   // Chuyển đổi từ nhị phân sang số nguyên, sau đó sang ký tự
				   char c = static_cast<char>(std::stoi(byte, nullptr, 2));
				   text += c; // Thêm ký tự vào chuỗi kết quả
			   }
			   return text; // Trả về chuỗi kết quả
		   }

		   string decryptBlock(string block, string* round_keys)
		   {
			   // Ban đầu, thực hiện hoán đổi ban đầu
			   block = permute(block, initial_permutation, 64);
			   // Tách block thành 2 nửa: left và right
			   string left = block.substr(0, 32);
			   string right = block.substr(32, 32);
			   // Bắt đầu vòng lặp để giải mã
			   for (int i = 15; i >= 0; --i)   // Lặp ngược lại các round keys
			   {
				   // Lưu trữ right trước khi thực hiện bất kỳ phép biến đổi nào
				   string previous_right = right;
				   // Mở rộng right thành 48 bit bằng bảng mở rộng
				   string expanded_right = permute(right, expansion_table, 48);
				   // Thực hiện phép XOR giữa expanded_right và round key tương ứng
				   string xored = XOR(expanded_right, round_keys[i]);
				   // Thực hiện thay thế S-box
				   string substituted = applySBox(xored);
				   // Thực hiện hoán vị theo bảng hoán vị cuối cùng
				   string permuted = permute(substituted, permutation_tab, 32);
				   // Thực hiện phép XOR giữa left và permuted
				   string temp = left;
				   left = right;
				   right = XOR(temp, permuted);
				   // Lặp lại vòng lặp với right và left mới
				   // Điều này đảm bảo rằng giải mã là ngược lại với quá trình mã hóa
			   }
			   // Kết hợp left và right sau khi đã giải mã
			   string combined = right + left;
			   // Áp dụng bảng hoán vị cuối cùng (hoán vị nghịch đảo của hoán vị ban đầu)
			   string plaintext_block = permute(combined, inverse_permutation, 64);
			   // Trả về khối văn bản đã được giải mã
			   return plaintext_block;
		   }

		   //tesst
		   string DES_Decrypt(string ciphertext, string key)
		   {
			   // Convert key to binary
			   key = stringToBinary(key);
			   // Generate round keys
			   string round_keys[16];
			   generateRoundKeys(key, round_keys);
			   // Decrypt each 64-bit block of ciphertext
			   string plaintext = "";
			   for (std::string::size_type i = 0; i < ciphertext.length(); i += 64)
			   {
				   string block = ciphertext.substr(i, 64);
				   plaintext += decryptBlock(block, round_keys);
			   }
			   //cout << "\nChua xoa padding: " << plaintext << endl;
			   //cout << "\nchua xoa padding: " << binaryToString(plaintext) << endl;
			   // Remove any padding from plaintext
			   plaintext = removePadding(plaintext);
			   //cout << "\n xoa padding: " << binaryToString(plaintext) << endl;
			   // Convert binary plaintext back to string
			   plaintext = binaryToString(plaintext);
			   return plaintext;
		   }
		   /**/

		   System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
			   String^ key = textBox1->Text->Trim(); // Key DES
			   String^ data = richTextBox1->Text->Trim();
			   //DES newDes;
			   // Kiểm tra và thông báo key và data
			   if (IsValidKey(key)) {
				   string key = msclr::interop::marshal_as<std::string>(textBox1->Text->Trim());
				   string data = msclr::interop::marshal_as<std::string>(richTextBox1->Text->Trim());
				   string test = binaryToString(DES_Encrypt(data, key));

				   auto start_encrypt = high_resolution_clock::now();

				   richTextBox2->Text = gcnew String(test.c_str());

				   auto stop_encrypt = high_resolution_clock::now();
				   auto duration_encrypt = duration_cast<microseconds>(stop_encrypt - start_encrypt);
				   //richTextBox2->Text = key + data ;
				   textBox2->Text = duration_encrypt.count().ToString();
				   //string vanbanmahoa = newDes.binaryToString(newDes.DES_Encrypt(key, data));

				  // richTextBox2->Text = gcnew String(vanbanmahoa.c_str());

			   }
			   else {
				   MessageBox::Show("Key DES không hợp lệ. Vui lòng nhập key có đúng 64 ký tự hex (0-9, A-F, a-f).", "Lỗi", MessageBoxButtons::OK, MessageBoxIcon::Error);
				   return;
			   }
		   }

		   bool IsValidKey(String^ key) {
			   // Kiểm tra độ dài key
			   if (key->Length < 8) {
				   return false;
			   }

			   // Kiểm tra từng ký tự trong key
			   for each (char c in key) {
				   if (!isxdigit(c)) {
					   return false; // Nếu không phải ký tự hex, key không hợp lệ
				   }
			   }

			   return true; // Key hợp lệ nếu qua được tất cả các kiểm tra
		   }
	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		// Lấy dữ liệu người dùng nhập vào từ textBox1

	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		//String^ key = textBox1->Text->Trim(); // Key DES
		//String^ data2 = richTextBox2->Text;

		string decryptedData = msclr::interop::marshal_as<std::string>(textBox1->Text->Trim());
		string data2 = msclr::interop::marshal_as<std::string>(richTextBox2->Text);

		auto start_decrypt = high_resolution_clock::now();
		string test12 = DES_Decrypt(stringToBinary(data2), decryptedData);
		auto stop_decrypt = high_resolution_clock::now();
		auto duration_decrypt = duration_cast<microseconds>(stop_decrypt - start_decrypt);


		richTextBox3->Text = gcnew String(test12.c_str());

		textBox3->Text = duration_decrypt.count().ToString();
		//richTextBox2->Text = key + data ;

		//string vanbanmahoa = newDes.binaryToString(newDes.DES_Encrypt(key, data));

	   // richTextBox2->Text = gcnew String(vanbanmahoa.c_str());




	}
private: System::Void richTextBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void richTextBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}

