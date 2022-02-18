#include "utils.hpp"

int main(void)
{
    // Initialize variables
    DWORD pId;
    std::string procName;

    // Get process name from user
    std::cout << "Process name: ";
    std::cin >> procName;

    // Error processing
    if (!Utils::getPid(procName)) {
        std::cout << "Error in getting process identifier!" << std::endl
                  << "Press any key!";
        std::cin.get();
        return 0;
    }

    // Get process ID
    pId = Utils::getPid(procName);

    // Print list of modules
    Utils::moduleList(pId);

    return 0;
}
