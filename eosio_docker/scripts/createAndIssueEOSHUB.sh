#!/bin/bash
set -o errexit

echo "=== start createAndIssueEOSHUB ==="

# set PATH
PATH="$PATH:/opt/eosio/bin"

# change to script directory
cd "$(dirname "$0")"

# download jq for json reader, we use jq here for reading the json file ( accounts.json )
mkdir -p ~/bin && curl -sSL -o ~/bin/jq https://github.com/stedolan/jq/releases/download/jq-1.5/jq-linux64 && chmod +x ~/bin/jq && export PATH=$PATH:~/bin

# loop through the array in the json file, import keys and create accounts
# these pre-created accounts will be used for saving / erasing notes
# we hardcoded each account name, public and private key in the json.
# NEVER store the private key in any source code in your real life developmemnt
# This is just for demo purpose
# add the token account (amih)
####cleos create account eosio eosio.token EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
# sleep 1s
# cd ../contracts/eosio.contracts/eosio.token
# echo "--->>>=== compile TOKEN ==="
# eosio-cpp -I include -o eosio.token.wasm src/eosio.token.cpp --abigen
# sleep 5s

echo "--->>> === start ISSUE EOSHUB in blockchain ==="

cleos push action eosio.token create '[ "eosio", "1000000000.0000 EOSHUB"]' -p eosio.token@active
sleep 1s

jq -c '.[]' accounts.json | while read i; do
  name=$(jq -r '.name' <<< "$i")
  pub=$(jq -r '.publicKey' <<< "$i")

  # to simplify, we use the same key for owner and active key of each account
  #cleos create account eosio $name $pub $pub
  cleos push action eosio.token issue '[ "'$name'", "100.0000 EOSHUB", "airdrop eoshub token" ]' -p eosio@active
done
