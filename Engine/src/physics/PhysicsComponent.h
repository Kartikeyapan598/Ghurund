#pragma once

#include "ecs/Component.h"
#include "game/TransformComponent.h"
#include "physics/Physics.h"

#pragma warning(push, 0)
#include <PxShape.h>
#pragma warning(pop)

namespace Ghurund {
	using namespace physx;

	class PhysicsComponent :public Component {
	private:
		TransformComponent& transformComponent;
		PxShape* shape = nullptr;

		void finalize() {
			safeRelease2(shape);
		}

	protected:
		virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
			return Status::OK;
		}

		virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
			return Status::OK;
		}

	public:
		PhysicsComponent(TransformComponent& transform) :transformComponent(transform) {}

		PxShape* getShape() {
			return shape;
		}

		void setShape(PxShape* shape) {
			setPointer2(this->shape, shape);
		}

		__declspec(property(get = getShape, put = setShape)) PxShape* Shape;

		const static Ghurund::Type& TYPE;

		virtual const Ghurund::Type& getType() const override {
			return TYPE;
		}
	};
}