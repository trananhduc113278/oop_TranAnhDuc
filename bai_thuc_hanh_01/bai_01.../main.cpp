#include <iostream>
#include <string>
using namespace std;
class Xe {
private:
    int maXe;
    string loaiXe;
    int gioVao;
    int thoiGianDo;
    double phiDoXe;
    bool dangChiemCho;
public:
    Xe() {
        maXe = 0;
        loaiXe = "Bicycle";
        gioVao = 0;
        thoiGianDo = 1;
        phiDoXe = 0;
        dangChiemCho = false;
    }
    Xe(int ma, const string& loai, int gio, int thoiLuong) {
        maXe = ma;
        loaiXe = chuanHoaLoaiXe(loai);
        gioVao = gio;
        thoiGianDo = thoiLuong;
        phiDoXe = 0;
        dangChiemCho = true;
        tinhPhiDoXe();
    }
