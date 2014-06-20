#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Message.h"

#define MAX_MESSAGE_LENGTH 300

std::string dictionaryPath;
std::string cipherPath;
int keyLength = -1;

//std::string defaultAlphabet = std::string("abcdefghijklmnopqrstuvwxyz");

bool processArguments(int argc, char** argv) {
	char c;

	while ((c = getopt(argc, argv, "d:t:c:")) != -1)
		switch (c) {
		case 'd':
			dictionaryPath = std::string(optarg);
			break;
		case 'c':
			cipherPath = std::string(optarg);
			break;
		case 't':
			keyLength = (int)strtol(optarg, NULL, 0);
			break;
		case '?':
			if (isprint(optopt))
				fprintf(stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
			break;
		default:
			abort();
		}

	if (dictionaryPath.empty() && optind < argc)
		dictionaryPath = std::string(argv[optind]);

	if (!dictionaryPath.empty())
		return true;
	else
		return false;
}

void printUsage(std::ostream &os) {
	os << "Usage: decrypt -d <dictionaryPath> [-c <cipherPath>] [-t <keyLength>]" << std::endl;
	os << "or:    decrypt <dictionaryPath>" << std::endl;
	os << std::endl << "Attempts to decrypt a cipher text and identify the " <<
			"originating plain text from a dictionary of plain texts. You may " <<
			"specify the first form and provide all program inputs on the " <<
			"command line or use the second form and provide the key length " <<
			"and cipher text through stdin" << std::endl;
	os << std::endl << "-d <dictionaryPath> - optional path to a text file containing " <<
			"one plain text candidate per line" << std::endl;
	os << "-c <cipherPath> - optional path to a text file containing a single " <<
			"line of cipher text for the decryption attempt. If not provided " <<
			"as an argument, this will be requested via stdin" << std::endl;
	os << "-t <keyLength> - optional integer length of a key phrase believed " <<
			"to be used in the encryption. If not provided as an argument, " <<
			"this will be requested via stdin" << std::endl;
}

std::vector<Message> readDictionary() {

	std::vector<Message> dictionary;

	std::ifstream ifs(dictionaryPath.c_str(), std::ifstream::in);
    for (std::string line; std::getline(ifs, line); ) {
    	dictionary.push_back(Message(line));
    }

    ifs.close();

    return dictionary;
}

Message readCipher() {
	std::string cipherText;

	if (!cipherPath.empty()) {
		std::ifstream ifs(dictionaryPath.c_str(), std::ifstream::in);
	    std::getline(ifs, cipherText);
	    ifs.close();
	} else {
		std::cout << "Enter cipher text: ";
		std::cin >> cipherText;
	}

	return Message(cipherText);
}

int readKeyLength() {
	if (keyLength < 0) {
		std::cout << "Enter key length (t): ";
		std::cin >> keyLength;
	}

	return keyLength;
}


int main(int argc, char **argv) {

	if (!processArguments(argc, argv)) {
		printUsage(std::cout);
	}

	std::cout << dictionaryPath << std::endl << keyLength << std::endl << cipherPath << std::endl;

	std::vector<Message> dictionary = readDictionary();
	Message cipherText = readCipher();
	int keyLength = readKeyLength();


}
