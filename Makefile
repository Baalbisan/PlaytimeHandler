CC := clang
SRC := ./main.c ./functional/functional_fetch.c ./functional/functional_ptconf.c ./functional/functional_vdf.c ./lib/cJSON/cJSON.c ./lib/VDF/keyvalues.c

main: $(SRC)
	$(CC) $(SRC) -o ff_pt_handler

