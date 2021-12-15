#include <iostream>
#include <sstream>
#include <regex>
#include <numbers>
#include "Stack.h"
#include "MathUnit.h"

using namespace std;

MathUnit* parse_unit(string unit_str) {
    MathUnit::Unit unit_type;
    if (!unit_str.compare("+")) unit_type = MathUnit::add;
    else if (!unit_str.compare("-")) unit_type = MathUnit::subtract;
    else if (!unit_str.compare("*")) unit_type = MathUnit::multiply;
    else if (!unit_str.compare("/")) unit_type = MathUnit::divide;
    else if (!unit_str.compare("^")) unit_type = MathUnit::pow;
    else if (!unit_str.compare("(")) unit_type = MathUnit::open_bracket;
    else if (!unit_str.compare(")")) unit_type = MathUnit::close_bracket;
    else if (!unit_str.compare("_")) unit_type = MathUnit::negate;
    else if (!unit_str.compare("sin")) unit_type = MathUnit::sin;
    else if (!unit_str.compare("cos")) unit_type = MathUnit::cos;
    else if (!unit_str.compare("tg")) unit_type = MathUnit::tg;
    else if (!unit_str.compare("ctg")) unit_type = MathUnit::ctg;
    else if (!unit_str.compare("log2")) unit_type = MathUnit::binlog;
    else if (!unit_str.compare("ln")) unit_type = MathUnit::ln;
    else if (!unit_str.compare("log")) unit_type = MathUnit::log;
    else if (!unit_str.compare("sqrt")) unit_type = MathUnit::sqrt;
    else if (!unit_str.compare("pi")) return new MathUnit(numbers::pi);
    else if (!unit_str.compare("e")) return new MathUnit(numbers::e);
    else return new MathUnit(atof(unit_str.c_str()));
    return new MathUnit(unit_type);
}

Stack* process_expression(string expression) {
    expression.erase(remove_if(expression.begin(), expression.end(), ::isspace), expression.end()); // clear up whitespaces

    // make difference between the unary and binary minuses
    if (expression[0] == '-') {
        expression[0] = '_';
    }
    regex rgx_negate("\\(\\-");
    expression = regex_replace(expression, rgx_negate, "(_");

    Stack* init = new Stack(); // mathematical units in initial order
    regex rgx("[.\\d]+|[\\+\\-\\*\\/\\^\\(\\)]{1}|_|sin|cos|tg|ctg|log2|ln|log|sqrt|pi|e"); // number or operator or function or constant

    string copy = expression;
    copy = regex_replace(copy, rgx, ""); // should be clear after removing all allowed symbols
    if (!copy.empty()) {
        throw invalid_argument("Invalid symbols in the expression");
    }

    smatch match;
    while (regex_search(expression, match, rgx)) {
        string unit_str = match.str();
        MathUnit* parse = parse_unit(unit_str);
        init->push(parse);
        expression = match.suffix();
    }
    return init;
}

Stack* prefix_notation(Stack* expression) {
    Stack* temp = new Stack();
    Stack* out = new Stack();
    int brackets_counter = 0;
    while (MathUnit* unit = expression->pop()) { // pop from init and distribute to temp & out
        MathUnit::Unit type = unit->type();
        switch (type) {
        case MathUnit::add:
        case MathUnit::subtract:
        case MathUnit::multiply:
        case MathUnit::divide:
        case MathUnit::pow:
            if (!temp->empty() && abs(type) < abs(temp->last()->type()) && temp->last()->type() != MathUnit::close_bracket) {
                out->push(temp->pop());
            }
            temp->push(unit);
            break;
        case MathUnit::close_bracket:
            brackets_counter++;
            temp->push(unit);
            break;
        case MathUnit::open_bracket:
            brackets_counter--;
            if (brackets_counter < 0) {
                throw invalid_argument("Invalid brackets in the expression");
            }
            while (MathUnit* unit_from_temp = temp->pop()) { // pop from temp and push to out
                if (unit_from_temp->type() == MathUnit::close_bracket) { // until a closing bracket found
                    break;
                }
                out->push(unit_from_temp);
            }
            break;
        case MathUnit::negate:
        case MathUnit::sin:
        case MathUnit::cos:
        case MathUnit::tg:
        case MathUnit::ctg:
        case MathUnit::binlog:
        case MathUnit::ln:
        case MathUnit::log:
        case MathUnit::sqrt:
            out->push(unit);
            break;
        case MathUnit::number:
            out->push(unit);
            break;
        }
    }
    if (brackets_counter != 0) {
        throw invalid_argument("Invalid brackets in the expression");
    }
    while (MathUnit* unit_from_temp = temp->pop()) { // pop remaining units from temp and push to out
        out->push(unit_from_temp);
    }
    return out;
}

MathUnit* prefix_calculation(Stack* expression) {
    Stack* stack = new Stack();
    while (MathUnit* unit = expression->pop()) {
        MathUnit::Unit type = unit->type();
        if (type == MathUnit::number) {
            stack->push(unit);
        }
        else if (abs(type) <= 3) { // add, subtract, multiply, divide or pow
            double left = stack->pop()->val(), right = stack->pop()->val();
            double res;
            switch (type) {
            case MathUnit::add:
                res = left + right; break;
            case MathUnit::subtract:
                res = left - right; break;
            case MathUnit::multiply:
                res = left * right; break;
            case MathUnit::divide:
                res = left / right; break;
            case MathUnit::pow:
                res = pow(left, right); break;
            }
            stack->push(new MathUnit(res));
        }
        else { // negate, sin, cos, tg, ctg, log2, ln, log, sqrt
            double arg = stack->pop()->val();
            double res;
            switch (type) {
            case MathUnit::negate:
                res = -arg; break;
            case MathUnit::sin:
                res = sin(arg); break;
            case MathUnit::cos:
                res = cos(arg); break;
            case MathUnit::tg:
                res = tan(arg); break;
            case MathUnit::ctg:
                res = 1 / tan(arg); break;
            case MathUnit::binlog:
                res = log2(arg); break;
            case MathUnit::ln:
                res = log(arg); break;
            case MathUnit::log:
                res = log10(arg); break;
            case MathUnit::sqrt:
                res = sqrt(arg); break;
            }
            stack->push(new MathUnit(res));
        }
    }
    return stack->pop();
}

int main() {
    string expression;
    getline(cin, expression);
    Stack* init = process_expression(expression); // mathematical units in initial order
    Stack* out = prefix_notation(init); // mathematical units in prefix notation
    Stack* out_reverse = out->reverse();
    while (MathUnit* unit = out->pop()) { // print prefix notation
        cout << *unit;
    }
    cout << '\n' << *prefix_calculation(out_reverse);
}
