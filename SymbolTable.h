//
// Created by Shuaib on 5/25/2022.
//

#ifndef SYMBOLTABLEOFFLINE_SYMBOLTABLE_H
#define SYMBOLTABLEOFFLINE_SYMBOLTABLE_H

#include "ScopeTable.h"
#include<iostream>
#include<string>

/*
 * SymbolTable contains all the alive ScopeTables
 * in a FIFO (stack) manner. Parents are accessed
 * with a pointer from the current scope.
 * Outer scope is numbered
 * #1 and any scope with a non-null parent is numbered
 * #<parent_id>.<current_scope_id>.
 * <current_scope_id> is static, i;e, it maintains the
 * absolute numbering of the <current_scope_id> under its
 * parent.
 * Example:
 * {
 *      //SCOPE #1
 *      {
 *          //SCOPE #1.1
 *      }
 *      {
 *          //SCOPE #1.2
 *      }
 *      {
 *          //SCOPE #1.3
 *          {
 *              //SCOPE #1.3.1
 *          }
 *      }
 * }
 * Enter first scope with id --> 1
 * Enter another scope with id --> 1.1
 * Exit #1.1
 * Enter another scope with id --> 1.2
 * Exit #1.2
 * Enter another scope with id --> 1.3
 * Enter another scope with id --> 1.3.1
 * */
class SymbolTable {
private:
    ScopeTable *cur;
    size_t N;
public:
    explicit SymbolTable(size_t buckets) :
            cur{},
            N{buckets} {
        #ifdef VERBOSE
        std::cout << "Creating SymbolTable with initial global scope..." << std::endl;
        #endif
        enterScope();
    }

    ~SymbolTable() {
        if (cur == nullptr) return;
        while (cur != nullptr) {
            ScopeTable *ptr = cur;
            cur = cur->getParentScope();
            delete ptr;
        }
    }

    void enterScope() {
        ScopeTable *scopeTable{};
        if (cur == nullptr) {
            scopeTable = new ScopeTable(nullptr, 1, N);
            cur = scopeTable;
            return;
        }
        size_t curId = cur->getChildCount() + 1;
        cur->setChildCount(curId);
        scopeTable = new ScopeTable(cur, curId, N);
        cur = scopeTable;
    }

    void exitScope() {
        if (cur == nullptr) {
            #ifdef VERBOSE
            std::cout << "NO SCOPE TO EXIT" << std::endl;
            #endif
            return;
        }
        ScopeTable *parent = cur->getParentScope();
        delete cur;
        cur = parent;
    }

    bool insert(const std::string &name, const std::string &type) {
        if (cur == nullptr) cur = new ScopeTable(nullptr, 1, N);
        return cur->insertSymbol(name, type);
    }

    bool remove(const std::string &name) {
        if (cur == nullptr) return false;
        return cur->deleteSymbol(name);
    }

    SymbolInfo *lookUp(const std::string &name) {
        SymbolInfo *sym{};
        ScopeTable *ptr = cur;
        while (ptr != nullptr) {
            sym = ptr->lookUpSymbol(name);
            if (sym != nullptr) break;
            ptr = ptr->getParentScope();
        }
        #ifdef VERBOSE
        if (sym == nullptr) {
            std::cout << "Could not find < "
                      << name << " >"
                      << std::endl;
        }
        #endif
        return sym;
    }

    void printCurrentScope(std::ostream &out) {
        if (cur == nullptr) {
            #ifdef VERBOSE
            std::cout << "NO CURRENT SCOPE TO PRINT" << std::endl;
            #endif
            return;
        }
        cur->print(out);
    }

    void printAllScopes(std::ostream &out) {
        if (cur == nullptr) {
            #ifdef VERBOSE
            std::cout << "NO SCOPES TO PRINT" << std::endl;
            #endif
            return;
        }
        ScopeTable *ptr = cur;
        while (ptr != nullptr) {
            ptr->print(out);
            ptr = ptr->getParentScope();
        }
        out<<std::endl;
    }
};


#endif //SYMBOLTABLEOFFLINE_SYMBOLTABLE_H
