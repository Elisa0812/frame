#include "myjpeg.h"



unsigned char *read_JPEG_file(char *filename)
{
	struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;
	FILE * infile;
 	unsigned char*linebuffer; 
	unsigned char*buffer;
	int i;
	if ((infile = fopen(filename, "rb")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		return NULL;
	}
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	if (setjmp(jerr.setjmp_buffer)) {
		jpeg_destroy_decompress(&cinfo);
		fclose(infile);
		return NULL;
	}
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, infile);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);
	linebuffer = (unsigned char *) malloc(cinfo.output_width * cinfo.output_components);
	buffer = (unsigned char *) malloc(cinfo.output_height * cinfo.output_width * cinfo.output_components);
#if 0 
	printf("cinfo.output_width = %d\n",cinfo.output_width);	
	printf("cinfo.output_height = %d\n",cinfo.output_height);	
	printf("cinfo.output_scanline = %d\n",cinfo.output_scanline);	
	printf("cinfo.output_components = %d\n",cinfo.output_components);	
	printf("malloc = %d\n",cinfo.output_width * cinfo.output_components);	
#endif
//	printf("cinfo.output_scanline = %d",cinfo.output_scanline);
	while (cinfo.output_scanline < cinfo.output_height) {
		jpeg_read_scanlines(&cinfo, &linebuffer, 1);
		//printf("scanlines=%d\n",cinfo.output_scanline);
		for (i=0; i<(cinfo.output_width * cinfo.output_components); i++) {
		//	printf("%02X%02X%02X ", buffer[i*3], buffer[i*3+1], buffer[i*3+2]);
		//	if (0 == ((i+1) % 10) || i == cinfo.output_width-1) {
		//		printf("\n");
		buffer[(cinfo.output_scanline - 1) * cinfo.output_width * cinfo.output_components + i] = linebuffer[i];
		
//		printf("%02X ",	buffer[(cinfo.output_scanline - 1) * cinfo.output_width + i]);			
		//	}
		
		}
		//printf("least:%d\n\n", cinfo.output_height-cinfo.output_scanline);
	}
#if 0
	fb_info jpeg_inf;
	jpeg_inf.w = cinfo.output_width;
	jpeg_inf.h = cinfo.output_height;
	u32_t *buf = rgb24to32((u8_t *)buffer,jpeg_inf);
	
	printf("scanline = %d width = %d total = %d*3\n",cinfo.output_scanline-1,cinfo.output_width,(cinfo.output_scanline-1)*cinfo.output_width+i/3 );
	printfr(buf,1024,768);
	int j = 0;
	for(j = 0; j < 1366*768;j++)
	{
		printf("0x%08X\n ", buf[j]);
	}	
	printf("buf[0]size = %d\n",sizeof(buf[0]));
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	int j = 0;
	for(j = 0; j < 1024*768*3;j++)
	{
		printf("%02X ", buffer[j]);
	}
	
#endif
	free(linebuffer);
	fclose(infile);
	return (unsigned char *)buffer;

}
