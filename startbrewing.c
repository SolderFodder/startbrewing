#include <bcm2835.h>
#include <cjson.h>
#include <curl/curl.h>
#include <oauth.h>

struct oauth_keys {
	char *ckey;
	char *csecret;
	char *atok;
	char *atoksecret;
};

int main(int argc, char *argv[])
{
	oauth_keys *keys;
	
	if(argc != 2)
	{
		printf("usage: startbrewing file");
	} else {
		read_in_keys(argv[1]);
	}
	

	return 0;
}

void read_in_keys(char *file_name) {
	char *buffer;
	long size;
	size_t result;
	FILE *file = fopen(file_name, "r");
	
	fseek()

	buffer = (char*)malloc(sizeof(char)*lsize);

	fread(keys, 1, sizeof(keys))

}

void stream_init()
{
	
}

void parse()
{
	
}

