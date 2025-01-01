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


#include <iostream>
#include <iomanip>
#include "UsageHelper.h"

void printUsageExamples() {
    const int commandWidth = 20;
    const int descriptionWidth = 50;

    std::cout << std::endl
              << "==================== Usage Example(s) ====================" << std::endl;
    std::cout << std::left << std::setw(commandWidth) << "!<session_id>"
              << std::setw(descriptionWidth) << "// Switch to the specified session by its ID" << std::endl;
    std::cout << std::left << std::setw(commandWidth) << "!5"
              << std::setw(descriptionWidth) << "// Example: Switch to session 5" << std::endl;
    std::cout << std::left << std::setw(commandWidth) << "!list"
              << std::setw(descriptionWidth) << "// Show active sessions" << std::endl;
    std::cout << std::left << std::setw(commandWidth) << "!tty [py|py3|perl]"
              << std::setw(descriptionWidth) << "// e.g. tty py3" << std::endl;          
    std::cout << std::left << std::setw(commandWidth) << "!clear"
              << std::setw(descriptionWidth) << "// Clear screen" << std::endl;
    std::cout << std::left << std::setw(commandWidth) << "!exit"
              << std::setw(descriptionWidth) << "// Close current session" << std::endl;
    std::cout << std::left << std::setw(commandWidth) << "!"
              << std::setw(descriptionWidth) << "// Show help menu" << std::endl
              << std::endl;
}