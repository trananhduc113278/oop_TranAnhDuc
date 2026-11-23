#include <iostream>
#include <string>
using namespace std;
class khach_hang{
	string hoten;
	string diachi;
	string dienthoai;
	string masothue;
	
	public:
		void nhap() {
        cout << "Nhap ten khach hang: ";
        getline(cin, hoten);
        cout << "Nhap dia chi: ";
        getline(cin, diachi);
        cout << "Nhap dien thoai: ";
        getline(cin, dienthoai);
        cout << "Nhap ma so thue: ";
        getline(cin, masothue);
    }
    void xuat() {
        cout << "Ban cho: " << hoten << endl;
        cout << "Dia chi: " << diachi << endl;
        cout << "Dien thoai: " << dienthoai << "\t\tMST: " << masothue << endl;
    }
};
class hang_hoa {
    string tenhang;
    string donvitinh;
    int soluong;
    long long dongia;
    
    public:
    void nhap() {
        cout << " Ten hang hoa: ";
        getline(cin, tenhang);
        cout << " Don vi tinh: ";
        getline(cin, donvitinh);
        cout << " So luong: ";
        cin >> soluong;
        cout << " Don gia: ";
        cin >> dongia;
        cin.ignore();
    }
     long long tinhthanhtien() {
        return soluong * dongia;
    }
     void xuat(int stt) {
        cout << stt << "\t" << tenhang << "\t\t" << donvitinh << "\t"
             << soluong << "\t" << dongia << "\t\t" << tinhthanhtien() << endl;
    }
};
class HOA_DON {
    khach_hang x;
    int smh;
    hang_hoa *a;
    string sohoadon;
    string ngaylap;
    int thueGTGT;
    
    public:
    HOA_DON() {
        smh = 0;
        a = NULL;
        thueGTGT = 0;
    }
    ~HOA_DON() {
        delete[] a;
    }
    
    void nhap() {
        cout << "Nhap so hoa don: ";
        getline(cin, sohoadon);
        cout << "Nhap ngay lap: ";
        getline(cin, ngaylap);
        x.nhap();
        cout << "Nhap so mat hang: ";
        cin >> smh;
        cin.ignore();
        a = new hang_hoa[smh];
        for (int i = 0; i < smh; i++) {
            cout << "Nhap mat hang thu " << i + 1 << ":" << endl;
            a[i].nhap();
        }
        cout << "Nhap thue GTGT (%): ";
        cin >> thueGTGT;
    }
    long long tinhcongtienhang() {
        long long tong = 0;
        for (int i = 0; i < smh; i++) {
            tong += a[i].tinhthanhtien();
        }
        return tong;
    }
    long long tinhtienthue() {
        return tinhcongtienhang() * thueGTGT / 100;
    }
    long long tinhtongthanhtoan() {
        return tinhcongtienhang() + tinhtienthue();
    }
    void xuat() {
        cout << "\n=====================================================================" << endl;
        cout << "\t\t\tHOA DON BAN HANG" << endl;
        cout << "=====================================================================" << endl;
        cout << "So HD: " << sohoadon << "\t\tNgay: " << ngaylap << endl;
        x.xuat();
        cout << "---------------------------------------------------------------------" << endl;
        cout << "STT\tTen hang hoa\t\tDVT\tSL\tDon gia\t\tThanh tien" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        for (int i = 0; i < smh; i++) {
            a[i].xuat(i + 1);
        }
        cout << "---------------------------------------------------------------------" << endl;
        cout << "\t\t\t\t\tCong tien hang: " << tinhcongtienhang() << endl;
        cout << "\t\tThue GTGT (%): " << thueGTGT << "%\tTien thue: " << tinhtienthue() << endl;
        cout << "---------------------------------------------------------------------" << endl;
        cout << "\t\t\t\t\tTONG THANH TOAN: " << tinhtongthanhtoan() << endl;
        cout << "=====================================================================" << endl;
    }
};
int main() {
    HOA_DON hd;
    hd.nhap();
    hd.xuat();
    return 0;
}
