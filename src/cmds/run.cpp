#include "cmds.h"

#include <memory>
#include <iostream>

#include <intx/intx.hpp>

#include "../utils/utils.h"
#include "../state/state.h"
#include "rpc.h"

struct RunData {
  std::string snapshotFile;
  std::shared_ptr<State> state;
  
  std::string serverAddress;
  int serverPort;
};

std::unique_ptr<RunData> parseRunDBCmdlineArgs(int argc, char *argv[]) {
  // Cmdline Args
  std::string snapshotFile;
  std::string serverAddress;
  int serverPort = 0;

  const std::string helpText = "Usage: " + std::string(argv[0]) + " run [options]\n"
                               "  Run RPC server exposing state access\n\n"
                               "Options:\n"
                               "  --snapshotFile <file>     Snapshot file to use (required)\n"
                               "  --rpcAddress <address>    Address to bind server to (default: localhost)\n"
                               "  --rpcPort <port>          Port to bind server to (default: 8545)\n";

  if(argc < 3) {
    std::cerr << helpText << std::endl;
    exit(1);
  }

  // Parse cmdline args
  for(int i = 2; i < argc; i++) {
    std::string arg = argv[i];
    if(arg == "--snapshotFile") {
      if(i + 1 >= argc) {
        std::cerr << "Missing argument for --snapshotFile" << std::endl;
        exit(1);
      }
      snapshotFile = argv[++i];
    } else if(arg == "--rpcAddress") {
      if(i + 1 >= argc) {
        std::cerr << "Missing argument for --rpcAddress" << std::endl;
        exit(1);
      }
      serverAddress = argv[++i];
    } else if(arg == "--rpcPort") {
      if(i + 1 >= argc) {
        std::cerr << "Missing argument for --rpcPort" << std::endl;
        exit(1);
      }
      serverPort = std::stoi(argv[++i]);
    } else {
      std::cerr << "Unknown argument: " << arg << std::endl;
      exit(1);
    }
  }

  // Check required args
  if(snapshotFile.empty()) {
    std::cerr << "Missing required argument --snapshotFile" << std::endl;
    exit(1);
  }

  // Set defaults
  if(serverAddress.empty()) {
    serverAddress = "localhost";
  }

  if(serverPort == 0) {
    serverPort = 8545;
  }

  auto state = std::make_shared<State>(snapshotFile);

  return std::make_unique<RunData>(RunData{snapshotFile, state, serverAddress, serverPort});
}

void runServer(std::shared_ptr<State> state, std::string address, int port) {
  // Create RPC server
  RpcServer server = RpcServer(state);

  // Start server
  server.Start(address, port);
}

int runDBCmdline(int argc, char *argv[]) {
  auto data = parseRunDBCmdlineArgs(argc, argv);
  runServer(data->state, data->serverAddress, data->serverPort);
  
  // Snapshot the state
  data->state->snapshot(data->snapshotFile);

  // TODO: dump mutex data from state?
  return 0;
}
