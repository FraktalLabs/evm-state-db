#pragma once

#include <string>
#include <memory>

#include "../state/state.h"

class RpcServer {
public:
    RpcServer(std::shared_ptr<State> state): state(state) {}

    void Start(const std::string& addr, int port);
    int Exec(const std::string& cmd);
private:
    std::shared_ptr<State> state;
};
