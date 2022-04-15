#include <cstdio>
#include <cstdlib>
#include <windows.h>
using namespace std;
typedef struct
{
    BYTE b;
    BYTE g;
    BYTE r;
} RGB;
int main()
{
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    FILE *pfin;
    FILE *pfout;
    errno_t err;
    err = fopen_s(&pfin, "c:\\wpfang\\a.bmp", "rb");
    err = fopen_s(&pfout, "c:\\wpfang\\b.bmp", "wb");
    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pfin);
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, pfin);
    const int height = 512, width = 512;
    if (infoHeader.biBitCount >= 1)
    {
        int size = height * width;
        RGB img[height][width];
        RGB img2[width][height];
        fread(img, sizeof(RGB), size, pfin);
        int i, j;
        for (i = 0; i < height; i++)
            for (j = 0; j < width; j++)
            {
                (img2[i][j]).b = (img[width - 1 - j][i]).b;
                (img2[i][j]).r = (img[width - 1 - j][i]).r;
                (img2[i][j]).g = (img[width - 1 - j][i]).g;
            }
        fwrite(&fileHeader, sizeof(fileHeader), 1, pfout);
        fwrite(&infoHeader, sizeof(infoHeader), 1, pfout);
        fwrite(img2, sizeof(RGB), size, pfout);
    }
    err = fclose(pfin);
    err = fclose(pfout);
    return 0;
}