//#include <bcm2835.h>
//#include <cjson.h>
//#include <curl/curl.h>
//#include <oauth.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct oauth_keys {
	char *ckey;
	char *csecret;
	char *atok;
	char *atoksecret;
};

void read_in_keys(char*, struct oauth_keys*);

int main(int argc, const char* argv[])
{
	struct oauth_keys *keys = malloc(sizeof(struct oauth_keys)+1);
	keys->ckey = malloc(sizeof(char*)+1);
	keys->csecret = malloc(sizeof(char*)+1);
	keys->atok = malloc(sizeof(char*)+1);
	keys->atoksecret = malloc(sizeof(char*)+1);
	char *filename = malloc(strlen(argv[1])+1);
	
	strcpy(filename, argv[1]);
	
	if(argc != 2)
	{
		printf("usage: startbrewing file");
	} else {
		read_in_keys(filename, keys);
		
		printf("%s\n", keys->ckey);
		//printf("%s\n", keys->csecret);
		//printf("%s\n", keys->atok);
		//printf("%s\n", keys->atoksecret);
	}
	

	return 0;
}

void read_in_keys(char *f, struct oauth_keys *k) {

	FILE *file = fopen(f, "r");

	fscanf(file, "%s\n", k->ckey);
	//fscanf(file, "%s\n", k->csecret);
	//fgets(k->atok, 100, file);
	//fgets(k->atoksecret, 100, file);

	fclose(file);
}

void stream_init()
{
	
}

void parse()
{
	
}

