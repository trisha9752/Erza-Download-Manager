#pragma once
//for linking the libcurl libraries
#define CURL_STATICLIB
#ifdef _DEBUG
#pragma comment(lib,"curl/libcurl_a_debug.lib")
#else
#pragma comment (lib, "curl/libcurl_a.lib")
#endif
#include "curl/curl.h"
#include"endeavour.h"
// this function use the header file and fetch file size and file type before downloading
size_t readHeader(char* header, size_t size, size_t nitems, void *userdata);
class Erza :public Endeavour {

	public: long file_size;
	CURL *curl;
	FILE *fp;
	CURLcode res;
	curl_version_info_data * vinfo = curl_version_info(CURLVERSION_NOW);

	size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
		size_t written;
		written = fwrite(ptr, size, nmemb, stream);
		return written;
	}

	// replace all %20 and %40 from the string
	public: std::string  newFileName(std::string link) {
		reverse(link.begin(), link.end());
		std::size_t pos_one = link.find("/");
		link = link.substr(0, pos_one);
		reverse(link.begin(), link.end());
		link = Endeavour::replaceAll(link, "%20", " ");
		link = Endeavour::replaceAll(link, "%40", " ");
		return link;
	}

	public:bool download (const char *url,const char* path){
		curl = curl_easy_init();
		if (curl) {
			fp = fopen(path, "wb");
			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_CAINFO, "./ca-bundle.crt");
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
			curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, readHeader);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			fclose(fp);
			return false;
		}else
			return true;
		
	}
};


size_t readHeader(char* header, size_t size, size_t nitems, void *userdata) {
	Erza oprations;
	if (oprations.startsWith(header, "Content-Length:")) {
		std::string header_in_string = oprations.replaceAll(header, "Content-Length:", "");
		long size = atol(header_in_string.c_str());
		oprations.file_size = size;
		std::cout << size;
	}
	else if (oprations.startsWith(header, "Content-Type:")) {

	}
	return size * nitems;
}

