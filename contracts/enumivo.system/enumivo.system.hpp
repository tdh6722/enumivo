/**
 *  @file
 *  @copyright defined in enumivo/LICENSE.txt
 */
#pragma once

#include "native.hpp"

#include <enumivolib/asset.hpp>
#include <enumivolib/contract.hpp>
#include <enumivolib/optional.hpp>
#include <enumivolib/privileged.hpp>
#include <enumivolib/singleton.hpp>

#include <string>

namespace enumivosystem {

   using enumivo::asset;
   using enumivo::indexed_by;
   using enumivo::const_mem_fun;

   struct block_header {
      checksum256                               previous;
      time                                      timestamp;
      checksum256                               transaction_mroot;
      checksum256                               action_mroot;
      checksum256                               block_mroot;
      account_name                              producer;
      uint32_t                                  schedule_version;
      enumivo::optional<enumivo::producer_schedule> new_producers;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      ENULIB_SERIALIZE(block_header, (previous)(timestamp)(transaction_mroot)(action_mroot)(block_mroot)
                                     (producer)(schedule_version)(new_producers))
   };

   struct enumivo_parameters : enumivo::blockchain_parameters {
      uint64_t          max_storage_size = 10 * 1024 * 1024;
      uint32_t          percent_of_max_inflation_rate = 0;
      uint32_t          storage_reserve_ratio = 1000;      // ratio * 1000

      // explicit serialization macro is not necessary, used here only to improve compilation time
      ENULIB_SERIALIZE_DERIVED( enumivo_parameters, enumivo::blockchain_parameters, (max_storage_size)(percent_of_max_inflation_rate)(storage_reserve_ratio) )
   };

   struct enumivo_global_state : enumivo_parameters {
      uint64_t             total_storage_bytes_reserved = 0;
      enumivo::asset         total_storage_stake;
      enumivo::asset         payment_per_block;
      enumivo::asset         payment_to_enu_bucket;
      time                 first_block_time_in_cycle = 0;
      uint32_t             blocks_per_cycle = 0;
      time                 last_bucket_fill_time = 0;
      enumivo::asset         enu_bucket;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      ENULIB_SERIALIZE_DERIVED( enumivo_global_state, enumivo_parameters, (total_storage_bytes_reserved)(total_storage_stake)
                                (payment_per_block)(payment_to_enu_bucket)(first_block_time_in_cycle)(blocks_per_cycle)
                                (last_bucket_fill_time)(enu_bucket) )
   };

   struct producer_info {
      account_name      owner;
      uint128_t         total_votes = 0;
      enumivo_parameters  prefs;
      enumivo::bytes      packed_key; /// a packed public key object
      enumivo::asset      per_block_payments;
      time              last_rewards_claim = 0;
      time              time_became_active = 0;
      time              last_produced_block_time = 0;

      uint64_t    primary_key()const { return owner;       }
      uint128_t   by_votes()const    { return total_votes; }
      bool active() const { return 0 < packed_key.size(); }

      // explicit serialization macro is not necessary, used here only to improve compilation time
      ENULIB_SERIALIZE( producer_info, (owner)(total_votes)(prefs)(packed_key)
                        (per_block_payments)(last_rewards_claim)
                        (time_became_active)(last_produced_block_time) )
   };

   typedef enumivo::multi_index< N(producerinfo), producer_info,
                               indexed_by<N(prototalvote), const_mem_fun<producer_info, uint128_t, &producer_info::by_votes>  >
                               >  producers_table;

   typedef enumivo::singleton<N(global), enumivo_global_state> global_state_singleton;

   static constexpr uint32_t     max_inflation_rate = 5;  // 5% annual inflation
   static constexpr uint32_t     seconds_per_day = 24 * 3600;
   static constexpr uint64_t     system_token_symbol = S(4,ENU);

   class system_contract : public native, private enumivo::contract {
      public:

         using enumivo::contract::contract;

         // Actions:

         // functions defined in delegate_bandwidth.cpp
         void delegatebw( const account_name from, const account_name receiver,
                          const asset stake_net_quantity, const asset stake_cpu_quantity,
                          const asset stake_storage_quantity );

         void undelegatebw( const account_name from, const account_name receiver,
                            const asset unstake_net_quantity, const asset unstake_cpu_quantity,
                            const uint64_t unstake_storage_bytes );

         void refund( const account_name owner );

         // functions defined in voting.cpp

         void regproducer( const account_name producer, const bytes& producer_key, const enumivo_parameters& prefs );

         void unregprod( const account_name producer );

         enumivo::asset payment_per_block(uint32_t percent_of_max_inflation_rate);

         void update_elected_producers(time cycle_time);

         void voteproducer( const account_name voter, const account_name proxy, const std::vector<account_name>& producers );

         void regproxy( const account_name proxy );

         void unregproxy( const account_name proxy );

         void nonce( const std::string& /*value*/ ) {}

         // functions defined in producer_pay.cpp

         void onblock( const block_header& header );

         void claimrewards( const account_name& owner );

      private:
         // Implementation details:

         //defined in voting.hpp
         static enumivo_global_state get_default_parameters();

         // defined in voting.cpp
         void increase_voting_power( account_name acnt, const enumivo::asset& amount );

         void decrease_voting_power( account_name acnt, const enumivo::asset& amount );

         // defined in producer_pay.cpp
         bool update_cycle( time block_time );

   };

} /// enumivosystem
