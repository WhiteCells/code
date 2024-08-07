#include "number_expression.h"
#include "operator_expression.h"
#include "context.h"
#include <string>

class Interpreter {
public:
    static Expression *parse(const std::string &input) {
        Context context;
        for (char c : input) {
            if (std::isdigit(c)) {
                context.pushExpression(new NumberExpression(c - '0'));
            } else if (c == '+' || c == '-' || c == '*' || c == '/') {
                Expression *left = context.popExpression();
                Expression *right = context.popExpression();
            }
        }
    }
};

int main(int argc, char *argv[]) {
    
    return 0;
}