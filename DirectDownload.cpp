#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include "directdownload.h"
#define MAX_LINE 512



int main()
{
	char url[MAX_LINE];
	char destination[MAX_LINE];


	// getting the download link and destination
	printf("Enter Download Link:");
	std::cin >> url;
	// changing name of the file as per the url
	std::string file_name = DownloadManager::fileName(url);
	strncpy_s(destination, file_name.c_str(), sizeof(url));

	std::thread showPercentage(DownloadManager::percentDownload, destination, 6677653);


	// Using function to download file from server

	HRESULT  dl;
	typedef HRESULT(WINAPI * URLDownloadToFileA_t)(LPUNKNOWN pCaller, LPCSTR szURL, LPCSTR szFileName, DWORD dwReserved, void * lpfnCB);
	URLDownloadToFileA_t xURLDownloadToFileA;
	xURLDownloadToFileA = (URLDownloadToFileA_t)GetProcAddress(LoadLibraryA("urlmon"), "URLDownloadToFileA");
	dl = xURLDownloadToFileA(NULL, url, destination, 0, NULL);

	printf("Downloading File From: %s,\n To: %s\n", url, destination);
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
	// this thread function will show how much percent is downloaded
	showPercentage.join();

}
