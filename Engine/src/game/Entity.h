#pragma once

#include "collection/String.h"
#include "ParameterProvider.h"
#include "ParameterManager.h"
#include "collection/List.h"
#include "resource/Resource.h"
#include "core/NamedObject.h"
#include "BoundingBox.h"

namespace Ghurund {

    enum class EntityType {
        CAMERA, LIGHT, TARGET, UNKNOWN
    };

    class Entity: public Resource, public ParameterProvider, public NamedObject {
    private:
        XMFLOAT3 position = {}, rotation = {}, scale = {1,1,1};
        BoundingBox localBoundingBox, boundingBox;
        XMFLOAT4X4 world;

        Parameter *parameterPosition, *parameterRotation, *parameterScale, *parameterWorld;

        EntityType type;

    protected:
        List<Entity*> subentities;

        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size) {
            return Status::NOT_IMPLEMENTED;
        }

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size)const {
            return Status::NOT_IMPLEMENTED;
        }

        virtual void clean() {}

    public:
        virtual ~Entity() = default;

        virtual void initParameters(ParameterManager &parameterManager) override {
            for(Entity *e:subentities)
                e->initParameters(parameterManager);
            parameterPosition = parameterManager.add(Parameter::POSITION, ParameterType::FLOAT3);
            parameters.add(parameterPosition);
            parameterRotation = parameterManager.add(Parameter::ROTATION, ParameterType::FLOAT3);
            parameters.add(parameterRotation);
            parameterScale = parameterManager.add(Parameter::SCALE, ParameterType::FLOAT3);
            parameters.add(parameterScale);
            parameterWorld = parameterManager.add(Parameter::WORLD, ParameterType::MATRIX);
            parameters.add(parameterWorld);
        }

        virtual void fillParameters() override {
            for(Entity *e:subentities)
                e->fillParameters();
            parameterPosition->setValue(&position);
            parameterRotation->setValue(&rotation);
            parameterScale->setValue(&scale);
            XMStoreFloat4x4(&world, XMMatrixScaling(scale.x, scale.y, scale.z)*XMMatrixRotationRollPitchYaw(rotation.y, rotation.x, rotation.z)*XMMatrixTranslation(position.x, position.y, position.z));
            parameterWorld->setValue(&world);
        }

        virtual EntityType getType() const {
            return EntityType::UNKNOWN;
        }

        __declspec(property(get = getType)) EntityType Type;

        void setPosition(const XMFLOAT3 &pos) {
            this->position = pos;
        }

        void setPosition(float x, float y, float z) {
            this->position.x = x;
            this->position.y = y;
            this->position.z = z;
        }

        inline const XMFLOAT3 &getPosition()const {
            return position;
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT3 &Position;

        void setRotation(const XMFLOAT3 &rotation) {
            this->rotation = rotation;
        }

        void setRotation(float yaw, float pitch, float roll) {
            this->rotation.x = yaw;
            this->rotation.y = pitch;
            this->rotation.z = roll;
        }

        inline const XMFLOAT3 &getRotation()const {
            return rotation;
        }

        __declspec(property(get = getRotation, put = setRotation)) XMFLOAT3 &Rotation;

        void setScale(const XMFLOAT3 &scale) {
            this->scale = scale;
        }

        void setScale(float x, float y, float z) {
            this->scale.x = x;
            this->scale.y = y;
            this->scale.z = z;
        }

        inline const XMFLOAT3 &getScale()const {
            return scale;
        }

        __declspec(property(get = getScale, put = setScale)) XMFLOAT3 &Scale;

        List<Entity*> &getSubentities() {
            return subentities;
        }

        __declspec(property(get = getSubentities)) List<Entity*> &Subentities;

        BoundingBox &getBoundingBox() {
            return boundingBox;
        }

        __declspec(property(get = getBoundingBox)) BoundingBox &BoundingBox;
    };
}