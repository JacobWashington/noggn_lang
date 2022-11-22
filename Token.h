#pragma once
#include <string>
#include "TokenType.h"
using namespace std;

class Token
{
	TokenType type;
	string lexeme;
	string identifier;
	string stringLiteral;
	double numberLiteral;
	int line;

public:
	Token(TokenType type, string lexeme, string literal, int line) {
		this->type = type;
		this->lexeme = lexeme;
		this->identifier = literal;
		this->line = line;
	}

	Token(TokenType type, string lexeme, double numberLiteral, int line) {
		this->type = type;
		this->lexeme = lexeme;
		this->numberLiteral = numberLiteral;
		this->line = line;
	}
};

