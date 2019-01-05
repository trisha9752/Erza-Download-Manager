#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <thread>
#include "directdownload.h"
#define MAX_LINE 512

int main()
{
		char url[MAX_LINE];
		char destination[MAX_LINE];
		char buffer[MAX_LINE];

		// getting the download link and destination
		printf("Enter Download Link:");
		std::cin >> url;
		// changing name of the file as per the url
		std::string destination_name = Direct::rename(url);
		strncpy_s(destination, destination_name.c_str(), sizeof(url));

		// Using function to download file from server
		HRESULT  dl;
		typedef HRESULT(WINAPI * URLDownloadToFileA_t)(LPUNKNOWN pCaller, LPCSTR szURL, LPCSTR szFileName, DWORD dwReserved, void * lpfnCB);
		URLDownloadToFileA_t xURLDownloadToFileA;
		xURLDownloadToFileA = (URLDownloadToFileA_t)GetProcAddress(LoadLibraryA("urlmon"), "URLDownloadToFileA");
		dl = xURLDownloadToFileA(NULL, url, destination, 0, NULL);

		sprintf_s(buffer, "Downloading File From: %s, To: %s", url, destination);
		if (dl == S_OK) {
			sprintf_s(buffer, "File Successfully Downloaded To: %s", destination);

		}
		else if (dl == E_OUTOFMEMORY) {
			sprintf_s(buffer, "Failed To Download File Reason: Insufficient Memory");
			return 0;
		}
		else {
			sprintf_s(buffer, "Failed To Download File Reason: Unknown");
			return 0;
		}


}
