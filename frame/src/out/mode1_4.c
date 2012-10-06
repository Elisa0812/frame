#include <stdio.h>
#include "common.h"
#include <linux/fb.h>
#include <linux/kd.h>
#include <time.h>
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
char *frameBuffer = NULL;

int main(int argc, char **argv)
{
	unsigned int width = 0, height = 0, size = 0;
	float rate = 0.0;
	int ret = get_JPEG_info(argv[1], &width, &height, &size, &rate);
	//得到图片的大小长度宽度等属性
	if (ret == 0)
		printf("widhth*height = %u * %u; size=%u; rate=%.2f\n", width, height, size, rate);
	
	unsigned char *bffer;
	bffer = read_JPEG_file(argv[1]);
//	u32_t buf32 = read_JPEG_file(argv[1]);

	frameBuffer = open_fb_ioctl(argv[2],&vinfo,&finfo);
	//打开/dev/fbx，并得到fb的属性vinfo，finfo，然后mmap到内存，返回内存的首地址
	printf("x = %d y = %d\n",vinfo.xres,vinfo.yres);
	if(width != vinfo.xres || height != vinfo.yres)
	{
		printf("photo is worrg\n");
		return 2;
	}
	printf("photo is ok\n");	
	
	fb_info jpeg_inf;
	jpeg_inf.w = width;
	jpeg_inf.h = height;	
	u32_t *buf32;
	u16_t *buf16;
	printf("%d\n",vinfo.bits_per_pixel);
	switch(vinfo.bits_per_pixel){
	case 32:
		buf32 = rgb24to32((u8_t *)bffer,jpeg_inf);
		printf("24 to 32\n");
		break;
	case 24:
	//	u24_t *buf = (u24_t *)buffer;
		printf("24 to 24\n");
		break;
	case 16:
	//	u16_t *buf = rgb24to16((u8_t *)buffer,jpeg_inf);
		printf("24 to 16\n");
		break;
	default:
		printf("worrg /dev/fb.bits_per_pixel\n");
		return 1;
	}
	int truex = finfo.smem_len/vinfo.yres/(vinfo.bits_per_pixel/8);

	int i = 0;
	int j = 0;
	for(j = 0;j < height;j ++)
	{
		for(i = 0; i < width; i++)
		{
			drawRect_rgbtest(i,width,j,truex,buf32[j*width+i],frameBuffer);	
		}
	}

return 0;
}
