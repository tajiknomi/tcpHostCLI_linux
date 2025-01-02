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

#include "tcpNetworkManager.h" /* Always use this header at the top */
#include "UsageHelper.h"
#include <iostream>
#include "ClientResponse.h"
#include <string>
#include "signalManager.h"

#define NumberOfArgs	2


int main(int argc, char* argv[]) {

	std::signal(SIGINT, signalHandler);	

	if (argc != NumberOfArgs) {
		std::cerr << "Usage: " << argv[0] << " <port_number>\n";
		return EXIT_FAILURE;
	}

	printUsageExamples();
	const std::string port_num(argv[1]);

	if (linuxSocket::isvalidatePort(port_num) == false) {
		return EXIT_FAILURE;
	}

	/* Create a tcp object */
	linuxSocket tcp;

	/* Initialize Socket */
	tcp.socket_init();

	/* Listen on <port_num> */
	const std::string server_ip("0.0.0.0");
	tcp.listen(server_ip.c_str(), port_num.c_str());
	std::cout << "Listening on " << server_ip << ":" << port_num << std::endl;

	/* Close socket */
	tcp.socket_cleanup();

	return 0;
}