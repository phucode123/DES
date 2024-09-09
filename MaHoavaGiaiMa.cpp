#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class DES {
private:
    int dodai = 0;
    // Initial permutation table for 64-bit blocks
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

    // Biến thành viên và các hằng số khác của DES
public:
    DES() {
        // Khởi tạo các giá trị mặc định hoặc đọc từ tập tin (nếu cần)
    }

    // Các phương thức để mã hóa và giải mã
    string padToMultipleOf64(string input) {
        // Cài đặt hàm padToMultipleOf64 ở đây
        int remainder = input.length() % 64;
        int padding_length = (remainder == 0) ? 64 : (64 - remainder);
        // Thêm một ký tự '1' đầu tiên
        input += '1';
        // Thêm các ký tự '0' vào cuối
        input.append(padding_length - 1, '0');
        return input;
    }

    string stringToBinary(string input) {
        // Cài đặt hàm stringToBinary ở đây
        string binary_string = "";
        for (char& c : input)
        {
            binary_string += bitset<8>(c).to_string();
        }
        return binary_string;
    }

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
        return plaintext.substr(0, dodai);
    }
};


