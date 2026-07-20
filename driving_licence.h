#pragma once

#include "identity_document.h"
#include <iostream>
#include <string>

using namespace std::string_view_literals;

class DrivingLicence {
public:
    DrivingLicence() {
        // this указывает на начало объекта, т.е. IdentityDocument.
        // Первое поле объекта — v_table_ptr_ (указатель на VTable).
        // Чтобы записать vtable, нужно получить доступ к первому полю объекта.
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

    void Delete() {
        DrivingLicenceDelete(this);
    }

    void* operator new(size_t size) {
        std::cout << "DrivingLicence::operator new(size: " << size << ")" << std::endl;
        return ::operator new(size);
    }

    void operator delete(void* ptr) noexcept {
        std::cout << "DrivingLicence::operator delete()" << std::endl;
        ::operator delete(ptr);
    }

     void operator delete(void* ptr, size_t size) noexcept {
        std::cout << "DrivingLicence::operator delete(size: " << size << ")" << std::endl;
        ::operator delete(ptr);
    }

    operator IdentityDocument() const {
        return base_document_;
    }

    struct VTable {
        void (*PrintID)(const void*);
        void (*Delete)(void*);
    };

private:
    static void DrivingLicencePrintID(const void* Object) {
        const auto DrivingLicenceObjectPtr = static_cast<const DrivingLicence*>(Object);
        DrivingLicenceObjectPtr->PrintID();
    }

    static void DrivingLicenceDelete(void* Object){
        auto DrivingLicenceObjectPtr = static_cast<DrivingLicence*>(Object);
        delete DrivingLicenceObjectPtr;
    }

    IdentityDocument base_document_;
    static constexpr VTable vtable_obj {DrivingLicencePrintID, DrivingLicenceDelete};
};