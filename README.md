# EVM State DB

[![readme style standard](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

Ethereum VM state database

Stand-alone C++20 executable used to run EVM state database.
Basically acts as a command wrapper around `evm-cpp-utils` state.

## Table of Contents

- [Install](#install)
- [Usage](#usage)
- [Dependencies](#dependencies)
- [Testing](#testing)
- [Maintainer](#maintainer)
- [License](#license)

## Install

```
make all
```

**NOTE:** [Dependencies](#dependencies) must be compiled & linked into compilation aswell.

## Usage

evm-state-db comes with various commandline functions, including :

**Get** - get a value at (contract address, key) pair in state
```
./bin/evm-state-db get --snapshotFile ./path/to/snapshot.json --contractAddress 4200000000000000000000000000000000000000 --key 42
```

**Set** - set a value at (contract address, key) pair in state ( and saves changes )
```
./bin/evm-state-db set --snapshotFile ./path/to/snapshot.json --contractAddress 4200000000000000000000000000000000000000 --key 42 --value 512
```

**Run** - runs an RPC server giving access to EVM state db ( for gets and sets )
( TODO: not yet implemented )
```
./bin/evm-state-db run --snapshotFile ./path/to/snapshot.json --rpcPort 8999
# Get request
curl -X POST -H "Content-Type: application/json" --data '--contractAddress 4200000000000000000000000000000000000000 --key 42' http://localhost:8999
# Set request
curl -X POST -H "Content-Type: application/json" --data '--contractAddress 4200000000000000000000000000000000000000 --key 42 --value 512' http://localhost:8999
```

**Note** : Use `-h` flag on each sub-command to see more options

## Dependencies

- [intx][intx] : 256-bit (32-byte) unsigned integers
- [ethash][ethash] : Ethereum hash functions
- [evm-cpp-utils][evm-cpp-utils] : EVM state types + utils

## Testing

This repo contains various tests under `./test/` to make sure things are working.
To run use :

```
make get-test
make set-test

# RPC test
make run-rpc-local
# In a seperate terminal
make get-rpc-test
make set-rpc-test
make get-rpc-test
# Ctrl-C to stop RPC & snapshot state
```

Check the diff in `./test/snapshot.json` to see if things processed properly.

## Maintainer

Brandon Roberts [@b-j-roberts]

## License

[MIT][MIT]


[intx]: https://github.com/chfast/intx
[ethash]: http://github.com/chfast/ethash
[evm-cpp-utils]: https://github.com/FraktalLabs/evm-cpp-utils
[MIT]: LICENSE
[@b-j-roberts]: https://github.com/b-j-roberts
