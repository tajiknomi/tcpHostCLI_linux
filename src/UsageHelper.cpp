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