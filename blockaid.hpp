/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#pragma once

#include <eosiolib/time.hpp>

namespace blockaid {

    using eosio::contract;

    class blockaid : public contract {

    public:
        explicit blockaid(account_name self);

        //@abi table userdata i64
        struct user_data {
            uint64_t          info_id;
            std::string       packed_data;
            time              update_time = now();

            auto     primary_key()const { return info_id; }
            EOSLIB_SERIALIZE( user_data, (info_id)(packed_data)(update_time) )
        };

        typedef eosio::multi_index< N(userdata), user_data >  user_data_table;

        //@abi table requests i64
        struct requests {
            uint64_t          req_id;
            uint64_t          info_id;
            std::string       status;
            time              update_time = now();

            auto     primary_key()const { return req_id; }
            EOSLIB_SERIALIZE( requests, (req_id)(info_id)(status)(update_time) )
        };

        typedef eosio::multi_index< N(requests), requests >  request_table;


        public:

            //@abi action
            void uploadinfo( account_name user, std::string packed_data, std::string memo);

            //@abi action
            void updateinfo( account_name user, uint64_t info_id, std::string packed_data, std::string memo);

            //@abi action
            void reqremove( account_name user, uint64_t reg_info_id, std::string memo);

            //@abi action
            void updatereq(account_name user, uint64_t req_id, std::string new_status, std::string memo);

    };

}

EOSIO_ABI( blockaid::blockaid, (uploadinfo)(updateinfo)(reqremove)(updatereq) )
