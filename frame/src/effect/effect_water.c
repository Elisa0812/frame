#include"common.h"

int water(char *frameBuffer, int width, int height,int truex, u32_t * buf32)
{
	int i = 0;
	int j = 0;
	for(j = 0; j < height; j ++)
	{
		for(i = 0; i < width; i= i +10)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
	
//--------------------------------------------------------------
	usleep(30000);
	for(j = 0; j < height; j ++)
	{
		for(i = 1; i < width;i= i + 10)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}

//--------------------------------------------------------------
	usleep(30000);

	for(j = 0; j < height; j ++)
	{
		for(i = 2; i < width; i=i + 10)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
//--------------------------------------------------------------
	usleep(30000);

	for(j = 0; j < height; j ++)
	{
		for(i = 3; i < width; i=i + 10)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
//--------------------------------------------------------------
	usleep(30000);

	for(j = 0; j < height; j ++)
	{
		for(i = 4; i < width; i=i + 10)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
//--------------------------------------------------------------
	usleep(30000);

	for(j = 0; j < height; j ++)
	{
		for(i = 5; i < width; i=i + 10)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
//--------------------------------------------------------------
	usleep(30000);

	for(j = 0; j < height; j ++)
	{
		for(i = 6; i < width; i=i + 10)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
//--------------------------------------------------------------
	usleep(30000);

	for(j = 0; j < height; j ++)
	{
		for(i = 7; i < width; i=i + 10)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}

//--------------------------------------------------------------
	usleep(30000);
	for(j = 0; j < height; j ++)
	{
		for(i = 8; i < width; i=i + 10)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
//--------------------------------------------------------------
	usleep(30000);

	for(j = 0; j < height; j ++)
	{
		for(i = 9; i < width; i=i + 10)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
//--------------------------------------------------------------
	usleep(30000);
	for(j = 0; j < height; j ++)
	{
		for(i = 10; i < width; i=i + 10)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}

	usleep(30000);

}
