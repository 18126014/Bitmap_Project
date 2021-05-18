/*
	Code mau Do an 2 - Xu ly anh, PPLTTT - 18VP
	Vu Quoc Hoang, FIT - HCMUS, 03/2019
*/

#include <iostream>
#include "Bitmap.h"
using namespace std;

int main()
{
	char *inFileName = "MARBLES.BMP";
	char *outFileName= "out.bmp";
	Bitmap bmp, outbmp;
	
	if(LoadBitmap(inFileName, bmp))
	{	
		Enlarge(bmp, outbmp);
		if(SaveBitmap(outFileName, outbmp))
		{
		}
		else
			cout << "Can not save the bitmap file!!!" << endl;
		DisposeBitmap(bmp);
		DisposeBitmap(outbmp);
	}
	else
		cout << "Can not load the bitmap file!!!" << endl;
	
	cout << "Bye!";
	
	return 0;
}
