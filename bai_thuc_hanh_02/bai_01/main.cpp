#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

class phuong_tien {
private:
int ma_xe;
string loai_xe;
int gio_vao;
int tg_do;

public:
phuong_tien();
phuong_tien(int ma, string loai, int gio, int tg);

int lay_ma_xe() const;
string lay_loai_xe() const;
int lay_gio_vao() const;
int lay_tg_do() const;

void dat_ma_xe(int ma);
void dat_loai_xe(const string& loai);
void dat_gio_vao(int gio);
void dat_tg_do(int tg);

double tinh_phi() const;
void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
: ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }
int phuong_tien::lay_gio_vao() const { return gio_vao; }
int phuong_tien::lay_tg_do() const { return tg_do; }

void phuong_tien::dat_ma_xe(int ma) { ma_xe = ma; }
void phuong_tien::dat_loai_xe(const string& loai) { loai_xe = loai; }
void phuong_tien::dat_gio_vao(int gio) { gio_vao = gio; }
void phuong_tien::dat_tg_do(int tg) { tg_do = tg; }

double phuong_tien::tinh_phi() const {
double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
double tong = 0;
for (int h = 0; h < tg_do; ++h) {
if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
else tong += gia * 0.90;
}
return tong;
}

void phuong_tien::hien_thi() const {
cout << " ID: " << ma_xe << " | " << loai_xe
<< " | " << gio_vao << "h | " << tg_do << "h"
<< " | Phi: $" << fixed << setprecision(2) << tinh_phi() << "\n";
}


class bai_xe {
private:
int ma_bai;
char kich_thuoc;
static const int MAX_XE = 3; 
phuong_tien ds_xe[MAX_XE]; 
int so_xe; 

public:
bai_xe();
bai_xe(int ma, char kt);

int lay_ma() const;
char lay_kich_thuoc() const;
int lay_so_xe() const;
int suc_chua() const; 
bool day() const; 

int tim_xe(int ma_xe) const; 
bool chua(int ma_xe) const;
bool them(const phuong_tien& v);
bool xoa(int ma_xe); 

void hien_thi() const;
void hien_thi_theo_loai(const string& loai) const;
bool co_loai(const string& loai, int& dem, double& tong) const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), so_xe(0) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), so_xe(0) {}

int bai_xe::lay_ma() const { return ma_bai; }
char bai_xe::lay_kich_thuoc() const { return kich_thuoc; }
int bai_xe::lay_so_xe() const { return so_xe; }

int bai_xe::suc_chua() const {
return (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
}

bool bai_xe::day() const { return so_xe >= suc_chua(); }

int bai_xe::tim_xe(int ma_xe) const {
for (int i = 0; i < so_xe; ++i)
if (ds_xe[i].lay_ma_xe() == ma_xe) return i;
return -1;
}

bool bai_xe::chua(int ma_xe) const { return tim_xe(ma_xe) != -1; }

bool bai_xe::them(const phuong_tien& v) {
if (day()) return false;
ds_xe[so_xe] = v;
++so_xe;
return true;
}

bool bai_xe::xoa(int ma_xe) {
int vt = tim_xe(ma_xe);
if (vt == -1) return false;
for (int i = vt; i < so_xe - 1; ++i) 
ds_xe[i] = ds_xe[i + 1];
--so_xe;
ds_xe[so_xe] = phuong_tien(); 
return true;
}

void bai_xe::hien_thi() const {
cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
<< so_xe << "/" << suc_chua() << " xe\n";
for (int i = 0; i < so_xe; ++i) ds_xe[i].hien_thi();
}

void bai_xe::hien_thi_theo_loai(const string& loai) const {
for (int i = 0; i < so_xe; ++i)
if (ds_xe[i].lay_loai_xe() == loai) ds_xe[i].hien_thi();
}

bool bai_xe::co_loai(const string& loai, int& dem, double& tong) const {
dem = 0; tong = 0;
for (int i = 0; i < so_xe; ++i) {
if (ds_xe[i].lay_loai_xe() == loai) {
++dem;
tong += ds_xe[i].tinh_phi();
}
}
return dem > 0;
}


class SystemInterface {
private:
static const int MAX_BAI = 10; 
bai_xe ds_bai[MAX_BAI]; 
int so_bai; 


int nhap_so(const string& thong_bao, int nho_nhat, int lon_nhat);
char nhap_kich_thuoc();
string nhap_loai_xe();


void tao_bai();
void them_xe();
void xoa_bai();
void lay_xe_ra();
void hien_thi_tat_ca() const;
void hien_thi_theo_bai() const;
void liet_ke_theo_loai() const;
void bao_cao_phi() const;

int tim_bai(int ma_bai) const;

public:
SystemInterface();
void runMenu();
bool ma_bai_ton_tai(int ma) const;
bool ma_xe_ton_tai(int ma) const;
int sinh_id_ngau_nhien() const;
};

SystemInterface::SystemInterface() : so_bai(0) {
srand((unsigned)time(0));
}

int SystemInterface::tim_bai(int ma_bai) const {
for (int i = 0; i < so_bai; ++i)
if (ds_bai[i].lay_ma() == ma_bai) return i;
return -1;
}

bool SystemInterface::ma_bai_ton_tai(int ma) const {
return tim_bai(ma) != -1;
}

bool SystemInterface::ma_xe_ton_tai(int ma) const {
for (int i = 0; i < so_bai; ++i)
if (ds_bai[i].chua(ma)) return true;
return false;
}

int SystemInterface::sinh_id_ngau_nhien() const {
int id;
do {
id = 1000 + rand() % 9000; 
} while (ma_bai_ton_tai(id) || ma_xe_ton_tai(id));
return id;
}

int SystemInterface::nhap_so(const string& thong_bao, int nho_nhat, int lon_nhat) {
int x;
while (true) {
cout << thong_bao;
if (cin >> x && x >= nho_nhat && x <= lon_nhat) {
cin.ignore(numeric_limits<streamsize>::max(), '\n');
return x;
}
if (cin.eof()) { cout << "\nHet du lieu nhap!\n"; exit(0); }
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Nhap sai! Hay nhap so nguyen trong khoang ["
<< nho_nhat << ", " << lon_nhat << "].\n";
}
}

char SystemInterface::nhap_kich_thuoc() {
string s;
while (true) {
cout << "Kich thuoc (S/M/L): ";
if (cin >> s && s.size() == 1) {
char c = (char)toupper((unsigned char)s[0]);
if (c == 'S' || c == 'M' || c == 'L') {
cin.ignore(numeric_limits<streamsize>::max(), '\n');
return c;
}
}
if (cin.eof()) { cout << "\nHet du lieu nhap!\n"; exit(0); }
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Nhap sai! Chi nhan S, M hoac L.\n";
}
}

string SystemInterface::nhap_loai_xe() {
string s;
while (true) {
cout << "Loai (Car/Motorcycle/Bicycle): ";
if (cin >> s && (s == "Car" || s == "Motorcycle" || s == "Bicycle")) {
cin.ignore(numeric_limits<streamsize>::max(), '\n');
return s;
}
if (cin.eof()) { cout << "\nHet du lieu nhap!\n"; exit(0); }
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Nhap sai! Chi nhan Car, Motorcycle hoac Bicycle.\n";
}
}

void SystemInterface::tao_bai() {
if (so_bai >= MAX_BAI) {
cout << "Het cho! Da dat toi da " << MAX_BAI << " bai.\n";
return;
}
int ma = nhap_so("Ma bai: ", 1, 999999);
char kt = nhap_kich_thuoc();
if (ma_bai_ton_tai(ma)) {
int moi = sinh_id_ngau_nhien();
cout << "Canh bao: ma bai " << ma << " da ton tai! Tu dong gan ma moi: " << moi << "\n";
ma = moi;
}
ds_bai[so_bai] = bai_xe(ma, kt);
++so_bai;
cout << "Da tao bai " << ma << "\n";
}

void SystemInterface::them_xe() {
if (so_bai == 0) {
cout << "Chua co bai do nao! Hay tao bai truoc.\n";
return;
}
int ma = nhap_so("Ma xe: ", 1, 999999);
string loai = nhap_loai_xe();
int gio = nhap_so("Gio vao (0-23): ", 0, 23);
int tg = nhap_so("Thoi luong (1-23): ", 1, 23);

if (ma_xe_ton_tai(ma)) {
int moi = sinh_id_ngau_nhien();
cout << "Canh bao: ma xe " << ma << " da ton tai! Tu dong gan ma moi: " << moi << "\n";
ma = moi;
}

phuong_tien v(ma, loai, gio, tg);
for (int i = 0; i < so_bai; ++i) {
if (!ds_bai[i].day()) {
ds_bai[i].them(v);
cout << "Da them xe " << ma << " vao bai " << ds_bai[i].lay_ma()
<< " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
return;
}
}
cout << "Canh bao: tat ca cac bai da day!\n";
}

void SystemInterface::xoa_bai() {
int ma = nhap_so("Ma bai can xoa: ", 1, 999999);
int vt = tim_bai(ma);
if (vt == -1) {
cout << "Khong tim thay bai " << ma << "\n";
return;
}
for (int i = vt; i < so_bai - 1; ++i) 
ds_bai[i] = ds_bai[i + 1];
--so_bai;
ds_bai[so_bai] = bai_xe();
cout << "Da xoa bai " << ma << "\n";
}


void SystemInterface::lay_xe_ra() {
int ma = nhap_so("Ma xe can lay ra: ", 1, 999999);
for (int i = 0; i < so_bai; ++i) {
if (ds_bai[i].xoa(ma)) {
cout << "Da lay xe " << ma << " ra khoi bai " << ds_bai[i].lay_ma() << "\n";
return;
}
}
cout << "Khong tim thay xe\n";
}


void SystemInterface::hien_thi_tat_ca() const {
if (so_bai == 0) {
cout << "Chua co bai do nao.\n";
return;
}
for (int i = 0; i < so_bai; ++i) ds_bai[i].hien_thi();
}


void SystemInterface::hien_thi_theo_bai() const {
// hàm const nên không dùng nhap_so (không const) -> nhập trực tiếp có kiểm tra
int ma;
while (true) {
cout << "Ma bai: ";
if (cin >> ma) {
cin.ignore(numeric_limits<streamsize>::max(), '\n');
break;
}
if (cin.eof()) { cout << "\nHet du lieu nhap!\n"; exit(0); }
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Nhap sai! Hay nhap so nguyen.\n";
}
int vt = tim_bai(ma);
if (vt == -1) cout << "Khong tim thay bai " << ma << "\n";
else ds_bai[vt].hien_thi();
}

void SystemInterface::liet_ke_theo_loai() const {
string loai;
while (true) {
cout << "Loai xe (Car/Motorcycle/Bicycle): ";
if (cin >> loai && (loai == "Car" || loai == "Motorcycle" || loai == "Bicycle")) {
cin.ignore(numeric_limits<streamsize>::max(), '\n');
break;
}
if (cin.eof()) { cout << "\nHet du lieu nhap!\n"; exit(0); }
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Nhap sai! Chi nhan Car, Motorcycle hoac Bicycle.\n";
}
bool thay = false;
for (int i = 0; i < so_bai; ++i) {
int dem; double tong;
if (ds_bai[i].co_loai(loai, dem, tong)) {
cout << "Bai " << ds_bai[i].lay_ma() << ":\n";
ds_bai[i].hien_thi_theo_loai(loai);
thay = true;
}
}
if (!thay) cout << "Khong co xe loai " << loai << "\n";
}

void SystemInterface::bao_cao_phi() const {
const int SO_LOAI = 3;
string loai_arr[SO_LOAI] = {"Car", "Motorcycle", "Bicycle"};

cout << "--- Toan he thong ---\n";
for (int t = 0; t < SO_LOAI; ++t) {
int dem = 0; double tong = 0;
for (int i = 0; i < so_bai; ++i) {
int d; double s;
ds_bai[i].co_loai(loai_arr[t], d, s);
dem += d; tong += s;
}
cout << loai_arr[t] << ": ";
if (dem == 0) cout << "khong co xe\n";
else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
}

cout << "--- Theo tung bai ---\n";
for (int i = 0; i < so_bai; ++i) {
cout << "Bai " << ds_bai[i].lay_ma() << ":\n";
for (int t = 0; t < SO_LOAI; ++t) {
int d; double s;
ds_bai[i].co_loai(loai_arr[t], d, s);
cout << " " << loai_arr[t] << ": ";
if (d == 0) cout << "khong co xe\n";
else cout << d << " xe | TB: $" << fixed << setprecision(2) << s / d << "\n";
}
}
}

void SystemInterface::runMenu() {
int chon;
do {
cout << "\n===== QUAN LY BAI DO XE =====\n";
cout << "1. Tao bai do\n";
cout << "2. Them xe\n";
cout << "3. Xoa bai do\n";
cout << "4. Lay xe ra\n";
cout << "5. Hien thi tat ca bai do\n";
cout << "6. Hien thi xe theo bai\n";
cout << "7. Liet ke xe theo loai\n";
cout << "8. Bao cao phi trung binh\n";
cout << "9. Thoat\n";
chon = nhap_so("Chon: ", 1, 9);

switch (chon) {
case 1: tao_bai(); break;
case 2: them_xe(); break;
case 3: xoa_bai(); break;
case 4: lay_xe_ra(); break;
case 5: hien_thi_tat_ca(); break;
case 6: hien_thi_theo_bai(); break;
case 7: liet_ke_theo_loai(); break;
case 8: bao_cao_phi(); break;
case 9: cout << "Tam biet!\n"; break;
default: cout << "Lua chon khong hop le!\n"; break;
}
} while (chon != 9);
}

int main() {
SystemInterface sys;
sys.runMenu();
return 0;
}
