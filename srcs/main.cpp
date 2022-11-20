#include "webserv.hpp"
#include "Server.hpp"
#include "Config.hpp"

bool g_status = false;
pthread_mutex_t g_write;

static void	interruptHandler(int sig_int) {
	(void)sig_int;
	g_status = true;
	std::stringstream message;
	message << BgMAGENTA << "\nAttention! Interruption signal caught.";
	Logger::printCriticalMessage(&message);
}

static void	*routine(void *webserv) {
	reinterpret_cast<Server *>(webserv)->initiate(reinterpret_cast<Server *>(webserv)->webConfig.getHost().c_str(), reinterpret_cast<Server *>(webserv)->webConfig.getPort());
	reinterpret_cast<Server *>(webserv)->runServer(-1);
	return (NULL);
}

int main(int argc, char *argv[]) {
	std::stringstream message;
	message << "C++ version is " << __cplusplus;
	Logger::printCriticalMessage(&message);
	signal(SIGINT, interruptHandler);
	Config config(argc, argv);
	std::vector<ServerConfig> servers = config.getServers();
	Server webserv[servers.size()];

	for (size_t i = 0; i < servers.size(); i++) {
		webserv[i].webConfig = servers[i];
		webserv[i].serverID = i;
		if (pthread_create(&webserv[i].tid, NULL, &routine, &webserv[i]) != 0)
			exit (EXIT_FAILURE);
		pthread_detach(webserv[i].tid);
	}

	while(!g_status) {
		if (g_status) {
			pthread_mutex_lock(&g_write);
			message << BgMAGENTA << "Closing connections... ";
			pthread_mutex_unlock(&g_write);
			Logger::printCriticalMessage(&message);
		}
	}

	pthread_mutex_destroy(&g_write);
	return 0;
}
