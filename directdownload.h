#pragma once

class Direct {
	
	public: static double convertBytesToKB(double bytes){
		return bytes / 1024;
	}
	
	public: static double convertKBToMB(long double KB) {
		return (double) KB / 1024;
	}

	public: static long double convertMBToGB(long double MB) {
		return MB / 1024;
	}
	
	// use this in thread to get the current downloaded percentage.
	public: static int percentDownload(const char* filename ,double real_file_size ){
		std::ifstream in(filename, std::ios::binary | std::ios::ate);
		double current_file_size = (double) in.tellg();
		std::cout <<(current_file_size / real_file_size) * 100;
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
		link = Direct::replaceAll(link,"%20"," ");
		link = Direct::replaceAll(link, "%40", " ");
		return link;
		}
};
