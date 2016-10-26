#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>

int main() {

	char* hola = "HOLA\n";
	void* buf = (char*) malloc(8);

	int fd = open("/dev/ttyUSB0", O_RDWR);

	write(fd, hola, 5);

	int size = read(fd, buf, 2);

	printf("size: " + (int) size);

	printf(buf == NULL? "BUF ES NULL" : "BUF NO ES NULL");

	printf((char*) buf);

	close(fd);
}
