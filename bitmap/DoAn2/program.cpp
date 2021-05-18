/*
	Code mau Do an 2 - Xu ly anh, PPLTTT - 18VP
	Vu Quoc Hoang, FIT - HCMUS, 03/2019
*/
#include <iostream>
#include "Bitmap.h"
#include "screen.h"

using namespace std;

int main()
{
	char *inFileName = "MARBLES.BMP";
	char *inFileName2 = "test.bmp";
	char *outFileName = "out.bmp";
	Bitmap bmp, bmp2, outbmp;

	if(LoadBitmap(inFileName, bmp) && LoadBitmap(inFileName2, bmp2))
	{	
		int luachon;
		while(1)
		{
			mainscreen();
			cout << "Moi nhap lua chon: ";
			cin >> luachon;
			if(luachon == 1)
			{
				float k;
				cout << endl << "Nhap he so k (0 < k < 2): ";
				cin >> k;
				AdjustBrightness(bmp, outbmp, k);
			}
			else if(luachon == 2)
			{
				float k;
				cout << endl << "Nhap he so k (1 < k < 100): ";
				cin >> k;
				adjustContrast(bmp, outbmp, k);
			}
			else if(luachon == 3)
			{
				float k;
				cout << endl << "Nhap he so k (0 < k < 3): ";
				cin >> k;
				adjustSaturation(bmp, outbmp, k);
			}
			else if(luachon == 4)
			{
				float k;
				cout << endl << "Ban muon phong to len may lan? ";
				cin >> k;
				Enlarge(bmp, outbmp, k);
			}
			else if(luachon == 5)
			{
				float k;
				cout << endl << "Nhap he so k (0 < k < 1): ";
				cin >> k;
				minimize(bmp, outbmp, k);
			}
			else if(luachon == 6)
				setNega(bmp, outbmp);
			else if(luachon == 7)
			{
				blend();
				cout << "Moi nhap lua chon: ";
				cin >> luachon;
				if(luachon == 1)
				{
					float k;
					cout << endl << "Nhap he so k (0 < k < 1): ";
					cin >> k;
					blendRed(bmp, outbmp, k);
				}
				else if(luachon == 2)
				{
					float k;
					cout << endl << "Nhap he so k (0 < k < 1): ";
					cin >> k;
					blendGreen(bmp, outbmp, k);
				}
				else if(luachon == 3)
				{
					float k;
					cout << endl << "Nhap he so k (0 < k < 1): ";
					cin >> k;
					blendBlue(bmp, outbmp, k);
				}
				else if(luachon == 4)
				{
					float k;
					cout << endl << "Nhap he so k (0 < k < 1): ";
					cin >> k;
					blendCyan(bmp, outbmp, k);
				}
				else if(luachon == 5)
				{
					float k;
					cout << endl << "Nhap he so k (0 < k < 1): ";
					cin >> k;
					blendMagenta(bmp, outbmp, k);
				}
				else if(luachon == 6)
				{
					float k;
					cout << endl << "Nhap he so k (0 < k < 1): ";
					cin >> k;
					blendYellow(bmp, outbmp, k);
				}
			}
			else if(luachon == 8)
				BnW(bmp, outbmp);
			else if(luachon == 9)
				gray(bmp, outbmp);
			else if(luachon == 10)
				flipVertical(bmp, outbmp);
			else if(luachon == 11)
				flipHorizontal(bmp, outbmp);
			else if(luachon == 12)
				combine(bmp, bmp2, outbmp);
			else if(luachon == 13)
			{
				float y, x;
				cout << endl << "Nhap vi tri y, x ban muon them icon (y la vi tri tren chieu rong, x la chieu dai, vd: y = 0.1, x = 0.5): ";
				cin >> y;
				cin >> x;
				insertIcon(bmp, bmp2, outbmp, y, x);
			}
				
			else if(luachon == 14)
			{
				rotate();
				cout << "Moi nhap lua chon: ";
				cin >> luachon;
				if(luachon == 1)
					rotate90(bmp, outbmp);
				if(luachon == 2)
					rotate180(bmp, outbmp);
				if(luachon == 3)
					rotate270(bmp, outbmp);
			}
			else if(luachon == 15)
			{
				cut();
				cout << "Moi nhap lua chon: ";
				cin >> luachon;
				if(luachon == 1)
				{
					float k;
					cout << endl << "Nhap he so k (0 < k < 1): ";
					cin >> k;
					cutHead(bmp, outbmp, k);
				}
				else if(luachon == 2)
				{
					float k;
					cout << endl << "Nhap he so k (0 < k < 1): ";
					cin >> k;
					cutFoot(bmp, outbmp, k);
				}
				else if(luachon == 3)
				{
					float k;
					cout << endl << "Nhap he so k (0 < k < 1): ";
					cin >> k;
					cutRight(bmp, outbmp, k);
				}
				else if(luachon == 4)
				{
					float k;
					cout << endl << "Nhap he so k (0 < k < 1): ";
					cin >> k;
					cutLeft(bmp, outbmp, k);
				}
			}
			else if(luachon == 16)
			{
				int k;
				cout << endl << "Nhap so tu nhien k (1 <= k <= 5): ";
				cin >> k;
				blur(bmp, outbmp, k);
			}
			else if(luachon == 17)
				sharpen(bmp, outbmp);
			else if(luachon == 0)
				break;
				
			if(SaveBitmap(outFileName, outbmp))
			{
			}
			else
				cout << "Can not save the bitmap file!!!" << endl;
			//DisposeBitmap(bmp);
			//DisposeBitmap(outbmp);
		}
	}
	else
		cout << "Can not load the bitmap file!!!" << endl;
	
	cout << "Bye!";
	
	return 0;
}
