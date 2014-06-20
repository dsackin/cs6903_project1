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

	int decrypt();
	const std::string& getCipherText() const;
	void setCipherText(const std::string& cipherText);
	int getDictionaryIndex() const;
	void setDictionaryIndex(int dictionaryIndex);
	const std::string& getPlainText() const;
	void setPlainText(const std::string& plainText);

protected:

	Decryptor(int index, std::string plainText, std::string cipherText);
	Decryptor();
	virtual ~Decryptor();

	int dictionaryIndex;
	std::string plainText;
	std::string cipherText;
};

#endif /* DECRYPTOR_H_ */
