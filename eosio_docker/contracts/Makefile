all:
	mkdir -p build/eoshub/
	eosio-cpp -o build/eoshub/eoshub.wasm eoshub/eoshub.cpp -abigen --contract eoshub


deploy:
	docker exec eosio_notechain_container /opt/eosio/bin/cleos -u http://localhost:8888 wallet import -n notechainwal --private-key 5KFyaxQW8L6uXFB6wSgC44EsAbzC7ideyhhQ68tiYfdKQp69xKo || true
	docker exec eosio_notechain_container /opt/eosio/bin/cleos -u http://localhost:8888 wallet import -n notechainwal --private-key 5K7mtrinTFrVTduSxizUc5hjXJEtTjVTsqSHeBHes1Viep86FP5 || true
	docker exec eosio_notechain_container /opt/eosio/bin/cleos -u http://localhost:8888 set account permission eoshub active '{"threshold": 1,"keys": [{"key": "EOS8Du668rSVDE3KkmhwKkmAyxdBd73B51FKE7SjkKe5YERBULMrw","weight": 1}],"accounts": [{"permission":{"actor":"eoshub","permission":"eosio.code"},"weight":1}]}' owner -p eoshub@owner || true
	docker exec eosio_notechain_container /opt/eosio/bin/cleos -u http://localhost:8888 set account permission eosio active '{"threshold": 1,"keys": [{"key": "EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV","weight": 1}],"accounts": [{"permission":{"actor":"eoshub","permission":"eosio.code"},"weight":1}]}' owner -p eosio@owner || true
	docker exec eosio_notechain_container /opt/eosio/bin/cleos -u http://localhost:8888 set contract eoshub /opt/eosio/bin/contracts/build/eoshub

test-deposit:
	echo "Depositing 5 EOSHUB into contract"
	docker exec eosio_notechain_container /opt/eosio/bin/cleos -u http://localhost:8888 transfer useraaaaaaaa eoshub "5 EOSHUB" "test"

	echo "Showing accounts"
	docker exec eosio_notechain_container /opt/eosio/bin/cleos -u http://localhost:8888 get currency balance eosio.token useraaaaaaaa EOSHUB
	docker exec eosio_notechain_container /opt/eosio/bin/cleos -u http://localhost:8888 get table eoshub eoshub accounts	
	docker exec eosio_notechain_container /opt/eosio/bin/cleos -u http://localhost:8888 push action eoshub withdraw '["useraaaaaaaa","5.0000 EOSHUB"]' -p useraaaaaaaa@owner

	echo "Showing accounts"
	docker exec eosio_notechain_container /opt/eosio/bin/cleos -u http://localhost:8888 get currency balance eosio.token useraaaaaaaa EOSHUB
	docker exec eosio_notechain_container /opt/eosio/bin/cleos -u http://localhost:8888 get table eoshub eoshub accounts

