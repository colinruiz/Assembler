assembler: assembler.c ctranslate.c atranslate.c map.c
	gcc -o assembler assembler.c ctranslate.c atranslate.c map.c
