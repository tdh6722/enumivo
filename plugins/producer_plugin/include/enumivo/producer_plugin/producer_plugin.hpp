/**
 *  @file
 *  @copyright defined in enumivo/LICENSE.txt
 */

#pragma once

#include <enumivo/chain_plugin/chain_plugin.hpp>
#include <enumivo/http_client_plugin/http_client_plugin.hpp>

#include <appbase/application.hpp>

namespace enumivo {

using boost::signals2::signal;

class producer_plugin : public appbase::plugin<producer_plugin> {
public:
   APPBASE_PLUGIN_REQUIRES((chain_plugin)(http_client_plugin))

   struct runtime_options {
      fc::optional<int32_t> max_transaction_time;
      fc::optional<int32_t> max_irreversible_block_age;
   };

   producer_plugin();
   virtual ~producer_plugin();

   virtual void set_program_options(
      boost::program_options::options_description &command_line_options,
      boost::program_options::options_description &config_file_options
      ) override;

   bool                   is_producer_key(const chain::public_key_type& key) const;
   chain::signature_type  sign_compact(const chain::public_key_type& key, const fc::sha256& digest) const;

   virtual void plugin_initialize(const boost::program_options::variables_map& options);
   virtual void plugin_startup();
   virtual void plugin_shutdown();

   void pause();
   void resume();
   bool paused() const;
   void update_runtime_options(const runtime_options& options);
   runtime_options get_runtime_options() const;

   signal<void(const chain::producer_confirmation&)> confirmed_block;
private:
   std::shared_ptr<class producer_plugin_impl> my;
};

} //enumivo

FC_REFLECT(enumivo::producer_plugin::runtime_options, (max_transaction_time)(max_irreversible_block_age));
