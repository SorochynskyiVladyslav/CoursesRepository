#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "CURL\include\curl\curl.h"


size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
	strcpy((char*)stream, (char*)ptr);
	return size*count;
}

int main(void) {
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	char resString[5000];

	char* resuestFields = "result=3";

	curl_easy_setopt(curl, CURLOPT_URL, "http://pb-homework.appspot.com/var/2");
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, resuestFields);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resString);

	res = curl_easy_perform(curl);

	if (res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));

	puts(resString);
	curl_easy_cleanup(curl);

	curl_global_cleanup();

	getchar();
	return EXIT_SUCCESS;
}