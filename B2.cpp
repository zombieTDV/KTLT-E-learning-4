#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;

// Prototype
string getFirstName(const string &full);
string getLastName(const string &full);
void findNguyen(const string names[], int n);
void countDistinctLast(const string names[], int n);
void findAorT(const string names[], int n);


string trim(const string &s);
string reduceSpaces(const string &s);
string normalize(const string &raw);
void output_string(const string &s);

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

// Giảm nhiều khoảng trắng liên tiếp thành một
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

// Chuẩn hóa theo yêu cầu: trim, reduceSpaces, capitalize sau dấu câu, thêm " E-learning '04'"
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
    s += " E-learning '04'";
    return s;
}

// Trả về họ (từ đầu đến trước dấu cách đầu tiên)
string getFirstName(const string &full) {
    size_t pos = full.find(' ');
    if (pos == string::npos) return full;
    return full.substr(0, pos);
}

// Trả về tên (từ sau dấu cách cuối cùng đến hết)
string getLastName(const string &full) {
    size_t pos = full.rfind(' ');
    if (pos == string::npos) return full;
    return full.substr(pos + 1);
}

// a) Danh sách sinh viên có họ "Nguyen"
void findNguyen(const string names[], int n) {
    cout << "\na) Danh sách sinh viên có họ Nguyễn:\n";
    for (int i = 0; i < n; ++i) {
        if (getFirstName(names[i]) == "Nguyễn") {
            cout << "  " << names[i] << '\n';
        }
    }
}

// b) Đếm số họ khác nhau
void countDistinctLast(const string names[], int n) {
    // Mảng tạm lưu các họ đã gặp
    string distinct[100];  // giả sử n ≤ 100
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        string last = getFirstName(names[i]);
        // Kiểm tra đã có trong distinct chưa
        bool found = false;
        for (int j = 0; j < cnt; ++j) {
            if (distinct[j] == last) {
                found = true;
                break;
            }
        }
        if (!found) {
            distinct[cnt++] = last;
        }
    }
    cout << "\nb) Số họ khác nhau: " << cnt << '\n';
}

// c) Tên bắt đầu bằng A hoặc T (không phân biệt hoa thường)
void findAorT(const string names[], int n) {
    cout << "\nc) Sinh viên có tên bắt đầu bằng A hoặc T:\n";
    for (int i = 0; i < n; ++i) {
        string last = getLastName(names[i]);
        if (!last.empty()) {
            char c = std::toupper(static_cast<unsigned char>(last[0]));
            if (c == 'A' || c == 'T') {
                cout << "  " << names[i] << '\n';
            }
        }
    }
}



int main() {
    int n;
    cout << "Nhập số sinh viên n: ";
    cin >> n;
    cin.ignore();

    // Dùng mảng động để lưu tên
    string *names = new string[n];
    cout << "Nhập lần lượt Họ và Tên (mỗi dòng một sinh viên):\n";
    for (int i = 0; i < n; ++i) {
        std::getline(cin, names[i]);
    }

    findNguyen(names, n);
    countDistinctLast(names, n);
    findAorT(names, n);

    delete[] names;
    return 0;
}