#ifndef SERVER_HPP
#define SERVER_HPP

#include "webserv.hpp"
#include "Config.hpp"
#include "RequestParser.hpp"
#include "Response.hpp"
#include "Logger.hpp"

extern pthread_mutex_t g_write;
class ServerConfig;
class RequestParser;
class Response;
class Logger;

typedef struct s_reqData {
	bool			isTransfer;
	bool			isMultipart;
	bool			foundHeaders;
	char			*responseStr;
	size_t			chunkInd;
	size_t			reqLength;
	size_t			responseSize;
	std::string		bound;
	std::string		finalBound;
	std::string		method;
	std::string		reqString;
	Response		*response;
}	t_reqData;

class Server {
private:
	bool						findReqEnd(t_reqData &req);
	int 						_listenSocket;
	int							_timeout;
	void						clearConnections();
	void						isChunked(std::string headers, s_reqData *req);
	void						pollError(pollfd &pfd);
	sockaddr_in					_servAddr;
	std::vector<struct pollfd>	_fds;
	std::map<long, t_reqData>	_clients;
	std::set<int>				_fdToDel;
	std::stringstream 			_message;
	Server(const Server &other);
	Server						&operator=(const Server &other);

public:
	bool						endByTimeout(t_reqData &req);
	int							getListenSocket(void) const;
	int							getTimeout(void) const;
	int							serverID;
	void						acceptConnection(void);
	void						closeConnection(int socket);
	void						initiate(const char *ipAddr, int port);
	void						initReqDataStruct(int clientFD);
	void						receiveRequest(pollfd &pfd);
	void						runServer(int timeout);
	void						sendResponse(pollfd &pfd);
	void						setTimeout(int timeout);
	pthread_t					tid;
	class ServerConfig			webConfig;
	Server();
	~Server();
};

char	*getCstring(const std::string &cppString);

#endif //SERVER_HPP
