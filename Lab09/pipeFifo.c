#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TFIFO "/tmp/task4_fifo"
#define READ_END 0
#define WRITE_END 1

int main()
{
	//Make fifo so I don't have to make fifo every time I log in
	umask(0000);
	int ffd;
	ffd = mkfifo("/tmp/task4_fifo", 0777);

	//Variables
	int data_processed;
	int fd;
	const char some_data[] = "123";
	char *buffer;
	int len = strlen(some_data);

	buffer = (char*)malloc(len*sizeof(char));

	//Open write only fifo
	if((fd = open("/tmp/task4_fifo", O_WRONLY)) < 0);
		exit(1);
	data_processed = write(fd, some_data, strlen(some_data));
	printf("Wrote %d bytes\n", data_processed);

	//Open read only fifo
	data_processed = read(fd, buffer, len);		
	printf("Read %d bytes: %s\n", data_processed, buffer);
	close(fd);

	free(buffer);
	exit(EXIT_SUCCESS);
}
