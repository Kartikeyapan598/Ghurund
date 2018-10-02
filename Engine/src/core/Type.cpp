#include "Type.h"
#include "graphics/Light.h"
#include "graphics/Camera.h"
#include "game/Scene.h"
#include "audio/Sound.h"

namespace Ghurund {
    const Type &Type::LIGHT = Type([]() {return ghnew Light(); }, _T("light"));
    const Type &Type::CAMERA = Type([]() {return ghnew Camera(); }, _T("camera"));
    const Type &Type::SCENE = Type([]() {return ghnew Scene(); }, _T("scene"));
    const Type &Type::SHADER = Type([]() {return ghnew Shader(); }, _T("shader"));
    const Type &Type::TEXTURE = Type([]() {return ghnew Texture(); }, _T("texture"));
    const Type &Type::MATERIAL = Type([]() {return ghnew Material(); }, _T("material"));
    const Type &Type::IMAGE = Type([]() {return ghnew Image(); }, _T("image"));
    const Type &Type::MODEL = Type([]() {return ghnew Model(); }, _T("model"));
    const Type &Type::MESH = Type([]() {return ghnew Mesh(); }, _T("mesh"));
    const Type &Type::SOUND = Type([]() {return ghnew Sound(); }, _T("sound"));
}