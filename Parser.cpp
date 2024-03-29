#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

enum class TokenType {
    INTEGER,
    PLUS,
    MINUS,
    PRINT,
    MAIN,
    PYTHON,
    IMPORT,
    INPUT,
    EOF_TOKEN
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(std::string text) : text(text), pos(0) {}

    Token getNextToken() {
        if (pos >= text.size())
            return Token{TokenType::EOF_TOKEN, ""};

        if (isdigit(text[pos])) {
            std::string num;
            while (pos < text.size() && isdigit(text[pos])) {
                num.push_back(text[pos]);
                pos++;
            }
            return Token{TokenType::INTEGER, num};
        }

        if (text[pos] == '+') {
            pos++;
            return Token{TokenType::PLUS, "+"};
        }

        if (text[pos] == '-') {
            pos++;
            return Token{TokenType::MINUS, "-"};
        }

        // Invalid token
        throw std::runtime_error("Invalid character");
    }

private:
    std::string text;
    size_t pos;
};

class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer), currentToken(lexer.getNextToken()) {}

    void eat(TokenType expectedType) {
        if (currentToken.type == expectedType) {
            currentToken = lexer.getNextToken();
        } else {
            throw std::runtime_error("Invalid syntax");
        }
    }

    int factor() {
        Token token = currentToken;
        eat(TokenType::INTEGER);
        return std::stoi(token.value);
    }

    int expr() {
        int result = factor();

        while (currentToken.type == TokenType::PLUS || currentToken.type == TokenType::MINUS) {
            Token op = currentToken;
            if (op.type == TokenType::PLUS) {
                eat(TokenType::PLUS);
                result += factor();
            } else {
                eat(TokenType::MINUS);
                result -= factor();
            }
        }

        return result;
    }

    int parse() {
        return expr();
    }

private:
    Lexer& lexer;
    Token currentToken;
};

int main() {
    std::string input = "10 + 5 - 3";
    Lexer lexer(input);
    Parser parser(lexer);

    try {
        int result = parser.parse();
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
