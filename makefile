# Makefile to build sackin-decrypt.exe for CS6903 Project 1
# Douglas Sackin
# CS 6903 - Summer 2014
# July 8, 2014

# Run 'make sackin-decrypt.exe' to build executable to ./bin
# Run 'make clean' to remove object and executable files

sackin-decrypt.exe: 
	@echo 'Building target: $@'
	mkdir obj bin
	@echo 'Compiling...'
	gcc -std=c++0x -I"/Users/doug/Documents/workspace/decrypt/contrib" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"obj/decrypt_main.d" -MT"obj/decrypt_main.d" -o "obj/decrypt_main.o" "src/decrypt_main.cpp"
	@echo 'Linking...'
	gcc  -o "bin/sackin-decrypt.exe"  ./obj/decrypt_main.o   -lstdc++
	@echo 'Compiled and linked $@'
	
clean:
	@echo 'Removing ./obj'
	rm -r ./obj
	@echo 'Removing ./bin'
	rm -r ./bin
