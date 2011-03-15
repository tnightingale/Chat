#include "User.h"

User::User(char * address) 
: address_(new QString(address)) {}

User::~User() {
    delete address_;
    delete userName_;
}
