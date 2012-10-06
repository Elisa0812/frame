//--------------------------------------------------------------------------------------------------------
// 特效： 从下到上和从上到下 打印图片
//--------------------------------------------------------------------------------------------------------

#include "common.h"
int jiaocha(char *frameBuffer, int width, int height,int truex ,u32_t * buf32)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int l =0;
	int a,b,c,d,e,f,g,h,m,n,o,p,q;
	for (i =0,h =width,a=0,b=width,c=0,d=width,e=0,f=width,g=0;i<width;i++,h--,a++,c++,e++,g++,b--,d--,f--)
	{
		for(j =0;j<height/8;j++)
			drawRect_rgbtest (a, width, j, truex,buf32[j * width + a], frameBuffer);
		for(k = height/8;k<height/4;k++)
			drawRect_rgbtest (b, width, k, truex,buf32[k * width + b], frameBuffer);
		for(l = height/4;l<3*height/8;l++)
			drawRect_rgbtest (c, width, l, truex,buf32[l * width + c], frameBuffer);
		for(m =3*height/8;m<height/2;m++)
			drawRect_rgbtest (d, width, m, truex,buf32[m * width + d], frameBuffer);
		for(n = height/2;n<5*height/8;n++)
			drawRect_rgbtest (e, width, n, truex,buf32[n * width + e], frameBuffer);
		for(o = 5*height/8;o<6*height/8;o++)
			drawRect_rgbtest (f, width, o, truex,buf32[o * width + f], frameBuffer);
		for(p =6*height/8;p<7*height/8;p++)
			drawRect_rgbtest (g, width, p, truex,buf32[p * width + g], frameBuffer);
		for(q =7* height/8;q<height;q++)
			drawRect_rgbtest (h, width, q, truex,buf32[q * width + h], frameBuffer);
		usleep (1000);
	}
}
