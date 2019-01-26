#pragma once
#include"akuma.h"
class Haki :public Akuma {
	// replace all %20 and %40 from the string
	public: std::string  newFileName(std::string link) {
		reverse(link.begin(), link.end());
		std::size_t pos_one = link.find("/");
		link = link.substr(0, pos_one);
		reverse(link.begin(), link.end());
		link = Akuma::replaceAll(link, "%20", " ");
		link = Akuma::replaceAll(link, "%40", " ");
		return link;
	}


};