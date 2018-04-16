/**
 *  @file
 *  @copyright defined in enumivo/LICENSE.txt
 */

#include <enumivo/chain/get_config.hpp>
#include <enumivo/chain/config.hpp>
#include <enumivo/chain/types.hpp>

namespace enumivo { namespace chain {

fc::variant_object get_config()
{
   fc::mutable_variant_object result;

//   result["block_interval_ms"] = config::block_interval_ms;
//   result["producer_count"] = config::producer_count;
   /// TODO: add extra config parms
   return result;
}

} } // enumivo::chain
