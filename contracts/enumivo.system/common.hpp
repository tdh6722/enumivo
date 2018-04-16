#pragma once
#include <enumivolib/enumivo.hpp>

#include <enumivolib/generic_currency.hpp>
#include <enumivolib/multi_index.hpp>
#include <enumivolib/privileged.hpp>
#include <enumivolib/singleton.hpp>

namespace enumivosystem {

   template<account_name SystemAccount>
   class common {
      public:
         static constexpr account_name system_account = SystemAccount;
         typedef enumivo::generic_currency< enumivo::token<system_account,S(4,EOS)> > currency;
         typedef typename currency::token_type                                    system_token_type;

         static constexpr uint64_t   currency_symbol = currency::symbol;            // S(4,EOS)
         static constexpr uint32_t   max_inflation_rate = 5;                        // 5% annual inflation

         static constexpr uint32_t   blocks_per_producer = 12;
         static constexpr uint32_t   seconds_per_day = 24 * 3600;
         static constexpr uint32_t   days_per_4years = 1461;

         struct enumivo_parameters : enumivo::blockchain_parameters {
            uint64_t          max_storage_size = 10 * 1024 * 1024;
            uint32_t          percent_of_max_inflation_rate = 0;
            uint32_t          storage_reserve_ratio = 1000;      // ratio * 1000

            ENULIB_SERIALIZE_DERIVED( enumivo_parameters, enumivo::blockchain_parameters, (percent_of_max_inflation_rate)(storage_reserve_ratio) )
         };

         struct enumivo_global_state : enumivo_parameters {
            uint64_t             total_storage_bytes_reserved = 0;
            system_token_type    total_storage_stake;
            system_token_type    payment_per_block = system_token_type();
            system_token_type    payment_to_eos_bucket = system_token_type();
            time                 first_block_time_in_cycle = 0;
            uint32_t             blocks_per_cycle = 0;
            time                 last_bucket_fill_time = 0;
            system_token_type    eos_bucket = system_token_type();

            ENULIB_SERIALIZE_DERIVED( enumivo_global_state, enumivo_parameters, (total_storage_bytes_reserved)(total_storage_stake)
                                      (payment_per_block)(payment_to_eos_bucket)(first_block_time_in_cycle)(blocks_per_cycle)
                                      (last_bucket_fill_time)(eos_bucket) )
         };

         typedef enumivo::singleton<SystemAccount, N(inflation), SystemAccount, enumivo_global_state> global_state_singleton;

         static enumivo_global_state& get_default_parameters() {
            static enumivo_global_state dp;
            get_blockchain_parameters(dp);
            return dp;
         }
   };

}
