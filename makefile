all: teste_trie

teste_trie: trie.o main.o
		gcc -o teste_trie main.o trie.o linkedList.o

trie.o: trie.c
		gcc -o trie.o -c trie.c -W -Wall -ansi -pedantic

linkedList.o: linkedList.c
		gcc -o linkedList.o -c linkedList.c -W -Wall -ansi -pedantic

main.o: main.c trie.h linkedList.o
		gcc -o main.o -c main.c -W -Wall -ansi -pedantic
clean:
		rm -rf *.o
mrproper: clean
		rm -rf trie