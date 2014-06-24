/*
 * Decryptor.h
 *
 *  Created on: Jun 18, 2014
 *      Author: doug
 */

#ifndef DECRYPTOR_H_
#define DECRYPTOR_H_

#include <string>

class Decryptor {
public:
	Decryptor(int index, std::string plainText, std::string cipherText);
	Decryptor();
	virtual ~Decryptor();

	virtual bool decrypt() = 0;
	const std::string& getCipherText() const;
	void setCipherText(const std::string& cipherText);
	int getDictionaryIndex() const;
	void setDictionaryIndex(int dictionaryIndex);
	const std::string& getPlainText() const;
	void setPlainText(const std::string& plainText);
	virtual const std::string getExplanation() const = 0;

protected:



	void initialize();

	int dictionaryIndex;
	bool isInitialized;
	std::string plainText;
	std::string cipherText;
};

#endif /* DECRYPTOR_H_ */
