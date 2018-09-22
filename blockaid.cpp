#include "blockaid.hpp"

namespace blockaid {
    void blockaid::uploadinfo( account_name user, std::string packed_data, std::string memo) {
        require_auth(user);

        user_data_table _userdata(_self, user);

        auto info_id = _userdata.available_primary_key();

        _userdata.emplace(user, [&](auto &the_info) {
            the_info.info_id = info_id;
            the_info.packed_data = packed_data;
        });
    }

    void blockaid::updateinfo( account_name user, uint64_t info_id, std::string packed_data, std::string memo) {
        require_auth(user);

        user_data_table _userdata(_self, user);

        auto itr = _userdata.find(info_id);
        _userdata.modify(itr, 0, [&](auto &the_info) {
            the_info.packed_data = packed_data;
            the_info.update_time = now();
        });

    }

    void blockaid::reqremove( account_name user, uint64_t reg_info_id, std::string memo) {
        require_auth(user);

        request_table _requests(_self, user);

        auto req_id = _requests.available_primary_key();
        _requests.emplace(user, [&](auto &the_req) {
            the_req.req_id = req_id;
            the_req.info_id = reg_info_id;
            the_req.status = "pending";
        });
    }

    void blockaid::updatereq(account_name user, uint64_t req_id, std::string new_status, std::string memo) {
        require_auth(_self);

        request_table _requests(_self, user);

        auto itr = _requests.find(req_id);
        _requests.modify(itr, _self, [&](auto &the_req) {
            the_req.status = new_status;
            the_req.update_time = now();
        });
    }

    blockaid::blockaid(account_name self) : contract(self){

    }
}

