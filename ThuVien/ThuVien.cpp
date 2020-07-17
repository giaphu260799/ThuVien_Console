// 2.cpp : Defines the entry point for the console application.
//
// ThuVien.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <string>
#include <algorithm>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#pragma warning(disable: 4996)
void resizeConsole(int width, int height) // ham thay doi kich thuoc man hinh console
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
char * wchar_to_string(_TCHAR* widechar) //ham chuyen doi TCHAR thanh chuoi
{
	int size = 0;
	while ((char)widechar[size] != '\0') {
		size++;
	}
	size++;
	char * charpointer = new char[size];
	wcstombs(charpointer, widechar, size);
	return charpointer;
}
struct TaiKhoan //struct tai khoan nguoi dung
{
	char id[20];
	char pass[20];
	char chucvu;
};
struct NgayThangNam //struct ngay thang nam
{
	int day;
	int month;
	int year;
};
struct DocGia //struct thong tin doc gia
{
	int MaDocGia;
	char hoten[50];
	char CMND[12];
	NgayThangNam NgaySinh;
	char gioitinh[6];
	char email[35];
	NgayThangNam NgayLapThe;
	NgayThangNam NgayHetHan;
};
struct ThongTinCaNhan //struct thong tin ca nhan cua tai khoan nguoi dung
{
	char id[20];
	char ten[50];
	char cmnd[20];
	char diachi[100];
	char gioitinh[5];
	int ngaysinh;
	int thangsinh;
	int namsinh;
	char tinhtrang;
};
struct Sach //struct thong tin sach
{
	char MaISBN[11];
	char TenSach[50];
	char TacGia[50];
	char NXB[40];
	int NamXB;
	char TheLoai[35];
	char GiaSach[12];
	int SoQuyen;
};
struct PhieuMuonTra //struct thong tin phieu muon sach
{
	int MaDocGia;
	NgayThangNam ngaymuon;
	int sosachmuon;
	char ISBN[10][11];
};
struct NODE //struct NODE trong LIST
{
	void *key; //con tro void co the tro den bat ki kieu du lieu nao
	NODE * pNext;
};
struct LIST //stuct LIST gom so luong phan tu trong list va day danh sach lien ket
{
	int n;
	NODE * pHead;
	NODE * pTail;
};
void KhoiTao(LIST &l) //khoi tao list rong so phan tu la 0
{
	l.n = 0;
	l.pHead = NULL;
}
void TaoNode(NODE *pNew, void *x) //tao node voi nhieu kieu du lieu khac nhau do doi so void* x
{
	pNew->key = x;
	pNew->pNext = NULL;
}
void addLast(LIST &l, void* x) // them node vao cuoi list
{
	NODE *pNew = new NODE;
	TaoNode(pNew, x);
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = pNew;
	}
	else
	{
		l.pTail->pNext = pNew;
		l.pTail = pNew;
	}
}
void DeleteFirst(LIST &l) // xoa node o dau
{
	NODE *p;
	if (l.pHead == l.pTail)
	{
		delete(l.pHead);
		l.pHead = l.pTail = NULL;
	}
	else
	{
		p = l.pHead;
		l.pHead = l.pHead->pNext;
		delete(p);
	}
}
void DeleteLast(LIST &l) //xoa node o cuoi
{

	NODE *p;
	if (l.pHead == l.pTail)
	{
		delete(l.pHead);
		l.pHead = l.pTail = NULL;
	}
	else
	{
		for (p = l.pHead; p->pNext != l.pTail; p = p->pNext);
		delete(l.pTail);
		l.pTail = p;
		p->pNext = NULL;

	}
}
void DeleteMid(NODE *p) //xoa node o giua
{
	NODE *q;
	q = p->pNext;
	*p = *q;
	delete(q);
}
void clrscr() //ham xoa man hinh
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0, 0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}
void textcolor(int x) //ham thay doi mau chu
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
void gotoxy(int x, int y) //ham thay doi vi tri tren man hinh console theo toa do (x, y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1, y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void vekhung(int toadobdx, int toadobdy, int sochucnang) //ve khung xung quanh cac lua chon cua menu, cac chuc nang chinh
{
	textcolor(8);
	int r = sochucnang + 12;
	for (int y = toadobdy; y <= toadobdy + r; y++)
	{
		gotoxy(toadobdx, y);
		printf("%c%c", 219, 219);
		gotoxy(toadobdx + 48, y);
		printf("%c%c", 219, 219);
	}
	for (int x = toadobdx; x <= toadobdx + 49; x++)
	{
		gotoxy(x, toadobdy - 1);
		printf("%c", 219);
		gotoxy(x, toadobdy + r + 1);
		printf("%c", 219);
	}

}
void vekhung2(int toadobdx, int toadobdy, int sochucnang) //ve khung xung quanh cac lua chon cua cac chuc nang con
{
	textcolor(11);
	int r = sochucnang + 8;
	for (int y = toadobdy; y <= toadobdy + r; y++)
	{
		gotoxy(toadobdx, y);
		printf("%c", 179);
		gotoxy(toadobdx + 54, y);
		printf("%c", 179);
	}
	for (int x = toadobdx + 1; x <= toadobdx + 54; x++)
	{
		gotoxy(x, toadobdy - 1);
		printf("%c", 196);
		gotoxy(x, toadobdy + r + 1);
		printf("%c", 196);
	}
	gotoxy(toadobdx, toadobdy - 1); printf("%c", 218);
	gotoxy(toadobdx + 54, toadobdy - 1); printf("%c", 191);
	gotoxy(toadobdx, toadobdy + r + 1); printf("%c", 192);
	gotoxy(toadobdx + 54, toadobdy + r + 1); printf("%c", 217);

}
void khungdocgia(int n) // ve khung danh sach doc gia
{
	textcolor(10);
	gotoxy(65, 2);
	printf("DANH SACH DOC GIA %c %d %c", 175, n, 174);
	textcolor(15);
	for (int i = 1; i <= n - 1; i++)   // ve - - - 
	{
		for (int x = 5; x <= 158; x = x + 2)
		{
			gotoxy(x, 6 + 2 * i);
			printf(" -");
		}
	}
	textcolor(11);
	for (int x = 5; x <= 158; x++)  //3 cot ngang
	{
		gotoxy(x, 3);
		printf("%c", 196);
	}
	for (int x = 5; x <= 158; x++)
	{
		gotoxy(x, 6);
		printf("%c", 196);
	}
	for (int x = 5; x <= 158; x++)  //3 cot ngang
	{
		gotoxy(x, 6 + 2 * n);
		printf("%c", 196);
	}
	for (int y = 4; y <= 5 + 2 * n; y++) //doc dau
	{
		gotoxy(4, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 5 + 2 * n; y++) //doc ho ten
	{
		gotoxy(15, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 5 + 2 * n; y++) //doc cmnd
	{
		gotoxy(46, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 5 + 2 * n; y++) //doc ngay sinh
	{
		gotoxy(59, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 5 + 2 * n; y++) //doc gioi tinh
	{
		gotoxy(74, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 5 + 2 * n; y++) //doc email
	{
		gotoxy(89, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 5 + 2 * n; y++) //doc ngay
	{
		gotoxy(123, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 5 + 2 * n; y++) //doc ngay
	{
		gotoxy(142, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 5 + 2 * n; y++) //doc ngay
	{
		gotoxy(159, y);
		printf("%c", 179);
	}
	gotoxy(4, 3);        //goc trai tren
	printf("%c", 218);
	gotoxy(159, 3);     //goc phai tren
	printf("%c", 191);
	gotoxy(4, 6 + 2 * n);
	printf("%c", 192);    //goc trai duoi
	gotoxy(159, 6 + 2 * n);     //goc trai phai
	printf("%c", 217);
	textcolor(10);
	gotoxy(7, 4);
	printf("1.MA SO");
	gotoxy(26, 4);
	printf("2.HO TEN");
	gotoxy(49, 4);
	printf("3.CMND");
	gotoxy(49, 5);
	printf("(9 so)");
	gotoxy(61, 4);
	printf("4.NGAY SINH");
	gotoxy(61, 5);
	printf("(dd_mm_yyyy)");
	gotoxy(76, 4);
	printf("5.GIOI TINH");
	gotoxy(104, 4);
	printf("6.EMAIL");
	gotoxy(125, 4);
	printf("7.NGAY LAP THE");
	gotoxy(125, 5);
	printf("(dd_mm_yyyy)");
	gotoxy(144, 4);
	printf("8.NGAY HET HAN");
	gotoxy(144, 5);
	printf("(dd_mm_yyyy)");
}
void khungds(int n)   // khung de in danh sach cac sach
{
	textcolor(10);
	gotoxy(65, 2);
	printf("DANH SACH SACH %c%d%c", 175, n, 174);
	textcolor(15);
	for (int i = 1; i <= n - 1; i++)   // ve - - - 
	{
		for (int x = 3; x <= 165; x = x + 3)
		{
			gotoxy(x, 5 + 2 * i);
			printf(" - ");
		}
	}
	textcolor(11);
	for (int x = 3; x <= 165; x++)  //3 cot ngang
	{
		gotoxy(x, 3);
		printf("%c", 196);
	}
	for (int x = 3; x <= 165; x++)
	{
		gotoxy(x, 5);
		printf("%c", 196);
	}
	for (int x = 3; x <= 165; x++)
	{
		gotoxy(x, 5 + 2 * n);
		printf("%c", 196);
	}
	gotoxy(2, 3);        //goc trai tren
	printf("%c", 218);
	gotoxy(166, 3);     //goc phai tren
	printf("%c", 191);
	gotoxy(2, 5 + 2 * n);
	printf("%c", 192);    //goc trai duoi
	gotoxy(166, 5 + 2 * n);     //goc trai phai
	printf("%c", 217);
	for (int y = 4; y <= 4 + 2 * n; y++) //doc dau
	{
		gotoxy(2, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 4 + 2 * n; y++) //doc isbn
	{
		gotoxy(14, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 4 + 2 * n; y++) //doc ten sach
	{
		gotoxy(52, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 4 + 2 * n; y++)//doc tac gia
	{
		gotoxy(79, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 4 + 2 * n; y++) //doc nxb
	{
		gotoxy(103, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 4 + 2 * n; y++)//nam xb
	{
		gotoxy(113, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 4 + 2 * n; y++)//doc the loai
	{
		gotoxy(139, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 4 + 2 * n; y++)//doc gia sach
	{
		gotoxy(156, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 4 + 2 * n; y++) //doc gia sach
	{
		gotoxy(166, y);
		printf("%c", 179);
	}

	textcolor(10);
	gotoxy(3, 4);
	printf("1.ISBN(10)");
	gotoxy(27, 4);
	printf("2.TEN SACH");
	gotoxy(62, 4);
	printf("3.TAC GIA");
	gotoxy(85, 4);
	printf("4.NHA XUAT BAN");
	gotoxy(104, 4);
	printf("5.NAM XB");
	gotoxy(120, 4);
	printf("6.THE LOAI");
	gotoxy(140, 4);
	printf("7.GIA SACH(vnd)");
	gotoxy(157, 4);
	printf("8.SO SACH");
	gotoxy(15, 15);
}
void DangXuat() // ham dang xuat thoat khoi chuong trinh
{
	textcolor(15);
	clrscr();
	printf("Dang nhap lai");
}
void TK(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void Menu(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void nhappass(char pass[20])
{
	int i = 0;
	while (1)
	{
		pass[i] = getch();
		if (pass[i] == 13)
			break;
		else
			printf("*");
		i++;
	}
	pass[i] = NULL;
}

void DoiPass(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
// thay doi mat khau
{
	clrscr();
	char pass[20];
	vekhung2(51, 10, 4);
	textcolor(15);
	gotoxy(54, 11);
	printf("%c Nhap mat khau hien tai: ", 175);
	nhappass(pass);
	rewind(stdin);
	if (strcmp(pass, wchar_to_string(argv[2])) == 0)
	{
		char pass1[20], pass2[20];
		gotoxy(54, 13);
		printf("%c Nhap mat khau moi: ", 175);
		nhappass(pass1);
		gotoxy(54, 15);
		printf("%c Nhap lai mat khau moi: ", 175);
		nhappass(pass2);
		textcolor(11);
		if (strcmp(pass1, pass2) != 0)
		{

			gotoxy(54, 17);
			printf("=>Ban nhap sai mat khau moi. Vui long nhap lai\n");
			Sleep(600);
			clrscr();
			DoiPass(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		}
		else
		{
			NODE *p = ltaikhoan.pHead;
			while (p != NULL)
			{
				if (strcmp(((TaiKhoan*)p->key)->id, wchar_to_string(argv[1])) == 0)
				{
					strcpy(((TaiKhoan*)p->key)->pass, pass1);
					FILE *f = fopen("acc.txt", "wb");
					fwrite(&ltaikhoan.n, sizeof(int), 1, f);
					for (p = ltaikhoan.pHead; p; p = p->pNext)
						fwrite(p->key, sizeof(TaiKhoan), 1, f);
					fclose(f);
					gotoxy(53, 17);
					printf("=>Doi mat khau thanh cong. Vui long dang nhap lai");
					Sleep(1000);
					DangXuat();
					return;
				}
				p = p->pNext;
			}
		}
	}
	else
	{
		gotoxy(53, 13);
		printf("=>Nhap sai mat khau hien tai. Vui long nhap lai.\n");
		Sleep(600);
		DoiPass(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
	}
}
void HienThongTinCaNhan(NODE *p) //in thong tin ca nhan cua nguoi dung
{
	vekhung2(51, 10, 10);
	textcolor(15);
	gotoxy(54, 11);
	printf("1. Ten: %s\n", ((ThongTinCaNhan*)p->key)->ten);
	gotoxy(54, 13);
	printf("2. Ngay thang nam sinh: %d/%d/%d\n", ((ThongTinCaNhan*)p->key)->ngaysinh, ((ThongTinCaNhan*)p->key)->thangsinh, ((ThongTinCaNhan*)p->key)->namsinh);
	gotoxy(54, 15);
	printf("3. CMND: %s\n", ((ThongTinCaNhan*)p->key)->cmnd);
	gotoxy(54, 17);
	printf("4. Dia chi: %s\n", ((ThongTinCaNhan*)p->key)->diachi);
	gotoxy(54, 19);
	printf("5. Gioi tinh: %s\n", ((ThongTinCaNhan*)p->key)->gioitinh);
	gotoxy(54, 21);
	textcolor(11);
	printf("BACKSPACE. ");
	textcolor(15);
	printf("Chuc nang 1");
	gotoxy(54, 23);
	textcolor(11);
	printf("ESC. ");
	textcolor(15);
	printf("Menu\n");
}
bool CheckDay(int day, int month, int year) //kiem tra tinh hop le cua ngay thang nam duoc nhap
{
	int daymax = 0;
	switch (month)
	{
	case 1: case 3:case 5:case 7:case 8:case 10:case 12:daymax = 31; break;
	case 4: case 6: case 9: case 11: daymax = 30; break;
	case 2: if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) daymax = 29;
			else daymax = 28;
			break;
	}
	if ((day > 0) && (day <= daymax) && (year > 0)) return true;
	else return false;
}
void DoiThongTinCaNhan(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
// thay doi thong tin ca nhan cua nguoi dung
{
	clrscr();
	NODE *p = lthongtincanhan.pHead;
	char tam;
	FILE *f;
	while (p != NULL)
	{
		if (strcmp(((ThongTinCaNhan*)p->key)->id, wchar_to_string(argv[1])) == 0)
		{
			HienThongTinCaNhan(p);
			textcolor(11);
			gotoxy(54, 25);
			printf("Nhap lua chon cua ban: ");
			char a = _getch();
			gotoxy(54, 27);
			switch (a)
			{
			case '1':
				printf("Nhap lai ten:");
				gets_s(((ThongTinCaNhan*)p->key)->ten);
				DoiThongTinCaNhan(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
				return;
			case '2':
				do
				{
					gotoxy(54, 27);
					printf("Nhap lai ngay thang nam sinh(dd_mm_yyyy):          ");
					gotoxy(95, 27);
					scanf("%d %d %d", &((ThongTinCaNhan*)p->key)->ngaysinh, &((ThongTinCaNhan*)p->key)->thangsinh, &((ThongTinCaNhan*)p->key)->namsinh);
					rewind(stdin);
					if (CheckDay(((ThongTinCaNhan*)p->key)->ngaysinh, ((ThongTinCaNhan*)p->key)->thangsinh, ((ThongTinCaNhan*)p->key)->namsinh))
						break;
				} while (true);
				DoiThongTinCaNhan(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
				return;
			case '3':
				printf("Nhap lai CMND:");
				gets_s(((ThongTinCaNhan*)p->key)->cmnd);
				DoiThongTinCaNhan(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
				return;
			case '4':
				printf("Nhap lai dia chi:");
				gets_s(((ThongTinCaNhan*)p->key)->diachi);
				DoiThongTinCaNhan(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
				return;
			case '5':
				do
				{
					gotoxy(54, 27);
					printf("Nhap lai gioi tinh(Nam/Nu/Khac):      ");
					gotoxy(86, 27);
					gets_s(((ThongTinCaNhan*)p->key)->gioitinh);
					if (stricmp(((ThongTinCaNhan*)p->key)->gioitinh, "Nam") == 0 || stricmp(((ThongTinCaNhan*)p->key)->gioitinh, "Nu") == 0
						|| stricmp(((ThongTinCaNhan*)p->key)->gioitinh, "Khac") == 0)
						break;
				} while (true);
				DoiThongTinCaNhan(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
				return;
			case VK_BACK: //BACKSPACE
				f = fopen("thongtincanhan.txt", "wb");
				fwrite(&lthongtincanhan.n, sizeof(int), 1, f);
				for (p = lthongtincanhan.pHead; p; p = p->pNext)
					fwrite(p->key, sizeof(ThongTinCaNhan), 1, f);
				fclose(f);
				TK(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
				return;
			case 27: //ESC
				f = fopen("thongtincanhan.txt", "wb");
				fwrite(&lthongtincanhan.n, sizeof(int), 1, f);
				for (p = lthongtincanhan.pHead; p; p = p->pNext)
					fwrite(p->key, sizeof(ThongTinCaNhan), 1, f);
				fclose(f);
				Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
				return;
			default:
				DoiThongTinCaNhan(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
				return;
			}
		}
		p = p->pNext;
	}
}
void TaoNguoiDung(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
// tao them nguoi dung (chi admin)
{
	TaiKhoan *a = new TaiKhoan; ThongTinCaNhan *b = new ThongTinCaNhan;
	vekhung2(51, 10, 7);
	textcolor(15);
	gotoxy(54, 11);
	printf("%c Nhap ten dang nhap: ", 175);
	gets_s(a->id);
	for (NODE*p = ltaikhoan.pHead; p; p = p->pNext)
	{
		if (strcmp(a->id, ((TaiKhoan*)p->key)->id) == 0)
		{
			gotoxy(53, 13);
			printf("Ten dang nhap da ton tai, vui long nhap ten khac.\n");
			Sleep(600);
			clrscr();
			TaoNguoiDung(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
			return;
		}
	}
	//khoi tao thong tin nguoi dung rong
	strcpy(b->id, a->id);
	strcpy(b->gioitinh, "0");
	strcpy(b->ten, "0");
	strcpy(b->cmnd, "0");
	strcpy(b->diachi, "0");
	b->tinhtrang = 'a';
	b->namsinh = b->ngaysinh = b->thangsinh = 0;
	gotoxy(54, 13);
	printf("%c Nhap mat khau: ", 175);
	nhappass(a->pass);
	gotoxy(54, 15);
	printf("%c Nhap chuc vu ", 175);
	textcolor(9);
	printf("(q: quan ly, ");
	textcolor(10);
	printf("c: chuyen vien) : ", 175);
	textcolor(15);
	scanf("%c", &a->chucvu);
	rewind(stdin);
	if (a->chucvu != 'c' && a->chucvu != 'q')
	{
		gotoxy(54, 17);
		printf("Ban nhap sai cu phap. Vui long nhap lai.");
		Sleep(1000);
		clrscr();
		TaoNguoiDung(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		return;
	}
	addLast(ltaikhoan, a);
	ltaikhoan.n++;
	lthongtincanhan.n++;
	addLast(lthongtincanhan, b);
	FILE *f1 = fopen("acc.txt", "r + b");
	FILE *f2 = fopen("thongtincanhan.txt", "r + b");
	fseek(f1, 0, 0);
	fseek(f2, 0, 0);
	fwrite(&ltaikhoan.n, sizeof(int), 1, f1);
	fwrite(&lthongtincanhan.n, sizeof(int), 1, f2);
	fseek(f1, 0, SEEK_END);
	fseek(f2, 0, SEEK_END);
	fwrite(a, sizeof(TaiKhoan), 1, f1);
	fwrite(b, sizeof(ThongTinCaNhan), 1, f2);
	fclose(f1);
	fclose(f2);
	gotoxy(54, 17);
	textcolor(11);
	printf("ENTER. ");
	textcolor(15);
	printf("Tao them nguoi dung");
	textcolor(11);
	gotoxy(54, 19);
	printf("BACKSPACE. ");
	textcolor(15);
	printf("Chuc nang 1");
	gotoxy(54, 21);
	textcolor(11);
	printf("ESC. ");
	textcolor(15);
	printf("Menu");
	gotoxy(54, 23);
	textcolor(11);
	printf("Nhap lua chon cua ban: ");
	char c = _getch();
	switch (c)
	{
	case VK_BACK: //BACKSPACE
		clrscr();
		TK(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case 27: //ESC
		Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case VK_RETURN://ENTER
		clrscr();
		TaoNguoiDung(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	}
}
void InPhanQuyen(LIST &ltaikhoan)
// in danh sach cac tai khoan nguoi dung cung chuc vu cua ho tru admin
{
	int dem = 0;
	clrscr();
	gotoxy(26, 6);
	textcolor(11);
	printf("%c TAI KHOAN %c", 175, 174);
	gotoxy(47, 6); printf("%c", 186);  //ve duong giua
	gotoxy(47, 7); printf("%c", 186);
	gotoxy(56, 6);
	printf("%c CHUC VU %c", 175, 174);
	NODE *p;
	int i = 8;
	for (p = ltaikhoan.pHead; p; p = p->pNext)
	{
		if (strcmp(((TaiKhoan*)p->key)->id, "admin") != 0)
		{
			textcolor(15);
			gotoxy(23, i);
			printf("%s", ((TaiKhoan*)p->key)->id);
			gotoxy(56, i);
			if (((TaiKhoan*)p->key)->chucvu == 'q')
			{
				textcolor(9);
				printf("Quan ly\n"); dem++;
			}
			else
			{
				textcolor(10);
				printf("Chuyen vien\n");
				dem++;
			}
			i++;
		}
	}
	vekhung2(20, 5, i - 8 - 4);
}
void PhanQuyenNguoiDung(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
// lua chon phan quyen nguoi dung trong bang (quan ly hoac chuyen vien)(chi admin)
{
	InPhanQuyen(ltaikhoan);
	char id[20];
	textcolor(15);
	gotoxy(80, 11);
	printf("%c HOAC ""0 + ENTER"" DE QUAY LAI", 175);
	gotoxy(80, 10);
	printf("%c Nhap ten tai khoan ban muon phan quyen: ", 175);

	gets_s(id);
	if (strcmp(id, "0") == 0)
	{
		TK(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		return;
	}
	else
	{
		NODE *p;
		for (p = ltaikhoan.pHead; p; p = p->pNext)
		{
			if (strcmp(((TaiKhoan*)p->key)->id, id) == 0 && strcmp(((TaiKhoan*)p->key)->id, "admin") != 0)
				break;
		}
		if (p == NULL)
		{
			gotoxy(80, 13);
			printf("=> Ten tai khoan khong ton tai. Vui long nhap lai");
			Sleep(1000);
			PhanQuyenNguoiDung(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		}
		else
		{
			char newcv;
			gotoxy(80, 13);
			printf("Nhap chuc vu ban muon phan quyen cho tai khoan: ");
			textcolor(9);
			printf("(q: quanly,");
			textcolor(10);
			printf("c: chuyenvien) : ");
			textcolor(15);
			scanf("%c", &newcv);
			textcolor(15);
			rewind(stdin);
			if (newcv != 'q' && newcv != 'c')
			{
				gotoxy(80, 15);
				printf("Ban nhap sai cu phap, vui long chon lai...");
				Sleep(1000);
				PhanQuyenNguoiDung(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
			}
			else
			{
				((TaiKhoan*)p->key)->chucvu = newcv;
				FILE *f = fopen("acc.txt", "wb");
				fwrite(&ltaikhoan.n, sizeof(int), 1, f);
				for (p = ltaikhoan.pHead; p; p = p->pNext)
					fwrite(p->key, sizeof(TaiKhoan), 1, f);
				fclose(f);
				InPhanQuyen(ltaikhoan);
				gotoxy(80, 8);
				textcolor(11);
				printf("ENTER. ");
				textcolor(15);
				printf("Phan quyen them nguoi dung");
				gotoxy(80, 10);
				textcolor(11);
				printf("BACKSPACE. ");
				textcolor(15);
				printf("Chuc nang 1");
				gotoxy(80, 12);
				textcolor(11);
				printf("ESC. ");
				textcolor(15);
				printf("Menu");
				gotoxy(80, 14);
				textcolor(11);
				printf("Nhap lua chon cua ban: ");
				char c = _getch();
				switch (c)
				{
				case VK_BACK:
					TK(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
					break;
				case 27:
					Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
					break;
				case VK_RETURN:
					PhanQuyenNguoiDung(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
					break;
				default:
					PhanQuyenNguoiDung(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
					break;
				}
			}
		}
	}
}
void InTinhTrang(LIST &lthongtincanhan) // in danh sach cac tai khoan nguoi dung cung tinh trang cua ho tru admin
{

	clrscr();
	gotoxy(26, 6);
	textcolor(11);
	printf("%c TAI KHOAN %c", 175, 174);
	gotoxy(50, 6); printf("%c", 186);  //ve duong giua	
	gotoxy(50, 7); printf("%c", 186);
	gotoxy(56, 6);
	printf("%c TINH TRANG %c", 175, 174);
	NODE *p;
	int i = 8;
	for (p = lthongtincanhan.pHead; p; p = p->pNext)
	{
		textcolor(15);
		if (strcmp(((ThongTinCaNhan*)p->key)->id, "admin") != 0)
		{
			gotoxy(23, i);
			printf("%s", ((ThongTinCaNhan*)p->key)->id);
			gotoxy(60, i);
			if (((ThongTinCaNhan*)p->key)->tinhtrang == 'a')
			{
				textcolor(10);
				printf("Active\n");
			}
			else
			{
				textcolor(12);
				printf("Block");
			}
			i++;
		}
	}
	vekhung2(20, 5, i - 8 - 4);
}
void ThayDoiTinhTrangNguoiDung(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
// thay doi tinh trang cua tai khoan nguoi dung (activated hoac block) (chi admin)
{
	InTinhTrang(lthongtincanhan);
	char id[20];
	gotoxy(80, 9);
	textcolor(15);
	printf("%c HOAC ""0 + ENTER"" DE QUAY LAI", 175);
	gotoxy(80, 8);
	printf("%c Nhap ten tai khoan ban muon thay doi tinh trang: ", 175);
	gets_s(id);
	if (strcmp(id, "0") == 0)
	{
		TK(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		return;
	}
	else
	{
		NODE *p;
		for (p = lthongtincanhan.pHead; p; p = p->pNext)
		{
			if (strcmp(((ThongTinCaNhan*)p->key)->id, id) == 0 && strcmp(((ThongTinCaNhan*)p->key)->id, "admin") != 0)
				break;
		}
		if (p == NULL)
		{
			textcolor(15);
			gotoxy(80, 11);
			printf("=> Ten tai khoan khong ton tai. Vui long nhap lai");
			Sleep(1000);
			ThayDoiTinhTrangNguoiDung(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		}
		else
		{
			char newtt;
			textcolor(15);
			gotoxy(80, 11);
			printf("%c Nhap tinh trang ban muon thay doi cho tai khoan", 175);
			textcolor(10);
			printf("(a: Activated, ");
			textcolor(12);
			printf("b: Block) : ", 175);
			textcolor(15);
			scanf("%c", &newtt);
			rewind(stdin);
			if (newtt != 'a' && newtt != 'b')
			{
				gotoxy(80, 13);
				textcolor(15);
				printf("=> Ban nhap sai cu phap, vui long chon lai...");
				Sleep(1000);
				ThayDoiTinhTrangNguoiDung(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
			}
			else
			{
				((ThongTinCaNhan*)p->key)->tinhtrang = newtt;
				FILE *f = fopen("thongtincanhan.txt", "wb");
				fwrite(&lthongtincanhan.n, sizeof(int), 1, f);
				for (p = lthongtincanhan.pHead; p; p = p->pNext)
					fwrite(p->key, sizeof(ThongTinCaNhan), 1, f);
				fclose(f);
				InTinhTrang(lthongtincanhan);
				gotoxy(80, 8);
				textcolor(11);
				printf("ENTER. ");
				textcolor(15);
				printf("Phan quyen them nguoi dung");
				gotoxy(80, 10);
				textcolor(11);
				printf("BACKSPACE. ");
				textcolor(15);
				printf("Chuc nang 1");
				gotoxy(80, 12);
				textcolor(11);
				printf("ESC. ");
				textcolor(15);
				printf("Menu");
				gotoxy(80, 14);
				textcolor(11);
				printf("Nhap lua chon cua ban: ");
				char c = _getch();
				switch (c)
				{
				case VK_BACK: //BACKSPACE
					TK(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
					break;
				case 27: //ESC
					Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
					break;
				case VK_RETURN:
					ThayDoiTinhTrangNguoiDung(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
					break;
				default: //ENTER
					ThayDoiTinhTrangNguoiDung(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
					break;
				}
			}
		}
	}
}
void TK(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
// menu chuc nang 1
{
	clrscr();
	gotoxy(59, 11);
	textcolor(10);
	printf("* CHUC NANG 1: QUAN LY TAI KHOAN *");
	if (chucvu == 'a') //chuc nang 1 ung voi admin
	{
		vekhung(51, 10, 6);
		gotoxy(56, 13);
		textcolor(15);
		printf("1.Dang Xuat");
		gotoxy(56, 15);
		printf("2.Thay Doi Mat Khau");
		gotoxy(56, 17);
		printf("3.Thay Doi Thong Tin Ca Nhan");
		gotoxy(56, 19);
		printf("4.Tao Nguoi Dung");
		gotoxy(56, 21);
		printf("5.Phan Quyen Nguoi Dung");
		gotoxy(56, 23);
		printf("6.Thay Doi Tinh Trang Nguoi Dung");
		gotoxy(61, 25);
		printf("Menu");
		textcolor(10);
		gotoxy(56, 25);
		printf("ESC. ");
		gotoxy(56, 27);
		printf("Nhap lua chon cua ban: ");
		gotoxy(79, 27);
	}
	else //chuc nang 1 ung voi quan ly hoac chuyen vien
	{
		vekhung(51, 10, 4);
		gotoxy(56, 13);
		textcolor(15);
		printf("1.Dang Xuat");
		gotoxy(56, 15);
		printf("2.Thay Doi Mat Khau");
		gotoxy(56, 17);
		printf("3.Thay Doi Thong Tin Ca Nhan");
		gotoxy(61, 19);
		printf("Menu");
		textcolor(10);
		gotoxy(56, 19);
		printf("ESC. ");
		gotoxy(56, 21);
		printf("Nhap lua chon cua ban: ");
	}
	char a = _getch();
	switch (a)
	{
	case '1':
		DangXuat();
		return;
	case '2':
		clrscr();
		DoiPass(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case '3':
		DoiThongTinCaNhan(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case '4':
		clrscr();
		if (chucvu == 'a') // chi admin moi duoc su dung
			TaoNguoiDung(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		else TK(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case '5':
		if (chucvu == 'a')
			PhanQuyenNguoiDung(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		else TK(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case '6':
		if (chucvu == 'a')
			ThayDoiTinhTrangNguoiDung(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		else TK(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case 27:
		Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	default:
		TK(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	}
}
bool CheckMaSoDocGia(LIST &l, int maso) //kiem tra ma so doc gia co trung hay khong
{
	for (NODE*p = l.pHead; p; p = p->pNext)
	{
		if ((((DocGia*)p->key)->MaDocGia) == maso)
			return false;
	}

	return true;
}
bool CheckCMNDDocGia(LIST &l, char cmnd[11]) //kiem tra CMND doc gia co trung hay khong
{
	for (NODE*p = l.pHead; p; p = p->pNext)
	{
		if (stricmp(((DocGia*)p->key)->CMND, cmnd) == 0)
			return false;
	}
	return true;
}
void ChucNang2(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void InDSDocGia(LIST &l);
void InDSDocGiaKhongOption(LIST &l);
void ThemDocGia(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void ChinhSuaThongTinDocGia(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void XoaDocGia(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void TimKiemDocGiaCMND(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void TimKiemDocGiaHoTen(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void OptionThemDocGia(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{   //bang cac nut chuc nang
	clrscr();
	InDSDocGiaKhongOption(ldocgia);//in ds doc gia khong tuy chon quay ve
	gotoxy(70, 8 + 2 * ldocgia.n);
	textcolor(11);
	printf("ENTER. ");
	textcolor(15);
	printf("Them tiep doc gia khac");
	gotoxy(70, 10 + 2 * ldocgia.n);
	textcolor(11);
	printf("BACKSPACE. ");
	textcolor(15);
	printf("Chuc nang 2");
	gotoxy(70, 12 + 2 * ldocgia.n);
	textcolor(11);
	printf("ESC. ");
	textcolor(15);
	printf("Menu\n");
	gotoxy(70, 14 + 2 * ldocgia.n);
	textcolor(11);
	printf("Nhap lua chon cua ban: ");
	char c = getch();
	switch (c)
	{
	case VK_RETURN:

		clrscr();
		ThemDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case  VK_BACK:
		clrscr();
		ChucNang2(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default:
		OptionThemDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	}
}
void ThemDocGia(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	FILE *f = fopen("DSDocGia.txt", "r+b");
	DocGia *a = new DocGia;
	int x = 1;
	InDSDocGiaKhongOption(ldocgia);
	do
	{
		gotoxy(7, 7 + 2 * ldocgia.n);
		scanf_s("%d", &a->MaDocGia);
		rewind(stdin);
	} while (CheckMaSoDocGia(ldocgia, a->MaDocGia) == false);
	gotoxy(16, 7 + 2 * ldocgia.n);
	rewind(stdin);
	gets_s(a->hoten);
	do
	{
		gotoxy(47, 7 + 2 * ldocgia.n);
		rewind(stdin);
		gets_s(a->CMND);
	} while (CheckCMNDDocGia(ldocgia, a->CMND) == false);
	do
	{
		gotoxy(60, 7 + 2 * ldocgia.n);
		printf("          ");
		gotoxy(60, 7 + 2 * ldocgia.n);
		scanf_s("%d", &a->NgaySinh.day);
		scanf("%d", &a->NgaySinh.month);
		scanf("%d", &a->NgaySinh.year);
		rewind(stdin);
	} while (CheckDay(a->NgaySinh.day, a->NgaySinh.month, a->NgaySinh.year) == false);

	rewind(stdin);
	do
	{
		gotoxy(75, 7 + 2 * ldocgia.n);
		printf("    ");
		gotoxy(75, 7 + 2 * ldocgia.n);
		gets_s(a->gioitinh);
	} while (stricmp((a->gioitinh), "Nam") != 0 && stricmp((a->gioitinh), "Nu") != 0 && stricmp((a->gioitinh), "Khac") != 0);
	gotoxy(90, 7 + 2 * ldocgia.n);
	rewind(stdin);
	gets_s(a->email);
	do
	{
		gotoxy(124, 7 + 2 * ldocgia.n);
		printf("          ");
		gotoxy(124, 7 + 2 * ldocgia.n);
		scanf("%d", &a->NgayLapThe.day);
		scanf("%d", &a->NgayLapThe.month);
		scanf("%d", &a->NgayLapThe.year);
		rewind(stdin);
	} while (CheckDay(a->NgayLapThe.day, a->NgayLapThe.month, a->NgayLapThe.year) == false);
	a->NgayHetHan.day = a->NgayLapThe.day;
	a->NgayHetHan.month = a->NgayLapThe.month;
	a->NgayHetHan.year = a->NgayLapThe.year + 4;
	printf("\n");
	ldocgia.n++;
	addLast(ldocgia, (DocGia*)a); //them vao LIST l
	fseek(f, 0, SEEK_SET);   // them so luong doc gia vao dau file
	fwrite(&ldocgia.n, sizeof(int), 1, f);
	fseek(f, 0, SEEK_END);
	fwrite(a, sizeof(DocGia), 1, f); // ghi struct vao file
	fclose(f);
	OptionThemDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
}// ghi them vao file
void ThemLaiDocGia(LIST &l) // ghi lai toan bo ds vao file
{
	FILE *f = fopen("DSDocGiA.txt", "wb");
	fwrite(&l.n, sizeof(int), 1, f);
	for (NODE*p = l.pHead; p; p = p->pNext)
	{
		fwrite(p->key, sizeof(DocGia), 1, f);
	}
	fclose(f);
}
void In1DocGiaTuyChon(LIST &l, NODE *p, int &x);
void InDSDocGiaKhongOption(LIST &l)
{
	khungdocgia(l.n);
	int x = 1;
	textcolor(15);
	for (NODE*p = l.pHead; p; p = p->pNext)
	{
		gotoxy(7, 5 + 2 * x);
		printf("%d", ((DocGia*)p->key)->MaDocGia);
		gotoxy(16, 5 + 2 * x);
		puts(((DocGia*)p->key)->hoten);
		gotoxy(47, 5 + 2 * x);
		puts(((DocGia*)p->key)->CMND);
		gotoxy(60, 5 + 2 * x);
		printf("%d-%d-%d", ((DocGia*)p->key)->NgaySinh.day, ((DocGia*)p->key)->NgaySinh.month, ((DocGia*)p->key)->NgaySinh.year);
		gotoxy(75, 5 + 2 * x);
		puts(((DocGia*)p->key)->gioitinh);
		gotoxy(90, 5 + 2 * x);
		puts(((DocGia*)p->key)->email);
		gotoxy(124, 5 + 2 * x);
		printf("%d-%d-%d", ((DocGia*)p->key)->NgayLapThe.day, ((DocGia*)p->key)->NgayLapThe.month, ((DocGia*)p->key)->NgayLapThe.year);
		gotoxy(144, 5 + 2 * x);
		printf("%d-%d-%d", ((DocGia*)p->key)->NgayHetHan.day, ((DocGia*)p->key)->NgayHetHan.month, ((DocGia*)p->key)->NgayHetHan.year);
		x++;
	}
}
void InDSDocGia(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	khungdocgia(ldocgia.n);
	int x = 1;
	textcolor(15);
	for (NODE*p = ldocgia.pHead; p; p = p->pNext)
	{
		gotoxy(7, 5 + 2 * x);
		printf("%d", ((DocGia*)p->key)->MaDocGia);
		gotoxy(16, 5 + 2 * x);
		puts(((DocGia*)p->key)->hoten);
		gotoxy(47, 5 + 2 * x);
		puts(((DocGia*)p->key)->CMND);
		gotoxy(60, 5 + 2 * x);
		printf("%d-%d-%d", ((DocGia*)p->key)->NgaySinh.day, ((DocGia*)p->key)->NgaySinh.month, ((DocGia*)p->key)->NgaySinh.year);
		gotoxy(75, 5 + 2 * x);
		puts(((DocGia*)p->key)->gioitinh);
		gotoxy(90, 5 + 2 * x);
		puts(((DocGia*)p->key)->email);
		gotoxy(124, 5 + 2 * x);
		printf("%d-%d-%d", ((DocGia*)p->key)->NgayLapThe.day, ((DocGia*)p->key)->NgayLapThe.month, ((DocGia*)p->key)->NgayLapThe.year);
		gotoxy(144, 5 + 2 * x);
		printf("%d-%d-%d", ((DocGia*)p->key)->NgayHetHan.day, ((DocGia*)p->key)->NgayHetHan.month, ((DocGia*)p->key)->NgayHetHan.year);
		x++;
	}
	gotoxy(70, 8 + 2 * ldocgia.n);
	textcolor(11);
	printf("BACKSPACE.");
	textcolor(15);
	printf("Chuc nang 3");
	gotoxy(70, 10 + 2 * ldocgia.n);
	textcolor(11);
	printf("ESC.");
	textcolor(15);
	printf("Menu");
	textcolor(11);
	gotoxy(70, 12 + 2 * ldocgia.n);
	printf("Nhap lua chon cua ban : ");
	char c = getch();
	switch (c)
	{
	case VK_BACK:

		clrscr();
		ChucNang2(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	case 27:
		Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	default:
		clrscr();
		InDSDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	}
}
void In1DocGiaTuyChon(LIST &l, NODE *p, int &x)   //chi in 1 nguoi theo node * p truyen vao
{
	khungdocgia(x);
	textcolor(15);
	gotoxy(7, 5 + 2 * x);
	printf("%d", ((DocGia*)p->key)->MaDocGia);
	gotoxy(16, 5 + 2 * x);
	puts(((DocGia*)p->key)->hoten);
	gotoxy(47, 5 + 2 * x);
	puts(((DocGia*)p->key)->CMND);
	gotoxy(60, 5 + 2 * x);
	printf("%d-%d-%d", ((DocGia*)p->key)->NgaySinh.day, ((DocGia*)p->key)->NgaySinh.month, ((DocGia*)p->key)->NgaySinh.year);
	gotoxy(75, 5 + 2 * x);
	puts(((DocGia*)p->key)->gioitinh);
	gotoxy(90, 5 + 2 * x);
	puts(((DocGia*)p->key)->email);
	gotoxy(124, 5 + 2 * x);
	printf("%d-%d-%d", ((DocGia*)p->key)->NgayLapThe.day, ((DocGia*)p->key)->NgayLapThe.month, ((DocGia*)p->key)->NgayLapThe.year);
	gotoxy(144, 5 + 2 * x);
	printf("%d-%d-%d", ((DocGia*)p->key)->NgayHetHan.day, ((DocGia*)p->key)->NgayHetHan.month, ((DocGia*)p->key)->NgayHetHan.year);
	x++;

}
void ChinhSuaDocGiaCMND(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu, char cmnd[11]) //Chinh sua tat ca thong tin 1 doc gia
{
	int i = 0, x = 1;
	for (NODE*p = ldocgia.pHead; p; p = p->pNext)
	{
		if (strcmp(((DocGia*)p->key)->CMND, cmnd) == 0)
		{
			clrscr();
			i++;
			In1DocGiaTuyChon(ldocgia, p, x);
			gotoxy(52, 11);
			textcolor(15);
			printf("Loai thong tin muon sua: ");
			textcolor(11);
			printf("(1 -> 7)");
			vekhung2(50, 10, 3);
			gotoxy(52, 13);
			textcolor(11);
			printf("ENTER. ");
			textcolor(15);
			printf("Chinh sua doc gia khac");
			gotoxy(52, 15);
			textcolor(11);
			printf("BACKSPACE. ");
			textcolor(15);
			printf("Chuc nang 2");
			textcolor(11);
			gotoxy(52, 17);
			printf("ESC. ");
			textcolor(15);
			printf("Menu\n");
			textcolor(11);
			gotoxy(52, 19);
			printf("Nhap lua chon cua ban: ");
			gotoxy(75, 19);
			char c = getch();
			switch (c)
			{
			case '1':
				int tam;
				do
				{
					gotoxy(52, 21);
					printf("%c Ma doc moi:     ", 175);
					gotoxy(68, 21);
					scanf("%d", &tam);
					rewind(stdin);
				} while (CheckMaSoDocGia(ldocgia, tam) == false);
				((DocGia*)p->key)->MaDocGia = tam;
				clrscr();
				ChinhSuaDocGiaCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, cmnd);
				break;
			case '2':
				gotoxy(52, 21);
				printf("%c Ho va ten moi ", 175);
				rewind(stdin);
				gets_s(((DocGia*)p->key)->hoten);
				clrscr();
				ChinhSuaDocGiaCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, cmnd);
				break;
			case '3':
				char tam1[12];
				do
				{
					gotoxy(52, 21);
					printf("%c CMND moi: ", 175);
					rewind(stdin);
					gets_s(tam1);
				} while (CheckCMNDDocGia(ldocgia, tam1) == false);
				strcpy(((DocGia*)p->key)->CMND, tam1);
				cmnd = ((DocGia*)p->key)->CMND; // de tiep tuc chinh sua thong tin cua docgia do theo cmnd moi
				clrscr();
				ChinhSuaDocGiaCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, cmnd);
				break;
			case '4':
				do
				{
					gotoxy(52, 21);
					printf("%c Ngay thang nam sinh(ddmmyyyy) moi:           ", 175);
					gotoxy(89, 21);
					scanf_s("%d", &((DocGia*)p->key)->NgaySinh.day);
					scanf("%d", &((DocGia*)p->key)->NgaySinh.month);
					scanf("%d", &((DocGia*)p->key)->NgaySinh.year);
					rewind(stdin);
				} while (CheckDay(((DocGia*)p->key)->NgaySinh.day, ((DocGia*)p->key)->NgaySinh.month, ((DocGia*)p->key)->NgaySinh.year) == false);
				clrscr();
				ChinhSuaDocGiaCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, cmnd);
				break;
			case '5':
				do
				{
					gotoxy(52, 21);
					printf("%c Gioi tinh(Nam/Nu/Khac): ", 175);
					gets_s(((DocGia*)p->key)->gioitinh);
				} while (stricmp(((DocGia*)p->key)->gioitinh, "Nam") != 0 && stricmp(((DocGia*)p->key)->gioitinh, "Nu") != 0 && stricmp(((DocGia*)p->key)->gioitinh, "Khac") != 0);
				clrscr();
				ChinhSuaDocGiaCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, cmnd);
				break;
			case '6':
				gotoxy(52, 21);
				printf("%c Email: ", 175);
				rewind(stdin);
				gets_s(((DocGia*)p->key)->email);
				clrscr();
				ChinhSuaDocGiaCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, cmnd);
				break;
			case '7':
				do
				{
					gotoxy(52, 21);
					printf("%c Ngay lap the (ddmmyyyy):           ", 175);
					gotoxy(80, 21);
					scanf_s("%d", &((DocGia*)p->key)->NgayLapThe.day);
					scanf("%d", &((DocGia*)p->key)->NgayLapThe.month);
					scanf("%d", &((DocGia*)p->key)->NgayLapThe.year);
					rewind(stdin);
				} while (CheckDay(((DocGia*)p->key)->NgayLapThe.day, ((DocGia*)p->key)->NgayLapThe.month, ((DocGia*)p->key)->NgayLapThe.year) == false);
				((DocGia*)p->key)->NgayHetHan.day = ((DocGia*)p->key)->NgayLapThe.day;
				((DocGia*)p->key)->NgayHetHan.month = ((DocGia*)p->key)->NgayLapThe.month;
				((DocGia*)p->key)->NgayHetHan.year = ((DocGia*)p->key)->NgayLapThe.year + 4;
				clrscr();
				ChinhSuaDocGiaCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, cmnd);
				break;
			case VK_RETURN: //ENTER
				ThemLaiDocGia(ldocgia);
				clrscr();
				ChinhSuaThongTinDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;

			case VK_BACK: //BACKSPACE
				clrscr();
				ThemLaiDocGia(ldocgia);
				ChucNang2(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
			case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;  //ESC
			default:
				clrscr();
				ChinhSuaDocGiaCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, cmnd);
				break;
			}
		}
	}
	if (i == 0)
	{
		textcolor(15);
		gotoxy(52, 12);
		printf("=> KHONG TIM THAY CMND DOC GIA");
		vekhung2(50, 14, 3);
		gotoxy(52, 15);
		textcolor(11);
		printf("ENTER. ");
		textcolor(15);
		printf("Tim tiep doc gia khac");
		gotoxy(52, 17);
		textcolor(11);
		printf("BACKSPACE. ");
		textcolor(15);
		printf("Chuc nang 2");
		textcolor(11);
		gotoxy(52, 19);
		printf("ESC. ");
		textcolor(15);
		printf("Menu\n");
		textcolor(11);
		gotoxy(52, 21);
		printf("Nhap lua chon cua ban: ");
		char c = getch();
		switch (c)
		{
		case VK_RETURN: //ENTER
			clrscr();
			ChinhSuaThongTinDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;

		case VK_BACK: //BACKSPACE
			clrscr();
			ChucNang2(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		case 27: break;  //ESC
		default:
			clrscr();
			ChinhSuaDocGiaCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, cmnd);
			break;
		}
	}
}
void ChinhSuaThongTinDocGia(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	char cmnd[11];
	rewind(stdin);
	textcolor(11);
	gotoxy(52, 10);
	printf("%c Nhap CMND doc gia muon sua: ", 175);
	textcolor(15);
	gets_s(cmnd);
	ChinhSuaDocGiaCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, cmnd);

}
void OptionXoaDocGia(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	clrscr();
	InDSDocGiaKhongOption(ldocgia);//in ds doc gia khong co tuy chon quay ve
	gotoxy(65, 8 + 2 * ldocgia.n);
	textcolor(11);
	printf("ENTER. ");
	textcolor(15);
	printf("Xoa tiep doc gia khac");
	gotoxy(65, 10 + 2 * ldocgia.n);
	textcolor(11);
	printf("BACKSPACE. ");
	textcolor(15);
	printf("Chuc nang 2");
	gotoxy(65, 12 + 2 * ldocgia.n);
	textcolor(11);
	printf("ESC. ");
	textcolor(15);
	printf("Menu\n");
	gotoxy(65, 14 + 2 * ldocgia.n);
	textcolor(11);
	printf("Nhap lua chon cua ban: ");
	char c = getch();
	switch (c)
	{
	case VK_RETURN:

		clrscr();
		XoaDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case  VK_BACK:
		clrscr();
		ChucNang2(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default:
		OptionXoaDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	}
}
void XoaDocGia(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	char cmnd[11];
	int  i = 0, x = 1;
	if (ldocgia.pHead == NULL)
	{
		textcolor(11);
		printf("\t=> Hien khong co doc gia nao"); Sleep(1000);
		clrscr();
		ChucNang2(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
	}
	InDSDocGiaKhongOption(ldocgia);
	textcolor(11);
	gotoxy(52, 8 + 2 * ldocgia.n);
	printf("%c Nhap CMND doc gia muon xoa: ", 175);
	gets_s(cmnd);
	if (strcmp(((DocGia*)ldocgia.pHead->key)->CMND, cmnd) == 0)
	{
		DeleteFirst(ldocgia);
		textcolor(11);
		gotoxy(52, 10 + 2 * ldocgia.n);
		printf("%c Da xoa doc gia", 175);
		Sleep(1000);
		i++;
		ldocgia.n--;
	}
	else
	{
		if (strcmp(((DocGia*)ldocgia.pTail->key)->CMND, cmnd) == 0)
		{
			DeleteLast(ldocgia);
			textcolor(11);
			gotoxy(52, 10 + 2 * ldocgia.n);
			printf("%c Da xoa doc gia", 175);
			Sleep(1000);
			i++;
			ldocgia.n--;
		}
		for (NODE*p = ldocgia.pHead; p; p = p->pNext)
		{
			if (strcmp(((DocGia*)p->key)->CMND, cmnd) == 0)
			{
				{
					DeleteMid(p);
					textcolor(11);
					gotoxy(52, 10 + 2 * ldocgia.n);
					printf("%c Da xoa doc gia", 175);
					Sleep(1000);
					i++;
					ldocgia.n--;
				}
			}
		}
	}
	if (i == 0)
	{
		textcolor(15);
		gotoxy(52, 10 + 2 * ldocgia.n);
		printf("=> KHONG TIM THAY DOC GIA MUON XOA\n");
		Sleep(1000);
	}
	else
		ThemLaiDocGia(ldocgia);
	OptionXoaDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
}
void OptionTimCMND(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu, char cmnd[11])
{

	int x = 1;
	for (NODE *p = ldocgia.pHead; p; p = p->pNext)
	{
		if (strcmp(((DocGia*)p->key)->CMND, cmnd) == 0)
		{
			In1DocGiaTuyChon(ldocgia, p, x);
		}
	}
	vekhung2(50, 14, 3);
	gotoxy(52, 14);
	textcolor(11);
	printf("ENTER. ");
	textcolor(15);
	printf("Tim tiep doc gia khac");
	gotoxy(52, 16);
	textcolor(11);
	printf("BACKSPACE. ");
	textcolor(15);
	printf("Chuc nang 3");
	textcolor(11);
	gotoxy(52, 18);
	printf("ESC. ");
	textcolor(15);
	printf("Menu\n");
	textcolor(11);
	gotoxy(52, 20);
	printf("Nhap lua chon cua ban: ");
	char c = getch();
	switch (c)
	{
	case VK_RETURN:

		clrscr();
		TimKiemDocGiaCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case  VK_BACK:
		clrscr();
		ChucNang2(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default:
		clrscr();
		OptionTimCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, cmnd);
		break;
	}
}
void TimKiemDocGiaCMND(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	char cmnd[11];
	int  i = 0, x = 1;
	if (ldocgia.pHead == NULL)
	{
		textcolor(11);
		printf("\t=> Hien khong co sach nao trong thu vien"); Sleep(1000);
		clrscr();
		ChucNang2(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
	}
	textcolor(11);
	gotoxy(52, 10);
	printf("%c Nhap CMND doc gia muon tim: ", 175);

	textcolor(15);
	rewind(stdin);
	gets_s(cmnd);
	textcolor(0);
	for (NODE *p = ldocgia.pHead; p; p = p->pNext)
	{
		if (strcmp(((DocGia*)p->key)->CMND, cmnd) == 0)
		{
			i++;
		}
	}
	if (i == 0)
	{
		textcolor(15);
		gotoxy(52, 12);
		printf("=> KHONG TIM THAY DOC GIA");
		OptionTimCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, cmnd);
	}
	else
	{
		for (int a = 52; a <= 100; a++)
		{
			gotoxy(a, 10);
			printf("%c%c", 217, 217);
		}

		OptionTimCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, cmnd);
	}
}
void OptionTimHoTen(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu, char hoten[50])
{
	clrscr();
	int x = 1;
	for (NODE *p = ldocgia.pHead; p; p = p->pNext)
	{
		if (stricmp(((DocGia*)p->key)->hoten, hoten) == 0)
		{
			In1DocGiaTuyChon(ldocgia, p, x);
		}
	}
	vekhung2(50, 8 + 2 * x, 2);
	gotoxy(52, 9 + 2 * x);
	textcolor(11);
	printf("ENTER. ");
	textcolor(15);
	printf("Tim tiep doc gia khac");
	gotoxy(52, 11 + 2 * x);
	textcolor(11);
	printf("BACKSPACE. ");
	textcolor(15);
	printf("Chuc nang 2");
	textcolor(11);
	gotoxy(52, 13 + 2 * x);
	printf("ESC. ");
	textcolor(15);
	printf("Menu\n");
	textcolor(11);
	gotoxy(52, 15 + 2 * x);
	printf("Nhap lua chon cua ban: ");
	char c = getch();
	switch (c)
	{
	case VK_RETURN:

		clrscr();
		TimKiemDocGiaHoTen(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case  VK_BACK:
		clrscr();
		ChucNang2(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default:
		clrscr();
		OptionTimHoTen(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, hoten);
		break;
	}
}
void TimKiemDocGiaHoTen(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	char hoten[50];
	int  i = 0, x = 1;
	if (ldocgia.pHead == NULL)
	{
		textcolor(11);
		printf("\t=> Hien khong co sach nao trong thu vien"); Sleep(1000);
		clrscr();
		ChucNang2(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
	}
	textcolor(11);
	gotoxy(52, 10);
	printf("%c Nhap Ho Ten doc gia muon tim: ", 175);
	textcolor(15);
	rewind(stdin);
	gets_s(hoten);
	for (NODE *p = ldocgia.pHead; p; p = p->pNext)
	{
		if (stricmp(((DocGia*)p->key)->hoten, hoten) == 0)
		{
			i++;
		}
	}
	if (i == 0)
	{
		textcolor(15);
		gotoxy(52, 12);
		printf("=> KHONG TIM THAY DOC GIA");
		Sleep(600);
	}
	OptionTimHoTen(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, hoten);
}
void ChucNang2(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	clrscr();
	gotoxy(60, 11);
	textcolor(10);
	printf("* CHUC NANG 2: QUAN LY DOC GIA *");
	if (chucvu != 'c')
	{
		vekhung(51, 10, 6);
		gotoxy(56, 13);
		textcolor(15);
		printf("1.Danh Sach Doc Gia");
		gotoxy(56, 15);
		printf("2.Them Doc Gia");
		gotoxy(56, 17);
		printf("3.Chinh Sua Thong Tin Doc Gia");
		gotoxy(56, 19);
		printf("4.Xoa Doc Gia");
		gotoxy(56, 21);
		printf("5.Tim Kiem Doc Gia Theo CMND");
		gotoxy(56, 23);
		printf("6.Tim Kiem Doc Gia Theo Ho Ten");
		gotoxy(61, 25);
		printf("Menu");
		textcolor(10);
		gotoxy(56, 25);
		printf("ESC. ");
		gotoxy(56, 27);
		printf("Nhap lua chon cua ban: ");
	}
	else
	{
		vekhung(51, 10, 5);
		gotoxy(56, 13);
		textcolor(15);
		printf("1.Danh Sach Doc Gia");
		gotoxy(56, 15);
		printf("2.Them Doc Gia");
		gotoxy(56, 17);
		printf("3.Chinh Sua Thong Tin Doc Gia");
		gotoxy(56, 19);
		printf("4.Tim Kiem Doc Gia Theo CMND");
		gotoxy(56, 21);
		printf("5.Tim Kiem Doc Gia Theo Ho Ten");
		gotoxy(61, 23);
		printf("Menu");
		textcolor(10);
		gotoxy(56, 23);
		printf("ESC. ");
		gotoxy(56, 25);
		printf("Nhap lua chon cua ban: ");
	}
	char c = getch();
	clrscr();
	switch (c)
	{
	case '1': InDSDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);  break;
	case '2': ThemDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);  break;
	case '3': ChinhSuaThongTinDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	case '4':
		if (chucvu != 'c')
		{
			XoaDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
			break;
		}
		else
		{
			TimKiemDocGiaCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
			break;
		}
	case '5':
		if (chucvu != 'c')
		{
			TimKiemDocGiaCMND(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
			break;
		}
		else
		{
			TimKiemDocGiaHoTen(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
			break;
		}
	case '6':
		if (chucvu != 'c')
		{
			TimKiemDocGiaHoTen(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
			break;
		}
		else
		{
			ChucNang2(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
			break;
		}
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default: ChucNang2(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	}
}
bool CheckMaSach(LIST l, char maso[11])
{
	for (NODE*p = l.pHead; p; p = p->pNext)
	{
		if (stricmp(((Sach*)p->key)->MaISBN, maso) == 0)
			return false;
	}

	return true;
}
void ChucNang3(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void ThemSach(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void InDSSachKhongOption(LIST &l);
void InDSSach(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void In1Sach(LIST &l, NODE *p, int &x);
void ChinhSuaThongTinSach(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void ChinhSuaSachISBN(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu, char ISBN[11]);
void XoaSachTheoISBN(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void TimSachTheoISBN(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void TimKiemSachTheoTen(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void ThemTheLoaiSach(int &x, int &y, int n)// them cac the loai sach moi
{
	char *a = new char[35];
	FILE *f = fopen("TheLoaiSach.txt", "r+b");
	n++;
	gotoxy(x, y);
	printf("%d: ", n);
	rewind(stdin);
	gets_s(a, 35);
	fseek(f, 0, 0);
	fwrite(&n, sizeof(int), 1, f);
	fseek(f, 0, SEEK_END);
	fwrite(a, sizeof(char[35]), 1, f);
	fclose(f);
}
void ChonTheLoaiSach(char p[35]) //xem va chon the loai sach mong muon
{
	clrscr();
	FILE *f;
	int x = 15, y = 5, n = 0;
	f = fopen("TheLoaiSach.txt", "rb");
	fread(&n, sizeof(int), 1, f); //l.n la so luong the loai dang co
	gotoxy(60, 2);
	textcolor(12);
	printf("NHUNG THE LOAI SACH HIEN CO %c %d %c", 175, n, 174);
	textcolor(15);
	char a[35];
	for (int i = 1; i <= n; i++)          // Doc Va In Cac The Loai Sach Trong Thu Vien
	{
		fread(a, (sizeof(char)) * 35, 1, f);
		gotoxy(x, y);
		printf("%d. %s", i, a);
		if (x == 105)      // tang x,y de in cho phu hop
		{
			x = 15;
			y++;
		}
		else x += 30;
	}
	for (int x = 6; x <= 140; x++)  //2 ngang
	{
		gotoxy(x, 4);
		printf("%c", 196);
	}
	for (int x = 6; x <= 140; x++)
	{
		gotoxy(x, y + 1);
		printf("%c", 196);
	}
	for (int l = 5; l <= y; l++)    // 2 doc
	{
		gotoxy(5, l);
		printf("%c", 179);
	}
	for (int l = 5; l <= y; l++)
	{
		gotoxy(141, l);
		printf("%c", 179);
	}
	gotoxy(5, 4);        //goc trai tren
	printf("%c", 218);
	gotoxy(141, 4);     //goc phai tren
	printf("%c", 191);
	gotoxy(5, y + 1);
	printf("%c", 192);    //goc trai duoi
	gotoxy(141, y + 1);     //goc phai duoi
	printf("%c", 217);    //goc trai duoi

	int choose;
	textcolor(11);
	gotoxy(45, y + 4);
	printf("%c Chon the loai(theo so), '0' de them the loai moi: ", 175); //Nhap so
	scanf("%d", &choose);
	rewind(stdin);
	if (choose == 0)
	{
		ThemTheLoaiSach(x, y, n); // Sau khi them the loai goi lai ham lua chon
		ChonTheLoaiSach(p);
	}
	else
	if (choose >= 1 && choose <= n)
	{
		fseek(f, sizeof(int)+((choose - 1) * sizeof(char[35])), 0);
		fread(a, sizeof(char[35]), 1, f);
		strcpy(p, a);

	}
	else ChonTheLoaiSach(p);
	fclose(f);
}
void OptionThemSach(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu) // bang lua chon quay ve hay tiep tuc o phan them sach
{
	clrscr();
	InDSSachKhongOption(lsach);//in ds doc gia khong lua chon quay ve menu
	gotoxy(70, 7 + 2 * lsach.n);
	textcolor(11);
	printf("ENTER. ");
	textcolor(15);
	printf("Them tiep sach khac");
	gotoxy(70, 9 + 2 * lsach.n);
	textcolor(11);
	printf("BACKSPACE. ");
	textcolor(15);
	printf("Chuc nang 3");
	gotoxy(70, 11 + 2 * lsach.n);
	textcolor(11);
	printf("ESC. ");
	textcolor(15);
	printf("Menu\n");
	gotoxy(70, 13 + 2 * lsach.n);
	textcolor(11);
	printf("Nhap lua chon cua ban: ");
	char c = getch();
	switch (c)
	{
	case VK_RETURN:
		clrscr();
		ThemSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case  VK_BACK:
		clrscr();
		ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default:
		OptionThemSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	}
}
void ThemSach(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	FILE *f = fopen("Sach.txt", "r+b");
	Sach *a = new Sach;
	int x = 1;

	rewind(stdin);
	ChonTheLoaiSach(a->TheLoai);
	clrscr();
	InDSSachKhongOption(lsach);
	gotoxy(114, 6 + 2 * lsach.n);
	puts(a->TheLoai);
	do
	{
		gotoxy(3, 6 + 2 * lsach.n);
		rewind(stdin);
		gets_s(a->MaISBN);
	} while (CheckMaSach(lsach, a->MaISBN) == false);
	gotoxy(15, 6 + 2 * lsach.n);
	rewind(stdin);
	gets_s(a->TenSach);
	gotoxy(53, 6 + 2 * lsach.n);
	rewind(stdin);
	gets_s(a->TacGia);
	gotoxy(80, 6 + 2 * lsach.n);
	rewind(stdin);
	gets_s(a->NXB);
	gotoxy(106, 6 + 2 * lsach.n);
	scanf("%d", &a->NamXB);
	gotoxy(140, 6 + 2 * lsach.n);
	rewind(stdin);
	gets_s(a->GiaSach);
	gotoxy(158, 6 + 2 * lsach.n);
	scanf("%d", &a->SoQuyen);
	rewind(stdin);
	lsach.n++;
	addLast(lsach, (Sach*)a); //them vao LIST l
	fseek(f, 0, SEEK_SET);   // ghi n vao dau file, n la so sach
	fwrite(&lsach.n, sizeof(int), 1, f);
	fseek(f, 0, SEEK_END);
	fwrite(a, sizeof(Sach), 1, f); // ghi vao file
	fclose(f);
	OptionThemSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
}
void ThemLaiSach(LIST &l) // ghi loai toan bo ds vao file
{
	FILE *f = fopen("Sach.txt", "wb");
	fwrite(&l.n, sizeof(int), 1, f);
	for (NODE*p = l.pHead; p; p = p->pNext)
	{
		fwrite(p->key, sizeof(Sach), 1, f);
	}
	fclose(f);
}
void InDSSachKhongOption(LIST &l)  //in ds doc gia khong lua chon quay ve menu
{
	khungds(l.n);
	int i = 1;
	textcolor(15);
	for (NODE*p = l.pHead; p; p = p->pNext)
	{
		gotoxy(3, 4 + 2 * i);
		printf("%s", ((Sach*)p->key)->MaISBN);       //4*2+i là toa do y de in ds
		gotoxy(15, 4 + 2 * i);
		puts(((Sach*)p->key)->TenSach);
		gotoxy(53, 4 + 2 * i);
		puts(((Sach*)p->key)->TacGia);
		gotoxy(80, 4 + 2 * i);
		puts(((Sach*)p->key)->NXB);
		gotoxy(106, 4 + 2 * i);
		printf("%d", ((Sach*)p->key)->NamXB);
		gotoxy(114, 4 + 2 * i);
		puts(((Sach*)p->key)->TheLoai);
		gotoxy(140, 4 + 2 * i);
		puts(((Sach*)p->key)->GiaSach);
		gotoxy(158, 4 + 2 * i);
		printf("%d", ((Sach*)p->key)->SoQuyen);
		i++;
	}
}
void InDSSach(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	khungds(lsach.n);
	int i = 1;
	textcolor(15);
	for (NODE*p = lsach.pHead; p; p = p->pNext)
	{
		gotoxy(3, 4 + 2 * i);
		printf("%s", ((Sach*)p->key)->MaISBN);       //4*2+i là toa do y de in ds
		gotoxy(15, 4 + 2 * i);
		puts(((Sach*)p->key)->TenSach);
		gotoxy(53, 4 + 2 * i);
		puts(((Sach*)p->key)->TacGia);
		gotoxy(80, 4 + 2 * i);
		puts(((Sach*)p->key)->NXB);
		gotoxy(106, 4 + 2 * i);
		printf("%d", ((Sach*)p->key)->NamXB);
		gotoxy(114, 4 + 2 * i);
		puts(((Sach*)p->key)->TheLoai);
		gotoxy(140, 4 + 2 * i);
		puts(((Sach*)p->key)->GiaSach);
		gotoxy(158, 4 + 2 * i);
		printf("%d", ((Sach*)p->key)->SoQuyen);
		i++;
	}
	gotoxy(70, 7 + 2 * lsach.n);
	textcolor(11);
	printf("BACKSPACE.");
	textcolor(15);
	printf("Chuc nang 3");
	gotoxy(70, 8 + 2 * lsach.n);
	textcolor(11);
	printf("ESC.");
	textcolor(15);
	printf("Menu");
	textcolor(11);
	gotoxy(70, 9 + 2 * lsach.n);
	printf("Nhap lua chon cua ban : ");
	char c = getch();
	switch (c)
	{
	case VK_BACK:

		clrscr();
		ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	case 27:
		Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default:
		clrscr();
		InDSSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	}
}
void In1Sach(LIST &l, NODE *p, int &x) // x de in sach trung ten,  x tang len moi khi in
{
	khungds(x);
	textcolor(15);
	gotoxy(3, 4 + 2 * x);
	printf("%s", ((Sach*)p->key)->MaISBN);       //4*2+i là toa do y de in ds
	gotoxy(15, 4 + 2 * x);
	puts(((Sach*)p->key)->TenSach);
	gotoxy(53, 4 + 2 * x);
	puts(((Sach*)p->key)->TacGia);
	gotoxy(80, 4 + 2 * x);
	puts(((Sach*)p->key)->NXB);
	gotoxy(106, 4 + 2 * x);
	printf("%d", ((Sach*)p->key)->NamXB);
	gotoxy(114, 4 + 2 * x);
	puts(((Sach*)p->key)->TheLoai);
	gotoxy(140, 4 + 2 * x);
	puts(((Sach*)p->key)->GiaSach);
	gotoxy(158, 4 + 2 * x);
	printf("%d", ((Sach*)p->key)->SoQuyen);
	x++;;
}
void ChinhSuaSachISBN(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu, char ISBN[11]) //Chinh sua tat ca thong tin 1 sach theo ma ISBN
{

	int i = 0, x = 1;
	for (NODE*p = lsach.pHead; p; p = p->pNext)
	{
		if (strcmp(((Sach*)p->key)->MaISBN, ISBN) == 0)
		{
			clrscr();
			i++;
			In1Sach(lsach, p, x);
			gotoxy(52, 10);
			textcolor(15);
			printf("Loai thong tin muon sua: ");
			textcolor(11);
			printf("(1 -> 8)");
			vekhung2(50, 9, 3);
			gotoxy(52, 12);
			textcolor(11);
			printf("ENTER. ");
			textcolor(15);
			printf("Tim tiep sach khac");
			gotoxy(52, 14);
			textcolor(11);
			printf("BACKSPACE. ");
			textcolor(15);
			printf("Chuc nang 3");
			textcolor(11);
			gotoxy(52, 16);
			printf("ESC. ");
			textcolor(15);
			printf("Menu\n");
			textcolor(11);
			gotoxy(52, 18);
			printf("Nhap lua chon cua ban: ");
			gotoxy(75, 18);
			char c = getch();
			textcolor(11);
			switch (c)
			{
			case '1':
				char tam[11];
				do
				{
					gotoxy(52, 20);
					printf("%c Cap nhat ma ISBN: ", 175);
					gets_s(tam);
				} while (CheckMaSach(lsach, tam) == false);
				strcpy(((Sach*)p->key)->MaISBN, tam);
				strcpy(ISBN, tam);
				clrscr();
				ChinhSuaSachISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, ISBN);
				break;
			case '2':
				gotoxy(52, 20);
				printf("%c Cap nhat ten sach: ", 175);
				rewind(stdin);
				gets_s(((Sach*)p->key)->TenSach);
				clrscr();
				ChinhSuaSachISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, ISBN);
				break;
			case '3':
				gotoxy(52, 20);
				printf("%c Cap nhat tac gia: ", 175);
				rewind(stdin);
				gets_s(((Sach*)p->key)->TacGia);
				clrscr();
				ChinhSuaSachISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, ISBN);
				break;
			case '4':
				gotoxy(52, 20);
				printf("%c Cap nhat nha xuat ban: ", 175);
				rewind(stdin);
				gets_s(((Sach*)p->key)->NXB);
				clrscr();
				ChinhSuaSachISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, ISBN);
				break;
			case '5':
				gotoxy(52, 20);
				printf("%c Cap nhat nam xuat ban: ", 175);
				scanf("%d", &((Sach*)p->key)->NamXB);
				rewind(stdin);
				clrscr();
				ChinhSuaSachISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, ISBN);
				break;
			case '6':
				ChonTheLoaiSach(((Sach*)p->key)->TheLoai);
				clrscr();
				ChinhSuaSachISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, ISBN);
				break;
			case '7':
				gotoxy(52, 20);
				printf("%c Cap nhat gia sach : ", 175);
				gets_s(((Sach*)p->key)->GiaSach);
				clrscr();
				ChinhSuaSachISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, ISBN);
				break;
			case '8':
				gotoxy(52, 20);
				printf("%c Cap nhat so quyen: ", 175);
				scanf("%d", &((Sach*)p->key)->SoQuyen);
				rewind(stdin);
				clrscr();
				ChinhSuaSachISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, ISBN);
				break;
			case VK_RETURN: //ENTER
				ThemLaiSach(lsach);
				clrscr();
				ChinhSuaThongTinSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
			case VK_BACK: //BACKSPACE
				clrscr();
				ThemLaiSach(lsach);
				ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
			case 27:
				Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;  //ESC
			default:
				clrscr();
				ThemLaiSach(lsach);
				ChinhSuaSachISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, ISBN);
				break;
			}
		}
	}
	if (i == 0)
	{
		textcolor(15);
		gotoxy(52, 12);
		printf("=> KHONG TIM THAY ISBN SACH");
		vekhung2(50, 14, 3);
		gotoxy(52, 15);
		textcolor(11);
		printf("ENTER. ");
		textcolor(15);
		printf("Tim tiep sach khac");
		gotoxy(52, 17);
		textcolor(11);
		printf("BACKSPACE. ");
		textcolor(15);
		printf("Chuc nang 3");
		textcolor(11);
		gotoxy(52, 19);
		printf("ESC. ");
		textcolor(15);
		printf("Menu\n");
		textcolor(11);
		gotoxy(52, 21);
		printf("Nhap lua chon cua ban: ");
		char c = getch();
		switch (c)
		{
		case VK_RETURN: //ENTER
			clrscr();
			ChinhSuaThongTinSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;

		case VK_BACK: //BACKSPACE
			clrscr();
			ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;  //ESC
		default:
			clrscr();
			ChinhSuaSachISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, ISBN);
			break;
		}
	}
}
void ChinhSuaThongTinSach(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	char ISBN[11];
	rewind(stdin);
	textcolor(11);
	gotoxy(52, 10);
	printf("%c Nhap Ma ISBN Cua Sach: ", 175);
	textcolor(15);
	gets_s(ISBN);
	ChinhSuaSachISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, ISBN);

}  //THEO MA ISBN
void OptionXoaSach(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	clrscr();
	InDSSachKhongOption(lsach);//in ds doc gia moi
	gotoxy(70, 7 + 2 * lsach.n);
	textcolor(11);
	printf("ENTER. ");
	textcolor(15);
	printf("Them tiep sach khac");
	gotoxy(70, 9 + 2 * lsach.n);
	textcolor(11);
	printf("BACKSPACE. ");
	textcolor(15);
	printf("Chuc nang 3");
	gotoxy(70, 11 + 2 * lsach.n);
	textcolor(11);
	printf("ESC. ");
	textcolor(15);
	printf("Menu\n");
	gotoxy(70, 13 + 2 * lsach.n);
	textcolor(11);
	printf("Nhap lua chon cua ban: ");
	char c = getch();
	switch (c)
	{
	case VK_RETURN:
		clrscr();
		XoaSachTheoISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case  VK_BACK:
		clrscr();
		ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default:
		OptionXoaSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	}
}
void XoaSachTheoISBN(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	char ISBN[11];
	int  i = 0, x = 1;
	if (lsach.pHead == NULL)
	{
		textcolor(11);
		printf("\t=> Hien khong co sach nao trong thu vien"); Sleep(1000);
		clrscr();
		ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
	}
	InDSSachKhongOption(lsach);
	textcolor(11);
	gotoxy(45, 7 + 2 * lsach.n);
	printf("%c Nhap ma ISBN cua sach muon xoa: ", 175);
	textcolor(15);
	gets_s(ISBN);
	if (strcmp(((Sach*)lsach.pHead->key)->MaISBN, ISBN) == 0)
	{
		//In1Sach(lsach, lsach.pHead, x);
		DeleteFirst(lsach);
		textcolor(11);
		gotoxy(45, 9 + 2 * lsach.n);
		printf("%c Da xoa sach nay", 175);
		Sleep(1000);
		i++;
		lsach.n--;
	}
	else
	{
		if (strcmp(((Sach*)lsach.pTail->key)->MaISBN, ISBN) == 0)
		{
			DeleteLast(lsach);
			textcolor(11);
			gotoxy(45, 9 + 2 * lsach.n);
			printf("%c Da xoa sach nay", 175);
			Sleep(1000);
			i++;
			lsach.n--;
		}
		for (NODE*p = lsach.pHead; p; p = p->pNext)
		{
			if (strcmp(((Sach*)p->key)->MaISBN, ISBN) == 0)
			{
				{
					DeleteMid(p);
					textcolor(11);
					gotoxy(45, 9 + 2 * lsach.n);
					printf("%c Da xoa sach nay", 175);
					Sleep(1000);
					i++;
					lsach.n--;
				}
			}
		}
	}
	if (i == 0)
	{
		textcolor(11);
		gotoxy(45, 9 + 2 * lsach.n);
		printf("%c KHONG TIM THAY MA ISBN TUONG UNG\n", 175);
		Sleep(1000);
	}
	else
		ThemLaiSach(lsach);  //tim thay sach theo ma isbn va xoa thi ghi lai list sach vao file
	OptionXoaSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
}
void OptionTimSachISBN(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu, char ISBN[11])
{
	int x = 1;
	for (NODE *p = lsach.pHead; p; p = p->pNext)
	{
		if (strcmp(((Sach*)p->key)->MaISBN, ISBN) == 0)
		{
			In1Sach(lsach, p, x);
		}
	}
	vekhung2(50, 11, 3);
	gotoxy(52, 12);
	textcolor(11);
	printf("ENTER. ");
	textcolor(15);
	printf("Tim tiep sach khac");
	gotoxy(52, 14);
	textcolor(11);
	printf("BACKSPACE. ");
	textcolor(15);
	printf("Chuc nang 3");
	textcolor(11);
	gotoxy(52, 16);
	printf("ESC. ");
	textcolor(15);
	printf("Menu\n");
	textcolor(11);
	gotoxy(52, 18);
	printf("Nhap lua chon cua ban: ");
	char c = getch();
	switch (c)
	{
	case VK_RETURN:

		clrscr();
		TimSachTheoISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case  VK_BACK:
		clrscr();
		ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default:
		clrscr();
		OptionTimSachISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, ISBN);
		break;
	}
}
void TimSachTheoISBN(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	char ISBN[11];
	int  i = 0, x = 1;
	if (lsach.pHead == NULL)
	{
		textcolor(11);
		printf("\t=> Hien khong co sach nao trong thu vien"); Sleep(1000);
		clrscr();
		ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
	}

	textcolor(11);
	gotoxy(52, 7);
	printf("%c Nhap ma ISBN cua sach muon tim: ", 175);
	textcolor(15);
	gets_s(ISBN);
	for (NODE*p = lsach.pHead; p; p = p->pNext)
	{
		if (strcmp(((Sach*)p->key)->MaISBN, ISBN) == 0)
		{
			i++;
		}
	}
	if (i == 0)
	{
		textcolor(15);
		gotoxy(52, 9);
		printf("=> KHONG TIM THAY MA ISBN TUONG UNG");
	}
	OptionTimSachISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, ISBN);
}
void OptionTimSachTheoTen(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu, char tensach[50])
{
	int x = 1;
	for (NODE *p = lsach.pHead; p; p = p->pNext)
	{
		if (stricmp(((Sach*)p->key)->TenSach, tensach) == 0)
		{
			In1Sach(lsach, p, x);
		}
	}
	vekhung2(50, 9 + 2 * x, 3);
	gotoxy(52, 10 + 2 * x);
	textcolor(11);
	printf("ENTER. ");
	textcolor(15);
	printf("Tim tiep sach khac");
	textcolor(11);
	gotoxy(52, 12 + 2 * x);
	printf("BACKSPACE. ");
	textcolor(15);
	printf("Chuc nang 3");
	textcolor(11);
	gotoxy(52, 14 + 2 * x);
	printf("ESC. ");
	textcolor(15);
	printf("Menu\n");
	textcolor(11);
	gotoxy(52, 16 + 2 * x);
	printf("Nhap lua chon cua ban: ");
	char c = getch();
	switch (c)
	{
	case VK_RETURN:

		clrscr();
		TimKiemSachTheoTen(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case  VK_BACK:
		clrscr();
		ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default:
		clrscr();
		OptionTimSachTheoTen(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, tensach);
		break;
	}
}
void TimKiemSachTheoTen(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	char tensach[50];
	int  i = 0, x = 1;
	if (lsach.pHead == NULL)
	{
		textcolor(11);
		printf("\t=> Hien khong co sach nao trong thu vien"); Sleep(1000);  //neu list khong co sach nao thi goi lai chuc nang 3
		clrscr();
		ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
	}
	textcolor(11);
	gotoxy(52, 7);
	printf("%c Nhap ten sach muon tim: ", 175);
	rewind(stdin);
	textcolor(15);
	gets_s(tensach);
	for (NODE *p = lsach.pHead; p; p = p->pNext)
	{
		if (stricmp(((Sach*)p->key)->TenSach, tensach) == 0)
		{
			i++;
		}
	}
	if (i == 0)
	{
		textcolor(15);
		gotoxy(52, 9);
		printf("=> KHONG TIM THAY SACH");
	}
	OptionTimSachTheoTen(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu, tensach);
}
void ChucNang3(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	clrscr();
	gotoxy(61, 11);
	textcolor(10);
	printf("* CHUC NANG 3: QUAN LY SACH *");
	if (chucvu != 'c')
	{
		vekhung(51, 10, 6);
		gotoxy(56, 13);
		textcolor(15);
		printf("1.Danh Sach Cac Sach");
		gotoxy(56, 15);
		printf("2.Them Sach");
		gotoxy(56, 17);
		printf("3.Chinh Sua Thong Tin Mot Quyen Sach");
		gotoxy(56, 19);
		printf("4.Xoa Thong Tin Sach");
		gotoxy(56, 21);
		printf("5.Tim Kiem Sach Theo Ma ISBN");
		gotoxy(56, 23);
		printf("6.Tim Kiem Sach Theo Ten Sach");
		gotoxy(61, 25);
		printf("Menu");
		textcolor(10);
		gotoxy(56, 25);
		printf("ESC. ");
		gotoxy(56, 27);
		printf("Nhap lua chon cua ban: ");
	}
	else
	{
		vekhung(51, 10, 2);
		gotoxy(56, 15);
		textcolor(15);
		printf("1.Tim Kiem Sach Theo Ma ISBN");
		gotoxy(56, 17);
		printf("2.Tim Kiem Sach Theo Ten Sach");
		gotoxy(61, 19);
		printf("Menu");
		textcolor(10);
		gotoxy(56, 19);
		printf("ESC. ");
		gotoxy(56, 21);
		printf("Nhap lua chon cua ban: ");
	}
	char c = getch();
	clrscr();
	switch (c)
	{
	case '1':
		if (chucvu != 'c')
		{
			InDSSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);  break;
		}
		else
		{
			TimSachTheoISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
	case '2':
		if (chucvu != 'c')
		{
			ThemSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);  break;
		}
		else
		{
			TimKiemSachTheoTen(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
	case '3':
		if (chucvu != 'c')
		{
			ChinhSuaThongTinSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
		else
		{
			ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
	case '4':
		if (chucvu != 'c')
		{
			XoaSachTheoISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);  break;
		}
		else
		{
			ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
	case '5':
		if (chucvu != 'c')
		{
			TimSachTheoISBN(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);  break;
		}
		else
		{
			ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
	case '6':
		if (chucvu != 'c')
		{
			TimKiemSachTheoTen(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);  break;
		}
		else
		{
			ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default: ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	}
}
int thisIsMagic(int day, int month, int year) //tong so ngay hien tai
{
	if (month < 3) {
		year--;
		month += 12;
	}
	return 365 * year + year / 4 - year / 100 + year / 400 + (153 * month - 457) / 5 + day - 306;
}
void Sau7Ngay(int day, int month, int year, int &day7, int &month7, int &year7) //ngay thang nam sau khi them 7 ngay
{
	int daymax = 0;
	switch (month)
	{
	case 1: case 3:case 5:case 7:case 8:case 10:case 12:daymax = 31; break;
	case 4: case 6: case 9: case 11: daymax = 30; break;
	case 2: if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) daymax = 29;
			else daymax = 28;
			break;
	}
	if (day <= daymax - 7)
	{
		day7 = day + 7;
		month7 = month;
		year7 = year;
	}
	else
	{
		int m = 7 - (daymax - day);
		day7 = m;
		if (month == 12)
		{
			month7 = 1;
			year7 = year + 1;
		}
		else
		{
			month7 = month + 1;
			year7 = year;
		}
	}
}
void khungsachmuon(int n, LIST l) //ve khung sach phuc vu cho viec chon ISBN muon sach
{
	textcolor(10);
	gotoxy(105, 2);
	printf("DANH SACH SACH %c%d%c", 175, n, 174);
	textcolor(15);
	for (int i = 1; i <= n - 1; i++)   // ve - - - 
	{
		for (int x = 75; x <= 162; x = x + 3)
		{
			gotoxy(x, 5 + 2 * i);
			printf(" - ");
		}
	}
	textcolor(11);
	for (int x = 75; x <= 162; x++)  //3 cot ngang
	{
		gotoxy(x, 3);
		printf("%c", 196);
	}
	for (int x = 75; x <= 162; x++)
	{
		gotoxy(x, 5);
		printf("%c", 196);
	}
	for (int x = 75; x <= 162; x++)
	{
		gotoxy(x, 5 + 2 * n);
		printf("%c", 196);
	}
	gotoxy(74, 3);        //goc trai tren
	printf("%c", 218);
	gotoxy(163, 3);     //goc phai tren
	printf("%c", 191);
	gotoxy(74, 5 + 2 * n);
	printf("%c", 192);    //goc trai duoi
	gotoxy(163, 5 + 2 * n);     //goc trai phai
	printf("%c", 217);
	for (int y = 4; y <= 4 + 2 * n; y++) //doc dau
	{
		gotoxy(74, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 4 + 2 * n; y++) //doc isbn
	{
		gotoxy(91 - 5, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 4 + 2 * n; y++) //doc ten sach
	{
		gotoxy(124, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 4 + 2 * n; y++)//doc tac gia
	{
		gotoxy(152, y);
		printf("%c", 179);
	}
	for (int y = 4; y <= 4 + 2 * n; y++)//doc so quyen
	{
		gotoxy(163, y);
		printf("%c", 179);
	}
	textcolor(10);
	gotoxy(81 - 5, 4);
	printf("1.ISBN(10)");
	gotoxy(101, 4);
	printf("2.TEN SACH");
	gotoxy(133, 4);
	printf("3.TAC GIA");
	gotoxy(153, 4);
	printf("4.SO QUYEN");
	textcolor(15);
	int y = 6;
	for (NODE *p = l.pHead; p; p = p->pNext)
	{
		gotoxy(81 - 5, y);
		puts(((Sach*)p->key)->MaISBN);
		gotoxy(92 - 5, y);
		puts(((Sach*)p->key)->TenSach);
		gotoxy(125, y);
		puts(((Sach*)p->key)->TacGia);
		gotoxy(155, y);
		printf("%d", ((Sach*)p->key)->SoQuyen);
		y += 2;
	}
}
void MuonSach(LIST &lsach, LIST &lmuonsach, PhieuMuonTra *b, int i) //lua chon sach thu i+1 muon muon
{
	gotoxy(2, 13 + 2 * i);
	printf("%c Nhap ma ISBN thu %d muon muon:            ", 175, i + 1);
	printf("\n\n                                          ");
	gotoxy(34, 13 + 2 * i);
	gets_s(b->ISBN[i]);
	if (CheckMaSach(lsach, b->ISBN[i]))
	{
		gotoxy(2, 15 + 2 * i);
		printf("=> ISBN khong ton tai.");
		Sleep(600);
		MuonSach(lsach, lmuonsach, b, i);
	}
	NODE *p;
	for (p = lsach.pHead; p; p = p->pNext)
	{
		if (strcmp(((Sach*)p->key)->MaISBN, b->ISBN[i]) == 0)
			break;
	}
	if (((Sach*)p->key)->SoQuyen >= 1)
		((Sach*)p->key)->SoQuyen--;
	else
	{
		gotoxy(2, 15 + 2 * i);
		printf("=> Sach da het. Vui long nhap sach khac.");
		Sleep(600);
		MuonSach(lsach, lmuonsach, b, i);
	}
}
void InPhieuMuonSach(LIST &ldocgia, LIST &lsach, LIST &lmuonsach, PhieuMuonTra *b, int n)
// in phieu muon sach sau khi lap xong hoac tra
{
	clrscr();
	textcolor(13);
	gotoxy(73, 5);
	printf("PHIEU MUON SACH");
	vekhung(56, 4, 12 + n * 2);
	NODE*p;
	for (p = ldocgia.pHead; p; p = p->pNext)
	{
		if (b->MaDocGia == ((DocGia*)p->key)->MaDocGia)
			break;
	}
	textcolor(15);
	gotoxy(59, 7);
	printf("%c Ma doc gia: %d", 175, ((DocGia*)p->key)->MaDocGia);
	gotoxy(59, 9);
	printf("%c Ho ten: %s", 175, ((DocGia*)p->key)->hoten);
	gotoxy(59, 11);
	printf("%c CMND: %s", 175, ((DocGia*)p->key)->CMND);
	gotoxy(59, 13);
	printf("%c Ngay sinh: %d/%d/%d", 175, ((DocGia*)p->key)->NgaySinh.day, ((DocGia*)p->key)->NgaySinh.month, ((DocGia*)p->key)->NgaySinh.year);
	gotoxy(59, 15);
	printf("%c Gioi tinh: %s", 175, ((DocGia*)p->key)->gioitinh);
	gotoxy(59, 17);
	printf("%c Email: %s", 175, ((DocGia*)p->key)->email);
	gotoxy(59, 19);
	printf("%c Ngay lap the: %d/%d/%d", 175, ((DocGia*)p->key)->NgayLapThe.day, ((DocGia*)p->key)->NgayLapThe.month, ((DocGia*)p->key)->NgayLapThe.year);
	gotoxy(59, 21);
	printf("%c Ngay het han: %d/%d/%d", 175, ((DocGia*)p->key)->NgayHetHan.day, ((DocGia*)p->key)->NgayHetHan.month, ((DocGia*)p->key)->NgayHetHan.year);
	gotoxy(59, 23);
	printf("%c Danh sach sach da muon:", 175);
	for (int i = 0; i < n; i++)
	{
		gotoxy(59, 25 + i * 2);
		for (p = lsach.pHead; p; p = p->pNext)
		{
			if (strcmp(((Sach*)p->key)->MaISBN, b->ISBN[i]) == 0)
				break;
		}
		printf("%c %d/ %s - %s", 175, i + 1, ((Sach*)p->key)->TenSach, ((Sach*)p->key)->MaISBN);
	}
	gotoxy(59, 25 + n * 2);
	printf("%c Ngay muon: %d/%d/%d", 175, b->ngaymuon.day, b->ngaymuon.month, b->ngaymuon.year);
	NgayThangNam ngaytradk;
	Sau7Ngay(b->ngaymuon.day, b->ngaymuon.month, b->ngaymuon.year, ngaytradk.day, ngaytradk.month, ngaytradk.year);
	gotoxy(59, 27 + n * 2);
	printf("%c Ngay tra du kien: %d/%d/%d", 175, ngaytradk.day, ngaytradk.month, ngaytradk.year);
}
void LapPhieuMuonSach(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
// lap phieu muon sach theo ma doc gia
{
	clrscr();
	textcolor(15);
	int a, i;
	PhieuMuonTra *b = new PhieuMuonTra;
	gotoxy(2, 5);
	textcolor(11);
	printf("* CHUC NANG 4: LAP PHIEU MUON SACH *");
	gotoxy(2, 7);
	textcolor(15);
	printf("%c Nhap ma doc gia:", 175);
	scanf("%d", &a);
	rewind(stdin);
	NODE *p;
	for (p = ldocgia.pHead; p; p = p->pNext)
	{
		if (a == ((DocGia*)p->key)->MaDocGia)
		{
			b->MaDocGia = a;
			break;
		}
	}
	if (p == NULL)
	{
		gotoxy(2, 9);
		printf("=> Khong ton tai doc gia. Vui long nhap lai");
		Sleep(1000);
		LapPhieuMuonSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		return;
	}
	NODE *q;
	for (q = lmuonsach.pHead; q; q = q->pNext)
	{
		if (a == ((PhieuMuonTra*)q->key)->MaDocGia)
			break;
	}
	if (q != NULL)
	{
		gotoxy(2, 9);
		printf("=> Doc gia can tra sach truoc khi muon\n");
		gotoxy(2, 11);
		textcolor(11);
		printf("ESC. ");
		textcolor(15);
		printf("Quay lai menu");
		textcolor(11);
		gotoxy(2, 13);
		printf("Nhap lua chon cua ban");
		do
		{
			if (_getch() == 27)
			{
				Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
				return;
			}
		} while (true);
	}
	else
	{
		do
		{
			gotoxy(2, 9);
			printf("%c Nhap ngay muon (dd_mm_yyyy):           ", 175);
			gotoxy(32, 9);
			scanf("%d %d %d", &b->ngaymuon.day, &b->ngaymuon.month, &b->ngaymuon.year);
			rewind(stdin);
		} while (CheckDay(b->ngaymuon.day, b->ngaymuon.month, b->ngaymuon.year) == false);
		if ((thisIsMagic(((DocGia*)p->key)->NgayHetHan.day, ((DocGia*)p->key)->NgayHetHan.month, ((DocGia*)p->key)->NgayHetHan.year) -
			thisIsMagic(b->ngaymuon.day, b->ngaymuon.month, b->ngaymuon.year)) < 0) //kiem tra han su dung cua the
		{
			gotoxy(2, 11);
			printf("The cua doc gia da het han.\n");
			textcolor(11);
			gotoxy(2, 13);
			printf("ESC. ");
			textcolor(15);
			printf("Quay lai menu");
			textcolor(11);
			gotoxy(2, 15);
			printf("Nhap lua chon cua ban");
			do
			{
				if (_getch() == 27)
				{
					Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
					return;
				}
			} while (_getch() != 27);
		}
		else
		{
			do
			{
				gotoxy(2, 11);
				printf("%c Nhap so loai sach muon muon (toi da 10):   ", 175);
				gotoxy(44, 11);
				scanf("%d", &b->sosachmuon);
				rewind(stdin);
			} while (b->sosachmuon > 10 || b->sosachmuon <= 0);
			khungsachmuon(lsach.n, lsach);
			for (int i = 0; i < b->sosachmuon; i++)
			{
				MuonSach(lsach, lmuonsach, b, i);
			}
			lmuonsach.n++;
			addLast(lmuonsach, b);
			FILE *f = fopen("Sach.txt", "wb");
			fwrite(&lsach.n, sizeof(int), 1, f);
			for (NODE *p = lsach.pHead; p; p = p->pNext)
				fwrite(p->key, sizeof(Sach), 1, f);
			fclose(f);
			f = fopen("MuonTraSach.txt", "r + b");
			fseek(f, 0, 0);
			fwrite(&lmuonsach.n, sizeof(int), 1, f);
			fseek(f, 0, SEEK_END);
			fwrite(b, sizeof(PhieuMuonTra), 1, f);
			fclose(f);
			InPhieuMuonSach(ldocgia, lsach, lmuonsach, b, b->sosachmuon);
			gotoxy(69, 31 + 2 * b->sosachmuon);
			printf("Tao them phieu muon sach");
			gotoxy(67, 33 + 2 * b->sosachmuon);
			printf("Menu");
			textcolor(13);
			gotoxy(62, 31 + 2 * b->sosachmuon);
			printf("ENTER. ");
			gotoxy(62, 33 + 2 * b->sosachmuon);
			printf("ESC. ");
			gotoxy(62, 35 + 2 * b->sosachmuon);
			printf("Nhap lua chon cua ban: ");
			char c = _getch();
			switch (c)
			{
			case 27: //ESC
				Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
				return;
			case VK_RETURN: //ENTER
				LapPhieuMuonSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
				return;
			default:
				Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
				return;
			}
		}
	}
}
void XoaPhieuMuon(LIST &l, int madocgia)
// xoa phieu muon sach khi tra sach thanh cong
{
	if (((PhieuMuonTra*)l.pHead->key)->MaDocGia == madocgia)
	{
		DeleteFirst(l);
		l.n--;
	}
	else
	{
		if (((PhieuMuonTra*)l.pTail->key)->MaDocGia == madocgia)
		{
			DeleteLast(l);
			l.n--;
		}
		for (NODE*p = l.pHead; p; p = p->pNext)
		{
			if (((PhieuMuonTra*)l.pTail->key)->MaDocGia == madocgia)
			{
				{
					DeleteMid(p);
					l.n--;
				}
			}
		}
	}
}
void LapPhieuTraSach(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
// lap phieu tra sach theo ma doc gia
{
	clrscr();
	gotoxy(57, 11);
	textcolor(11);
	printf("* CHUC NANG 5: LAP PHIEU TRA SACH *");
	vekhung2(50, 10, 2);
	if (lmuonsach.n == 0)
	{

		textcolor(15);
		gotoxy(52, 13);
		printf("%c Khong co doc gia nao muon sach", 175);
		textcolor(11);
		gotoxy(52, 15);
		printf("%c ESC. ", 175);
		textcolor(15);
		printf("Quay lai menu");
		gotoxy(52, 17);
		textcolor(11);
		printf("%c Nhap chuc nang ban muon", 175);
		char b = _getch();
		switch (b)
		{
		case 27:
			Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
			break;
		default:
			LapPhieuTraSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
			break;
		}
		return;
	}
	int a;
	textcolor(15);
	gotoxy(52, 13);
	printf("%c Nhap ma doc gia:", 175);
	scanf("%d", &a);
	rewind(stdin);
	NODE *p;
	for (p = ldocgia.pHead; p; p = p->pNext)
	{
		if (a == ((DocGia*)p->key)->MaDocGia)
			break;
	}
	if (p == NULL)
	{
		gotoxy(52, 15);
		printf("=> Khong ton tai doc gia. Vui long nhap lai.");
		Sleep(1000);
		LapPhieuTraSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		return;
	}
	NODE *q;
	for (q = lmuonsach.pHead; q; q = q->pNext)
	{
		if (a == ((PhieuMuonTra*)q->key)->MaDocGia)
			break;
	}
	if (q == NULL)
	{
		gotoxy(52, 15);
		printf("=> Doc gia chua muon sach.");
		textcolor(11);
		gotoxy(52, 17);
		printf("ESC. ");
		textcolor(15);
		printf("Quay lai menu");
		textcolor(11);
		gotoxy(52, 19);
		printf("Nhap lua chon cua ban");
		do
		{
			if (_getch() == 27)
			{
				Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
				return;
			}
		} while (true);
	}
	else
	{
		InPhieuMuonSach(ldocgia, lsach, lmuonsach, (PhieuMuonTra*)q->key, ((PhieuMuonTra*)q->key)->sosachmuon);
		textcolor(15);
		NgayThangNam ngaytratt;
		int phat = 0;
		do
		{
			gotoxy(2, 15);
			printf("%c Ngay tra thuc te (dd_mm_yyyy):           ", 175);
			gotoxy(34, 15);
			scanf("%d %d %d", &ngaytratt.day, &ngaytratt.month, &ngaytratt.year);
			rewind(stdin);
		} while (CheckDay(ngaytratt.day, ngaytratt.month, ngaytratt.year) == false);
		int tam = thisIsMagic(ngaytratt.day, ngaytratt.month, ngaytratt.year)
			- thisIsMagic(((PhieuMuonTra*)q->key)->ngaymuon.day, ((PhieuMuonTra*)q->key)->ngaymuon.month, ((PhieuMuonTra*)q->key)->ngaymuon.year);
		int ngaytre;
		if (tam > 7)
			ngaytre = tam - 7;
		else ngaytre = 0;
		if (ngaytre > 0)
			phat += ngaytre * 5000;
		int sachmat;
		gotoxy(2, 17);
		printf("%c Nhap so sach bi mat:", 175);
		scanf("%d", &sachmat);
		rewind(stdin);
		if (sachmat > 0)
		{
			int *b = new int[sachmat];
			for (int i = 0; i < sachmat; i++)
			{
				do
				{
					gotoxy(2, 19 + i * 2);
					printf("%c Nhap so thu tu sach bi mat:   ", 175);
					gotoxy(32, 19 + i * 2);
					scanf("%d", &b[i]);
					rewind(stdin);
				} while (b[i] >((PhieuMuonTra*)q->key)->sosachmuon || b[i] <= 0);
				for (p = lsach.pHead; p; p = p->pNext)
				{
					if (strcmp(((PhieuMuonTra*)q->key)->ISBN[b[i] - 1], ((Sach*)p->key)->MaISBN) == 0)
						break;
				}
				phat += 2 * atoi(((Sach*)p->key)->GiaSach);
			}
			for (int i = 0; i < ((PhieuMuonTra*)q->key)->sosachmuon; i++)
			{
				int j = 0;
				for (j = 0; j < sachmat; j++)
				{
					if (i == b[j] - 1)
						break;
				}
				if (j == sachmat)
				{
					for (p = lsach.pHead; p; p = p->pNext)
					{
						if (strcmp(((PhieuMuonTra*)q->key)->ISBN[i], ((Sach*)p->key)->MaISBN) == 0)
							break;
					}
					((Sach*)p->key)->SoQuyen++;
				}
			}

		}
		else
		{
			for (int i = 0; i < ((PhieuMuonTra*)q->key)->sosachmuon; i++)
			{
				for (p = lsach.pHead; p; p = p->pNext)
				{
					if (strcmp(((PhieuMuonTra*)q->key)->ISBN[i], ((Sach*)p->key)->MaISBN) == 0)
						break;
				}
				((Sach*)p->key)->SoQuyen++;
			}
		}
		gotoxy(2, 19 + sachmat * 2);
		printf("=> Ban bi tre %d ngay - Tien phat: %d d\n", ngaytre, phat);
		XoaPhieuMuon(lmuonsach, a);
		FILE *f1 = fopen("Sach.txt", "wb");
		fwrite(&lsach.n, sizeof(int), 1, f1);
		for (NODE *p = lsach.pHead; p; p = p->pNext)
			fwrite(p->key, sizeof(Sach), 1, f1);
		fclose(f1);
		FILE *f = fopen("MuonTraSach.txt", "wb");
		fwrite(&lmuonsach.n, sizeof(int), 1, f);
		for (p = lmuonsach.pHead; p; p = p->pNext)
			fwrite(p->key, sizeof(PhieuMuonTra), 1, f);
		fclose(f);
		gotoxy(9, 21 + sachmat * 2);
		printf("Tao them phieu tra sach");
		gotoxy(7, 23 + sachmat * 2);
		printf("Menu");
		textcolor(11);
		gotoxy(2, 21 + sachmat * 2);
		printf("ENTER. ");
		gotoxy(2, 23 + sachmat * 2);
		printf("ESC. ");
		gotoxy(2, 25 + sachmat * 2);
		printf("Nhap lua chon cua ban: ");
		char c = _getch();
		switch (c)
		{
		case 27: //ESC
			Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
			break;
		case VK_RETURN: //ENTER
			LapPhieuTraSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
			break;
		default:
			Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
			break;
		}
	}
}
void ChucNang6(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu);
void SoLuongSach(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
// thong ke tong so loai sach trong thu vien
{
	clrscr();
	vekhung2(51, 10, 1);
	textcolor(15);
	gotoxy(58, 11);
	printf("%c So luong sach trong thu vien: %d %c", 175, lsach.n, 174);
	gotoxy(69, 13);
	printf("Chuc nang 6");
	gotoxy(63, 15);
	printf("Menu");
	textcolor(11);
	gotoxy(58, 13);
	printf("BACKSPACE. ");
	gotoxy(58, 15);
	printf("ESC. ");
	gotoxy(58, 17);
	printf("Nhap lua chon cua ban: ");
	char c = getch();
	switch (c)
	{
	case VK_BACK://BACKSPACE
		clrscr();
		ChucNang6(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default: clrscr(); SoLuongSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	}
}
void SoLuongSachTheoTheLoai(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
// thong ke so luong sach theo tung the loai
{

	clrscr();
	FILE *f;
	int x = 15, y = 5, n = 0, dem = 0;
	f = fopen("TheLoaiSach.txt", "rb");
	fread(&n, sizeof(int), 1, f); //l.n la so luong the loai dang co
	gotoxy(60, 2);
	textcolor(11);
	printf("NHUNG THE LOAI SACH HIEN CO %c %d %c", 175, n, 174);
	textcolor(15);
	char a[35];
	for (int i = 1; i <= n; i++)          // Doc Va In Cac The Loai Sach Trong Thu Vien
	{
		fread(a, (sizeof(char)) * 35, 1, f);
		{
			{
				for (NODE *p = lsach.pHead; p; p = p->pNext)  // neu sach nao co the loai trung thi tang bien dem
				{
					if (stricmp(((Sach*)p->key)->TheLoai, a) == 0)
					{
						dem++;
					}
				}
			}
		}
		gotoxy(x, y);
		printf("%s: %d", a, dem);
		if (x == 105)      // tang x,y de in cho phu hop
		{
			x = 15;
			y++;
		}
		else x += 30;
		dem = 0;
	}
	for (int x = 6; x <= 140; x++)  //2 ngang
	{
		gotoxy(x, 4);
		printf("%c", 196);
	}
	for (int x = 6; x <= 140; x++)
	{
		gotoxy(x, y + 1);
		printf("%c", 196);
	}
	for (int l = 5; l <= y; l++)    // 2 doc
	{
		gotoxy(5, l);
		printf("%c", 179);
	}
	for (int l = 5; l <= y; l++)
	{
		gotoxy(141, l);
		printf("%c", 179);
	}
	gotoxy(5, 4);        //goc trai tren
	printf("%c", 218);
	gotoxy(141, 4);     //goc phai tren
	printf("%c", 191);
	gotoxy(5, y + 1);
	printf("%c", 192);    //goc trai duoi
	gotoxy(141, y + 1);     //goc phai duoi
	printf("%c", 217);
	fclose(f);
	textcolor(15);
	gotoxy(70, y + 4);
	printf("Chuc nang 6");
	gotoxy(64, y + 6);
	printf("Menu");
	textcolor(11);
	gotoxy(59, y + 4);
	printf("BACKSPACE. ");
	gotoxy(59, y + 6);
	printf("ESC. ");
	gotoxy(59, y + 8);
	printf("Nhap lua chon cua ban: ");
	char c = getch();

	switch (c)
	{
	case VK_BACK:
		clrscr();
		ChucNang6(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default: clrscr();  SoLuongSachTheoTheLoai(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	}
}
void SoLuongDocGia(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
// thong ke so luong doc gia trong thu vien
{
	clrscr();
	vekhung2(51, 10, 1);
	textcolor(15);
	gotoxy(58, 11);
	printf("%c So luong doc gia trong thu vien: %d %c", 175, ldocgia.n, 174);
	gotoxy(69, 13);
	printf("Chuc nang 6");
	gotoxy(63, 15);
	printf("Menu");
	textcolor(11);
	gotoxy(58, 13);
	printf("BACKSPACE. ");
	gotoxy(58, 15);
	printf("ESC. ");
	gotoxy(58, 17);
	printf("Nhap lua chon cua ban: ");
	char c = getch();
	switch (c)
	{
	case VK_BACK:
		clrscr();
		ChucNang6(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default:clrscr();  SoLuongDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	}
}
void SoLuongDocGiaTheoGioiTinh(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
// thong ke so luong doc gia theo gioi tinh Nam, Nu, Khac
{
	int *a = new int[3]; a[1] = 0; a[2] = 0; a[3] = 0;
	for (NODE *p = ldocgia.pHead; p; p = p->pNext)
	{
		if (stricmp(((DocGia*)p->key)->gioitinh, "Nam") == 0) a[1]++;
		if (stricmp(((DocGia*)p->key)->gioitinh, "Nu") == 0) a[2]++;
		if (stricmp(((DocGia*)p->key)->gioitinh, "Khac") == 0) a[3]++;
	}
	vekhung2(51, 10, 4);
	textcolor(15);
	gotoxy(58, 11);
	printf("%c Gioi tinh nam: %d doc gia %c", 175, a[1], 174);
	gotoxy(58, 13);
	printf("%c Gioi tinh nu: %d doc gia %c", 175, a[2], 174);
	gotoxy(58, 15);
	printf("%c Gioi tinh khac: %d doc gia %c", 175, a[3], 174);
	gotoxy(69, 17);
	printf("Chuc nang 6");
	gotoxy(63, 19);
	printf("Menu");
	textcolor(11);
	gotoxy(58, 17);
	printf("BACKSPACE. ");
	gotoxy(58, 19);
	printf("ESC. ");
	gotoxy(58, 21);
	printf("Nhap lua chon cua ban: ");
	char c = getch();
	switch (c)
	{
	case VK_BACK:
		clrscr();
		ChucNang6(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case 27:  Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default: clrscr();  SoLuongSachTheoTheLoai(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	}
}
void SoSachDangDuocMuon(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
// thong ke so sach dang duoc muon
{
	clrscr();
	int sachdangmuon = 0;
	for (NODE*p = lmuonsach.pHead; p; p = p->pNext)
		sachdangmuon += ((PhieuMuonTra*)p->key)->sosachmuon;
	vekhung2(51, 10, 1);
	textcolor(15);
	gotoxy(58, 11);
	printf("%c So sach dang duoc muon: %d %c", 175, sachdangmuon, 174);
	gotoxy(69, 13);
	printf("Chuc nang 6");
	gotoxy(63, 15);
	printf("Menu");
	textcolor(11);
	gotoxy(58, 13);
	printf("BACKSPACE. ");
	gotoxy(58, 15);
	printf("ESC. ");
	gotoxy(58, 17);
	printf("Nhap lua chon cua ban: ");
	char c = getch();
	switch (c)
	{
	case VK_BACK: //BACKSPACE
		clrscr();
		ChucNang6(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default: SoSachDangDuocMuon(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	}
}
void SoDocGiaBiTreHan(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
// thong ke so doc gia bi tre han tra sach so voi thoi gian he thong
{
	clrscr();
	int docgiatrehan = 0;
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	for (NODE*p = lmuonsach.pHead; p; p = p->pNext)
	{
		if (thisIsMagic(timeinfo->tm_mday, 1 + timeinfo->tm_mon, 1900 + timeinfo->tm_year)
			- thisIsMagic(((PhieuMuonTra*)p->key)->ngaymuon.day, ((PhieuMuonTra*)p->key)->ngaymuon.month, ((PhieuMuonTra*)p->key)->ngaymuon.year) > 7)
			docgiatrehan++;
	}
	vekhung2(51, 10, 1);
	textcolor(15);
	gotoxy(58, 11);
	printf("%c So doc gia bi tre han: %d %c", 175, docgiatrehan, 174);
	gotoxy(69, 13);
	printf("Chuc nang 6");
	gotoxy(63, 15);
	printf("Menu");
	textcolor(11);
	gotoxy(58, 13);
	printf("BACKSPACE. ");
	gotoxy(58, 15);
	printf("ESC. ");
	gotoxy(58, 17);
	printf("Nhap lua chon cua ban: ");
	char c = getch();
	switch (c)
	{
	case VK_BACK: //BACKSPACE
		clrscr();
		ChucNang6(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default: SoDocGiaBiTreHan(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	}
}
void ChucNang6(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{
	clrscr();
	gotoxy(58, 11);
	textcolor(10);
	printf("* CHUC NANG 6: CAC THONG KE CO BAN *");
	if (chucvu != 'c')
	{
		vekhung(51, 10, 6);
		gotoxy(56, 13);
		textcolor(15);
		printf("1.So Luong Sach Trong Thu Vien");
		gotoxy(56, 15);
		printf("2.So Luong Sach Theo The Loai");
		gotoxy(56, 17);
		printf("3.So Luong Doc Gia");
		gotoxy(56, 19);
		printf("4.So Luong Doc Gia Theo Gioi Tinh");
		gotoxy(56, 21);
		printf("5.So Luong Sach Dang Duoc Muon");
		gotoxy(56, 23);
		printf("6.So Luong Doc Gia Bi Tre Han");
		gotoxy(61, 25);
		printf("Menu");
		textcolor(10);
		gotoxy(56, 25);
		printf("ESC. ");
		gotoxy(56, 27);
		printf("Nhap lua chon cua ban: ");
	}
	else
	{
		vekhung(51, 10, 2);
		gotoxy(56, 15);
		textcolor(15);
		printf("1.So Luong Sach Dang Duoc Muon");
		gotoxy(56, 17);
		printf("2.So Luong Doc Gia Bi Tre Han");
		gotoxy(61, 19);
		printf("Menu");
		gotoxy(56, 19);
		textcolor(10);
		printf("ESC. ");
		gotoxy(56, 21);
		printf("Nhap lua chon cua ban: ");
	}
	char c = getch();
	clrscr();
	switch (c)
	{
	case '1':
		if (chucvu != 'c')
		{
			SoLuongSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);  break;
		}
		else
		{
			SoSachDangDuocMuon(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
	case '2':
		if (chucvu != 'c')
		{
			SoLuongSachTheoTheLoai(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);  break;
		}
		else
		{
			SoDocGiaBiTreHan(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
	case '3':
		if (chucvu != 'c')
		{
			SoLuongDocGia(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
		else
		{
			ChucNang6(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
	case '4':
		if (chucvu != 'c')
		{
			SoLuongDocGiaTheoGioiTinh(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
		else
		{
			ChucNang6(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
	case '5':
		if (chucvu != 'c')
		{
			SoSachDangDuocMuon(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
		else
		{
			ChucNang6(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
	case '6':
		if (chucvu != 'c')
		{
			SoDocGiaBiTreHan(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
		else
		{
			ChucNang6(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
		}
	case 27: Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	default: ChucNang6(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu); break;
	}
}
void VeThuVien(bool &yes, char &c);
void Menu(int argc, _TCHAR* argv[], LIST &ltaikhoan, LIST &lthongtincanhan, LIST &ldocgia, LIST &lsach, LIST &lmuonsach, char chucvu)
{

	clrscr();
	char c;
	bool yes = true;
	vekhung(48, 16, 8);
	gotoxy(61, 17);
	textcolor(11);
	printf("%c QUAN LY THU VIEN %c", 175, 174);
	textcolor(15);
	gotoxy(54, 19);
	printf("1.Quan Ly Tai Khoan");
	gotoxy(54, 21);
	printf("2.Quan Ly Doc Gia");
	gotoxy(54, 23);
	printf("3.Quan Ly Sach");
	gotoxy(54, 25);
	printf("4.Lap Phieu Muon Sach");
	gotoxy(54, 27);
	printf("5.Lap Phieu Tra Sach");
	gotoxy(54, 29);
	printf("6.Cac Thong Ke Co Ban");
	gotoxy(54, 31);
	textcolor(11);
	printf("ESC. ");
	textcolor(15);
	printf("Dang Xuat");
	textcolor(11);
	gotoxy(54, 33);
	printf("Nhap lua chon cua ban: ");
	VeThuVien(yes, c);
	if (yes == true)
	{
		gotoxy(77, 33);
		c = getch();
	}
	switch (c)
	{
	case '1':
		TK(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case '2':
		ChucNang2(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case '3':
		ChucNang3(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case '4':
		LapPhieuMuonSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case '5':
		LapPhieuTraSach(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case '6':
		ChucNang6(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	case 27:
		DangXuat();
		break;
	default:
		Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		break;
	}
}
void VeThuVien(bool &yes, char &c)
{
	textcolor(9);
	for (int y = 4; y <= 10; y++) //L
	{
		gotoxy(35, y);
		printf("%c%c", 219, 219);
	}
	for (int x = 36; x <= 43; x++)
	{
		gotoxy(x, 10);
		printf("%c", 219);
	}
	for (int y = 4; y <= 10; y++) //I
	{
		gotoxy(46, y);
		printf("%c%c", 219, 219);
	}
	for (int y = 4; y <= 10; y++) //B
	{
		gotoxy(50, y);
		printf("%c%c", 219, 219);
	}
	for (int x = 51; x <= 54; x++) //net ngang tren dau
	{
		gotoxy(x, 4);
		printf("%c%c", 219, 219);
	}
	gotoxy(55, 4);
	printf("%c%c%c", 219, 219, 219);
	for (int y = 5; y <= 9; y++) //net doc
	{
		gotoxy(58, y);
		printf("%c%c", 219, 219);
	}
	for (int x = 51; x <= 56; x++) //net ngang giua
	{
		gotoxy(x, 7);
		printf("%c%c", 219, 219);
	}
	for (int x = 51; x <= 54; x++)//net ngang cuoi
	{
		gotoxy(x, 10);
		printf("%c%c", 219, 219);
	}
	gotoxy(55, 10);
	printf("%c%c%c", 219, 219, 219);
	for (int x = 61; x <= 69; x++) //R
	{
		gotoxy(x, 4);
		printf("%c%c", 219, 219);
	}
	for (int y = 4; y <= 10; y++)
	{
		gotoxy(61, y);
		printf("%c%c", 219, 219);
	}
	for (int x = 61; x <= 69; x++)
	{
		gotoxy(x, 7);
		printf("%c%c", 219, 219);
	}
	for (int y = 4; y <= 7; y++)
	{
		gotoxy(69, y);
		printf("%c%c", 219, 219);
	}
	int y = 7;
	for (int x = 61; x <= 69; x++)
	{
		gotoxy(x, y);
		printf("%c%c", 219, 219);
		if ((x % 2 != 0) && (x != 61)) y++;
	}
	for (int y = 4; y <= 10; y++) //A
	{
		gotoxy(73, y);
		printf("%c%c", 219, 219);
	}
	for (int x = 73; x <= 81; x++)
	{
		gotoxy(x, 4);
		printf("%c%c", 219, 219);
	}
	for (int y = 4; y <= 10; y++)
	{
		gotoxy(81, y);
		printf("%c%c", 219, 219);
	}
	for (int x = 73; x <= 81; x++)
	{
		gotoxy(x, 7);
		printf("%c%c", 219, 219);
	}
	for (int x = 85; x <= 93; x++) //R
	{
		gotoxy(x, 4);
		printf("%c%c", 219, 219);
	}
	for (int y = 4; y <= 10; y++)
	{
		gotoxy(85, y);
		printf("%c%c", 219, 219);
	}
	for (int x = 85; x <= 93; x++)
	{
		gotoxy(x, 7);
		printf("%c%c", 219, 219);
	}
	for (int y = 4; y <= 7; y++)
	{
		gotoxy(93, y);
		printf("%c%c", 219, 219);
	}
	y = 7;
	for (int x = 85; x <= 93; x++)
	{
		gotoxy(x, y);
		printf("%c%c", 219, 219);
		if ((x % 2 != 0) && (x != 85)) y++;
	}
	for (int y = 4; y <= 7; y++)
	{
		gotoxy(97, y);
		printf("%c%c", 219, 219);
	}
	for (int x = 97; x <= 105; x++)
	{
		gotoxy(x, 7);
		printf("%c%c", 219, 219);
	}
	for (int y = 4; y <= 10; y++)
	{
		gotoxy(105, y);
		printf("%c%c", 219, 219);
	}
	for (int x = 97; x <= 105; x++)
	{
		gotoxy(x, 10);
		printf("%c%c", 219, 219);
	}
	for (int i = 9; i <= 14; i++)
	{
		textcolor(i);
		for (int x = 35; x <= 105; x++)
		{
			gotoxy(x, 12);
			printf("%c%c", 219, 219);
			Sleep(6);
		}
		textcolor(15 - i);
		for (int x = 105; x >= 35; x--)
		{
			gotoxy(x, 12);
			printf("%c%c", 219, 219);
			Sleep(6);

		}
		if (kbhit())
		{
			c = getch();
			yes = false;
			break;

		}
	}
}
void DangNhap(int argc, _TCHAR* argv[])
{
	resizeConsole(1366, 768);
	FILE *f1 = fopen("acc.txt", "rb"); FILE *f2 = fopen("thongtincanhan.txt", "rb");
	LIST ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach;
	KhoiTao(ltaikhoan); KhoiTao(lthongtincanhan); KhoiTao(ldocgia); KhoiTao(lsach); KhoiTao(lmuonsach);
	fread(&ltaikhoan.n, sizeof(int), 1, f1);
	TaiKhoan *tam = new TaiKhoan[ltaikhoan.n];
	fread(&lthongtincanhan.n, sizeof(int), 1, f2);
	ThongTinCaNhan *temp = new ThongTinCaNhan[lthongtincanhan.n];
	for (int i = 0; i < ltaikhoan.n; i++)
	{
		fread(tam + i, sizeof(TaiKhoan), 1, f1);
		addLast(ltaikhoan, tam + i);
		fread(temp + i, sizeof(ThongTinCaNhan), 1, f2);
		addLast(lthongtincanhan, temp + i);
	}
	fclose(f1);
	fclose(f2);
	FILE *f3 = fopen("DSDocGia.txt", "rb");
	fread(&ldocgia.n, sizeof(int), 1, f3);
	DocGia *docgia = new DocGia[ldocgia.n];
	for (int i = 0; i < ldocgia.n; i++)
	{
		fread(docgia + i, sizeof(DocGia), 1, f3);
		addLast(ldocgia, docgia + i);
	}
	fclose(f3);
	FILE *f4 = fopen("Sach.txt", "rb");
	fread(&lsach.n, sizeof(int), 1, f4);
	Sach *sach = new Sach[lsach.n];
	for (int i = 0; i < lsach.n; i++)
	{
		fread(sach + i, sizeof(Sach), 1, f4);
		addLast(lsach, sach + i);
	}
	fclose(f4);
	FILE *f5 = fopen("MuonTraSach.txt", "rb");
	if (f5 != NULL)
	{
		fread(&lmuonsach.n, sizeof(int), 1, f5);
		PhieuMuonTra *muonsach = new PhieuMuonTra[lmuonsach.n];
		for (int i = 0; i < lmuonsach.n; i++)
		{
			fread(muonsach + i, sizeof(PhieuMuonTra), 1, f5);
			addLast(lmuonsach, muonsach + i);
		}
		fclose(f5);
	}
	char chucvu;
	NODE *p = ltaikhoan.pHead;
	NODE *q = lthongtincanhan.pHead;
	while (p != NULL)
	{
		if (strcmp(wchar_to_string(argv[1]), ((TaiKhoan*)p->key)->id) == 0 && strcmp(wchar_to_string(argv[2]), ((TaiKhoan*)p->key)->pass) == 0)
		{
			chucvu = ((TaiKhoan*)p->key)->chucvu;
			break;
		}
		p = p->pNext;
		q = q->pNext;
	}
	if (p == NULL)
		printf("Sai id hoac pass.");
	else
	{
		if (((ThongTinCaNhan*)q->key)->tinhtrang == 'b')
			printf("Tai khoan da bi Block.");
		else
		{
			printf("Dang nhap thanh cong.\nHe thong dang xu ly...");
			Sleep(1000);
			Menu(argc, argv, ltaikhoan, lthongtincanhan, ldocgia, lsach, lmuonsach, chucvu);
		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	DangNhap(argc, argv);
	return 0;
}