#include <iostream> // Thu vien cho phep su dung cac ham nhap xuat
using namespace std;
struct Ngay { // Khai bao cau truc Ngay
    int ngay, thang, nam; // Truong ngay, thang, nam
};
struct SinhVien {  // Khai bao cau truc SinhVien
    char maSV[9]; // Ma so sinh vien
    char hoTen[50]; // Ho va ten sinh vien
    int gioiTinh; // Gioi tinh: 1 la Nam, 0 la Nu
    Ngay ngaySinh; // Ngay sinh theo cau truc Ngay
    char diaChi[100]; // Dia chi sinh vien
    char lop[12]; // Lop cua sinh vien
    char khoa[7]; // Khoa cua sinh vien
};
struct Node { // Khai bao cau truc Node
    SinhVien data; // Du lieu la mot SinhVien
    Node *link; // Con tro toi node tiep theo
};
struct List { // Khai bao cau truc List
    Node *first; // Con tro toi node dau tien
    Node *last; // Con tro toi node cuoi cung
};
void khoitaodanhsachrong(List &list) { // Ham khoi tao danh sach rong
    list.first = nullptr; // Gan first la nullptr
    list.last = nullptr; // Gan last la nullptr
}
int sosanhchuoi(const char* str1, const char* str2) { // Ham so sanh chuoi
    int i = 0; // Khoi tao bien dem
    while (str1[i] != '\0' && str2[i] != '\0') { // Lap khi hai chuoi chua ket thuc
        if (str1[i] != str2[i]) { // Neu ky tu khong giong nhau
            return str1[i] - str2[i]; // Tra ve hieu cua ky tu
        }
        i++; // Tang bien dem
    }
    return str1[i] - str2[i]; // Tra ve ket qua so sanh
}
Node* taosinhvien (const SinhVien &sv) { // Ham tao node SinhVien moi
    Node* newNode = new Node; // Cap phat bo nho cho node moi
    newNode->data = sv; // Gan du lieu cho node moi
    newNode->link = nullptr; // Node moi chua co lien ket
    return newNode; // Tra ve node moi
}
void themsinhvienvaodanhsach(List &list, const SinhVien &sv) { // Ham them sinh vien vao danh sach
    Node* newNode = taosinhvien(sv); // Tao node moi chua sinh vien
    if (!list.first) { // Neu danh sach rong
        list.first = list.last = newNode; // Gan node moi la dau va cuoi
        return;
    }
    if (sosanhchuoi(newNode->data.maSV, list.first->data.maSV) < 0) { // Neu maSV cua node moi nho hon maSV cua node dau
        newNode->link = list.first; // Gan link cua node moi tro den node dau
        list.first = newNode; // Gan node moi thanh node dau
        return;
    }
    Node *current = list.first; // Bat dau tu node dau
    while (current->link && sosanhchuoi(current->link->data.maSV, sv.maSV) < 0) { // Tim vi tri thich hop de chen
        current = current->link;
    }
    newNode->link = current->link; // Chen node moi vao vi tri tim duoc
    current->link = newNode;
    if (newNode->link == nullptr) { // Neu node moi la node cuoi
        list.last = newNode; // Cap nhat node cuoi
    }
}
void xuatdanhsach(const List &list) { // Ham xuat danh sach sinh vien
    Node *current = list.first; // Bat dau tu node dau
    while (current) { // Lap qua cac node
        const SinhVien &sv = current->data; // Lay du lieu cua sinh vien
        cout << "MaSV: " << sv.maSV << ", HoTen: " << sv.hoTen
             << ", GioiTinh: " << (sv.gioiTinh ? "Nam" : "Nu")
             << ", NgaySinh: " << sv.ngaySinh.ngay << "/" << sv.ngaySinh.thang << "/" << sv.ngaySinh.nam
             << ", DiaChi: " << sv.diaChi << ", Lop: " << sv.lop
             << ", Khoa: " << sv.khoa << endl;
        current = current->link; // Di chuyen den node tiep theo
    }
}
void timsinhviencocungngaysinhnhat(const List &list) { // Ham tim sinh vien co cung ngay sinh nhat
    bool found = false; // Bien kiem tra neu tim thay
    for (Node *p = list.first; p != nullptr; p = p->link) { // Duyet tung sinh vien
        bool hasDuplicate = false; // Kiem tra neu co sinh vien trung ngay sinh
        for (Node *q = p->link; q != nullptr; q = q->link) { // So sanh sinh vien hien tai voi cac sinh vien sau do
            if (p->data.ngaySinh.ngay == q->data.ngaySinh.ngay &&
                p->data.ngaySinh.thang == q->data.ngaySinh.thang &&
                p->data.ngaySinh.nam == q->data.ngaySinh.nam) { // Neu trung ngay sinh
                if (!hasDuplicate) { // Neu chua in sinh vien dau tien co ngay sinh trung
                    cout << "Cac sinh vien co ngay sinh " << p->data.ngaySinh.ngay << "/"
                         << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << ":\n";
                    cout << "MaSV: " << p->data.maSV << ", HoTen: " << p->data.hoTen << endl;
                    hasDuplicate = true; // Da tim thay sinh vien trung ngay sinh
                    found = true;
                }
                cout << "MaSV: " << q->data.maSV << ", HoTen: " << q->data.hoTen << endl; // In sinh vien trung ngay sinh
            }
        }
    }
    if (!found) { // Neu khong tim thay sinh vien trung ngay sinh
        cout << "Khong tim thay sinh vien cung ngay sinh." << endl;
    }
}
void xoasinhviencocungngaysinh(List &list) { // Ham xoa sinh vien co cung ngay sinh
    Node *prev = nullptr, *p = list.first; // Khoi tao bien con tro
    while (p != nullptr) { // Duyet qua danh sach
        bool hasDuplicate = false; // Kiem tra neu co sinh vien trung ngay sinh
        Node *current = p->link, *prevDup = p; // Bat dau tu node hien tai
        while (current != nullptr) { // So sanh voi cac node sau
            if (p->data.ngaySinh.ngay == current->data.ngaySinh.ngay &&
                p->data.ngaySinh.thang == current->data.ngaySinh.thang &&
                p->data.ngaySinh.nam == current->data.ngaySinh.nam) { // Neu trung ngay sinh
                hasDuplicate = true;
                Node *temp = current; // Xoa node trung ngay sinh
                prevDup->link = current->link;
                current = current->link;
                delete temp;
            } else {
                prevDup = current;
                current = current->link;
            }
        }
        if (hasDuplicate) { // Xoa sinh vien dau tien co ngay sinh trung
            if (prev == nullptr) { 
                list.first = p->link;
                delete p;
                p = list.first;
            } else { 
                prev->link = p->link;
                delete p;
                p = prev->link;
            }
        } else {
            prev = p;
            p = p->link;
        }
    }
    if (!list.first) { // Neu danh sach rong
        list.last = nullptr;
    }
}
void giaiphongbonho(List &list) { // Ham giai phong bo nho cho danh sach
    while (list.first) { // Lap qua tung node
        Node* temp = list.first; // Lay node dau
        list.first = list.first->link; // Di chuyen den node tiep theo
        delete temp; // Xoa node
    }
    list.last = nullptr; // Cap nhat node cuoi la nullptr
}
int main() {
    List list;
    khoitaodanhsachrong(list);
    SinhVien sv1 = {"20224428", "Nguyen Van An", 1, {01, 1, 2004}, "Ha Tinh", "K67", "IOT"};
    SinhVien sv2 = {"20224402", "Nguyen Van An", 1, {02, 1, 2004}, "Vinh Phuc", "K67", "IOT"};
    SinhVien sv3 = {"20224429", "Tran Quang Anh", 1, {03, 1, 2004}, "Phu Tho", "K67", "IOT"};
    SinhVien sv4 = {"20224416", "Nguyen Phan Anh", 1, {04, 1, 2004}, "Ha Noi", "K67", "IOT"};
    SinhVien sv5 = {"20224430", "Truong Quoc Anh", 1, {05, 1, 2004}, "Vung Tau", "K67", "IOT"};
    SinhVien sv6 = {"20224403", "Le Duc Anh", 1, {06, 1, 2004}, "Nam Dinh", "K67", "IOT"};
    SinhVien sv7 = {"20224417", "Nguyen Cong Bach", 1, {07, 1, 2004}, "Ha Giang", "K67", "IOT"};
    SinhVien sv8 = {"20224404", "Hoang Nguyen Bao", 1, {13, 1, 2004}, "Ha Noi", "K67", "IOT"};
    SinhVien sv9 = {"20224431", "Pham Manh Cuong", 1, {12, 1, 2004}, "Hai Phong", "K67", "IOT"};
    SinhVien sv10 = {"20224419", "Nguyen Tat Dat", 1, {10, 1, 2004}, "Ha Noi", "K67", "IOT"};
    SinhVien sv11= {"20224432", "Do Thanh Dat", 1, {11, 1, 2004}, "Ha Noi", "K67", "IOT"};
    SinhVien sv12 = {"20224405", "Bui Ngoc Dat", 1, {01, 1, 2004}, "Hai Phong", "K67", "IOT"};
    SinhVien sv13= {"20224420", "Kieu Tuan Dinh", 1, {07, 1, 2004}, "Thai Nguyen", "K67", "IOT"};
    SinhVien sv14= {"20224434", "Nguyen Dong Truong Duc", 1, {05, 1, 2004}, "Dak Lak", "K67", "IOT"};
    themsinhvienvaodanhsach(list, sv1);
    themsinhvienvaodanhsach(list, sv2);
    themsinhvienvaodanhsach(list, sv3);
    themsinhvienvaodanhsach(list, sv4);
    themsinhvienvaodanhsach(list, sv5);
    themsinhvienvaodanhsach(list, sv6);
    themsinhvienvaodanhsach(list, sv7);
    themsinhvienvaodanhsach(list, sv8);
    themsinhvienvaodanhsach(list, sv9);
    themsinhvienvaodanhsach(list, sv10);
    themsinhvienvaodanhsach(list, sv11);
    themsinhvienvaodanhsach(list, sv12);
    themsinhvienvaodanhsach(list, sv13);
    themsinhvienvaodanhsach(list, sv14);
    cout << "Danh sach sinh vien:\n";
    xuatdanhsach(list);
    cout << "\nTim sinh vien co cung ngay sinh:\n";
    timsinhviencocungngaysinhnhat(list);
    cout << "\nXoa sinh vien co cung ngay sinh:\n";
    xoasinhviencocungngaysinh(list);
    cout << "\nDanh sach sinh vien sau khi xoa:\n";
    xuatdanhsach(list);
    giaiphongbonho(list);
    return 0;
}










