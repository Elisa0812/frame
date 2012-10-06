#include<setjmp.h> 
#include"common.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>

void drawRect_rgbtest(int x0,int width,int y0,int truex, int clor,char *frameBuffer)
{
	int *dest = (int *)(frameBuffer)+y0*truex+x0;
	*dest = clor;
}
