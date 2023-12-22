#pragma once

#include "account.h"

// TODO: Same code from proc-evm

class State {
public:
  State() {}
  State(const std::string& snapshot) {
    restore(snapshot);
  }

  void snapshot(const std::string& filepath);
  void restore(const std::string& filepath);

  void insert(const address& addr, const Account& account) {
    state[addr] = account;
  }

  void insert(const std::string& addr, const Account& account) {
    uint8_t keyBytes[20];
    for (int i = 0; i < 20; i++) {
      std::string byteStr = addr.substr(i * 2, 2);
      keyBytes[i] = static_cast<uint8_t>(std::stoi(byteStr, nullptr, 16));
    }
    std::array<uint8_t, 20> keyArray;
    std::copy(keyBytes, keyBytes + 20, keyArray.begin());
    insert(keyArray, account);
  }

  Account* getAccount(const address& addr) {
    auto it = state.find(addr);
    if (it == state.end()) {
      return nullptr;
    }
    return &it->second;
  }
  Account* getAccount(const std::string& addr) {
    uint8_t keyBytes[20];
    for (int i = 0; i < 20; i++) {
      std::string byteStr = addr.substr(i * 2, 2);
      keyBytes[i] = static_cast<uint8_t>(std::stoi(byteStr, nullptr, 16));
    }
    std::array<uint8_t, 20> keyArray;
    std::copy(keyBytes, keyBytes + 20, keyArray.begin());
    return getAccount(keyArray);
  }
  void removeAccount(const address& addr) {
    state.erase(addr);
  }
  void removeAccount(const std::string& addr) {
    uint8_t keyBytes[20];
    for (int i = 0; i < 20; i++) {
      std::string byteStr = addr.substr(i * 2, 2);
      keyBytes[i] = static_cast<uint8_t>(std::stoi(byteStr, nullptr, 16));
    }
    std::array<uint8_t, 20> keyArray;
    std::copy(keyBytes, keyBytes + 20, keyArray.begin());
    removeAccount(keyArray);
  }

  intx::uint256 getDBValue(const address& addr, const intx::uint256& key) {
    auto it = state.find(addr);
    if (it == state.end()) {
      return 0;
    }
    return it->second.getStorageValue(key);
  }

  void setDBValue(const address& addr, const intx::uint256& key, const intx::uint256& value) {
    auto it = state.find(addr);
    // TODO: Create account if not found?
    if (it != state.end()) {
      it->second.setStorageValue(key, value);
    }
  }

private:
  std::map<address, Account> state;
};