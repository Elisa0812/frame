//--------------------------------------------------------------------------------------------------------
// 特效：duijiao  打印图片
//--------------------------------------------------------------------------------------------------------

#include "common.h"
int duijiao (char *frameBuffer, int width, int height,int truex ,u32_t * buf32)
{
	int i = 0;
	int j = 0;
	int k = 0;
	for (j = height,k =0 ; j >= 0; j--,k++)
	{
		for (i = 0; i <= width*(height-j)/height; i++)
			drawRect_rgbtest (i, width, j, truex,buf32[j * width + i], frameBuffer);
		usleep (1000);
		for (i = width-(width*k/height); i < width; i++)
			drawRect_rgbtest (i, width, k, truex,buf32[k * width + i], frameBuffer);

		usleep (1000);
	}
}

