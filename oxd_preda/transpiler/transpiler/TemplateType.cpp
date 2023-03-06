#include "ConcreteType.h"
#include "TemplateType.h"

namespace transpiler {

	ConcreteTypePtr TemplateType::GetConcreteTypeFromTemplateParams(const std::vector<ConcreteTypePtr> &templateParams)
	{
		if (templateParams.size() != numExpectedTemplateParams)
			return nullptr;
		auto itor = instantiatedConcreteTypes.find(templateParams);
		if (itor != instantiatedConcreteTypes.end())
			return itor->second;

		ConcreteTypePtr instantiatedType = InstantiateTemplate(templateParams);
		if (instantiatedType)
		{
			if (!parentType->AttachInnerConcreteType(instantiatedType))
				return nullptr;

			instantiatedConcreteTypes.insert(std::make_pair(templateParams, instantiatedType));
		}
		return instantiatedType;
	}

}
