#include "cmds.h"

#include <memory>
#include <iostream>

#include <intx/intx.hpp>

#include "../utils/utils.h"
#include "../state/state.h"

struct SetValueData {
  std::string snapshotFile;
  std::shared_ptr<State> state;

  address contractAddress;
  intx::uint256 key;
  intx::uint256 value;
  // TODO: Value nonce?
};

std::unique_ptr<SetValueData> parseSetCmdlineArgs(int argc, char *argv[]) {
  // Cmdline Args
  std::string snapshotFile;
  std::string contractAddressStr;
  std::string key;
  std::string value;

  const std::string helpText = "Usage: " + std::string(argv[0]) + " set [options]\n"
                               "  Set a value tp the EVM database at a given key\n\n"
                               "Options:\n"
                               "  --snapshotFile <file>        Snapshot file to use (required)\n"
                               "  --contractAddress <address>  Contract address (required)\n"
                               "  --key <key>                  Key to set value for (required)\n"
                               "  --value <value>              Value to set (required)\n";

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
    } else if(arg == "--contractAddress") {
      if(i + 1 >= argc) {
        std::cerr << "Missing argument for --contractAddress" << std::endl;
        exit(1);
      }
      contractAddressStr = argv[++i];
    } else if(arg == "--key") {
      if(i + 1 >= argc) {
        std::cerr << "Missing argument for --key" << std::endl;
        exit(1);
      }
      key = argv[++i];
    } else if(arg == "--value") {
      if(i + 1 >= argc) {
        std::cerr << "Missing argument for --value" << std::endl;
        exit(1);
      }
      value = argv[++i];
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

  if(contractAddressStr.empty()) {
    std::cerr << "Missing required argument --contractAddress" << std::endl;
    exit(1);
  }

  if(key.empty()) {
    std::cerr << "Missing required argument --key" << std::endl;
    exit(1);
  }

  if(value.empty()) {
    std::cerr << "Missing required argument --value" << std::endl;
    exit(1);
  }

  auto state = std::make_shared<State>(snapshotFile);

  bytes contractAddressBytes = parseBytes(contractAddressStr);
  address contractAddress;
  for(int i = 0; i < 20; i++) {
    contractAddress[i] = contractAddressBytes[i];
  }

  intx::uint256 keyValue = intx::from_string<intx::uint256>(key);
  intx::uint256 valueValue = intx::from_string<intx::uint256>(value);

  return std::make_unique<SetValueData>(SetValueData{snapshotFile, state, contractAddress, keyValue, valueValue});
}

void setDBValue(const SetValueData& data) {
  data.state->setDBValue(data.contractAddress, data.key, data.value);

  std::cout << "Set Value: " << intx::to_string(data.value) << std::endl;
}

int setDBValueCmdline(int argc, char *argv[]) {
  auto data = parseSetCmdlineArgs(argc, argv);
  setDBValue(*data);
  
  // Snapshot the state
  data->state->snapshot(data->snapshotFile);

  // TODO: dump mutex data from state?
  return 0;
}
