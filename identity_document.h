#pragma once

#include <iostream>
#include <string>

using namespace std::string_view_literals;

class IdentityDocument {
public:
    IdentityDocument()
        : unique_id_(++unique_id_count_) 
    {
        // this указывает на начало объекта IdentityDocument.
        // Первое поле объекта — v_table_ptr_ (указатель на VTable).
        // Чтобы записать vtable, нужно получить доступ к первому полю объекта.
        *static_cast<const VTable**>(static_cast<void*>(this)) = &vtable_obj;
        std::cout << "IdentityDocument::Ctor() : "sv << unique_id_ << std::endl;
    }

    ~IdentityDocument() {
        --unique_id_count_;
        std::cout << "IdentityDocument::Dtor() : "sv << unique_id_ << std::endl;
    }

    IdentityDocument(const IdentityDocument& other)
        : unique_id_(++unique_id_count_) 
    {
        std::cout << "IdentityDocument::CCtor() : "sv << unique_id_ << std::endl;
    }

    IdentityDocument& operator=(const IdentityDocument&) = delete;

    static void PrintUniqueIDCount() {
        std::cout << "unique_id_count_ : "sv << unique_id_count_ << std::endl;
    }

    [[nodiscard]] int GetID() const {
        return unique_id_;
    }

    void PrintID() const {
        this->v_table_ptr_->PrintID(this);
    }

    static void IdentityDocumentPrintID (const void* Object) {
        const auto IdentityDocumentObjectPtr = static_cast<const IdentityDocument*>(Object);
        IdentityDocumentObjectPtr->InnerPrintID();
    }

    void Delete(){
        this->v_table_ptr_->Delete(this);
    }

    static void IdentityDocumentDelete(void* Object) {
        auto IdentityDocumentObjectPtr = static_cast<IdentityDocument*>(Object);
        delete(IdentityDocumentObjectPtr);
    }

    struct VTable {
        void (*PrintID)(const void*);
        void (*Delete)(void*);
    };

    static constexpr VTable vtable_obj{IdentityDocumentPrintID, IdentityDocumentDelete};
private:
    const VTable* v_table_ptr_{&vtable_obj};
    static inline int unique_id_count_;
    int unique_id_;

    void InnerPrintID() const {
        std::cout << "IdentityDocument::PrintID() : "sv << unique_id_ << std::endl;
    }
};
