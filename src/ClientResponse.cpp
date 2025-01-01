// Copyright (c) Nouman Tajik [github.com/tajiknomi]
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "ClientResponse.h"
#include <vector>
#include "clientManager.h"
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <cstring>
#include <thread>
#include <chrono>

#define INVALID_SOCKET -1


int get_max_fd(fd_set* read_fds) {
    int max_fd = -1;  // Initialize max_fd to an invalid value

    for (int fd = 0; fd < FD_SETSIZE; ++fd) {
        if (FD_ISSET(fd, read_fds)) {
            if (fd > max_fd) {
                max_fd = fd;  // Update max_fd if we find a larger one
            }
        }
    }

    return max_fd;
}

void ClientResponse_t(std::shared_ptr<ClientsManager> clientManager_ptr) {

	timeval m_timeInterval;
	m_timeInterval.tv_sec = 0;
	m_timeInterval.tv_usec = 400000; // The maximum time for select(..) to wait
    
	while (true) {

        int max_fd = get_max_fd(&clientManager_ptr->m_readFds);
        const unsigned int idleTime_ms {300};                // to make the CPU less busy in
        std::this_thread::sleep_for(std::chrono::milliseconds(idleTime_ms));    // to make the CPU less busy       
		while (clientManager_ptr->getActiveClientsCount() < 1) {		        // wait for client(s) to connect
            const unsigned int connectionWaitTime_sec {1};
            std::this_thread::sleep_for(std::chrono::seconds(connectionWaitTime_sec));           
		}
        fd_set temp_fds = clientManager_ptr->m_readFds; // Copy the set
        int m_receivingStatus = select(max_fd + 1, &temp_fds, NULL, NULL, &m_timeInterval);
           
		if (m_receivingStatus == 0) {				// No socket active to read
            max_fd = get_max_fd(&clientManager_ptr->m_readFds);
			continue;
		}
        const unsigned int RecieveBuffLength{ 4096 };
        char recv_buf[RecieveBuffLength + 1] = {};
		if ((clientManager_ptr->getActiveClientSocket() > 0) && FD_ISSET(clientManager_ptr->getActiveClientSocket(), &temp_fds)) {
			int nDataLength = ::recv(clientManager_ptr->getActiveClientSocket(), recv_buf, RecieveBuffLength, 0);
			if (nDataLength == 0) {
                //std::cerr << "gracefully closed!";
				clientManager_ptr->clientDisconnected();
			}
            else if(nDataLength == -1 && errno == ECONNRESET){
                //std::cerr << "forcefully closed!";
                clientManager_ptr->clientDisconnected();   
            }
            else if(nDataLength == -1 && errno == EBADF){
                //std::cerr << "disconnected from server side!";
                clientManager_ptr->clientDisconnected();
            }
		}

        // Rebuild the fd_set
        FD_ZERO(&clientManager_ptr->m_readFds);
        for (unsigned int i = 0; i < clientManager_ptr->MaxNumOfClientsSupported; ++i) {
            int clientSocket = clientManager_ptr->getClientSocket(i);
            if (clientSocket != INVALID_SOCKET) {
                FD_SET(clientSocket, &clientManager_ptr->m_readFds);
                max_fd = std::max(max_fd, clientSocket);
            }
        }

		std::string recv_data { recv_buf };
		memset(recv_buf, 0, sizeof(recv_buf));
		std::cout << recv_data << std::flush;
		recv_data.clear();
	}
}