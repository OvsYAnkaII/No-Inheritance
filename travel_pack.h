#pragma once

#include "identity_document.h"
#include <iostream>
#include <string>

using namespace std::string_view_literals;

class TravelPack {
public:
    TravelPack()
    : identity_doc1_(reinterpret_cast<IdentityDocument*>(new Passport()))
    , identity_doc2_(reinterpret_cast<IdentityDocument*>(new DrivingLicence())) {
        *reinterpret_cast<const VTable**>(this) = &vtable_obj;
        std::cout << "TravelPack::Ctor()"sv << std::endl;
    }

    TravelPack(const TravelPack& other)
    : base_document(other.base_document)
    , identity_doc1_(reinterpret_cast<IdentityDocument*>(new Passport(*reinterpret_cast<Passport*>(other.identity_doc1_))))
    , identity_doc2_(reinterpret_cast<IdentityDocument*>(new DrivingLicence(*reinterpret_cast<DrivingLicence*>(other.identity_doc2_))))
    , additional_pass_(other.additional_pass_)
    , additional_dr_licence_(other.additional_dr_licence_) {
        *reinterpret_cast<const VTable**>(this) = &vtable_obj;
        std::cout << "TravelPack::CCtor()"sv << std::endl;
    }

    ~TravelPack() {
        identity_doc1_->Delete();
        identity_doc2_->Delete();
        std::cout << "TravelPack::Dtor()"sv << std::endl;
        *reinterpret_cast<const VTable**>(this) = reinterpret_cast<const VTable*>(&IdentityDocument::vtable_obj);
    }

    void PrintID() const {
        identity_doc1_->PrintID();
        identity_doc2_->PrintID();
        additional_pass_.PrintID();
        additional_dr_licence_.PrintID();
    }

    operator IdentityDocument() const {
        return base_document;
    }

    struct VTable {
        void (*PrintID)(const void*);
        void (*Delete)(void*);
    };

    void Delete() {
        DeleteTravelPack(this);
    }

private:
    IdentityDocument base_document{};
    IdentityDocument* identity_doc1_;
    IdentityDocument* identity_doc2_;
    Passport additional_pass_{};
    DrivingLicence additional_dr_licence_{};

    static void PrintIDTravelPack(const void* Object) {
        const auto TravelPackObjPtr = static_cast<const TravelPack*>(Object);
        TravelPackObjPtr->PrintID();
    }

    static void DeleteTravelPack(void* Object) {
        auto TravelPackObjPtr = static_cast<TravelPack*>(Object);
        delete TravelPackObjPtr;
    }

    static constexpr VTable vtable_obj{PrintIDTravelPack, DeleteTravelPack};
};