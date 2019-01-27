#define _CRT_SECURE_NO_WARNINGS // it is used so fopen doesn't throw compile error in Visual Studio
#include <iostream>
// using Endeavour and haki download Header file
#include"erza.h"
int main() {

	Erza *downloader = new Erza();
	const char* url = "https://stackoverflow.com/questions/1750055/with-php-curl-get-filename-from-file-header";
	char path[FILENAME_MAX] = "./json.zip";
	bool error = downloader->download(url, path);
	return 0;
}