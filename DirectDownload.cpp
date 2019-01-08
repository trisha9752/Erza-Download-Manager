#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include "directdownload.h"
#define MAX_LINE 512

	 void percentDownload(const char* filename, double real_file_size) {
		 double current_file_size;
		 do {
			 std::ifstream in(filename, std::ios::binary | std::ios::ate);
			 current_file_size = (double)in.tellg();
			 std::cout << (current_file_size / real_file_size) * 100;
		 } while (current_file_size != real_file_size);
	}

int main()
{
		char url[MAX_LINE];
		char destination[MAX_LINE];


		// getting the download link and destination
		printf("Enter Download Link:");
		std::cin >> url;
		// changing name of the file as per the url
		std::string file_name = Direct::fileName(url);
		strncpy_s(destination, file_name.c_str(), sizeof(url));

		std::thread th1(percentDownload,destination,23438713);
		th1.join();

		// Using function to download file from server
		
			HRESULT  dl;
			typedef HRESULT(WINAPI * URLDownloadToFileA_t)(LPUNKNOWN pCaller, LPCSTR szURL, LPCSTR szFileName, DWORD dwReserved, void * lpfnCB);
			URLDownloadToFileA_t xURLDownloadToFileA;
			xURLDownloadToFileA = (URLDownloadToFileA_t)GetProcAddress(LoadLibraryA("urlmon"), "URLDownloadToFileA");
			dl = xURLDownloadToFileA(NULL, url, destination, 0, NULL);

			printf("Downloading File From: %s, To: %s", url, destination);
			if (dl == S_OK) {
				printf("File Successfully Downloaded To: %s", destination);

			}
			else if (dl == E_OUTOFMEMORY) {
				printf("Failed To Download File Reason: Insufficient Memory");
				return 0;
			}
			else {
				printf("Failed To Download File Reason: Unknown");
				return 0;
			}

}
