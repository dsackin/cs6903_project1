#include <getopt.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "prettyprint/prettyprint.hpp"

#include "MultiShiftDecryptor.h"
#include "Dictionary.h"

std::string dictionaryPath;
std::string cipherPath;
int keyLength = -1;

void printUsage(std::ostream &os) {
	os << "Usage: decrypt [-d <dictionaryPath>] [-c <cipherPath>] [-t <keyLength>]" << std::endl;
	os << "Attempts to decrypt a cipher text and identify the originating plain text from " << std::endl;
	os << "a dictionary of plain texts. " << std::endl;
	os << std::endl;
	os << std::endl;
	os << "This program requires the dictionary, cipher text, and key length as inputs. " << std::endl;
	os << "You may specify any or none of these on the command line. If no dictionary " << std::endl;
	os << "path is provided, the default dictionary embedded in the program will be " << std::endl;
	os << "assumed. The rest will be collected from stdin." << std::endl;
	os << std::endl;
	os << "-d <dictionaryPath> - optional path to a text file containing one plain text " << std::endl;
	os << "   candidate per line" << std::endl;
	os << "-c <cipherPath> - optional path to a text file containing a single line of " << std::endl;
	os << "   cipher text for the decryption attempt. If not provided as an argument, " << std::endl;
	os << "   this will be requested via stdin" << std::endl;
	os << "-t <keyLength> - optional integer length of a key phrase believed to be used " << std::endl;
	os << "   in the encryption. If not provided as an argument, this will be requested " << std::endl;
	os << "   via stdin" << std::endl;
	os << std::endl;
}


void processArguments(int argc, char** argv) {
	char c;

	while ((c = getopt(argc, argv, "hd:t:c:")) != -1)
		switch (c) {
		case 'h':
			printUsage(std::cout);
			abort();
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

}


std::vector<std::string> readDictionary() {

	std::vector<std::string> dictionary;

	std::ifstream ifs(dictionaryPath.c_str(), std::ifstream::in);
    for (std::string line; std::getline(ifs, line); ) {
    	dictionary.push_back(line);
    }

    ifs.close();

    return dictionary;
}

std::string readCipher() {
	std::string cipherText;

	if (!cipherPath.empty()) {
		std::ifstream ifs(dictionaryPath.c_str(), std::ifstream::in);
	    std::getline(ifs, cipherText);
	    ifs.close();
	} else {
		std::cout << "Enter cipher text: ";
		std::cin >> cipherText;
	}

	return cipherText;
}

int readKeyLength() {
	if (keyLength < 0) {
		std::cout << "Enter key length (t): ";
		std::cin >> keyLength;
	}

	return keyLength;
}


int main(int argc, char **argv) {

	processArguments(argc, argv);

	std::vector<std::string> dictionary;
	if (!dictionaryPath.empty())
		dictionary = readDictionary();
	else
		dictionary = loadDefaultDictionary();

	std::string cipherText = readCipher();
	int keyLength = readKeyLength();

	int plainTextMatchIndex = -1;
	std::string explanation;
	for (unsigned int i = 0; i < dictionary.size(); i++) {
		Decryptor *decryptor = new MultiShiftDecryptor(i, dictionary[i], cipherText, keyLength);
		if (decryptor->decrypt()) {
			plainTextMatchIndex = decryptor->getDictionaryIndex();
			explanation = decryptor->getExplanation();
			delete decryptor;
			break;
		}
	}

	if (plainTextMatchIndex >= 0) {
		std::cout << explanation << std::endl;
	} else {
		std::cout << "No match found." << std::endl;
	}

}
