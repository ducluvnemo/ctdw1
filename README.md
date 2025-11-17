 Chuong trinh tao Index tu van ban

## Mo ta
Chuong trinh doc mot file van ban va tao bang chi dan (Index) cho cac tu trong van ban.  
Moi tu chi xuat hien 1 lan trong Index, keo theo so lan xuat hien va danh sach cac dong co tu do.  

- Bo qua cac **stop words** trong file `stopw.txt`  
- Bo qua cac **danh tu rieng** (viet hoa dau tu, khong dung sau dau cham)  
- Tat ca tu duoc chuyen ve chu thuong  
- Sap xep theo thu tu tu dien

---

## File trong du an

- `index.c` : Ma nguon chinh  
- `vanban.txt` : File van ban de xu ly  
- `stopw.txt` : Danh sach stop words  
- `alice30.txt` : File van ban khac de test  
- `Makefile` (neu co) : de build chuong trinh  
- `README.md` : File huong dan nay

---

## Cach build

1. Mo terminal trong thu muc `Bai1`  
2. Compile chuong trinh:

```bash
gcc index.c -o index

## Cach chay chuong trinh
./index <ten_file_vanban> <ten_file_ketqua>

