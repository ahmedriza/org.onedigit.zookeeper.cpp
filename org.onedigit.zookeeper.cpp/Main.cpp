#pragma warning(disable : 4996)
#include <iostream>
#include "Connection.h"

int main(int argc, char* argv[])
{
    Connection connection;
    connection.connect();

#ifdef WIN32
    Sleep(2000);
#endif

    std::cout << "remove...." << std::endl;
    connection.remove("/zk_ahmed my_data");

    std::cout << "getChildren..." << std::endl;
    connection.getChildren("/");

    std::cout << "create..." << std::endl;
    connection.create("/zk_risk");

    while (true) {
        getchar();
    }
}