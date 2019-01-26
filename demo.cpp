#define _CRT_SECURE_NO_WARNINGS // it is used so fopen doesn't throw compile error in Visual Studio
/*for linking the libcurl libraries*/
#define CURL_STATICLIB
#ifdef _DEBUG
#pragma comment(lib,"curl/libcurl_a_debug.lib")
#else
#pragma comment (lib, "curl/libcurl_a.lib")
#endif

#include <stdio.h>
#include "curl/curl.h"
#include <string>


// using Akuma and haki download Header file
#include"haki.h"

	size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
		size_t written;
		written = fwrite(ptr, size, nmemb, stream);
		return written;
	}


int main() {

	Haki *downloader = new Haki();
	CURL *curl;
	FILE *fp;
	CURLcode res;
	std::string url = "https://curl.haxx.se/download/curl-7.63.0.zip";
	char outfilename[FILENAME_MAX] = "./json.zip";
	curl_version_info_data * vinfo = curl_version_info(CURLVERSION_NOW);

	curl = curl_easy_init();
	if (curl) {
		fp = fopen(outfilename, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		/* Setup the https:// verification options - note we do this on all requests as there may
		   be a redirect from http to https and we still want to verify */
		   //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
		curl_easy_setopt(curl, CURLOPT_CAINFO, "./ca-bundle.crt");
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
		delete downloader;
	}
	return 0;
}