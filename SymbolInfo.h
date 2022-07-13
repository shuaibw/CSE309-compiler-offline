//
// Created by Shuaib on 5/25/2022.
//

#ifndef SYMBOLTABLEOFFLINE_SYMBOLINFO_H
#define SYMBOLTABLEOFFLINE_SYMBOLINFO_H

#include<string>
#include<ostream>
#include<vector>
/*
 * SymbolInfo classifies the tokens with respective description.
 * Each SymbolInfo is hashed in a ScopeTable. In case of a
 * collision with another SymbolInfo, those are resolved with
 * separate chaining, indicated by SymbolInfo *next
 * Example:
 * int main(){
 *      int x = 0;
 *      foo();
 * }
 * The tokens are classified as: < NAME : TYPE >
 * <main : FUNC>, <x : VAR>, <0 : NUM>, <foo : FUNC>
 */
class SymbolInfo {
private:
    std::string name, type;
    SymbolInfo *next;
public:
    // Helper fields for function type
    std::string ret_type;
    bool func_declared = false;
    bool func_defined = false;
    int param_decl_len;
    std::vector<std::string> param_list;
    //

    SymbolInfo(std::string name, std::string type) :
            name{std::move(name)},
            type{std::move(type)},
            next{} {}

    SymbolInfo(const SymbolInfo &x) = default;

    ~SymbolInfo() = default;

    const std::string &getName() const {
        return name;
    }

    const std::string &getType() const {
        return type;
    }

    SymbolInfo *getNext() const {
        return next;
    }

    void setNext(SymbolInfo *nextSym) {
        next = nextSym;
    }

    friend std::ostream &operator<<(std::ostream &os, const SymbolInfo &info) {
        os << "< " << info.name << " : " << info.type << " >";
        return os;
    }
};


#endif //SYMBOLTABLEOFFLINE_SYMBOLINFO_H
