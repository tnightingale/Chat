#include "Client.h"
#include "../core/Socket.h"

Client::Client() : serverSocket_(new Socket()) {}

Client::~Client() {
    delete serverSocket_;
}
