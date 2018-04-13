/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <enumivolib/enumivo.hpp>

namespace asserter {
   struct PACKED(assertdef) {
      int8_t   condition;
      int8_t   message_length;
      char     message[];
   };
}
