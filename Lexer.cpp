#include <iostream>
#include <string>
#include <vector>

enum class TokenType {
    INTEGER,
    PLUS,
    MINUS,
    EOF_TOKEN
    PRINT
    INT_MAIN
    PYTHON
    CPP
    CONSOLE
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

int main() {
    std::string input = "10 + 5 - 3";
    Lexer lexer(input);

    Token token;
    while ((token = lexer.getNextToken()).type != TokenType::EOF_TOKEN) {
        std::cout << "Token: " << token.value << std::endl;
    }

    return 0;
}
