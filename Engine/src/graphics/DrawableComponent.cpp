#include "DrawableComponent.h"

namespace Ghurund {
	const Ghurund::Type& DrawableComponent::TYPE = Ghurund::Type([]() {return ghnew DrawableComponent(); }, "DrawableComponent");

	Status DrawableComponent::loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
		Status result;
		mesh = (Ghurund::Mesh*)context.ResourceManager.load(context, workingDir, stream, &result, options);
		if (filterStatus(result, options) != Status::OK)
			return result;

		material = (Ghurund::Material*)context.ResourceManager.load(context, workingDir, stream, &result, options);

		initParameters(context.ParameterManager);

		return filterStatus(result, options);
	}

	Status DrawableComponent::saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
		if (mesh == nullptr)
			return Logger::log(LogType::ERR0R, Status::INV_STATE, _T("Mesh cannot be empty"));

		if (material == nullptr)
			return Logger::log(LogType::ERR0R, Status::INV_STATE, _T("Material cannot be empty"));

		Status result;
		result = context.ResourceManager.save(*mesh, context, workingDir, stream, options);
		if (filterStatus(result, options) != Status::OK)
			return result;
		result = context.ResourceManager.save(*material, context, workingDir, stream, options);
		return filterStatus(result, options);
	}
}