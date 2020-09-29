#include <iostream>

#include "client/Client.h"

int main() {
    std::cout << "Hello World!" << std::endl;
    Client client = Client();
    while (client.isAlive) {
        client.Render();
        // client.Tick(); TODO: Add Tick
    }
}