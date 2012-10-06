#include"common.h"

int water_down(char *frameBuffer, int width, int height,int truex, u32_t * buf32)
{
	int i = 0;
	int j = 0;
	for(j = 0; j < height; j = j + 10)
	{
		for(i = 0; i < width; i++)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
	
//--------------------------------------------------------------
	usleep(30000);
	for(j = 1; j < height; j = j + 10)
	{
		for(i = 0; i < width;i++)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}

#if 1
//--------------------------------------------------------------
	usleep(30000);

	for(j = 2; j < height; j = j + 10)
	{
		for(i = 0; i < width; i++)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
//--------------------------------------------------------------
	usleep(30000);

	for(j = 3; j < height; j = j + 10)
	{
		for(i = 0; i < width; i++)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
//--------------------------------------------------------------
	usleep(30000);

	for(j = 4; j < height; j = j + 10)
	{
		for(i = 0; i < width; i++)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
//--------------------------------------------------------------
	usleep(30000);

	for(j = 5; j < height; j = j + 10)
	{
		for(i = 0; i < width; i++)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
//--------------------------------------------------------------
	usleep(30000);

	for(j = 6; j < height; j = j + 10)
	{
		for(i = 0; i < width; i++)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}

	}
//--------------------------------------------------------------
	usleep(30000);

	for(j = 7; j < height; j = j + 10)
	{
		for(i = 0; i < width; i++)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}

//--------------------------------------------------------------
	usleep(30000);
	for(j = 8; j < height; j = j + 10)
	{
		for(i = 0; i < width; i++)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
//--------------------------------------------------------------
	usleep(30000);

	for(j = 9; j < height; j = j + 10)
	{
		for(i = 0; i < width; i++)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}
//--------------------------------------------------------------
	usleep(30000);
	for(j = 10; j < height; j = j + 10)
	{
		for(i = 0; i < width; i++)
		{
			drawRect_rgbtest (i, width, j,truex, buf32[j * width + i], frameBuffer);
		}
	}

	usleep(30000);

#endif
}
