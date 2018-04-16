/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <fc/exception/exception.hpp>
#include <enumivo/chain/exceptions.hpp>

#define ENU_DECLARE_INTERNAL_EXCEPTION( exc_name, seqnum, msg )  \
   FC_DECLARE_DERIVED_EXCEPTION(                                      \
      internal_ ## exc_name,                                          \
      enumivo::chain::internal_exception,                            \
      3990000 + seqnum,                                               \
      msg                                                             \
      )

namespace enumivo { namespace chain {

FC_DECLARE_DERIVED_EXCEPTION( internal_exception, enumivo::chain::chain_exception, 3990000, "internal exception" )

ENU_DECLARE_INTERNAL_EXCEPTION( verify_auth_max_auth_exceeded, 1, "Exceeds max authority fan-out" )
ENU_DECLARE_INTERNAL_EXCEPTION( verify_auth_account_not_found, 2, "Auth account not found" )

} } // enumivo::chain
