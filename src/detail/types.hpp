#pragma once

#include <string>
#include "ethrpc/abi/Arguments.hpp"


namespace BitProfile{


typedef std::string txid_t;
typedef std::string address_t;
typedef Ethereum::ABI::Arguments arguments_t;

using Ethereum::Connector::Provider;
using Ethereum::Connector::ContractResult;
using Ethereum::Connector::ContractArguments;
using Ethereum::Connector::TransactionObserver;

using Ethereum::ABI::int256_t;
using Ethereum::ABI::uint256_t;
using Ethereum::ABI::decimal_t;


}
