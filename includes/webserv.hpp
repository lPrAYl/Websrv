#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <cerrno>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <string>
#include <algorithm>

#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <dirent.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>

# define BLACK		"\x1b[30m"
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"
# define BgRED		"\x1b[41m"
# define BgGREEN	"\x1b[42m"
# define BgYELLOW	"\x1b[43m"
# define BgBLUE		"\x1b[44m"
# define BgMAGENTA	"\x1b[45m"
# define BgCYAN		"\x1b[46m"
# define BgWHITE	"\x1b[47m"

# define PORT				8888
# define DEFAULT_PORT		8080
# define BUFFER_SIZE		500000
# define DEBUG				2
# define DEFAULT_ERROR_PAGE	"www/errors/404.html"
# define DEFAULT_INDEX		"index.html"
# define DEFAULT_MAX_BODY	1024 * 1024
# define KEEP_ALIVE			5
# define ENDH				"\r\n\r\n"
# define CRLF				"\r\n"
# define NEED_CHUNKS		1024000
# define CHUNK_SIZE			256000

template <typename T>
std::string numberToString ( T Number ) {
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

template <class T> 
std::string getHex(T Value) {
	std::stringstream ss;
	ss << std::hex << Value;
	return std::string(ss.str());
}

bool		isPositiveDigit(std::string &s);
int			hexToDec(std::string hex);
int			stringToNumber (std::string &text);
void		baseError(std::string errorText);
void		printStrWithUnprintableChars(std::string string);
void		readSemicolon(std::istream &ifs);
std::string	&cutSemicolon(std::string &line);
std::string cutStringSpacesAndCr(std::string &str);

#endif //WEBSERV_HPP
