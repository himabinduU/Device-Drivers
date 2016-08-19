#include<stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	char choice[10];

	fd = open( "/dev/gpio_write", O_RDWR );

	printf( "Value of fd is: %d", fd );

	if( fd < 0 )
	{
		printf("Cannot open device \t");
		printf(" fd = %d \n",fd);
		return 0;
	}

	printf("\nPlease enter choice: \t");
	scanf( "%s", choice );
	printf("Your choice is: %s \n", choice );
	
	write( fd, choice, 1 );
	printf("writing\n");

	if( 0 != close(fd) )
	{
		printf("Could not close device\n");
	}

	return 0;
}
