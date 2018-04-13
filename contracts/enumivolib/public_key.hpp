#pragma once 
#include <enumivolib/varint.hpp>
#include <enumivolib/serialize.hpp>

namespace eosio {
   struct public_key {
      unsigned_int        type;
      std::array<char,33> data;

      ENULIB_SERIALIZE( public_key, (type)(data) )
   };
}
