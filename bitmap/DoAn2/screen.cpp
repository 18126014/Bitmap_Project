#include <stdlib.h>
#include <iostream>
#include "screen.h"

using namespace std;

void mainscreen()
{
	system("cls");
	cout << "=====================MENU====================" << endl;
	cout << "\t 1. Chinh do sang" << endl;
	cout << "\t 2. Chinh do tuong phan" << endl;
	cout << "\t 3. Chinh do bao hoa mau" << endl;
	cout << "\t 4. Phong to anh" << endl;
	cout << "\t 5. Thu nho anh" << endl;
	cout << "\t 6. Chuyen anh am ban" << endl;
	cout << "\t 7. Blend mau" << endl;
	cout << "\t 8. Chuyen thanh anh trang den" << endl;
	cout << "\t 9. Chuyen thanh anh xam" << endl;
	cout << "\t 10. Lat anh theo truc doc" << endl;
	cout << "\t 11. Lat anh theo truc ngang" << endl;
	cout << "\t 12. Ghep 2 anh cung chieu rong" << endl;
	cout << "\t 13. Chen them icon vao anh" << endl;
	cout << "\t 14. Xoay anh" << endl;
	cout << "\t 15. Cat anh" << endl;
	cout << "\t 16. Lam mo anh" << endl;
	cout << "\t 17. Tang do sac net cua anh" << endl;
	cout << "==============================================" << endl;
} 

void blend()
{
	system("cls");
	cout << "===================BLEND====================" << endl;
	cout << "\t 1. Blend mau do" << endl;
	cout << "\t 2. Blend mau xanh la" << endl;
	cout << "\t 3. Blend mau xanh lam" << endl;
	cout << "\t 4. Blend mau cyan" << endl;
	cout << "\t 5. Blend mau magenta" << endl;
	cout << "\t 6. Blend mau vang" << endl;
	cout << "============================================" << endl;
}

void rotate()
{
	system("cls");
	cout << "=================ROTATE=====================" << endl;
	cout << "\t 1. Xoay anh 90 do" << endl;
	cout << "\t 2. Xoay anh 180 do" << endl;
	cout << "\t 3. Xoay anh 270 do" << endl;
	cout << "============================================" << endl;
}

void cut()
{
	system("cls");
	cout << "=================cut=====================" << endl;
	cout << "\t 1. Cat dau anh" << endl;
	cout << "\t 2. Cat duoi anh" << endl;
	cout << "\t 3. Cat ben phai anh" << endl;
	cout << "\t 4. Cat ben trai anh" << endl;
	cout << "============================================" << endl;
}
