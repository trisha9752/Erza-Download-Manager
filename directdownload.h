#pragma once

class Direct {
	
	// replace all %20 from the string 
	private: static std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); 
		}
		return str;
	}

	public: static std::string rename(std::string link) {
		reverse(link.begin(), link.end());
		std::size_t pos_one = link.find("/");
		link = link.substr(0, pos_one);
		reverse(link.begin(), link.end());
		link = Direct::replaceAll(link,"%20"," ");
		return link;
		}
};
