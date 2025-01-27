#pragma once

#include "core/math/Size.h"
#include "ui/image/VectorImage.h"

#include <d2d1svg.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<ID2D1SvgDocument>();
}

namespace Ghurund::UI::Direct2D {
    using namespace Ghurund::Core;

    class SvgDocument:public Ghurund::UI::VectorImage {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

        static const Array<ResourceFormat>& GET_FORMATS();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        inline static const Array<ResourceFormat>& FORMATS = GET_FORMATS();

        virtual const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& getFormats() const override {
            return FORMATS;
        }

    private:
        ID2D1SvgDocument* svgDocument = nullptr;

    protected:
        virtual Status loadInternal(
            const Ghurund::Core::DirectoryPath& workingDir,
            Ghurund::Core::MemoryInputStream& stream,
            Ghurund::Core::LoadOption options
        );

        virtual Status saveInternal(
            const Ghurund::Core::DirectoryPath& workingDir,
            Ghurund::Core::MemoryOutputStream& stream,
            Ghurund::Core::SaveOption options
        ) const;

    public:
        ~SvgDocument() {
            finalize();
        }

        void finalize();

        virtual void invalidate() {
            finalize();
            svgDocument = nullptr;
            __super::invalidate();
        }

        virtual bool isValid() {
            return svgDocument != nullptr && __super::Valid;
        }

        inline ID2D1SvgDocument* getData() {
            return svgDocument;
        }

        __declspec(property(get = getData)) ID2D1SvgDocument* Data;

        Ghurund::Core::FloatSize getSize();

        __declspec(property(get = getSize)) Ghurund::Core::FloatSize Size;
    };
}