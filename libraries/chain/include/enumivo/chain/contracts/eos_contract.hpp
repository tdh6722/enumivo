/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <enumivo/chain/apply_context.hpp>

#include <enumivo/chain/types.hpp>

namespace enumivo { namespace chain { namespace contracts {

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_enumivo_newaccount(apply_context&);
   void apply_enumivo_updateauth(apply_context&);
   void apply_enumivo_deleteauth(apply_context&);
   void apply_enumivo_linkauth(apply_context&);
   void apply_enumivo_unlinkauth(apply_context&);

   void apply_enumivo_postrecovery(apply_context&);
   void apply_enumivo_passrecovery(apply_context&);
   void apply_enumivo_vetorecovery(apply_context&);

   void apply_enumivo_setcode(apply_context&);
   void apply_enumivo_setabi(apply_context&);

   void apply_enumivo_onerror(apply_context&);

   void apply_enumivo_canceldelay(apply_context&);
   ///@}  end action handlers

} } } /// namespace enumivo::contracts
