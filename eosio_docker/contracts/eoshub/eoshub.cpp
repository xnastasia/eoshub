#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

using namespace eosio;

// inflation_rate
// how much do we inflate the base supply to pay for services?
// uint64_t inflation_rate = 1;
const symbol hub_symbol = symbol("HUB", 4);
const name hub_name = name("eoshub");

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
    asset stakedBalance;
    asset registeredBalance;

    uint64_t lastCollectedBlock;
};


class [[eosio::contract]] eoshub : public eosio::contract {

  public:
    using contract::contract;

    // regservice registers an eosaccount service listing (metadata about the service etc)
    [[eosio::action]] void regservice(name owner, std::string description, std::string url) {


    }

    // stake stakes a balance in eoshub allowing it to be used for api services
    [[eosio::action]] void stake() {

    }

    // unstake unstakes balances allowing them to be withdrawn from the contract
    [[eosio::action]] void unstake() {
        //todo: timeout 1 month
    }

    // regapikey stakes a certain amount of eoshub with the service tied to an EOS public key
    [[eosio::action]] void regapikey(std::string key, asset delegateAmount, name service) {

    }

    // unregapikey unstakes an amount of eoshub with the service
    [[eosio::action]] void unregapikey(name client, asset delegateAmount, name service) {
        
    }

    // collectreward collects earnings from shares since account.lastCollectedBlock
    [[eosio::action]] void collectreward(name user) { 

    }

    // withdraw withdraws an amount of eoshub (from the unstaked balance) to a given account
    [[eosio::action]] void withdraw(name user) { 

    }

    // depositinf notification _from_ the eoshub.token contract
    [[eosio::action]] void depositinf( name from, name to, asset quantity, std::string memo ) {

    }

};


// Custom Dispatcher to handle deposit notifications into the token contract
extern "C" {
    void apply(uint64_t receiver, uint64_t code, uint64_t action) {
        if(code==receiver)
        {
            switch(action)
            {
                EOSIO_DISPATCH_HELPER(eoshub, (regservice)(stake)(unstake)(regapikey)(unregapikey)(collectreward)(withdraw) )
            }
        }
        else if(code==hub_name.value && action==name("transfer").value) {
            execute_action( name(receiver), name(code), &eoshub::depositinf );
        }
    }
};


