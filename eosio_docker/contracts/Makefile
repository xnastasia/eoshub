all:
	mkdir -p build/eoshub/
	eosio-cpp -o build/eoshub/eoshub.wasm eoshub/eoshub.cpp -abigen --contract eoshub


deploy:
	# docker exec eosio_notechain_container /opt/eosio/bin/cleos -u http://localhost:8888 wallet import -n notechainwal --private-key 5KFyaxQW8L6uXFB6wSgC44EsAbzC7ideyhhQ68tiYfdKQp69xKo
	docker exec eosio_notechain_container /opt/eosio/bin/cleos -u http://localhost:8888 set contract eoshub /opt/eosio/bin/contracts/build/eoshub
