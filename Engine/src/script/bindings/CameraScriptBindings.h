#pragma once

#include "ScriptBindings.h"
#include "graphics/entity/Camera.h"

namespace Ghurund {

    class CameraScriptBindings:ScriptBindings<Camera> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<Camera>::registerRefClass(engine, Camera::TYPE.Name);

            auto r = engine.RegisterObjectMethod(Camera::TYPE.Name, "bool getPerspective() const", asMETHOD(Camera, getPerspective), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod(Camera::TYPE.Name, "void setPerspective(bool pers)", asMETHOD(Camera, setPerspective), asCALL_THISCALL); assert(r >= 0);

            r = engine.RegisterObjectMethod(Camera::TYPE.Name, "void setPositionTargetUp(const float3 pos, const float3 target, const float3 up = float3(0, 1, 0))", asMETHOD(Camera, setPositionTargetUp), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod(Camera::TYPE.Name, "void setPositionDirectionDistanceUp(const float3 pos, const float3 dir, float dist = 1, const float3 up = float3(0, 1, 0))", asMETHOD(Camera, setPositionDirectionDistanceUp), asCALL_THISCALL); assert(r >= 0);

            r = engine.RegisterObjectMethod(Camera::TYPE.Name, "float3 getRotation() const", asMETHOD(Camera, getRotation), asCALL_THISCALL); assert(r >= 0);

            r = engine.RegisterObjectMethod(Camera::TYPE.Name, "void setRotation(float yaw, float pitch, float roll=0)", asMETHOD(Camera, setRotation), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod(Camera::TYPE.Name, "void setOrbit(float yaw, float pitch, float roll=0)", asMETHOD(Camera, setOrbit), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod(Camera::TYPE.Name, "void rotate(float yaw, float pitch, float roll=0)", asMETHOD(Camera, rotate), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod(Camera::TYPE.Name, "void orbit(float yaw, float pitch, float roll=0)", asMETHOD(Camera, orbit), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod(Camera::TYPE.Name, "void pan(float x, float y)", asMETHOD(Camera, pan), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod(Camera::TYPE.Name, "void zoom(float z)", asMETHOD(Camera, zoom), asCALL_THISCALL); assert(r >= 0);
        }
    };

}