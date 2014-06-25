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
 *
 */
class Decryptor {
public:
	/**
	 *
	 * @param index
	 * @param plainText
	 * @param cipherText
	 */
	Decryptor(int index, std::string plainText, std::string cipherText) {
		this->dictionaryIndex = index;
		this->plainText = plainText;
		this->cipherText = cipherText;
		this->isInitialized = false;
	}

	/**
	 *
	 */
	Decryptor() { }

	/**
	 *
	 */
	virtual ~Decryptor() {}

	virtual bool decrypt() = 0;

	/**
	 *
	 * @return
	 */
	const std::string& getCipherText() const {
		return cipherText;
	}

	/**
	 *
	 * @param cipherText
	 */
	void setCipherText(const std::string& cipherText)  {
		this->cipherText = cipherText;
	}

	/**
	 *
	 * @return
	 */
	int getDictionaryIndex() const {
		return dictionaryIndex;
	}

	/**
	 *
	 * @param dictionaryIndex
	 */
	void setDictionaryIndex(int dictionaryIndex) {
		this->dictionaryIndex = dictionaryIndex;
	}

	/**
	 *
	 * @return
	 */
	const std::string& getPlainText() const {
		return plainText;
	}

	/**
	 *
	 * @param plainText
	 */
	void setPlainText(const std::string& plainText) {
		this->plainText = plainText;
	}

	/**
	 *
	 * @return
	 */
	virtual const std::string getExplanation() const = 0;

protected:


	/**
	 *
	 */
	void initialize() {
		isInitialized = true;
	}

	int dictionaryIndex = -1;
	bool isInitialized = false;
	std::string plainText;
	std::string cipherText;
};

#endif /* DECRYPTOR_H_ */
