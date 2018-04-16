#include <enumivolib/enumivo.hpp>
#include <enumivolib/privileged.h>
#include <enumivolib/producer_schedule.hpp>

namespace enumivo {

   class testinline : public contract {
      public:
         testinline( action_name self ):contract(self){}

         void reqauth( account_name from ) {
            require_auth( from );
         }

         void forward( action_name reqauth, account_name forward_code, account_name forward_auth ) {
            require_auth( reqauth );
            dispatch_inline( permission_level{forward_auth,N(active)}, forward_code, N(reqauth), &testinline::reqauth, { forward_auth } );
         }
   };

} /// namespace enumivo
