/**
 *  @file
 *  @copyright defined in enumivo/LICENSE.txt
 */
#pragma once

#include <enumivolib/enumivo.hpp>
#include <enumivolib/multi_index.hpp>
#include <enumivolib/privileged.hpp>
#include <enumivolib/singleton.hpp>
#include <enumivolib/asset.hpp>

#include <enumivo.coin/enumivo.coin.hpp>

namespace enumivosystem {

   template<account_name SystemAccount>
   class common {
      public:
         static constexpr account_name system_account = SystemAccount;


         static constexpr uint32_t     blocks_per_producer = 12;
         static constexpr uint32_t     seconds_per_day = 24 * 3600;
         static constexpr uint32_t     days_per_4years = 1461;

         static enumivo_global_state& get_default_parameters() {
            static enumivo_global_state dp;
            get_blockchain_parameters(dp);
            return dp;
         }
   };

}
