#include "myjpeg.h"

int get_JPEG_info (char * filename, unsigned int *width, unsigned int *height, unsigned int *size, float *rate)
{
	struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;
	FILE * infile;
	struct stat st;
	if (stat(filename, &st)) {
		perror(filename);
		return -1;
	}
	if (size) *size = st.st_size;

	if ((infile = fopen(filename, "rb")) == NULL) {
		perror(filename);
		return -1;
	}


	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	if (setjmp(jerr.setjmp_buffer)) {
		jpeg_destroy_decompress(&cinfo);
		fclose(infile);
		return 0;
	}

	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, infile);
	(void) jpeg_read_header(&cinfo, TRUE);
	if (width) *width	= cinfo.image_width;
	if (height) *height = cinfo.image_height;
	if (rate) *rate = st.st_size * 8.0 / (cinfo.image_width * cinfo.image_height);
	jpeg_destroy_decompress(&cinfo);
	fclose(infile);
	return 0;
}
