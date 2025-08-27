#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

// Hàm tính GCD - dùng trong thuật toán mở rộng Euclid
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Hàm tính mũ với modulo
int powerMod(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Tạo khóa RSA (chọn các số nguyên tố nhỏ để đơn giản hóa)
void generateKeys(int &n, int &e, int &d) {
    // Chọn 2 số nguyên tố p và q
    int p = 61;
    int q = 53;
    n = p * q;
    int phi = (p - 1) * (q - 1);

    // Chọn e sao cho 1 < e < phi và gcd(e, phi) = 1
    e = 2;
    while (e < phi && gcd(e, phi) != 1) {
        e++;
    }

    // Tìm d sao cho (d * e) % phi = 1
    int k = 1;
    while ((1 + k * phi) % e != 0) {
        k++;
    }
    d = (1 + k * phi) / e;
}

// Mã hóa một ký tự bằng khóa công khai (n, e)
int encryptChar(char ch, int n, int e) {
    return powerMod(static_cast<int>(ch), e, n);
}

// Giải mã một ký tự bằng khóa bí mật (n, d)
char decryptChar(int cipher, int n, int d) {
    return static_cast<char>(powerMod(cipher, d, n));
}

// Mã hóa chuỗi
vector<int> encryptMessage(const string& msg, int n, int e) {
    vector<int> encrypted;
    for (char ch : msg) {
        encrypted.push_back(encryptChar(ch, n, e));
    }
    return encrypted;
}

// Giải mã chuỗi
string decryptMessage(const vector<int>& cipher, int n, int d) {
    string decrypted;
    for (int c : cipher) {
        decrypted += decryptChar(c, n, d);
    }
    return decrypted;
}

// Hàm nhập thông điệp từ người dùng
string input() {
    string msg;
    cout << "Enter a message: ";
    cin.ignore(); // Để bỏ qua ký tự newline trước đó
    getline(cin, msg);
    return msg;
}

// Hàm xuất thông tin ra màn hình
void output(const vector<int>& encrypted, const string& decrypted, int n, int e, int d) {
    cout << "Public Key: (" << n << ", " << e << ")" << endl;
    cout << "Private Key: (" << n << ", " << d << ")" << endl;

    cout << "Encrypted message: ";
    for (int c : encrypted) {
        cout << c << " ";
    }
    cout << endl;

    cout << "Decrypted message: " << decrypted << endl;
}

int main() {
    int n, e, d;
    generateKeys(n, e, d);

    string msg = input(); // Nhập thông điệp từ người dùng

    vector<int> encrypted = encryptMessage(msg, n, e);
    string decrypted = decryptMessage(encrypted, n, d);

    output(encrypted, decrypted, n, e, d); // Xuất thông tin ra màn hình

    return 0;
}