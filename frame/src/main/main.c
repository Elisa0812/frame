#include<stdio.h>
#include<ftw.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>

char *jpegname[10];//save jpeg name  MAX is 10
static int jpegs = 0;
//--------------------------save jpeg name----------------------------------//
int fn(const char *fpath, const struct stat *sb, int typeflag)
{
	jpegname[jpegs] = malloc(20);
	strcpy(jpegname[jpegs],fpath);
	jpegs++;
	return 0;
}
void sig_ctlcact(void)
{
	execlp("./a.out","sudo ./a.out",NULL);
}

int main(int argc, char *argv[])
{
//-------------------------open dir ---------------------------------------//
	
	struct sigaction leftact;
	printf("i = ");
	leftact.sa_handler = sig_ctlcact;
	sigemptyset(&leftact.sa_mask);
	leftact.sa_flags = 0;
	sigaction(SIGINT,&leftact,NULL);


	if(ftw((argc < 2)? "./res":argv[1],fn,200) == -1)
	{
		perror("ftw");
		return 0;
	}
	
#if 0 
	int j;
	for(j = 0;j < jpegs; j++)
	{
		printf("%s\n",jpegname[j]);
	}
#endif
	int i;
	int fd1;
	fd1 = open ("jpegname.txt",O_RDONLY,0644);
	if(fd1 < 0)
	{
		perror("open jpegname failed");
		exit(1);
	}
	char buf[20];
	int n,j;
	n = read(fd1, buf,20);
	for(j = 0; j < jpegs; j ++)
	{
		if((strncmp(buf,jpegname[j],n)) == 0) 
		{
			i = j;
			break;
		}
	}




#if 1
//	pthread_t tid;
//	pthread_create(&tid,NULL,mouse_fun,NULL);
	pid_t pid1;
	int fd,save_fd;
//----------------------------------make STDOUT_FILENO to config.txt-----------------------------//
	fd = open("config.txt",O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd < 0)
	{
		perror("open config.txt failed");
		exit(1);
	}
	save_fd = dup(STDOUT_FILENO);
	dup2(fd,STDOUT_FILENO);
	close(fd);
//---------------------------------print jpeg--------------------------------------------------//
	for(; i < jpegs;i ++)
	{
		pid1 = fork();
		if(pid1 < 0)
		{
			perror("fork failed");
			exit(1);
		}
		
		if(pid1 == 0)
		{
			
			execlp("./mode1_print_photo.out","./mode1_print_photo.out",jpegname[i],"/dev/fb0",NULL);
//			printf("printf photo %s\n",jpegname[i]);
			exit(1);
		}
		if(i == jpegs -1)
			i = 1;
		
		sleep(6);
	}
	dup2(save_fd,STDOUT_FILENO);
	close(save_fd);
	return 0;
#endif
}








			
