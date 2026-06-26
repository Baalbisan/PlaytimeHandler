CC := gcc
SRC := ./main.c ./functional/functional_fetch.c ./functional/functional_ptconf.c ./functional/functional_vdf.c ./functional/rpcs3/functional_rpcs3.c ./lib/cJSON/cJSON.c ./lib/VDF/keyvalues.c

main: $(SRC)
	$(CC) $(SRC) -o ff_pt_handler

