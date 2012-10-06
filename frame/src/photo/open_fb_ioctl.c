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


char *open_fb_ioctl(char *filename,struct fb_var_screeninfo *vinfo,struct fb_fix_screeninfo *finfo)
{
    long int screensize = 0;
    int fbFd = 0;
	char *frameBuffer;

    /* Open the file for reading and writing */
    fbFd = open (filename, O_RDWR);
    if (fbFd == -1)
    {
        perror ("Error: cannot open framebuffer device");
  	return NULL;
    }

    //»ñÈ¡finfoÐÅÏ¢²¢ÏÔÊ¾
    if (ioctl (fbFd, FBIOGET_FSCREENINFO, finfo) == -1)
    {
        perror ("Error reading fixed information");
	close(fbFd);
        return NULL;
    }
  //  printFixedInfo ();
    //»ñÈ¡vinfoÐÅÏ¢²¢ÏÔÊ¾
    if (ioctl (fbFd, FBIOGET_VSCREENINFO, vinfo) == -1)
    {
        perror ("Error reading variable information");
	close(fbFd);
        return NULL;
    }
//    printVariableInfo ();
	printf("smen_len = %d\n",finfo->smem_len);
    /* Figure out the size of the screen in bytes */
   screensize = finfo->smem_len;
   // screensize = 1408*768*4;

    /* Map the device to memory */
    frameBuffer = (char *) mmap (0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,fbFd, 0);
    if (frameBuffer == MAP_FAILED)
    {
        perror ("Error: Failed to map framebuffer device to memory");
	close(fbFd);
        return NULL;
    }
	close(fbFd);
	return frameBuffer;

 }
