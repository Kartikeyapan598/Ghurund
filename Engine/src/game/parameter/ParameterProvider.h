#pragma once

#include "ParameterManager.h"
#include "collection/Array.h"

namespace Ghurund {
    class ParameterProvider {
    public:
        virtual ~ParameterProvider() = default;

        virtual void initParameters(ParameterManager& parameterManager) {}

        virtual void updateParameters() {}

        virtual Array<Parameter*>& getParameters() = 0;

        __declspec(property(get = getParameters)) Array<Parameter*>& Parameters;

        Parameter* getParameter(const ASCIIString& name) {
            for (Parameter* p : Parameters) {
                if (p != nullptr && p->Name == name)
                    return p;
            }

            return nullptr;
        }
    };
}