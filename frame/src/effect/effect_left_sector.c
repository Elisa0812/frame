//---------------------------------------------------------------------------------------------------------
// 特效，从左到右百页窗 
//---------------------------------------------------------------------------------------------------------
#include "common.h"
int left_sector (char *frameBuffer,int width, int height,int truex ,u32_t *buf32)
{
  int i, j, m1, m2, m3, m4, m5, m6, m7;

  m1 = width / 8;
  m2 = width / 4;
  m3 = width / 4 + width / 8;
  m4 = width / 2;
  m5 = width / 2 + width / 8;
  m6 = width / 2 + width / 4;
  m7 = width / 2 + width / 8 + width / 4 ;
  for (i = 0; i <= width / 8; i++, m1++, m2++, m3++, m4++, m5++, m6++, m7++)
	{
      for (j = 0; j <= height; j++)
    {
	  drawRect_rgbtest(i, width, j ,  truex, buf32[i + j  * width], frameBuffer);
	  drawRect_rgbtest(m1, width, j,    truex, buf32[m1 + j * width], frameBuffer);
	  drawRect_rgbtest(m2, width, j,    truex, buf32[m2+ j * width], frameBuffer);
	  drawRect_rgbtest(m3, width, j,    truex, buf32[m3+ j * width], frameBuffer);
	  drawRect_rgbtest(m4, width, j,    truex, buf32[m4+ j * width], frameBuffer);
	  drawRect_rgbtest(m5, width, j,    truex, buf32[m5 + j * width], frameBuffer);
	  drawRect_rgbtest(m6, width, j,    truex, buf32[m6 + j * width], frameBuffer);
	  drawRect_rgbtest(m7, width, j,    truex, buf32[m7 + j * width], frameBuffer);
	}
      usleep (10000);
    }

  return 0;
}
