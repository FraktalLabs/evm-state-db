#include "rpc.h"

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "cmds.h"

void RpcServer::Start(const std::string& addr, int port) {
  // Create socket and bind to addr:port
  int fd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr_in;
  addr_in.sin_family = AF_INET;
  addr_in.sin_port = htons(port);
  addr_in.sin_addr.s_addr = inet_addr(addr.c_str());

  bind(fd, (struct sockaddr*)&addr_in, sizeof(addr_in));

  // Listen
  listen(fd, 10);

  // Accept
  while (true) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd = accept(fd, (struct sockaddr*)&client_addr, &client_addr_len);

    // Read
    char buf[1024];
    int len = read(client_fd, buf, sizeof(buf));

    // Parse
    std::string cmd(buf, len);
    int result = Exec(cmd);

    // Write
    std::string result_str = std::to_string(result);
    write(client_fd, result_str.c_str(), result_str.size());

    // Close
    close(client_fd);
  }

}

int RpcServer::Exec(const std::string& cmd) {
  int argc = 0;
  char* argv[1024];
  char* p = (char*)cmd.c_str();
  // set argv[0] to rpc
  // TODO: Fix this
  argv[argc++] = "rpc";
  while (*p != '\0') {
    if (*p == ' ') {
      *p = '\0';
      ++p;
      continue;
    }
    argv[argc++] = p;
    while (*p != '\0' && *p != ' ') {
      ++p;
    }
  }
  argv[argc] = NULL;

  std::cout << "argc: " << argc << "  argv: ";
  for (int i = 0; i < argc; ++i) {
    std::cout << argv[i] << " ";
  }

  return 0;

  //std::string subcommand = argv[1];
  //int result = 0;
  //if(subcommand == "get") {
  //  return getDB
  //} else if(subcommand == "set") {
  //  return setDBValueCmdline(argc, argv);
  //} else {
  //  return 1;
  //}
}
