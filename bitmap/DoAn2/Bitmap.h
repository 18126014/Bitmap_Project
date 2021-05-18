#ifndef _BITMAP_
#define _BITMAP_

struct Bitmap
{
	int width;
	int height;
	int rowSize;
	unsigned char *pixels;
};

struct Color
{
	int R, G, B;
};


int LoadBitmap(const char *fname, Bitmap &bmp);
int SaveBitmap(const char *fname, const Bitmap &bmp);
void DisposeBitmap(Bitmap &bmp);

int SetPixel(const Bitmap &bmp, int row, int col, Color color);
int GetPixel(const Bitmap &bmp, int row, int col, Color &color);

void AdjustBrightness(const Bitmap &bmp, Bitmap &outbmp, float factor);  //chinh do sang (so duong la tang so am la giam)
void adjustContrast(const Bitmap &bmp, Bitmap &outbmp, float factor); 	//chinh do tuong phan (0 < factor < 50)
void adjustSaturation(const Bitmap &inbmp, Bitmap &outbmp, float factor);	// 0 < factor < 2 (chinh do bao hoa mau)

void Enlarge(const Bitmap &inbmp, Bitmap &outbmp, float k);  //phong to
void minimize(const Bitmap &inbmp, Bitmap &outbmp, float factor); //thu nho

void setNega(const Bitmap &inbmp, Bitmap &outbmp);	//chinh am ban

void blendRed(const Bitmap &inbmp, Bitmap &outbmp, float k); //blend mau do
void blendGreen(const Bitmap &inbmp, Bitmap &outbmp, float k); //blend mau xanh la
void blendBlue(const Bitmap &inbmp, Bitmap &outbmp, float k); //blend mau xanh duong
void blendYellow(const Bitmap &inbmp, Bitmap &outbmp, float k); //blend mau vang
void blendCyan(const Bitmap &inbmp, Bitmap &outbmp, float k); //blend mau cyan
void blendMagenta(const Bitmap &inbmp, Bitmap &outbmp, float k); //blend mau magenta

void BnW(const Bitmap &inbmp, Bitmap &outbmp); //chinh trang den
void gray(const Bitmap &inbmp, Bitmap &outbmp); //chinh xam anh

void flipVertical(const Bitmap &inbmp, Bitmap &outbmp); //lat anh doc
void flipHorizontal(const Bitmap &inbmp, Bitmap &outbmp); //lat anh ngang

void combine(const Bitmap &inbmp, const Bitmap &inbmp2, Bitmap &outbmp); //ghep anh cung chieu rong
void insertIcon(const Bitmap &inbmp, const Bitmap &inbmp2, Bitmap &outbmp, float y, float x); //them icon vao anh

//chinh xoay
void rotate90(const Bitmap &inbmp, Bitmap &outbmp);
void rotate180(const Bitmap &inbmp, Bitmap &outbmp);
void rotate270(const Bitmap &inbmp, Bitmap &outbmp);

void cutHead(const Bitmap &inbmp, Bitmap &outbmp, float factor);	//xoa dau
void cutFoot(const Bitmap &inbmp, Bitmap &outbmp, float factor); 	//xoa chan
void cutLeft(const Bitmap &inbmp, Bitmap &outbmp, float factor); 	//xoa ben trai
void cutRight(const Bitmap &inbmp, Bitmap &outbmp, float factor); 	//xoa ben phai

void blur(const Bitmap &inbmp, Bitmap &outbmp, int factor);		//lam mo anh
void sharpen(const Bitmap &inbmp, Bitmap &outbmp);				//chinh do sac net
#endif                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
