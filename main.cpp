#include <iostream>
#include "include/jsonConv.h"

int main() {
    std::cout << "Awryte, Warld!" << std::endl;
    JsonConv::getProgInstance()->readConfig();
    JsonConv::getProgInstance()->getTextDocuments();
    JsonConv::getProgInstance()->getRequests();
    return 0;
}
