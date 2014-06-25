/**
 *  decrypt_main.h
 *
 *  This is the main program source for a simple, single-threaded substitution
 *  cipher decryptor. It attempts to decrypt a cipher text and identify the
 *  originating plain text from a dictionary of plain texts.
 *
 *  This program requires the dictionary, cipher text, and key length as inputs.
 *  You may specify any or none of these on the command line. If no dictionary
 *  path is provided, the default dictionary embedded in the program will be
 *  assumed. The rest will be collected from stdin.
 *
 *  -d <dictionaryPath> - optional path to a text file containing one plain text
 *     candidate per line
 *  -c <cipherPath> - optional path to a text file containing a single line of
 *     cipher text for the decryption attempt. If not provided as an argument,
 *     this will be requested via stdin
 *  -t <keyLength> - optional integer length of a key phrase believed to be
 *     used in the encryption. If not provided as an argument, this will be
 *     requested via stdin
 *
 *  Created on: Jun 18, 2014
 *      Author: Douglas Sackin, NYU CS6903, Summer 2014
 */

#include <getopt.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "prettyprint/prettyprint.hpp"

#include "MultiShiftDecryptor.h"
#include "Dictionary.h"

// Global variables to store the program inputs from wherever they are collected
std::string dictionaryPath;				// path to dictionary file, if given
std::string cipherPath;					// path to cipher file, if given
int keyLength = -1;						// initial key length, invalid by default


/**
 * Print a simple message describing the usage of this program
 * @param os - Reference to an output stream to which to write the usage message
 */
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
	os << "-h - print this help message" << std::endl;
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

/**
 * Process arguments passed to the command line of the program. These are passed
 * through directly from main(int argc, char** argv). Parse the options (short
 * options only) using the getopt.h library. Save argument values to global vars
 *
 * @param argc - count of arguments
 * @param argv - array of c-style strings
 */
void processArguments(int argc, char** argv) {
	char c;

	while ((c = getopt(argc, argv, "hd:c:t:")) != -1)
		switch (c) {
		case 'h':									// print help
			printUsage(std::cout);
			abort();
		case 'd':									// capture dictionary path
			dictionaryPath = std::string(optarg);
			break;
		case 'c':									// capture cipher file path
			cipherPath = std::string(optarg);
			break;
		case 't':									// capture key length
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

	// If no argument flags were specified, see if just a string (that may be a
	// path to a dictionary file) was specified. Validate it later.
	if (dictionaryPath.empty() && optind < argc)
		dictionaryPath = std::string(argv[optind]);

}

/**
 * Attempt to read in a dictionary file (one plaintext message per line).
 *
 * @return std::vector<std::string> - vector of strings. If the path could not
 * be read as a file or the file contained no content, return an empty vector.
 */
std::vector<std::string> readDictionary() {

	std::vector<std::string> dictionary;

	// try to read from the value saved as the dictionary path (if one exists)
	if (!dictionaryPath.empty()) {

		std::ifstream ifs(dictionaryPath.c_str(), std::ifstream::in);
		for (std::string line; std::getline(ifs, line); ) {
			dictionary.push_back(line);
		}

		ifs.close();
	}

	// if we tried and failed or never tried to read the dictionary, rever to
	// the default dictionary included with this program.
	if (dictionary.empty())
		dictionary = loadDefaultDictionary();

    return dictionary;
}

/**
 * Collect the cipher text to be decrypted. Attempt to read from a text file at
 * cipherPath if one was specified. Otherwise, request the cipher text from the
 * user via stdin.
 *
 * @return std::string - enciphered message text to decrypt
 */
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

/**
 * Collect the key length was not already specified on the command line, request
 * it from the user via stdin.
 *
 * @return int - key length
 */
int readKeyLength() {
	if (keyLength < 0) {
		std::cout << "Enter key length (t): ";
		std::cin >> keyLength;
	}

	return keyLength;
}

/**
 * Main program to execute the decrypt functionality using a provided cipher
 * text and plain text dictionary.
 *
 * @param argc - count of arguments
 * @param argv - array of c-style strings
 * @return
 */
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
