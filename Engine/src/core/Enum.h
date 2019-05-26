#pragma once

#include "Noncopyable.h"
#include "collection/Map.h"

namespace Ghurund {

    template<class Type, class Type2>
    class Enum;

    template<class Type, class Type2>
    class EnumValues:public Noncopyable {
    private:
        Map<Type, Type2*> values;
        Map<tchar*, Type2*> valuesByName;

        EnumValues(const std::initializer_list<const Type2*> list) {
            for (auto it = list.begin(); it != list.end(); ++it) {
                values.set((*it)->Value, (Type2*)(*it));
                valuesByName.set((tchar*)(*it)->Name, (Type2*)(*it));
            }
        }

    public:
        friend class Enum<Type, Type2>;
        friend typename Type2;

        inline const Type2& operator[](const Type& key) const {
            return *values.get(key);
        }

        inline const Type2& operator[](const size_t index) const {
            return *values.getValue(index);
        }

        inline const Type2& operator[](const tchar* name) const {
            return *valuesByName.get(name);
        }

        inline size_t getSize() const {
            return values.Size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline Type2* begin() {
            return values.begin();
        }

        inline Type2* end() {
            return values.end();
        }
    };

    template<class Type, class Type2>
    class Enum {
    private:
        Type value;
        const tchar* name;

    protected:
        Enum(Type value, const tchar* name) {
            this->value = value;
            this->name = name;
        }

    public:
        static EnumValues<Type, Type2> VALUES;

        EnumValues<Type, Type2>& getValues() const {
            return VALUES;
        }

        __declspec(property(get = getValues)) EnumValues<Type, Type2>& Values;

        inline Type getValue() const {
            return value;
        }

        __declspec(property(get = getValue)) Type Value;

        inline const tchar* getName() const {
            return name;
        }

        __declspec(property(get = getName)) const tchar* Name;

        inline bool operator==(const Enum& type) const {
            return this->value == type.value;
        }

        inline bool operator==(const Enum& type) {
            return this->value == type.value;
        }
    };
}