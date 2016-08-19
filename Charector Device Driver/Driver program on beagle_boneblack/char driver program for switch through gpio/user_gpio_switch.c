#include<stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	char gpio_buffer[10];

	fd = open( "/dev/gpio_read", O_RDWR );

	printf( "Value of fd is: %d", fd );

	if( fd < 0 )
	{
		printf("Cannot open device \t");
		printf(" fd = %d \n",fd);
		return 0;
	}

	read( fd, gpio_buffer, 1);

	printf("reading\n");
	printf("GPIO value is(user_pgm): %s \n", gpio_buffer );

	if( 0 != close(fd) )
	{
		printf("Could not close device\n");
	}

	return 0;
}
