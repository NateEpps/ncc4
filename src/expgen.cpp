/**
 * @file
 * @author Nathanael Epps
 *
 * Expression generator tool
 */

#include "Util.hpp"
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

int randInt(int lo, int hi) {
    static bool init = false;
    if (!init) {
        srand(time(nullptr));
        init = true;
    }
    
    if (lo >= hi)
        throw MakeException("Invalid parameters: " + std::to_string(lo) + ", " + std::to_string(hi));
    else
        return rand() % (hi - lo + 1) + lo;
}

void usage(std::string args0) {
    std::cerr << "Usage:\n\t" << args0 << " (seed) (iterations)\n";
}

enum class ElementType { Number, Operator, Parenthesis };

class Element {
    std::string data;
    ElementType type;

public:
    Element(std::string str) : data(str) {
        if (str.empty())
            throw MakeException("Received empty string");
        
        if (str == "(" || str == ")") {
            type = ElementType::Parenthesis;
        } else if (str == "+" || str == "-" || str == "/" || str == "*") {
            type = ElementType::Operator;
        } else {
            if (!isnumber(str[0]) && str[0] != '-')
                throw MakeException("Expected number");
            
            for (int x = 1; x < str.size(); x++) {
                if (!isnumber(str[x]))
                    throw MakeException("Expected number");
            }
            
            type = ElementType::Number;
        }
    }
    
    Element(int value) : Element(std::to_string(value)) {}
    
    std::list<Element> expand() const {
        if (type != ElementType::Number)
            throw MakeException("Cannot expand non-number (data: \"" + data + "\")");

        int value = convert<int>(data);

        int next0 = randInt(value - 10, value);
        int next1 = value - next0;

        std::list<Element> nextSeq;
        nextSeq.emplace_back("(");
        nextSeq.emplace_back(next0);
        nextSeq.emplace_back("+");
        nextSeq.emplace_back(next1);
        nextSeq.emplace_back(")");

        return nextSeq;
    }
    
    inline std::string toString() const {
        return data;
    }
    
    inline ElementType getType() const {
        return type;
    }
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

int main2(std::vector<std::string> args) {
    if (ncc::util::getOpt(args, "--help", "-h") != args.end()) {
        usage(args[0]);
        return EXIT_SUCCESS;
    } else if (args.size() < 3) {
        usage(args[0]);
        throw std::runtime_error("Not enough args");
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