//--------------------------------------------------------------------------------------------------------
// 特效： 从下到上和从上到下 打印图片
//--------------------------------------------------------------------------------------------------------

#include "common.h"
int left_right (char *frameBuffer, int width, int height,int truex ,u32_t * buf32)
{
	int i = 0;
	int j = 0;
	int k = 0;
	for (i= width,k=0 ; i >= width/2; i--,k++)
	{
		for (j = 0; j < height; j++)
		{
			drawRect_rgbtest (i, width, j, truex,buf32[j * width + i], frameBuffer);

			drawRect_rgbtest (k, width, j, truex,buf32[j * width + k], frameBuffer);


		}
			usleep (2000);
	}
}
