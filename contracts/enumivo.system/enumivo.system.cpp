/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <enumivo.system/enumivo.system.hpp> 

using namespace enumivosystem;

extern "C" {

    /// The apply method implements the dispatch of events to this contract
    void apply( uint64_t receiver, uint64_t code, uint64_t act ) {
       //print( enumivo::name(code), "::", enumivo::name(act) );
       enumivosystem::contract<N(enumivo)>::apply( receiver, code, act );
    }
}
