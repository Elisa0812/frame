//--------------------------------------------------------------------------------------------------------
// 特效： 从左到右 打印图片
//--------------------------------------------------------------------------------------------------------

#include "common.h"
int two (char *frameBuffer, int width, int height, int truex,u32_t * buf32)
{
  int i = 0;
  int j = 0;

  for (i = 0;i < width; i++)
    {
      for (j = 0; j < height/3; j++)
	{
	  drawRect_rgbtest (i, width, j,truex, buf32[i + j * width], frameBuffer);
	}
      usleep (1000);
    }
  for (i = width;i > 0; i--)
    {
      for (j = height/3; j <2*height/3; j++)
	{
	  drawRect_rgbtest (i, width, j,truex, buf32[i + j * width], frameBuffer);
	}
      usleep (800);
    }
  for (i = 0;i < width; i++)
    {
      for (j = 2*height/3; j < height; j++)
	{
	  drawRect_rgbtest (i, width, j,truex, buf32[i + j * width], frameBuffer);
	}
      usleep (500);
    }
}
