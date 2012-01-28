#include <string>
#include <iostream>

bool str_contains(const char* Haystack, const char* Needle) {
	return strstr(Haystack, Needle) != NULL;
}

std::string str_trim(std::string String, const char* CharList = " ") {
   std::string::size_type i = String.find_last_not_of(CharList);
   if(i != std::string::npos)
      String.erase(i + 1);

   i = String.find_first_not_of(CharList);
   if(i != std::string::npos)
      String.erase(0, i);

   return String;
}