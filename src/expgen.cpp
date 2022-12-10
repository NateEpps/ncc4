/**
 * @file
 * @author Nathanael Epps
 *
 * Expression generator tool
 */

#include "Util.hpp"
#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <list>

#define MakeException(mssg) std::runtime_error(std::string(__PRETTY_FUNCTION__) + ": " + mssg)

// Comment/uncomment to toggle debug mode
// #define EXPGEN_DEBUG

template <class T>
T convert(std::string str) {
    if (str.empty())
        throw MakeException("Can't convert empty string");
    
    std::stringstream ss(str);
    T data;
    if (ss >> data)
        return data;
    else
        throw MakeException("Conversion error for string \"" + str + "\"");
}

void usage(std::string args0) {
    std::cerr << "Usage:\n\t" << args0 << " (seed) (iterations)\n";
}

int nearestInt(double d) {
    return (int)(d + 0.5);
}

enum class ElementType { Number, Operator, Parenthesis };

class Element {
public:
    Element(std::string str) : data(str) {
        if (str.empty())
            throw MakeException("Received empty string");

        if (str == "(" || str == ")") {
            type = ElementType::Parenthesis;
        } else if (str == "+" || str == "-" || str == "/" || str == "*") {
            type = ElementType::Operator;
        } else {
            // Input string converts to int, or an exception is thrown
            (void) convert<int>(str);

            type = ElementType::Number;
        }
    }

    Element(int value) {
        data = std::to_string(value);
        type = ElementType::Number;
    }

    std::list<Element> expand() const {
        if (type != ElementType::Number)
            throw MakeException("Cannot expand non-number (data: \"" + data + "\")");

        switch(ncc::util::randInt(0, 3)) {
            case 0: return expandAdd();
            case 1: return expandSub();
            case 2: return expandMult();
            case 3: return expandDiv();
            default: throw MakeException("randInt is broken");
        }
    }

    inline std::string toString() const {
        return data;
    }

    inline ElementType getType() const {
        return type;
    }

private:
    std::list<Element> expandAdd() const {
        int value = convert<int>(data);

        int next0 = ncc::util::randInt(value - 10, value);
        int next1 = value - next0;

        return generateNextSeq(next0, next1, "+");
    }

    std::list<Element> expandSub() const {
        int value = convert<int>(data);
        
        int next0 = ncc::util::randInt(value, value + 10);
        int next1 = next0 - value;
        
        return generateNextSeq(next0, next1, "-");
    }

    std::list<Element> expandMult() const {
        int value = convert<int>(data);
        const int Limit = nearestInt(sqrt(value));
        
        bool found = false;
        int next0, next1;
        for (next0 = 2; next0 < Limit; next0++) {
            if (value % next0 == 0) {
                next1 = value / next0;
                found = true;
                break;
            }
        }
        
        if (!found) {
            next0 = 1;
            next1 = value;
        }
        
        return generateNextSeq(next0, next1, "*");
    }
    
    std::list<Element> expandDiv() const {
        int value = convert<int>(data);
        
        // let's not have divide by zero errors
        if (value == 0)
            return expandMult();
        
        const int Limit = value * value;
        
        bool found = false;
        int next0, next1;
        for (next0 = value + 1; next0 <= Limit; next0++) {
            for (next1 = 2; next1 <= next0; next1++) {
                if (next0 % next1 == 0 && next0 / next1 == value) {
                    found = true;
                    break;
                }
            }
            
            if (found)
                break;
        }
        
        if (!found) {
#ifdef EXPGEN_DEBUG
            std::cerr << __PRETTY_FUNCTION__ << ": !found case\n";
#endif
            next0 = Limit;
            next1 = value;
        }
        
        return generateNextSeq(next0, next1, "/");
    }
    
    static std::list<Element> generateNextSeq(int next0, int next1, std::string opStr) {
        std::list<Element> next;
        next.emplace_back("(");
        next.emplace_back(next0);
        next.emplace_back(opStr);
        next.emplace_back(next1);
        next.emplace_back(")");
        return next;
    }
    
    std::string data;
    ElementType type;
};

std::ostream& operator<<(std::ostream& stream, std::list<Element> list) {
    if (list.size() == 0)
        return stream;

    std::list<Element>::iterator itr, next;
    itr = list.begin();
    next = itr;
    next++;

    while (itr != list.end()) {
        stream << itr->toString();

        if (next->getType() == ElementType::Operator ||
            itr->getType() == ElementType::Operator)
            stream << " ";

        itr++;
        if (next != list.end())
            next++;
    }

    return stream;
}

int main2(ncc::args_t args) {
    if (ncc::util::getOpt(args, "--help", "-h") != args.end()) {
        usage(args[0]);
        return EXIT_SUCCESS;
    } else if (args.size() < 3) {
        usage(args[0]);
        return EXIT_FAILURE;
    }

    int seed = convert<int>(args[1]);
    int iterAmt = convert<int>(args[2]);

    std::list<Element> expr;
    expr.emplace_back(seed);
#ifdef EXPGEN_DEBUG
    std::cout << "Seed:         " << seed << "\n";
    std::cout << "Iterations:   " << iterAmt << "\n";
    std::cout << ">> " << expr << "\n";
#endif
    for (int x = 0; x < iterAmt; x++) {
        std::list<Element> nextExpr;

        for (auto itr = expr.begin(); itr != expr.end(); itr++) {
            if (itr->getType() != ElementType::Number) {
                nextExpr.push_back(*itr);
            } else {
                nextExpr.splice(nextExpr.end(), itr->expand());
            }
        }

        expr = std::move(nextExpr);
#ifdef EXPGEN_DEBUG
        std::cout << ">> " << expr << "\n";
#endif
    }
#ifdef EXPGEN_DEBUG
    std::cout << "\n";
#endif
    std::cout << expr << "\n";

    return EXIT_SUCCESS;
}

int main(int argc, const char** argv) {
    try {
        return main2(ncc::util::bundle(argc, argv));
    } catch (std::exception& ex) {
        std::cerr << "\n" << ex.what() << "\n";
    } catch (...) {
        std::cerr << "\nCaught unknown exception\n";
    }

    return EXIT_FAILURE;
}
