#include <iostream>

#include "client/Client.h"

int main() {
    std::cout << "Hello World!" << std::endl;
    Client client = Client();
    while (client.isAlive) {
        client.render();
        // client.tick(); TODO: Add Tick
    }
}