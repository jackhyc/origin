#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FILE_MODE S_IRWXU
int Getopt(int argc, char **argv, const char *optstring){
	int c;
	if((c=getopt(argc, argv, optstring)) != -1)
	{
		return c;
	}else{
		return -1;
	}
}

mqd_t Mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr
){
	mqd_t c;

	printf("name %s\n", name);
	if((c = mq_open(name, oflag, mode, attr)) != -1){
		return c;
	}else{
		perror("mq_open");

	}
}

void Mq_close(mqd_t mqdes){
	if(mq_close(mqdes) == -1){
		perror("mq_close");
	}
}

int main(int argc, char **argv)
{
	int c, flags;
	mqd_t mqd;
	flags = O_RDWR|O_CREAT;
	while((c=Getopt(argc, argv, "e")) != -1){
		switch(c){
			case 'e':
				flags |=O_EXCL;
				printf("get e ok\n");
				break;
		}
	}
printf("optind %d\n", optind);
	
	if(optind != argc - 1)
	{
		printf("usage:mqcreate [-e] <name>\n");
		exit(1);
	}

	mqd = Mq_open(argv[optind], flags, FILE_MODE, NULL);
	//Mq_close(mqd);
	exit(0);
}
