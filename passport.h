#pragma once

#include "identity_document.h"
#include <iostream>
#include <string>

using namespace std::string_view_literals;

class Passport{
public:
    Passport()
    {
        *static_cast<const VTable**>(static_cast<void*>(this)) = &vtable_obj;
        std::cout << "Passport::Ctor()"sv << std::endl;
    }

    Passport(const Passport& other)
    : base_document_(other.base_document_)
    {
        *static_cast<const VTable**>(static_cast<void*>(this)) = &vtable_obj;
        std::cout << "Passport::CCtor()"sv << std::endl;
    }

    ~Passport() {
        std::cout << "Passport::Dtor()"sv << std::endl;
        *static_cast<const VTable**>(static_cast<void*>(this)) = reinterpret_cast<const VTable*>(&IdentityDocument::vtable_obj);
    }

    void PrintID() const {
        std::cout << "Passport::PrintID() : "sv << base_document_.GetID();
        std::cout << " expiration date : "sv << expiration_date_.tm_mday << "/"sv << expiration_date_.tm_mon << "/"sv
                  << expiration_date_.tm_year + 1900 << std::endl;
    }

    static void PassportPrintID(const void* Object){
        const auto PassportObjectPtr = static_cast<const Passport*>(Object);
        PassportObjectPtr->PrintID();
    }

    void PrintVisa(const std::string& country) const {
        std::cout << "Passport::PrintVisa("sv << country << ") : "sv << base_document_.GetID() << std::endl;
    }

    static void PassportDelete(void* Object) {
        auto PassportObjectPtr = static_cast<Passport*>(Object);
        delete PassportObjectPtr;
    }

    static void PrintUniqueIDCount() {
        IdentityDocument::PrintUniqueIDCount();
    }

     operator IdentityDocument() const {
        return base_document_;
    }

    struct VTable {
        void (*PrintID)(const void*);
        void (*Delete)(void*);
    };

    void Delete() {
        PassportDelete(this);
    }

private:
    IdentityDocument base_document_;
    static constexpr VTable vtable_obj {PassportPrintID, PassportDelete};
    const struct tm expiration_date_{GetExpirationDate()};

    static tm GetExpirationDate() {
        time_t t = time(nullptr);
        tm exp_date = *localtime(&t);
        exp_date.tm_year += 10;
        mktime(&exp_date);
        return exp_date;
    }
};