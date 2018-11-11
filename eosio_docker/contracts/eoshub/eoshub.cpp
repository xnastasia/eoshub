#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

using namespace eosio;


const symbol hub_symbol = symbol("EOSHUB", 4);
const name hub_name = name("eoshub");



class [[eosio::contract]] eoshub : public eosio::contract {
    private:            
    struct [[eosio::table("services")]] service {
        name owner;

        std::string name;
        std::string description;
        std::string url;

        auto primary_key() const { return owner.value; }
    };

    typedef eosio::multi_index<name("services"), service> services_index;

    struct [[eosio::table("accounts")]] account {
        name owner;

        asset balance;
        asset staked_balance;

        uint64_t last_collection_time;

        auto primary_key() const { return owner.value; }
    };

    typedef eosio::multi_index<name("accounts"), account> accounts_index;


    public:
    using contract::contract;

    // regservice registers an eosaccount service listing (metadata about the service etc)
    [[eosio::action]] void regservice(name owner, std::string description, std::string url) {
        require_auth(owner);

        services_index services(_self, _self.value);
        services.emplace(owner, [&]( auto& svc ) {
            svc.owner = owner;
            svc.description = description;
            svc.url = url;
        });
    }

    // stake stakes a balance in eoshub allowing it to be used for api services
    [[eosio::action]] void stake(name owner, asset stakeAmount) {
        require_auth(owner);

        accounts_index accounts(_self,  _self.value);
        auto itr = accounts.find(owner.value);

        eosio_assert(itr != accounts.end(), "account not found");
        eosio_assert(stakeAmount.symbol == itr->balance.symbol, "incorrect symbol");
        eosio_assert(stakeAmount.amount <= itr->balance.amount, "insufficient funds");

        accounts.modify(itr, _self, [&](auto &a) {
            a.balance -= stakeAmount;
            a.staked_balance += stakeAmount;
        });
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
    // cleos set account permission eoshub active '{"threshold": 1,"keys": [{"key": "ACTIVE PUBKEY","weight": 1}],"accounts": [{"permission":{"actor":"eoshub","permission":"eosio.code"},"weight":1}]}' owner -p eoshub@owner
    [[eosio::action]] void withdraw(name to, asset withdrawlAmount) { 
        require_auth(to);
        accounts_index accounts(_self,  _self.value);

        auto itr = accounts.find(to.value);
        eosio_assert(itr != accounts.end(), "account not found");

        // sanity checks on the withdrawl
        eosio_assert(withdrawlAmount.symbol == hub_symbol, "withdrawlAmount has incorrect symbol");
        eosio_assert(withdrawlAmount.is_valid(), "withdrawlAmount is not valid");
        eosio_assert(withdrawlAmount.amount > 0, "withdrawlAmount must be positive");

        // finally check that we have the funds available to withdraw
        eosio_assert(withdrawlAmount.amount <= itr->balance.amount, "insufficient unstaked funds");                

        // use inline action to send withdrawlAmount via the eosio.token contract
        action{
            permission_level{_self, name("active")},
            name("eosio.token"),
            name("transfer"),
            std::tuple<name, name, asset, std::string>{name("eoshub"), to, withdrawlAmount, "withdrawl from eoshub"}
        }.send();

        // modified the stored balance on our ledger
        accounts.modify(itr, to, [&](auto &a) {
            a.balance -= withdrawlAmount;
        });

    }

    // deposithub notification _from_ the eoshub.token contract
    [[eosio::action]] void deposithub( name from, name to, asset quantity, std::string memo ) {
        if(from == _self || to != _self)
            return;

        eosio_assert(quantity.symbol == hub_symbol, "incorrect symbol");
        eosio_assert(quantity.is_valid(), "quantity is not valid");
        eosio_assert(quantity.amount > 0, "amount must be positive");

        accounts_index accounts(_self, _self.value);
        auto itr = accounts.find(from.value);

        // We don't currently have an account for this user, lets start one
        if (itr == accounts.end()) {
            accounts.emplace(_self, [&](auto &a) {
                a.owner = from;
                a.balance = quantity;
                a.staked_balance = asset(0, hub_symbol);
                a.last_collection_time = now();
            });
            return;
        }

        // This account does exist, lets add its balance to our records
        eosio_assert(itr != accounts.end(), "account doesn't exist");
        accounts.modify(itr, _self, [&](auto &a){
            a.balance += quantity;
        });
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
        else if(code==name("eosio.token").value && action==name("transfer").value) {
            execute_action( name(receiver), name(code), &eoshub::deposithub );
        }
    }
};


