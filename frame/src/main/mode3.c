#include<stdio.h>
#include<ftw.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>
#include<unistd.h>

char *jpegname[10];//save jpeg name  MAX is 10
static int jpegs = 0;
static int i = 1;
sigset_t s,old;
//--------------------------save jpeg name----------------------------------//
void *print_mode3(void *arg)
{
	int stat;
	pid_t pid1;
	int left = i;
	int zhong;
	int right;
	if (i == jpegs-1)
	{
		zhong = 1;
		right = 2;
	}
	else if(i == jpegs -2)
	{
		zhong = jpegs-1;
		right = 1;
	}
	else 
	{
		zhong = i + 1;
		right = i + 2;
	}
		
	pid1 = fork();
	if(pid1 < 0)
	{
		perror("fork failed");
		exit(1);
	}
	
	if(pid1 == 0)
	{
			
//		execlp("./mode1_print_photo.out","./mode1_print_photo.out","../../background/back2.jpg","/dev/fb0",NULL);
		execlp("./mode1_print_photo_2.out","./mode1_print_photo_2.out",jpegname[zhong],"/dev/fb0",NULL);
//		execlp("./mode1_print_photo_3.out","./mode1_print_photo_3.out",jpegname[i++],"/dev/fb0",NULL);
				
//			printf("printf photo %s\n",jpegname[i]);
		exit(1);
	}

//	wait(&stat);
	pid1 = fork();
	if(pid1 < 0)
	{
		perror("fork failed");
		exit(1);
	}
	
	if(pid1 == 0)
	{
			
//		execlp("./mode1_print_photo.out","./mode1_print_photo.out","../background/back2.jpg","/dev/fb0",NULL);
		execlp("./mode1_print_photo_1.out","./mode1_print_photo_1.out",jpegname[left],"/dev/fb0",NULL);
//		execlp("./mode1_print_photo_3.out","./mode1_print_photo_3.out",jpegname[i++],"/dev/fb0",NULL);
			
//			printf("printf photo %s\n",jpegname[i]);
		exit(1);
	}

	pid1 = fork();
	if(pid1 < 0)
	{
		perror("fork failed");
		exit(1);
	}
	
	if(pid1 == 0)
	{
			
//		execlp("./mode1_print_photo.out","./mode1_print_photo.out","../background/back2.jpg","/dev/fb0",NULL);
//		execlp("./mode1_print_photo_1.out","./mode1_print_photo_1.out",jpegname[i++],"/dev/fb0",NULL);
		execlp("./mode1_print_photo_3.out","./mode1_print_photo_3.out",jpegname[right],"/dev/fb0",NULL);
				
//			printf("printf photo %s\n",jpegname[i]);
		exit(1);
	}



}

void *hxk_mouse_main(void *arg)
{
	hxk_mouse();
	pthread_exit(NULL);
}
int fn(const char *fpath, const struct stat *sb, int typeflag)
{
	jpegname[jpegs] = malloc(20);
	strcpy(jpegname[jpegs],fpath);
	jpegs++;
	return 0;
}
void sig_leftact(void)
{
	if(i == 1)
		i = jpegs-1;
	else
		i = i - 1;
	print_mode3((void *)i);
}
void sig_rightact(void)
{
	if(i == jpegs-1)
		i = 1;
	else
		i = i + 1;
	print_mode3((void *)i);
}

void sig_startact(void)
{
	int fd;
	fd = open("jpegname.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);
	if (fd < 0)
	{
		perror("open jpegname failed");
		exit(1);
	}
	if(i == (jpegs-1))
		write(fd,jpegname[1],20);
	else 
		write(fd,jpegname[i+1],20);	
	execlp("./start.out","./start.out","./res",NULL);
}
int main(void)
{
//-------------------------open dir ---------------------------------------//
	
	sigset_t old;
	sigemptyset(&old);
	sigaddset(&old, SIGINT);
	sigaddset(&old, SIGRTMIN+2);
	sigprocmask(SIG_UNBLOCK,&old,NULL);

	pthread_t tid1;
	pthread_create(&tid1, NULL, hxk_mouse_main, NULL);	
	if(ftw("./res",fn,200) == -1)
	{
		perror("ftw");
		return 0;
	}
	
#if 1 
	int j;
	for(j = 0;j < jpegs; j++)
	{
		printf("%s\n",jpegname[j]);
	}
	printf("jpegs = %d\n",jpegs);
#endif
//	pthread_t tid;
//	pthread_create(&tid,NULL,mouse_fun,NULL);
	int fd,save_fd,stat;


//----------------------------------make STDOUT_FILENO to config.txt-----------------------------//
#if 1
	fd = open("config.txt",O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd < 0)
	{
		perror("open config.txt failed");
		exit(1);
	}
	save_fd = dup(STDOUT_FILENO);
	dup2(fd,STDOUT_FILENO);
	close(fd);
#endif
//---------------------------------print jpeg--------------------------------------------------//
	pid_t pid1;
	pid1 = fork();
	if(pid1 < 0)
	{
		perror("fork failed");
		exit(1);
	}
	
	if(pid1 == 0)
	{
//			
		execlp("./mode1_print_photo_4.out","./mode1_print_photo_4.out","./background/back2.jpg","/dev/fb0",NULL);
//		execlp("./mode1_print_photo_2.out","./mode1_print_photo_1.out",jpegname[i++],"/dev/fb0",NULL);
//		execlp("./mode1_print_photo_3.out","./mode1_print_photo_3.out",jpegname[i++],"/dev/fb0",NULL);
				
//			printf("printf photo %s\n",jpegname[i]);
		exit(1);
	}
	usleep(200);
	pthread_t tid;
	pthread_create(&tid, NULL, print_mode3, (void *)i);	
//--------------------------------sigaction----------------------------------------------------

	struct sigaction leftact,rightact, startact;
	leftact.sa_handler = sig_leftact;
	sigemptyset(&leftact.sa_mask);
	leftact.sa_flags = 0;
	sigaction(SIGRTMIN+3,&leftact,NULL);

	rightact.sa_handler = sig_rightact;
	sigemptyset(&rightact.sa_mask);
	rightact.sa_flags = 0;
	sigaction(SIGRTMIN+4,&rightact,NULL);

	startact.sa_handler = sig_startact;
	sigemptyset(&startact.sa_mask);
	startact.sa_flags = 0;
	sigaction(SIGRTMIN+2,&startact,NULL);



	while(1)
	{
	
	}
	dup2(save_fd,STDOUT_FILENO);
	close(save_fd);
	return 0;
}








			
