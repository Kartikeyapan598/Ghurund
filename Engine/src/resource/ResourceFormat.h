#pragma once

#include "Ghurund.h"

namespace Ghurund {
    using namespace std;

    class ResourceFormat {
    private:
        const tchar* extension = nullptr;
        bool save, load;

        static const ResourceFormat* values[13];

    public:
        static const ResourceFormat& ENTITY,
            & SCENE,
            & HLSL, & SHADER,
            & JPG, & JPEG, & PNG,
            & MATERIAL,
            & MODEL,
            & MESH, & OBJ,
            & WAV,
            & SCRIPT;

        ResourceFormat() {
            extension = nullptr;
        }

        ResourceFormat(const tchar* extension, bool save, bool load) {
            this->extension = extension;
            this->save = save;
            this->load = load;
        }

        ResourceFormat(const ResourceFormat& format) {
            this->extension = format.extension;
            this->save = format.save;
            this->load = format.load;
        }

        static const ResourceFormat** getValues() {
            return values;
        }

        static const size_t getValueCount() {
            return sizeof(values) / sizeof(values[0]);
        }

        const tchar* getExtension() const {
            return extension;
        }

        bool canSave() const {
            return save;
        }

        bool canLoad() const {
            return load;
        }
    };
}
