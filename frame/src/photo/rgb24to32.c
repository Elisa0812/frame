#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <jpeglib.h>
#include <jerror.h>

#include <time.h>

#ifndef u_char
#define u_char unsigned char
#endif		


#include "common.h"

static void jpeg_error_exit (j_common_ptr cinfo) {
  cinfo->err->output_message (cinfo);
  exit (EXIT_FAILURE);
}

/* XXX: 2010.2.5, by Tony add function  */
u32_t * rgb24to32(u8_t *buf24, fb_info jpeg_inf)
{
	int w = jpeg_inf.w;
	int h = jpeg_inf.h;
	
	u32_t *buf = malloc(w * h * 4);
	if (buf == NULL) return NULL;

	/* FIXME: why? */
	int i;
	for(i = 0; i < w * h; ++i){
		*((u8_t *)&buf[i] + 2) = buf24[i * 3 + 0];
		*((u8_t *)&buf[i] + 1) = buf24[i * 3 + 1];
		*((u8_t *)&buf[i] + 0) = buf24[i * 3 + 2];
		*((u8_t *)&buf[i] + 3) = 0x00;
	}
	return (u32_t *)buf;
}
