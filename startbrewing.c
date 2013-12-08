//#include <bcm2835.h>
//#include <cjson.h>
#include <curl/curl.h>
#include <oauth.h>
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
	if(argc != 2)
	{
		printf("usage: startbrewing file\n");
	} else {
		FILE *out = stdout;
		const char *url = "https://userstream.twitter.com/1.1/user.json";
		struct oauth_keys *keys = malloc(sizeof(struct oauth_keys)+1);

		keys->ckey = malloc(50);
		keys->csecret = malloc(50);
		keys->atok = malloc(50);
		keys->atoksecret = malloc(50);
		
		char *filename = malloc(strlen(argv[1])+1);
	
		strcpy(filename, argv[1]);
		
		read_in_keys(filename, keys);
		
		curl_global_init(CURL_GLOBAL_ALL);
		
		CURL *curl = curl_easy_init();
		char *signedurl = oauth_sign_url2(url, NULL, OA_HMAC, "GET", keys->ckey, keys->csecret, keys->atok, keys->atoksecret);
		
		curl_easy_setopt(curl, CURLOPT_URL, signedurl);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "Start Brewing/0.1");
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)out);
		
		int curl_status = curl_easy_perform(curl);
		
		curl_easy_cleanup(curl);
		curl_global_cleanup();
	}
	
	return 0;
}

void read_in_keys(char *f, struct oauth_keys *k) {

	FILE *file = fopen(f, "r");

	fscanf(file, "%s\n%s\n%s\n%s\n", k->ckey, k->csecret, k->atok, k->atoksecret);

	fclose(file);
}

void stream_init()
{
	
}

void parse()
{
	
}

