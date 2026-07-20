#pragma once

#include "driving_licence.h"
#include <iostream>
#include <string>

using namespace std::string_view_literals;

class InternationalDrivingLicence {
public:
    InternationalDrivingLicence() {
        std::cout << "InternationalDrivingLicence::Ctor()"sv << std::endl;
    }

    InternationalDrivingLicence(const InternationalDrivingLicence& other)
    : driving_licence_(other.driving_licence_)
    {
        std::cout << "InternationalDrivingLicence::CCtor()"sv << std::endl;
    }

    ~InternationalDrivingLicence() {
        std::cout << "InternationalDrivingLicence::Dtor()"sv << std::endl;
    }

    void PrintID() const {
        std::cout << "InternationalDrivingLicence::PrintID() : "sv;
        driving_licence_.PrintID();
        std::cout << std::endl;
    }

    void* operator new(size_t size) {
        std::cout << "InternationalDrivingLicence::operator new(size: " << size << ")" << std::endl;
        return ::operator new(size);
    }

    void operator delete(void* ptr) noexcept {
        std::cout << "InternationalDrivingLicence::operator delete()" << std::endl;
        ::operator delete(ptr);
    }

     void operator delete(void* ptr, size_t size) noexcept {
        std::cout << "InternationalDrivingLicence::operator delete(size: " << size << ")" << std::endl;
        ::operator delete(ptr);
    }

    operator IdentityDocument() const {
        return IdentityDocument(driving_licence_);
    }

    operator DrivingLicence() const {
        return driving_licence_;
    }

private:
    DrivingLicence driving_licence_;
};