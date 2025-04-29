#include <iostream>
#include <string>
#include <cctype>

using std::cout;
using std::cin;
using std::string;

string trim(const string &s);
string reduceSpaces(const string &s);
string normalize(const string &raw);
void output_string(const string &s);

int main() {
    cout << "Nhập một chuỗi bất kỳ:\n";
    string line;
    std::getline(cin, line);

    string result = normalize(line);
    output_string(result);

    return 0;
}

// Loại bỏ khoảng trắng đầu và cuối
string trim(const string &s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }
    if (start == s.size()) return "";

    size_t end = s.size() - 1;
    while (end > start && std::isspace(static_cast<unsigned char>(s[end]))) {
        --end;
    }
    return s.substr(start, end - start + 1);
}

// Bỏ nhiều khoảng trắng liên tiếp thành một
string reduceSpaces(const string &s) {
    string out;
    bool inSpace = false;
    for (char ch : s) {
        if (std::isspace(static_cast<unsigned char>(ch))) {
            if (!inSpace) {
                out.push_back(' ');
                inSpace = true;
            }
        } else {
            out.push_back(ch);
            inSpace = false;
        }
    }
    return out;
}

// Chuẩn hóa theo yêu cầu: trim, reduceSpaces, capitalize sau dấu câu, thêm " E-learning ‘04’"
string normalize(const string &raw) {
    string s = trim(raw);
    s = reduceSpaces(s);

    bool capNext = true;
    for (size_t i = 0; i < s.size(); ++i) {
        char &c = s[i];
        if (capNext && std::isalpha(static_cast<unsigned char>(c))) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
            capNext = false;
        } else {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
        if (c == '.' || c == '?' || c == '!') {
            capNext = true;
        }
    }
    s += " E-learning ‘04’";
    return s;
}

// Xuất chuỗi
void output_string(const string &s) {
    cout << "\nKết quả sau khi chuẩn hóa:\n";
    cout << s << '\n';
}
