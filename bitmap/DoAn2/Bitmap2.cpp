#include "Bitmap.h"
#include <math.h>

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

void Enlarge(const Bitmap &inbmp, Bitmap &outbmp, float k)
{
	outbmp.width = k * inbmp.width;
	outbmp.height = k * inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
//			
//			SetPixel(outbmp, k*row, k*col, color);
//			SetPixel(outbmp, k*row, k*col + 1, color);
//			SetPixel(outbmp, k*row + 1, k*col, color);
//			SetPixel(outbmp, k*row + 1, k*col + 1, color);
			for(int row2 = 0; row2 < k; row2++)
				for(int col2 = 0; col2 < k; col2++)
					SetPixel(outbmp, row2 + row*k, col2 + col*k, color);
		}
}

void minimize(const Bitmap &inbmp, Bitmap &outbmp, float factor)//4
{
	outbmp.width =  factor*inbmp.width;
	outbmp.height = factor*inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color1, color2, color3, color4, color;
			GetPixel(inbmp, row, col, color1);
			GetPixel(inbmp, row, col + 1, color2);
			GetPixel(inbmp, row + 1, col, color3);
			GetPixel(inbmp, row + 1, col + 1, color4);
			
			color.R = (color1.R + color2.R + color3.R + color4.R)/4;
			color.G = (color1.G + color2.G + color3.G + color4.G)/4;
			color.B = (color1.B + color2.B + color3.B + color4.B)/4;
			SetPixel(outbmp, row*factor, col*factor, color);
		}
}

void AdjustBrightness(const Bitmap &inbmp, Bitmap &outbmp, float factor)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			
			if (color.R*factor > 255)
				color.R = 255;
			else if (color.R*factor < 0)
				color.R = 0;
			else 
				color.R *= factor;

			if (color.G*factor > 255)
				color.G = 255;
			else if (color.G*factor < 0)
				color.G = 0;
			else
				color.G *= factor;

			if (color.B*factor > 255)
				color.B = 255;
			else if (color.B*factor < 0)
				color.B = 0;
			else
				color.B *= factor;
				
			SetPixel(outbmp, row, col, color);
		}
}

void adjustContrast(const Bitmap &inbmp, Bitmap &outbmp, float factor)
{
	float apmlifier;
	apmlifier = (100.0 + factor) / 100.0;
  	apmlifier *= apmlifier;
 	
 	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			
			float Red = color.R / 255.0;
           	float Green = color.G / 255.0;
           	float Blue = color.B / 255.0;
		
			Red = (((Red - 0.5) * apmlifier) + 0.5) * 255.0;
			if(Red > 255)
				Red = 255;
			else if(Red < 0)
				Red = 0;
				
           	Green = (((Green - 0.5) * apmlifier) + 0.5) * 255.0;
           	if(Green > 255)
           		Green = 255;
           	else if(Green < 0)
           		Green = 0;
         
          	Blue = (((Blue - 0.5) * apmlifier) + 0.5) * 255.0;
          	if(Blue > 255)
          		Blue = 255;
          	else if(Blue < 0)
          		Blue = 0;
          		
          	color.R = Red;
          	color.G = Green;
          	color.B = Blue;
          	
          	SetPixel(outbmp, row, col, color);
        }
}

void adjustSaturation(const Bitmap &inbmp, Bitmap &outbmp, float factor)
{
	float Pr =  0.299, Pg = 0.587, Pb = 0.114;
	
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			
			double amp = sqrt((color.R)*(color.R)*Pr + (color.G)*(color.G)*Pg + (color.B)*(color.B)*Pb);
			
			
			if(amp + ((color.R) - amp)*factor > 255)
				color.R = 255;
			else if(amp + ((color.R) - amp)*factor < 0)
				color.R = 0;
			else color.R = amp + ((color.R) - amp)*factor;
			
			if(amp + ((color.G) - amp)*factor > 255)
				color.G = 255;
			else if(amp + ((color.G) - amp)*factor < 0)
				color.G = 0;
			else color.G = amp + ((color.G) - amp)*factor;
			
			if(amp + ((color.B) - amp)*factor > 255)
				color.B = 255;
			else if(amp + ((color.B) - amp)*factor < 0)
				color.B = 0;
			else color.B = amp + ((color.B) - amp)*factor;
			
			SetPixel(outbmp, row, col, color);
		}
}

void setNega(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			color.R = 255 - color.R;
			color.G = 255 - color.G;
			color.B = 255 - color.B;
			SetPixel(outbmp, row, col, color);
		}
}

//blend mau su dung he so k (0 < k < 1)
void blendRed(const Bitmap &inbmp, Bitmap &outbmp, float k)		
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			color.G *= k;
			color.B *= k;
			SetPixel(outbmp, row, col, color);
		}
}

void blendGreen(const Bitmap &inbmp, Bitmap &outbmp, float k)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			
			color.R *= k;
			if(color.R > 255)
				color.R = 255;
			
			color.B *= k; 
			if(color.B > 255)
				color.B = 255;
			SetPixel(outbmp, row, col, color);
		}
}

void blendBlue(const Bitmap &inbmp, Bitmap &outbmp, float k)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			color.G *= k;
			color.R *= k;
			SetPixel(outbmp, row, col, color);
		}
}

void blendYellow(const Bitmap &inbmp, Bitmap &outbmp, float k)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			
			color.B *= k;
			SetPixel(outbmp, row, col, color);
		}
}

void blendCyan(const Bitmap &inbmp, Bitmap &outbmp, float k)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
	
			color.R *= k;
			SetPixel(outbmp, row, col, color);
		}
}

void blendMagenta(const Bitmap &inbmp, Bitmap &outbmp, float k)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
	
			color.G *= k;
			SetPixel(outbmp, row, col, color);
		}
}

void BnW(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			int temp = (color.R + color.G + color.B)/3;
			if(temp > 128)
				color.R = color.G = color.B = 255;
			else
				color.R = color.G = color.B = 0;
			SetPixel(outbmp, row, col, color);
		}
}

void gray(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			color.R = color.G = color.B = (color.R + color.G + color.B)/3;
			SetPixel(outbmp, row, col, color);
		}
}

void flipVertical(const Bitmap &inbmp, Bitmap &outbmp)
{
	Color temp;
	Color temp2;
		
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width/2; col++)
		{
			Color color;
			Color color2;
			GetPixel(inbmp, row, col, color);
			temp.R = color.R;
			temp.G = color.G;
			temp.B = color.B;
			
			GetPixel(inbmp, row, inbmp.width - col, color2);
			temp2.R = color2.R;
			temp2.G = color2.G;
			temp2.B = color2.B;
			
			SetPixel(outbmp, row, inbmp.width - col + 1, temp);
			SetPixel(outbmp, row, col, temp2);
		}
}

void flipHorizontal(const Bitmap &inbmp, Bitmap &outbmp)
{
	Color temp;
	Color temp2;
		
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height/2; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			Color color2;
			GetPixel(inbmp, row, col, color);
			temp.R = color.R;
			temp.G = color.G;
			temp.B = color.B;
			
			GetPixel(inbmp, inbmp.height - row, col, color2);
			temp2.R = color2.R;
			temp2.G = color2.G;
			temp2.B = color2.B;
			
			SetPixel(outbmp, inbmp.height - row + 1, col, temp);
			SetPixel(outbmp, row, col, temp2);
		}
}

void combine(const Bitmap &inbmp, const Bitmap &inbmp2, Bitmap &outbmp)
{
	outbmp.width = inbmp.width + inbmp2.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)	
		for(int col = 0, col2 = 0; col < inbmp.width || col2 < inbmp2.width; col++, col2++)
		{
			Color color, color2;
			
			GetPixel(inbmp, row, col, color);
			GetPixel(inbmp2, row, col2, color2);
			
			if(col < inbmp.width)
				SetPixel(outbmp, row, col, color);
			SetPixel(outbmp, row, col2 + inbmp.width, color2);
		}			
}

void rotate90(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = inbmp.height;
	outbmp.height = inbmp.width;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			
			SetPixel(outbmp, col, inbmp.height - row - 1, color);
		}
}

void rotate180(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			
			SetPixel(outbmp, inbmp.height - row - 1, inbmp.width - col - 1, color);
		}
}

void rotate270(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = inbmp.height;
	outbmp.height = inbmp.width;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			
			SetPixel(outbmp, inbmp.width - col - 1, row, color);
		}
}

void cutHead(const Bitmap &inbmp, Bitmap &outbmp, float factor)	//xoa dau
{
	outbmp.height = inbmp.height*(1 - factor);
	outbmp.width = inbmp.width;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	
	for(int row = 0; row < inbmp.height*(1 - factor); row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row + factor*inbmp.height, col, color);
			
			SetPixel(outbmp, row, col, color);
		}
}

void cutFoot(const Bitmap &inbmp, Bitmap &outbmp, float factor) //xoa chan
{
	outbmp.height = inbmp.height*(1 - factor);
	outbmp.width = inbmp.width;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	
	for(int row = 0; row < inbmp.height*(1 - factor); row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			
			SetPixel(outbmp, row, col, color);
		}
}

void cutLeft(const Bitmap &inbmp, Bitmap &outbmp, float factor) //xoa ben trai
{
	outbmp.height = inbmp.height;
	outbmp.width = inbmp.width*(1 - factor);
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width*(1 - factor); col++)
		{
			Color color;
			GetPixel(inbmp, row, col + factor*inbmp.width, color);
			
			SetPixel(outbmp, row, col, color);
		}
}

void cutRight(const Bitmap &inbmp, Bitmap &outbmp, float factor) //xoa ben phai
{
	outbmp.height = inbmp.height;
	outbmp.width = inbmp.width*(1 - factor);
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width*(1 - factor); col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			
			SetPixel(outbmp, row, col, color);
		}
}

void insertIcon(const Bitmap &inbmp, const Bitmap &inbmp2, Bitmap &outbmp, float y, float x)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0, row2 = 0; row < inbmp.height || row2 < inbmp2.height; row++, row2++)	
		for(int col = 0, col2 = 0; col < inbmp.width || col2 < inbmp2.width; col++, col2++)
		{
			Color color, color2;
			GetPixel(inbmp, row, col, color);
			GetPixel(inbmp2, row2, col2, color2);
			
			if(row < y*inbmp.height || row > y*inbmp.height + inbmp2.height || col < x*inbmp.width || col > x*inbmp.width + inbmp2.width)
				SetPixel(outbmp, row, col, color);
			
				SetPixel(outbmp, row + y*inbmp.height, col + x*inbmp.width, color2);
		}			
}   

void blur(const Bitmap &inbmp, Bitmap &outbmp, int factor)	//ham lam mo anh
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)	
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color, color2;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      		color.R = color.G = color.B = 0;
			
			for(int row2 = row; row2 < factor + row; row2++)
				for(int col2 = col; col2 < factor + col; col2++)
				{
					GetPixel(inbmp, row2, col2, color2);
					color.R += color2.R;
					color.G += color2.G;
					color.B += color2.B;
				}
			color.R /= factor*factor;
			color.G /= factor*factor;
			color.B /= factor*factor;
			SetPixel(outbmp, row, col, color);
		}
}

void sharpen(const Bitmap &inbmp, Bitmap &outbmp)
{
   	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	
	int rsum = 0;
    int gsum = 0;
    int bsum = 0;
    int ksum = 0;

	int filter[3][3] = {{0,-1,0}, {-1,5,-1}, {0,-1,0}}; 
	Color color;
	
    for (int row = 0; row < inbmp.height; row++)
    {
        for (int col = 0; col < inbmp.width; col++)
        {
            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    if ((row + r) >= 0 && (row + r) < inbmp.height)
                    {
                        if ((col + c) >= 0 && (col + c) < inbmp.width)
                        {
                            GetPixel(inbmp, row + r, col + c, color);
                         
                            rsum += filter[r + 1][c + 1] * color.R;
                            gsum += filter[r + 1][c + 1] * color.G; 
                            bsum += filter[r + 1][c + 1] * color.B; 
                            ksum += filter[r + 1][c + 1];
                        }
                    }
                }
            }
             
            if (ksum == 0)
            {
                color.R = rsum;
                color.G = gsum;
                color.B = bsum;
            }
            else
            {
                if (rsum/ksum > 255)
                    color.R = 255;
                else if (rsum/ksum < 0)
                    color.R = 0;
                else
                    color.R = rsum/ksum;

                if (gsum/ksum > 255)
                    color.G = 255;
                else if (gsum/ksum < 0)
                    color.G = 0;
                else
                    color.G = gsum/ksum;
                if (bsum/ksum > 255)
                    color.B = 255;
                else if (bsum/ksum < 0)
                    color.B = 0;
                else
                    color.B = bsum/ksum;
            }
     
            rsum = 0;   
            gsum = 0;
            bsum = 0;
            ksum = 0;
            SetPixel(outbmp, row, col, color); 
        }
    }
}
