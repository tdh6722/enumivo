#include "enumivo.system.hpp"
#include <enumivolib/dispatcher.hpp>

#include "delegate_bandwidth.cpp"
#include "producer_pay.cpp"
#include "voting.cpp"

ENUMIVO_ABI( enumivosystem::system_contract,
           // delegate_bandwith.cpp
           (delegatebw)(undelegatebw)(refund)
           (regproxy)
           // voting.cpp
           (unregproxy)(regproducer)(unregprod)(voteproducer)(onblock)
           // producer_pay.cpp
           (claimrewards)
           // native.hpp
           //XXX
           (newaccount)(updateauth)(deleteauth)(linkauth)(unlinkauth)(postrecovery)(passrecovery)(vetorecovery)(onerror)(canceldelay)
           // defined in enumivo.system.hpp
           (nonce)
)
