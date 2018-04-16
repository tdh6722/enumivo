/**
 *  @file
 *  @copyright defined in enumivo/LICENSE.txt
 */

#include <enumivolib/currency.hpp>

extern "C" {
    /// The apply method implements the dispatch of events to this contract
    void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
       enumivo::currency(receiver).apply( code, action ); 
    }
}
