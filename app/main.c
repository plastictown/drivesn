#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

char* get_root_device();

int main(int argc, char** argv)
{
	char* dev = get_root_device();
	if(NULL != dev)
	{
		size_t offset = 0u;
		while( !isprint(dev[offset])){++offset;}
		printf("device: %s\n", dev + offset);
		free(dev);
		return EXIT_SUCCESS;
	}
	printf("can't get device!\n");
	return EXIT_FAILURE;
}

char* get_root_device()
{
	const size_t max_buf_sz = 256u;
	const char* cmd = "awk '$2==\"/\"{print $1}' /proc/self/mounts";
	FILE* pipe = popen(cmd, "r");
	if(NULL == pipe)
	{
		perror("can't open pipe: ");
		return NULL;
	}
	char buf[max_buf_sz];
	if( fgets(buf, sizeof buf, pipe) == NULL)
	{
		perror("can't read from pipe: ");
		pclose(pipe);
		return NULL;
	}
	pclose(pipe);
	size_t len = strlen(buf);
	char* ret_buf = (char*) calloc(len +1u, sizeof(char));
	if(NULL == ret_buf)
	{
		perror("can't allocate memory: ");
		return NULL;
	}
	strcpy(ret_buf, buf);
	return ret_buf;

}
