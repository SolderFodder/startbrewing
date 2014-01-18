#include <bcm2835.h>
#include <curl/curl.h>
#include <oauth.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"

typedef struct {
	char *ckey;
	char *csecret;
	char *atok;
	char *atoksecret;
} oauth_keys;

void read_in_keys(char*, oauth_keys*);
size_t parse(char *ptr, size_t size, size_t nmemb, char *data);

int count;

int main(int argc, const char* argv[])
{	

	count = 0;
	
	if(argc != 2)
	{
		printf("usage: startbrewing file\n");
	} else {
		const char *url = "https://userstream.twitter.com/1.1/user.json";
		oauth_keys *keys = malloc(sizeof(oauth_keys)+1);	

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
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parse);
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);
		
		int curl_status = curl_easy_perform(curl);
		
		curl_easy_cleanup(curl);
		curl_global_cleanup();
	}
	
	return 0;
}

void read_in_keys(char *f, oauth_keys *k) {

	FILE *file = fopen(f, "r");

	fscanf(file, "%s\n%s\n%s\n%s\n", k->ckey, k->csecret, k->atok, k->atoksecret);

	fclose(file);
}

size_t parse(char *ptr, size_t size, size_t nmemb, char *data)
{
	if(size*nmemb <= 2)
	{
		return size*nmemb;
	} 

	printf("%s\n", ptr); //DEBUG

	cJSON *root = cJSON_Parse(ptr);
	struct cJSON *current = root->child;

	while(strcmp(current->string, "text") != 0) 
	{
		if(current->next != NULL)
		{
			current = current->next;
		} else {
			break;
			printf("done"); //DEBUG
		}
	}

	if(strstr(current->valuestring, "START") != NULL)
	{
		
	} else if(current->valuestring, "OFF") != NULL)
	{

	}

	printf("Current object: %s\n", cJSON_Print(current)); //DEBUG

	return size*nmemb;
}


