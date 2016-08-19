#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>

int main()
{
	char buf[30] = "weLCome to Adeptchips";
	char rbuf[30]= {0};
	printf("Before invoking driver module the string is %s\n", buf);
	
	int fd = open("/dev/mydev", O_RDWR);
	write(fd, buf, strlen(buf));
	printf("writing\n");
	read (fd, rbuf, sizeof(rbuf));
	printf("Reading\n");
	printf("After invoking driver module the string is %s\n", rbuf);

}
