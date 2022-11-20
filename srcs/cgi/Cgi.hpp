#ifndef CGI_HPP
#define CGI_HPP

#include "webserv.hpp"
#include "ServerConfig.hpp"
#include "RequestParser.hpp"

#define SIZE_BUF_TO_SEND	1234
#define SIZE_BUF_TO_RCV		456789

class Cgi {
private:
	RequestParser						_request;
	std::string							_body;
	std::map<std::string, std::string>	env_;
	char	**getNewEnviroment() const;
	std::pair <int, std::string>	error500_(int fdInput, int fdOutput, FILE *f1, FILE *f2);

public:
	Cgi(ServerConfig &serv,  RequestParser &req);
	std::pair<int, std::string>			execute();
};

#endif
