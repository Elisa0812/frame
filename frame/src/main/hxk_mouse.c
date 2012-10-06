#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <unistd.h>

#include "common.h"

/* ********** .h */
typedef struct 
{
	int x;
	int y;
	int button;
}mouse_event_t;

extern int mouse_open(char *device_name, int *fd);
extern int mouse_parse(const u8_t *buf, mouse_event_t* mevent, int x, int y);

extern int fb_restorecursor(fb_info fb_inf, int x, int y);
extern int fb_drawcursor(fb_info fb_inf, int x, int y);
extern int test_mouse(fb_info fb_inf);
int hxk_mouse(void); 
void signal_mouse(int x, int y);
void signal_handler1(int signum);                                
void signal_handler2(int signum);                                
void signal_handler3(int signum);                                

int init_fb(fb_info *fb_inf);
/* **************** end .h */


#define C_WIDTH  10
#define C_HEIGHT 17
#define T___     0XFFFFFFFF
#define BORD     0x0
#define X___     0xFFFF
#define FB_DEVICE "/dev/fb0"
static unsigned long cursor_pixel[C_WIDTH * C_HEIGHT] = {
	BORD, T___, T___, T___, T___, T___, T___, T___, T___, T___,
	BORD, BORD, T___, T___, T___, T___, T___, T___, T___, T___,
	BORD, X___, BORD, T___, T___, T___, T___, T___, T___, T___,
	BORD, X___, X___, BORD, T___, T___, T___, T___, T___, T___,
	BORD, X___, X___, X___, BORD, T___, T___, T___, T___, T___,
	BORD, X___, X___, X___, X___, BORD, T___, T___, T___, T___,
	BORD, X___, X___, X___, X___, X___, BORD, T___, T___, T___,
	BORD, X___, X___, X___, X___, X___, X___, BORD, T___, T___,
	BORD, X___, X___, X___, X___, X___, X___, X___, BORD, T___,
	BORD, X___, X___, X___, X___, X___, X___, X___, X___, BORD,
	BORD, X___, X___, X___, X___, X___, BORD, BORD, BORD, BORD,
	BORD, X___, X___, BORD, X___, X___, BORD, T___, T___, T___,
	BORD, X___, BORD, T___, BORD, X___, X___, BORD, T___, T___,
	BORD, BORD, T___, T___, BORD, X___, X___, BORD, T___, T___,
	T___, T___, T___, T___, T___, BORD, X___, X___, BORD, T___,
	T___, T___, T___, T___, T___, BORD, X___, X___, BORD, T___,
	T___, T___, T___, T___, T___, T___, BORD, BORD, T___, T___
};
static unsigned long save_cursor[C_WIDTH * C_HEIGHT];
/*---------------------------------------------
int main(void)                                 
{                                          
	fb_info fb;              
	for(;;)
	{ 
		init_fb(&fb);         
		test_mouse(fb);
	}             
	return 0;               
}
---------------------------------------------*/


int init_fb(fb_info *fb_inf)
{
	int fd;

	if ((fd = open(FB_DEVICE, O_RDWR)) < 0){
		fprintf(stderr, "Open %s failed:%s\n", FB_DEVICE, strerror(errno));
		return -1;
	}

	struct fb_var_screeninfo fb_var;

	if (ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0){
		fprintf(stderr, "fb ioctl failed:%s\n", strerror(errno));
		return -1;
	}

	fb_inf->w = fb_var.xres;
	fb_inf->h = fb_var.yres;
	fb_inf->bpp = fb_var.bits_per_pixel;
#if 1
	printf("width:%d\thign:%d\tbpp:%d\n",
			fb_inf->w, fb_inf->h, fb_inf->bpp);
#endif	
	fb_inf->fbmem = mmap(0, fb_inf->w * fb_inf->h * fb_inf->bpp /8,
			PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (fb_inf->fbmem == MAP_FAILED){
		fprintf(stderr, "fb mmap failed:%s\n", strerror(errno));
		return -1;
	}

	close(fd);

	return 0;
}






void m_sleep(unsigned int ms)
{
	unsigned int iloop = 0;

	for(iloop=0; iloop < ms; iloop++)
	{
		usleep(1000);
	}
	return;
}

int test_mouse(fb_info fb_inf)
{
	int mfd;
	mouse_open(NULL, &mfd);

	int m_x = fb_inf.w / 2;
	int m_y = fb_inf.h / 2;
	fb_drawcursor(fb_inf, m_x, m_y);

	u8_t buf[8];
	mouse_event_t mevent;

	int i;
	int n = 0;

	for(;;)
	{
		n = read(mfd, buf, 8);
		if (n != -1){

			mouse_parse(buf,&mevent, m_x, m_y);
			fb_restorecursor(fb_inf, m_x, m_y);

			m_x += mevent.x;
			m_y += mevent.y;
			fb_drawcursor(fb_inf, m_x, m_y);
		}

		m_sleep(5);
	}
	return 0;
}

int mouse_open(char *device_name, int *fd)
{
	if (NULL == device_name)
		device_name = "/dev/input/mice";

	*fd = open(device_name, O_RDONLY | O_NONBLOCK);
	if(*fd < 0){
		fprintf(stderr, "Open %s:%s\n", device_name, strerror(errno));
		exit(1);
	}

	return 0;
}

int mouse_parse(const u8_t *buf, mouse_event_t* mevent, int x, int y)
{
	switch(buf[0] & 0x7){
		case 1:	
			{				/* left */
				signal_mouse(x, y);
				mevent->button = 1;
				break;
			}
		case 2:
			mevent->button = 2;		/* right */
			break;
		case 4:
			mevent->button = 3;		/* middle */
			break;
		default:
			break;
	}
#if 0
	mevent->x = buf[1];
	mevent->y = buf[2];
#else
	mevent->x =  buf[1] - ((buf[0] & 0x10) ? 256 : 0);
	mevent->y = -buf[2] + ((buf[0] & 0x20) ? 256 : 0); 
#endif
	return 0;
}

/* cursor */

static int fb_pixel_m(fb_info fb_inf, int x, int y, u32_t color)
{
	/* 16 bits */
	u8_t *pos = (u8_t*)fb_inf.fbmem + (fb_inf.w * y + x) * fb_inf.bpp/8;


	switch (fb_inf.bpp){
		case 32:				  /* 32 bits */
			*(pos + 3) = color >> 24;
		case 24:				  /* 24 bits */
			*(pos + 2) = color >> 16;
		case 16:	  		       /* 16 bits */
			*(pos + 1) = color >> 8;
		case 8:			      /* 8 bits */
			*pos = color;
			return 0;
		default:
			return -1;
	}
	return -1;
}

int fb_restorecursor(fb_info fb_inf, int x, int y)
{
	int i, j;
	u32_t color;
	for (j = 0;j<C_HEIGHT;j++){
		for (i = 0;i<C_WIDTH;i++){
			color = save_cursor[i + j * C_WIDTH];
			fb_pixel_m(fb_inf,x+i,y+j,color);
		}
	}

	return 0;
}
static int  fb_savecursor (fb_info fb_inf,int x,int y)
{
	int i,j;
	u32_t color;

	for (j = 0;j<C_HEIGHT;j++)
	{
		for (i = 0;i<C_WIDTH;i++)
		{
			color = *(u32_t*)(fb_inf.fbmem + ((y + j) * fb_inf.w + x + i) * fb_inf.bpp/8);
			save_cursor[i + j * C_WIDTH] = color;
		}
	}
	return 0;
}

int  fb_drawcursor(fb_info fb_inf, int x, int y)
{
	int i,j;
	unsigned int color;

	fb_savecursor (fb_inf,x,y);

	for (j = 0;j<C_HEIGHT;j++)
	{
		for (i = 0;i<C_WIDTH;i++)
		{
			color = cursor_pixel[i + j * C_WIDTH];
			if (color != T___)
				fb_pixel_m(fb_inf,x+i,y+j,color);
		}
	}
	return 0;
}
int hxk_mouse()
{
	struct sigaction act, oact;

	fb_info fb;              
/*	for(;;)
	{ 
#if 0
		struct sigaction
		{
			void (*sa_handler) (int);
			void (*sa_sigaction) (int, siginfo_t *, void *);
			sigset_t sa_mask;
			int sa_flags;
			void (*sa_restorer) (void);
		};

		struct sigaction
		{
			union
			{
				__sighandler_t sa_handler;
				void (*sa_sigaction) (int, siginfo_t *, void *);
			} __sigaction_handler;
			__sigset_t sa_mask;
			int sa_flags;
			void (*sa_restorer) (void);
		}
#endif

		memset(&act, 0, sizeof(act));

		act.sa_handler = signal_handler1;
		sigemptyset(&act.sa_mask);
		// int sigaddset(sigset_t *set, int signum);
		sigaddset(&act.sa_mask, SIGRTMIN);
		act.sa_flags = 0;

		//int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
		if (sigaction(SIGRTMIN, &act, &oact) < 0)
		{
			fprintf(stderr, "Set new signal handler for SIGINT failed: %s\n", strerror(errno));
			exit(1);
		}
		act.sa_handler = signal_handler2;
		sigemptyset(&act.sa_mask);
		// int sigaddset(sigset_t *set, int signum);
		sigaddset(&act.sa_mask, SIGRTMIN+1);
		act.sa_flags = 0;

		//int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
		if (sigaction(SIGRTMIN+1, &act, &oact) < 0)
		{
			fprintf(stderr, "Set new signal handler for SIGINT failed: %s\n", strerror(errno));
			exit(1);
		}
		act.sa_handler = signal_handler3;
		sigemptyset(&act.sa_mask);
		// int sigaddset(sigset_t *set, int signum);
		sigaddset(&act.sa_mask, SIGRTMIN+2);
		act.sa_flags = 0;

		//int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
		if (sigaction(SIGRTMIN+2, &act, &oact) < 0)
		{
			fprintf(stderr, "Set new signal handler for SIGINT failed: %s\n", strerror(errno));
			exit(1);
		}
*/
		init_fb(&fb);         
		test_mouse(fb);
	//}             
	return 0;
}
void signal_handler1(int signum)
{
		write(1, "x\n", 1);
}
void signal_handler2(int signum)
{
		write(1, "y\n", 1);
}
void signal_handler3(int signum)
{
		write(1, "z\n", 1);
}
void signal_mouse(int x, int y)
{
	if(x > 0 && x < 256)
	{
		raise(SIGRTMIN + 3);
	}
	if(x > 768 && x < 1024)
	{
		raise(SIGRTMIN + 4);
	}
	if(x > 256 && x < 768&& y > 192&& y <576)
	{
		raise(SIGRTMIN+2);
	}
}
