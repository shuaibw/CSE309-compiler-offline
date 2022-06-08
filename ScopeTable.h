//
// Created by Shuaib on 5/25/2022.
//

#ifndef SYMBOLTABLEOFFLINE_SCOPETABLE_H
#define SYMBOLTABLEOFFLINE_SCOPETABLE_H

#include<string>
#include <ostream>
#include "SymbolInfo.h"

/*
 * ScopeTable contains the hashed SymbolInfo of the current scope
 * under a hash table. It uses sdbm hashing algorithm.
 * In case of a collision with another SymbolInfo, it is resolved
 * with separate chaining. Each ScopeTable also contains a pointer
 * to its parent ScopeTable to implement the FIFO structure in the
 * SymbolTable.
 * An example ScopeTable with 5 buckets:
 * {
 *      //SCOPE #1
 *      int y = 7 + 6;
 *      int x = 10 + 32;
 *      {
 *          //SCOPE #1.1
 *      }
 *      {
 *          //SCOPE #1.2
 *          {
 *              //SCOPE #1.2.1
 *          }
 *      }
 * }
 * [[BUCKET --> ...< NAME : TYPE >]]
 * 0 --> < y : VAR >< 7 : NUM >
 * 1 --> < x : VAR >< 10 : NUM >
 * 2 --> < + : ADD >
 * 3 --> < 6 : NUM >
 * 4 --> < 32 : NUM >
 */

uint32_t sdbmHash(const char *p) {
    uint32_t hash = 0;
    auto *str = (unsigned char *) p;
    int c{};
    while ((c = *str++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

class ScopeTable {
private:
    SymbolInfo **symbols;
    ScopeTable *parentScope;
    const std::string id;
    const size_t N;
    size_t childCount;
public:
    ScopeTable(ScopeTable *parent, size_t id, size_t buckets) :
            symbols{new SymbolInfo *[buckets]{}},
            parentScope{parent},
            id{std::move(
                    parentScope == nullptr ?
                    std::to_string(id) :
                    parentScope->getId() + "." + std::to_string(id)
            )},
            N{buckets},
            childCount{0} {
        #ifdef VERBOSE
        std::cout << "ScopeTable with ID# " << this->id << " created" << std::endl;
        #endif

    }

    ~ScopeTable() {

        #ifdef VERBOSE
        std::cout << "Destroying ScopeTable# " << id << std::endl;
        #endif

        for (size_t i = 0; i < N; i++) {
            SymbolInfo *ptr = symbols[i];
            while (ptr != nullptr) {
                SymbolInfo *temp = ptr;
                ptr = ptr->getNext();
                delete temp;
            }
        }
        delete[] symbols;
    }

    const std::string &getId() const {
        return id;
    }

    ScopeTable *getParentScope() const {
        return parentScope;
    }

    bool insertSymbol(const std::string &name, const std::string &type) {
        size_t pos{0};
        size_t idx = sdbmHash(name.c_str()) % N;
        SymbolInfo *cur{symbols[idx]};
        SymbolInfo *prev{};
        while (cur != nullptr) {
            if (cur->getName() == name) {

                #ifdef VERBOSE
                std::cout << *cur
                          << " already exists in ScopeTable# " << id
                          << " at position " << idx << ", " << pos
                          << std::endl;
                #endif

                return false;
            }
            prev = cur;
            cur = cur->getNext();
            pos++;
        }
        auto *symInfo = new SymbolInfo(name, type);
        if (prev == nullptr) symbols[idx] = symInfo;
        else prev->setNext(symInfo);

        #ifdef VERBOSE
        std::cout << "Inserted " << *symInfo
                  << " in ScopeTable# " << id
                  << " at position " << idx << ", " << pos
                  << std::endl;
        #endif

        return true;
    }

    SymbolInfo *lookUpSymbol(const std::string &name) {
        size_t idx = sdbmHash(name.c_str()) % N;
        size_t pos{0};
        SymbolInfo *cur{symbols[idx]};
        while (cur != nullptr) {
            if (cur->getName() == name) {
                #ifdef VERBOSE
                std::cout << "Found " << *cur
                          << " in ScopeTable# " << id
                          << " at position " << idx << ", " << pos
                          << std::endl;
                #endif
                return cur;
            }
            cur = cur->getNext();
            pos++;
        }
        return nullptr;
    }

    bool deleteSymbol(const std::string &name) {
        size_t idx = sdbmHash(name.c_str()) % N;
        size_t pos{0};
        SymbolInfo *cur{symbols[idx]};
        SymbolInfo *prev{};
        bool found{false};
        while (cur != nullptr) {
            if (cur->getName() == name) {
                found = true;
                break;
            }
            prev = cur;
            cur = cur->getNext();
            pos++;
        }
        //case 1: nothing exists
        if (!found) {
            #ifdef VERBOSE
            std::cout << "Could not delete < "
                      << name << " >: "
                      << "Symbol nonexistent"
                      << std::endl;
            #endif
            return false;
        }
        #ifdef VERBOSE
        std::cout << "Deleted " << *cur
                  << " in ScopeTable# " << id
                  << " at position " << idx << ", " << pos
                  << std::endl;
        #endif
        //case 2: first symbol is to be deleted
        if (prev == nullptr) {
            symbols[idx] = cur->getNext();
            delete cur;
        }
            //case 3: last symbol is to be deleted
        else if (cur->getNext() == nullptr) {
            prev->setNext(nullptr);
            delete cur;
        }
            //case 4: symbol exists in between
        else {
            prev->setNext(cur->getNext());
            delete cur;
        }
        return true;
    }

    void print() const {
        std::cout << "ScopeTable# " << id << std::endl;
        std::cout << "--------------------" << std::endl;
        for (size_t i = 0; i < N; i++) {
            std::cout << i << " --> ";
            SymbolInfo *cur = symbols[i];
            while (cur != nullptr) {
                std::cout << *cur;
                cur = cur->getNext();
            }
            std::cout << std::endl;
        }
        std::cout << "--------------------" << std::endl;
    }

    size_t getChildCount() const {
        return childCount;
    }

    void setChildCount(size_t count) {
        childCount = count;
    }
};


#endif //SYMBOLTABLEOFFLINE_SCOPETABLE_H
