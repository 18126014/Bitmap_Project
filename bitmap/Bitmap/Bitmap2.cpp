#include "Bitmap.h"

// O(1)
int SetPixel(const Bitmap &bmp, int row, int col, Color color)
{
	if(row < 0 || row >= bmp.height
		 || col < 0 || col >= bmp.width)
		return 0;
	
	// color: B, G, R
	int offset = (bmp.height - 1 - row)*bmp.rowSize + col*3;
	bmp.pixels[offset] = color.B;
	bmp.pixels[offset + 1] = color.G;
	bmp.pixels[offset + 2] = color.R;
}

int GetPixel(const Bitmap &bmp, int row, int col, Color &color)
{
	if(row < 0 || row >= bmp.height
		 || col < 0 || col >= bmp.width)
		return 0;
	
	// color: B, G, R
	int offset = (bmp.height - 1 - row)*bmp.rowSize + col*3;
	color.B = bmp.pixels[offset];
	color.G = bmp.pixels[offset + 1];
	color.R = bmp.pixels[offset + 2];
}

void Enlarge(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = 2 * inbmp.width;
	outbmp.height = 2 * inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			SetPixel(outbmp, 2*row, 2*col, color);
			SetPixel(outbmp, 2*row, 2*col + 1, color);
			SetPixel(outbmp, 2*row + 1, 2*col, color);
			SetPixel(outbmp, 2*row + 1, 2*col + 1, color);
		}
}

void AdjustBrightness(const Bitmap &bmp, double factor)
{
	for(int row = 0; row < bmp.height; row++)
		for(int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			color.R *= factor;
			color.G *= factor;
			color.B *= factor;
			SetPixel(bmp, row, col, color);
		}
}
