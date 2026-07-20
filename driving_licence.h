#pragma once

#include "identity_document.h"
#include <iostream>
#include <string>

using namespace std::string_view_literals;

class DrivingLicence {
public:
    DrivingLicence() {
        *reinterpret_cast<const VTable**>(this) = &vtable_obj;
        std::cout << "DrivingLicence::Ctor()"sv << std::endl;
    }

    DrivingLicence(const DrivingLicence& other)
    : base_document_(other.base_document_)
    {
        *reinterpret_cast<const VTable**>(this) = &vtable_obj;
        std::cout << "DrivingLicence::CCtor()"sv << std::endl;
    }

    ~DrivingLicence() {
        std::cout << "DrivingLicence::Dtor()"sv << std::endl;
        *reinterpret_cast<const VTable**>(this) = reinterpret_cast<const VTable*>(&IdentityDocument::vtable_obj);
    }

    void PrintID() const {
        std::cout << "DrivingLicence::PrintID() : "sv << base_document_.GetID() << std::endl;
    }

    static void DrivingLicencePrintID(const void* Object) {
        const auto DrivingLicenceObjectPtr = static_cast<const DrivingLicence*>(Object);
        DrivingLicenceObjectPtr->PrintID();
    }

    static void DrivingLicenceDelete(void* Object){
        auto DrivingLicenceObjectPtr = static_cast<DrivingLicence*>(Object);
        delete DrivingLicenceObjectPtr;
    }

     operator IdentityDocument() const {
        return base_document_;
    }

    struct VTable {
        void (*PrintID)(const void*);
        void (*Delete)(void*);
    };

    private:
    IdentityDocument base_document_;
    static constexpr VTable vtable_obj {DrivingLicencePrintID, DrivingLicenceDelete};
};