#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Noggn.h"
#include "TokenType.h"
#include "Token.h"

using namespace std;

class Scanner
{

public:
	unordered_map<string, TokenType> keywords;

    Scanner(string argsString) {
        this->source = argsString;
    }

private:
	void mapKeywords() {
		keywords["and"] = AND;
		keywords["else"] = ELSE;
		keywords["false"] = FALSE;
		keywords["for"] = FOR;
		keywords["fun"] = FUN;
		keywords["if"] = IF;
		keywords["nil"] = NIL;
		keywords["or"] = OR;
		keywords["print"] = PRINT;
		keywords["return"] = RETURN;
		keywords["super"] = SUPER;
		keywords["this"] = THIS;
		keywords["ture"] = TRUE;
		keywords["var"] = VAR;
		keywords["while"] = WHILE;
	}

	string source;
	vector<Token> tokens;
	int start = 0;
	int current = 0;
	int line = 1;

	vector<Token> scanTokens() {
		while (!isAtEnd()) {
			start = current;
			scanToken();
		}
        Token toke(ENDF, "", "", line);
		tokens.push_back(toke);
		return tokens;
	}

	void scanToken() {
		char c = advance();
		switch (c) {
        case '(':
            addToken(LEFT_PAREN);
            break;
        case ')':
            addToken(RIGHT_PAREN);
            break;
        case '{':
            addToken(LEFT_BRACE);
            break;
        case '}':
            addToken(RIGHT_BRACE);
            break;
        case ',':
            addToken(COMMA);
            break;
        case '.':
            addToken(DOT);
            break;
        case '-':
            addToken(MINUS);
            break;
        case '+':
            addToken(PLUS);
            break;
        case ';':
            addToken(SEMICOLON);
            break;
        case '*':
            addToken(STAR);
            break;
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
            break;
        case '/':
            if (match('/')) {
                while (peek() != '\n' && !isAtEnd()) advance();
            }
            else {
                addToken(SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;
        case '\n':
            line++;
            break;
        case '"':
            string();
            break;
        default:
            if (isDigit(c)) {
                number();
            }
            else if (isAlpha(c)) {
                identifier();
            }
            else {
                // Noggn::error(line, "Unexpected character.");
       
            }
            break;
		}
	}

    void identifier() {
        while (isAlphaNumeric(peek())) advance();

        TokenType type = keywords[source.substr(start, current)];
        if (type == NULL) type = IDENTIFIER;
        addToken(type);
    }

    void number() {
        while (isDigit(peek())) advance();

        // Look for a fractional part.
        if (peek() == '.' && isDigit(peekNext())) {
            // Consume the "."
            advance();

            while (isDigit(peek())) advance();
        }

        addToken(NUMBER, stod(source.substr(start, current)));
    }

    void string() {
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n') line++;
            advance();
        }

        if (isAtEnd()) {
           // Noggn::error(line, "Unterminated string.");
            return;
        }

        advance(); // The closing ".

        // Trim the surrounding quotes.
        addToken(STRING, source.substr(start + 1, current - 1));
    }

	bool isAtEnd() {
		return current >= source.length();
	}

    bool match(char expected) {
        if (isAtEnd()) return false;
        if (source[current] != expected) return false;

        current++;
        return true;
    }

	char advance() {
		return source[current++];
	}

    char peekNext() {
        if (current + 1 >= source.length()) return '\0';
        return source[current + 1];
    }

    char peek() {
        if (isAtEnd()) return '\0';
        return source[current];
    }

    bool isAlpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }

    bool isAlphaNumeric(char c) {
        return isAlpha(c) || isDigit(c);
    }

    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    void addToken(TokenType type) {
        cout << type;
        addToken(type, NULL);
    }

    void addToken(TokenType type,std::string literal) {
        cout << type;
        tokens.push_back(Token(type, source.substr(start, current), literal, line));
    }

    void addToken(TokenType type, double literal) {
        tokens.push_back(Token(type, source.substr(start, current), literal, line));
    }
};