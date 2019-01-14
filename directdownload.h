#pragma once

class DownloadManager {

	public: static double convertBytesToKB(double bytes) {
		return bytes / 1024;
	}

	public: static double convertKBToMB(long double KB) {
		return (double)KB / 1024;
	}

	public: static long double convertMBToGB(long double MB) {
		return MB / 1024;
	}

	public: static void percentDownload(const char* filename, long real_file_size) {
		long current_file_size;
		do{
			std::ifstream in(filename, std::ios::binary | std::ios::ate);
			current_file_size = (long)in.tellg();
			std::cout <<"\r" <<(current_file_size / real_file_size) * 100<<"%";
		} while (real_file_size != current_file_size);
		std::cout << "\n";
	}

			// a replaceall function 
	private: static std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
		return str;
	}
			 // replace all %20 and %40 from the string
	public: static std::string  fileName(std::string link) {
		reverse(link.begin(), link.end());
		std::size_t pos_one = link.find("/");
		link = link.substr(0, pos_one);
		reverse(link.begin(), link.end());
		link = DownloadManager::replaceAll(link, "%20", " ");
		link = DownloadManager::replaceAll(link, "%40", " ");
		return link;
	}
};
