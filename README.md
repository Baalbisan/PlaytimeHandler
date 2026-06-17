# Playtime Handler
A simple program written in C to display steam game playtime in fastfetch.  
  
Please check the wiki page for usage instructions.

# libraries used:
- [DaveGamble/cJSON](https://github.com/DaveGamble/cJSON)
- [DreamyCecil/VDF](https://github.com/DreamyCecil/VDF)

# To Compile (Temporary Solution for now.):
```
gcc main.c functional/functional_fetch.c functional/functional_vdf.c functional/functional_ptconf.c lib/cJSON/cJSON.c lib/VDF/keyvalues.c -o ./main
```
