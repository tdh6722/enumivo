/**
 *  @file
 *  @copyright defined in enumivo/LICENSE.txt
 */

#include <enumivo/chain/genesis_state.hpp>

// these are required to serialize a genesis_state
#include <fc/smart_ref_impl.hpp>   // required for gcc in release mode

namespace enumivo { namespace chain {


chain::chain_id_type genesis_state::compute_chain_id() const {
   return config::chain_id;
}

} } // namespace enumivo::chain
