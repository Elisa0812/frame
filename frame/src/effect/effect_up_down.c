//--------------------------------------------------------------------------------------------------------
// 特效： 从下到上和从上到下 打印图片
//--------------------------------------------------------------------------------------------------------

#include "common.h"
int up_down (char *frameBuffer, int width, int height,int truex ,u32_t * buf32)
{
	int i = 0;
	int j = 0;
	int k = 0;
	for (j = height,k=0 ; j >= height/2; j--,k++)
	{
		for (i = 0; i < width; i++)
		{
			drawRect_rgbtest (i, width, j, truex,buf32[j * width + i], frameBuffer);

			drawRect_rgbtest (i, width, k, truex,buf32[k * width + i], frameBuffer);


		}
			usleep (2000);
	}
}
