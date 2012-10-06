
#include <stdio.h>
#include <errno.h>
#include "jpeglib.h"
#include <setjmp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <jerror.h>
#include <time.h>



#ifndef u_char
#define u_char unsigned char
static void jpeg_error_exit (j_common_ptr cinfo) {
  cinfo->err->output_message (cinfo);
  exit (EXIT_FAILURE);
};
struct my_error_mgr {
	struct jpeg_error_mgr pub;	/* "public" fields */
	jmp_buf setjmp_buffer;	/* for return to caller */
};
typedef struct my_error_mgr * my_error_ptr;
METHODDEF(void) my_error_exit (j_common_ptr cinfo)
{
	my_error_ptr myerr = (my_error_ptr) cinfo->err;
	(*cinfo->err->output_message) (cinfo);
	longjmp(myerr->setjmp_buffer, 1);
};
#endif		
