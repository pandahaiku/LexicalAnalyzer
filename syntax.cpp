#include "Lexer.h"
#include "Syntax.h"
#include "Pair.h"
#include <iostream>

int line_count = 0;

void retError(std::list<Pair>& lexemes) {
	std::cout << "Error on line: " << line_count << std::endl;
	exit(0);
}

std::string getToken(std::list<Pair> &lexemes) {
	if (lexemes.front().val1 == "\\n") {
		line_count++;
		lexemes.pop_front();
		getToken(lexemes);
	}
	else if (lexemes.front().val1 == "\\t") {
		lexemes.pop_front();
		getToken(lexemes);
	}
	std::string token = lexemes.front().val1;
	lexemes.pop_front();
	return token;
}

bool functionA(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "A\n";
	//if (printSwitch) { std::cout << "A-> B %% CD" << std::endl; }
	if (functionB(lexemes, printSwitch)) {
		std::string token = getToken(lexemes);
		if (token == "%") {
			token == getToken(lexemes);
			if (token == "%") {
				if (!functionC(lexemes, printSwitch)) { retError(lexemes); }
				if (!functionD(lexemes, printSwitch)) { retError(lexemes); }
			}
			else {
				retError(lexemes);
				return false;
			}
		}
		else {
			retError(lexemes);
			return false;
		}
	}
	else { // if functionB returns false
		retError(lexemes);
		return false;
	}
}
bool functionB(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "B\n";
	if (functionE(lexemes, printSwitch)) {
		return true;
	}
	else if (functionEprime(printSwitch)) {
		return true;
	}
	return false;
}

bool functionE(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "E\n";
	if (functionF(lexemes, printSwitch)) {
		if (functionE(lexemes, printSwitch)) {
			return true;
		}
		return true;
	}
	else {
		return false;
	}
}

bool functionF(std::list<Pair> &lexemes, bool printSwitch) {
	std::string token = getToken(lexemes);
	std::cout << "F\n";
	if (token == "@") {
		if (!functionG(lexemes, printSwitch)) {
			return false;
		}
	}
	token = getToken(lexemes);

	if (token == "(") {
		if (!functionH(lexemes, printSwitch)) { return false; }
	}
	token = getToken(lexemes);

	if (token == ")") {
		if (!functionC(lexemes, printSwitch)) {
			return false;
		}
		if (!functionI(lexemes, printSwitch)) {
			return false;
		}
	}
}

bool functionH(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "H\n";
	if (functionJ(lexemes, printSwitch)) {
		return true;
	}
	else {
		functionEprime(printSwitch);
	}
}

bool functionJ(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "J\n";
	if (functionK(lexemes, printSwitch)) {
		std::string token = getToken(lexemes);

		if (token == ",") {
			if (functionJ(lexemes, printSwitch)) {
				return true;
			}
		}
		else { //token is not ,
			return true;
		}
	}
	else { return false; }
}

bool functionK(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "K\n";
	if (functionL(lexemes, printSwitch)) {
		return true;
	}
	std::string token = getToken(lexemes);

	if (token == ":") {
		if (functionM(lexemes, printSwitch)) {
			return true;
		}
	}
	else {
		retError(lexemes);
		return false;
	}
}

bool functionM(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "M\n";
	std::string token = getToken(lexemes);

	return (token == "integer") || (token == "boolean") || (token == "floating");
}

bool functionI(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "I\n";
	std::string token = getToken(lexemes);

	if (token == "{") {
		if (!functionD(lexemes, printSwitch)) {
			return false;
		}
		token = getToken(lexemes);

		return token == "}";
	}
}

bool functionC(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "C\n";
	if (functionN(lexemes, printSwitch)) {
		return true;
	}
	else {
		return functionEprime(printSwitch);
	}
}

bool functionN(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "N\n";
	if (functionO(lexemes, printSwitch)) {
		std::string token = getToken(lexemes);

		if (token == ";") {
			if (functionN(lexemes, printSwitch)) {
				return true;
			}
			else {
				return true;
			}
		}
		else {
			retError(lexemes);
			return false;
		}
		return true;
	}
}

bool functionO(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "M\n";
	if (functionM(lexemes, printSwitch)) {
		return functionL(lexemes, printSwitch);
	}
	else {
		retError(lexemes);
		return false;
	}
}

bool functionL(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "L\n";
	Pair temp;
	temp.val1 = lexemes.front().val1;
	temp.val2 = lexemes.front().val2;
	if (functionG(lexemes, printSwitch)) {
		std::string token = getToken(lexemes);
		if (token == ",") {
			if (functionL(lexemes, printSwitch)) {
				return true;
			}
		}
		else { //token is not ,
			lexemes.push_front(temp);
			return true;
		}
	}
	else { return false; }
}

bool functionD(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "D\n";
	if (functionP(lexemes, printSwitch)) {
		if (functionD(lexemes, printSwitch)) {
			return true;
		}
		return true;
	}
	else {
		return false;
	}
}

bool functionP(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "P\n";
	if (functionQ(lexemes, printSwitch)) { return true; }
	if (functionR(lexemes, printSwitch)) { return true; }
	if (functionS(lexemes, printSwitch)) { return true; }
	if (functionT(lexemes, printSwitch)) { return true; }
	if (functionU(lexemes, printSwitch)) { return true; }
	if (functionV(lexemes, printSwitch)) { return true; }
	if (functionW(lexemes, printSwitch)) { return true; }
	return false;
}

bool functionQ(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "Q\n";
	std::string token = getToken(lexemes);

	if (token == "{") {
		if (!functionD(lexemes, printSwitch)) {
			return false;
		}
		token = getToken(lexemes);

		return token == "}";
	}
	else {
		return false;
	}
}

bool functionR(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "R\n";
	if (functionG(lexemes, printSwitch)) {
		std::string token = getToken(lexemes);
		if (token == ":=") {
			if (functionX(lexemes, printSwitch)) {
				token = getToken(lexemes);

				return token == ";";
			}
		}
	}
	else {
		return false;
	}
}


bool functionS(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "S\n";
	std::string token = getToken(lexemes);
	if (token == "if") {
		token = getToken(lexemes);
		if (token == "(") {
			if (!functionY(lexemes, printSwitch)) {
				return false;
			}
			token = getToken(lexemes);
			if (token == ")") {
				if (!functionP(lexemes, printSwitch)) { return false; }
				if (!functionSprime(lexemes, printSwitch)) { return false; }
				return true;
			}
			else { return false; }
		}
		else { return false; }
	}
	else { return false; }
}

bool functionSprime(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "Sprime\n";
	std::string token = getToken(lexemes);
	if (token == "fi") {
		return true;
	}
	else if (token == "else") {
		if (functionP(lexemes, printSwitch)) {
			token = getToken(lexemes);
			if (token == "fi") {
				return true;
			}
		}
	}
	return false;
}


bool functionT(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "T\n";
	std::string token = getToken(lexemes);
	if (token == "return") {
		if (functionTprime(lexemes, printSwitch)) {
			return true;
		}
		else {
			return false;
		}
	}
}
bool functionTprime(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "Tprime\n";
	if (functionX(lexemes, printSwitch)) {
		std::string token = getToken(lexemes);
		return token == ";";
	}
	std::string token = getToken(lexemes);
	return token == ";";
}

bool functionU(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "U\n";
	std::string token = getToken(lexemes);
	if (token == "write") {
		token = getToken(lexemes);
		if (token == "(") {
			if (functionX(lexemes, printSwitch)) {
				token = getToken(lexemes);
				if (token == ")") {
					token = getToken(lexemes);
					if (token == ";") {
						return true;
					}
				}
			}
		}
	}
	// if token != write
	return false;
}


bool functionV(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "V\n";
	std::string token = getToken(lexemes);
	if (token == "read") {
		token = getToken(lexemes);
		if (token == "(") {
			if (functionL(lexemes, printSwitch)) {
				token = getToken(lexemes);
				if (token == ")") {
					token = getToken(lexemes);
					if (token == ";") {
						return true;
					}
				}
			}
		}
	}
	// if token != read
	return false;
}

bool functionW(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "W\n";
	std::string token = getToken(lexemes);
	if (token == "while") {
		token = getToken(lexemes);
		if (token == "(") {
			if (functionX(lexemes, printSwitch)) {
				token = getToken(lexemes);
				if (token == ")") {
					if (functionP(lexemes, printSwitch)) {
						return true;
					}
				}
			}
		}
	}
	// if token != while
	return false;
}

bool functionY(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "Y\n";
	if (functionX(lexemes, printSwitch)) {
		if (functionZ(lexemes, printSwitch)) {
			if (functionX(lexemes, printSwitch)) {
				return true;
			}
		}
	}
	else {
		return false;
	}
}

bool functionZ(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "Z\n";
	std::string token = getToken(lexemes);

	return (token == "=") || (token == "/=") || (token == ">")
		|| (token == "<") || (token == "=>") || (token == "<=");
}


bool functionX(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "X\n";
	if (functionAprime(lexemes, printSwitch)) {
		if (functionXprime(lexemes, printSwitch)) {
			return true;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

bool functionXprime(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "Xprime\n";
	std::string token = getToken(lexemes);
	if (token == "+") {
		if (functionAprime(lexemes, printSwitch)) {
			if (functionXprime(lexemes, printSwitch)) {
				return true;
			}
		}
	}
	else if (token == "-") {
		if (functionAprime(lexemes, printSwitch)) {
			if (functionXprime(lexemes, printSwitch)) {
				return true;
			}
		}
	}
	else {
		return functionEprime(printSwitch);
	}
}

bool functionAprime(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "Aprime\n";
	if (functionBprime(lexemes, printSwitch)) {
		if (functionA2(lexemes, printSwitch)) {
			return true;
		}
		else { return true; }
	}
	return false;
}

bool functionA2(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "A2\n";
	std::string token = getToken(lexemes);

	if (token == "*") {
		if (functionBprime(lexemes, printSwitch)) {
			if (functionA2(lexemes, printSwitch)) {
				return true;
			}
		}
	}
	else if (token == "/") {
		if (functionBprime(lexemes, printSwitch)) {
			if (functionA2(lexemes, printSwitch)) {
				return true;
			}
		}
	}
	else {
		return functionEprime(printSwitch);
	}
}

bool functionBprime(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "Bprime\n";
	std::string token = getToken(lexemes);

	if (token == "-") {
		if (functionCprime(lexemes, printSwitch)) {
			return true;
		}
	}
	else return functionCprime(lexemes, printSwitch);
}

bool functionCprime(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "Cprime\n";
	if (functionG(lexemes, printSwitch)) {
		std::string token = getToken(lexemes);
		if (token == "[") {
			if (functionL(lexemes, printSwitch)) {
				token = getToken(lexemes);
				if (token == "]") {
					return true;
				}
			}
		}
		return true;
	}
	if (functionDprime(printSwitch)) { return true; }
	if (functionFprime(printSwitch)) { return true; }
	std::string token = getToken(lexemes);
	if (token == "(") {
		if (functionX(lexemes, printSwitch)) {
			token = getToken(lexemes);
			if (token == ")") {
				return true;
			}
		}
	}
	return (token == "true") || (token == "false");
}

bool functionEprime(bool printSwitch) {
	std::cout << "Eprime\n";
	return true;
}

bool functionDprime(bool printSwitch) {
	std::cout << "Dprime\n";
	return true;
}

bool functionFprime(bool printSwitch) {
	std::cout << "Fprime\n";
	return true;
}

bool functionG(std::list<Pair> &lexemes, bool printSwitch) {
	std::cout << "G\n";
	std::string token = getToken(lexemes);
	std::cout << "--> " << token << std::endl;
	return true;
}