#include "tcpNetworkManager.h"
#include "clientManager.h"
#include "ServerQueries.h"
#include "ClientResponse.h"
#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <codecvt>
#include <locale>
#include <arpa/inet.h>
#include <sys/select.h>

#define INVALID_SOCKET -1

std::wstring s2ws(const std::string& str) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.from_bytes(str);
}

std::string ws2s(const std::wstring& wstr) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.to_bytes(wstr);
}

/*	Static function(s)	*/
bool linuxSocket::isvalidatePort(const std::string& input){
	
		for (char c : input) {
			if (!std::isdigit(c)) {
				std::cerr << "PORT is invalid, please put only the number for PORT [1 - 65535]\n";
				return false;
			}
		}
		try {
			int port = std::stoi(input);
			if (port < 1 || port > 65535) {
				std::cerr << "PORT is invalid, please select a PORT in the range [1 - 65535]\n";
				return false;
			}
		}
		catch (const std::invalid_argument&) {
			std::cerr << "PORT is invalid, please enter a valid number in the range [1 - 65535]\n";
			return false;
		}
		catch (const std::out_of_range&) {
			std::cerr << "PORT is invalid, number out of range\n";
			return false;
		}
		return true;
}

void linuxSocket::socket_init(){

    /* Build the socket. */
    struct protoent* protoent = getprotobyname("tcp");
    if (protoent == NULL) {
        perror("getprotobyname");
        //return -1;
    }
    ListenSocket = socket(AF_INET, SOCK_STREAM, protoent->p_proto);
    if (ListenSocket == -1) {
        perror("socket");
        //return -1;
    }
    //return 0;
}

void linuxSocket::listen(const std::string &url, const std::string &port){

	// This pointer will be shared with sending and recieving threads (i.e. ClientResponse and ServerQueries modules)
	std::shared_ptr<ClientsManager> clientManager_ptr = std::make_shared<ClientsManager>();

    /* Build the address. */
    struct hostent *hostent = gethostbyname(url.c_str());
    if (hostent == NULL) {
        std::cerr << "error: gethostbyname(\"" << url << "\")" << std::endl;
        //return -1;
    }
    in_addr_t in_addr = inet_addr(inet_ntoa(*(struct in_addr*)*(hostent->h_addr_list)));
    if (in_addr == (in_addr_t)-1) {
        std::cerr << "error: inet_addr(\"" << *(hostent->h_addr_list) << "\")" << std::endl;
        //return -1;
    }
    struct sockaddr_in sockaddr_in;
    const unsigned short server_port = std::stoi(port);
    sockaddr_in.sin_addr.s_addr = in_addr;
    sockaddr_in.sin_family = AF_INET;
    sockaddr_in.sin_port = htons(server_port);

    int opt = 1;
    setsockopt(ListenSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if(::bind(ListenSocket, (struct sockaddr*)&sockaddr_in, sizeof(struct sockaddr_in)) == -1){
        perror("bind");
    }

    if(::listen(ListenSocket, SOMAXCONN) == -1){
        perror("listen");
    }

    struct sockaddr_in sockaddr_out;
    unsigned int sockaddrlength = sizeof(sockaddr_out);
    char clientIP[INET_ADDRSTRLEN];
    
    std::thread send_thread(ServerQueries_t, clientManager_ptr);					// A thread which send commands to client(s)
    std::thread recv_tread(ClientResponse_t, clientManager_ptr);					// A thread which recieves response/data from client(s) 

    for (unsigned int ClientId = 0; ClientId < MaxNumberOfSessionsSupported; ++ClientId) {
        int newSocket = ::accept(ListenSocket, (struct sockaddr*)&sockaddr_out, &sockaddrlength);
        if(newSocket == -1){
            continue;
        }
    //    FD_ZERO(&clientManager_ptr->m_readFds);             // DELETE THIS!!
        FD_SET(newSocket, &clientManager_ptr->m_readFds);
        clientManager_ptr->clientConnected();
        inet_ntop(AF_INET, &(sockaddr_out.sin_addr), clientIP, INET_ADDRSTRLEN);
		std::cout << "====================== Client ID " << ClientId <<  ": "  << clientIP << " is connected ======================" << std::endl;
        clientManager_ptr->setClientSocket(ClientId, newSocket);
        newSocket = INVALID_SOCKET;
    }
}

void linuxSocket::socket_cleanup(){
    
}