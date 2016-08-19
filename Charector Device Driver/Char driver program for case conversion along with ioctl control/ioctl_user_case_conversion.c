#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include<sys/ioctl.h>

#define QUERY_GET_VALUE _IOR('q', 1, int *)
#define QUERY_CLEAR_VALUE _IO('q', 2)
#define QUERY_SET_VALUE _IOW('q', 3, int *)

int main()
{
	char buf[30] = "weLCome to Adeptchips";
	char rbuf[30];
	int a=0;

	printf("Please select the option which u want\n");
	printf("Select\n 0 -> for as it is\n 1 -> toupper \n 2 -> next successive charector \n");
	scanf("%d", &a);

	printf("Before invoking driver module the string is %s\n", buf);

	int fd = open("/dev/mydev", O_RDWR);
	write(fd , &a, 4);
	write(fd, buf, strlen(buf));
	printf("writing\n");

	ioctl(fd, QUERY_SET_VALUE, &a);

	read (fd, rbuf, sizeof(rbuf));
	printf("Reading\n");
	printf("After invoking driver module the string is %s\n", rbuf);

}
