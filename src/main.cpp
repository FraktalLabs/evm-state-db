#include <iostream>

#include "cmds/cmds.h"

int main(int argc, char*argv[])
{
    const std::string helpMessage = "Usage: " + std::string(argv[0]) + " <subcommand> [options]\n"
                                    "Subcommands:\n"
                                    "  run       : Run the EVM state-db service\n"
                                    "  set       : Set a key-value pair in evm state\n"
                                    "  get       : Get a value from evm state\n"
                                    "  help      : Print this help message\n";
    if (argc < 2) {
      std::cout << helpMessage << std::endl;
      return 0;
    }

    std::string subcommand = argv[1];
    if (subcommand == "run") {
      std::cout << "Running EVM state-db service" << std::endl;
      return runDBCmdline(argc, argv);
      // TODO: Run the service
    } else if (subcommand == "set") {
      std::cout << "Setting a key-value pair in evm state" << std::endl;
      return setDBValueCmdline(argc, argv);
    } else if (subcommand == "get") {
      std::cout << "Getting a value from evm state" << std::endl;
      return getDBValueCmdline(argc, argv);
    } else if (subcommand == "help") {
      std::cout << helpMessage << std::endl;
    } else {
      std::cout << "Unknown subcommand: " << subcommand << std::endl << std::endl;
      std::cout << helpMessage << std::endl;
      return 1;
    }

    return 0;
}
