//--------------------------------------------------------------------------------------------------------
// 特效： 从下到上 打印图片
//--------------------------------------------------------------------------------------------------------

#include "common.h"
int up (char *frameBuffer, int width, int height,int truex, u32_t * buf32)
{
  int i = 0;
  int j = 0;
      for (j = height; j >= 0; j--)
    {
  for (i = 0; i < width; i++)
	drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);

      usleep (3000);
    }
}
