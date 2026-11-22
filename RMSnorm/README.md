# RMSNorm 

## 1. Cấu trúc thư mục

Thư mục gốc của project là thư mục chứa `Makefile`, `include/`, `source/` và `test/`.

```
<thư-mục-gốc>/
├── Makefile
├── include/
│   ├── config.h           hằng số 
│   ├── data_type.h        kiểu bf16 và chuyển đổi bf16 <-> fp32
│   ├── data_structure.h   struct WTB_format, RAB_format, registers_format
│   ├── load.h
│   ├── store.h   
│   └── kernel.h           rmsnorm
├── source/
│   ├── data_type.c
│   ├── load.c
│   ├── store.c  
│   └── kernel.c
└── test/
    └── main.c             chương trình chạy thử
```

## 2. Các bước chạy (Windows, từ lúc mở PowerShell)

### Bước 1. Mở PowerShell

Nhấn phím Windows, gõ `PowerShell`, nhấn Enter.

### Bước 2. Kiểm tra đã có gcc, make và git

```powershell
gcc --version
```

```powershell
mingw32-make --version
```

```powershell
git --version
```

Mỗi lệnh phải in ra số phiên bản. Nếu lệnh nào báo `is not recognized` thì làm theo mục 3 (cài công cụ) rồi quay lại.

### Bước 3. Lấy code từ GitHub

```powershell
git clone https://github.com/htranngochuy/Deepseek.git
```

### Bước 4. Vào thư mục gốc của project

```powershell
cd Deepseek
```

### Bước 5. Kiểm tra đang ở đúng thư mục

```powershell
dir
```

Phải thấy `Makefile`, `include`, `source`, `test`.

### Bước 6. Biên dịch và chạy

```powershell
mingw32-make run
```
