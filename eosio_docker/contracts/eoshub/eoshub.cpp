#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

using namespace eosio;

// inflation_rate
// how much do we inflate the base supply to pay for services?
// uint64_t inflation_rate = 1;


struct [[eosio::table]] service {
    uint64_t key;
    // who registered this service?
    name owner;

    std::string name;
    std::string description;
    std::string url;

    auto primary_key() { return key; }
};

struct [[eosio::table]] account {
    name owner;

    asset balance;

    asset staked;
    asset delegated;

    uint64_t lastCollectedBlock;
};


class [[eosio::contract]] eoshub : public eosio::contract {

  public:
    using contract::contract;

    [[eosio::action]] void regservice(name owner, std::string description, std::string url) {}
    [[eosio::action]] void stake() {}
    [[eosio::action]] void unstake() {}
    [[eosio::action]] void delegate() {}
    [[eosio::action]] void undelegate() {}
    [[eosio::action]] void collectreward(name user) { }

};

EOSIO_DISPATCH(eoshub, (regservice)(stake)(unstake)(delegate)(undelegate)(collectreward) )
