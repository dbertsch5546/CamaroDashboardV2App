#ifndef INTERACTIVESHELL_H
#define INTERACTIVESHELL_H

#include <thread>

#define SHELL_PORT 3000
class InteractiveShell
{
public:
    InteractiveShell();
    int getClientSocketFD();
private:
    int _serverSocketfd = -1;
    int _clientSocketfd = -1;
    void initMicroshell();
    std::thread _shellThreadHandle;
    void shellTask();
};

#endif // INTERACTIVESHELL_H
