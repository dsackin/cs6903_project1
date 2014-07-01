/**
 * Decryptor.h
 *
 *  Created on: Jun 18, 2014
 *      Author: Douglas Sackin, NYU CS6903, Summer 2014
 */

#ifndef DECRYPTOR_H_
#define DECRYPTOR_H_

#include <vector>
#include <string>

/**
 * Decryptor is an abstract class defining a common interface for cipher
 * challenge decryption. A Decryptor requires a challenge cipher text, a
 * candidate plain text, and the index of that plain text from the input
 * dictionary. Different decryption strategies will extend this class.
 *
 * Construct a Decryptor through one of its subclasses, then call bool decrypt()
 * to attempt to decrypt the cipher text into the plain text using the strategy
 * of that Decryptor subclass. If the decryption was successful, this method
 * will return true. You can then get the index of the plain text candidate and
 * a brief explanation that may contain details specific to the encryption and
 * decryption strategy.
 */
class Decryptor {
public:

	/**
	 * Constructor to be called by subclasses to initialize the members of the
	 * parent Decryptor class
	 * @param index - integer dictionary index of the plain text candidate
	 * @param plainText - string plain text candidate
	 * @param cipherText - string cipher text
	 */
	Decryptor(int index, std::string plainText, std::string cipherText) {
		this->dictionaryIndex = index;
		this->plainText = plainText;
		this->cipherText = cipherText;
		this->isInitialized = false;
	}

	/**
	 * Default destructor.
	 */
	virtual ~Decryptor() { }

	/**
	 * Attempt to confirm the cipher text derived from the candidate plain text
	 * using the implemented strategy. This pure virtual method forces this
	 * class to be remain abstract and require implementing subclasses.
	 * @return bool - true if the cipher text was proven to be an encryption of
	 * the plain text
	 */
	virtual bool decrypt() = 0;

	/**
	 * Return the cipher text configured for this Decryptor
	 * @return std::string - cipher text
	 */
	const std::string& getCipherText() const {
		return cipherText;
	}

	/**
	 * Return the dictionary index configured for this Decryptor
	 * @return int - dictionary index
	 */
	int getDictionaryIndex() const {
		return dictionaryIndex;
	}

	/**
	 * Return the plain text configured for this Decryptor
	 * @return std::string - plain text
	 */
	const std::string& getPlainText() const {
		return plainText;
	}

	/**
	 * Provide an explanation of the strategy used by this decryptor to
	 * successfully decrypt the cipher text into the plain text. This pure
	 * virtual method forces this class to be remain abstract and require
	 * implementing subclasses.
	 * @return std::string - explanation message
	 */
	virtual const std::string getExplanation() const = 0;

protected:


	/**
	 * Perform setup work and mark this Decryptor as ready for the decryption
	 * attempt.
	 */
	void initialize() {
		isInitialized = true;
	}

	// plain text dictionary index for this Decryptor. Initialized to -1 which
	// is always invalide regardless of whether dictionary uses 0 or 1 indexing.
	int dictionaryIndex = -1;

	// set initialization flag to false
	bool isInitialized = false;

	// plain text candidate
	std::string plainText;

	// cipher text challenge
	std::string cipherText;
};

#endif /* DECRYPTOR_H_ */
