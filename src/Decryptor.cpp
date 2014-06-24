/*
 * Decryptor.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: doug
 */

#include <vector>

#include "Decryptor.h"

Decryptor::Decryptor(int index, std::string plainText, std::string cipherText) {
	this->dictionaryIndex = index;
	this->plainText = plainText;
	this->cipherText = cipherText;
	this->isInitialized = false;
}

Decryptor::Decryptor() : dictionaryIndex(0), isInitialized(false) {}

Decryptor::~Decryptor() {
	// TODO Auto-generated destructor stub
}

void Decryptor::initialize() {
	isInitialized = true;
}


const std::string& Decryptor::getCipherText() const {
	return cipherText;
}

void Decryptor::setCipherText(const std::string& cipherText) {
	this->cipherText = cipherText;
}

int Decryptor::getDictionaryIndex() const {
	return dictionaryIndex;
}

void Decryptor::setDictionaryIndex(int dictionaryIndex) {
	this->dictionaryIndex = dictionaryIndex;
}

const std::string& Decryptor::getPlainText() const {
	return plainText;
}

void Decryptor::setPlainText(const std::string& plainText) {
	this->plainText = plainText;
}


