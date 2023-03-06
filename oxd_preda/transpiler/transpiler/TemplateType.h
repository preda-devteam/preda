#pragma once
#include <vector>
#include <string>
#include <map>
#include <memory>
#include "ConcreteType.h"

namespace transpiler {

	// A template type is abstract and accepts template parameters to get instantiated into a concrete type
	struct TemplateType
	{
	public:
		std::string inputName;				// e.g. "mapping", "[]".
		// There's no need to define an outputName for template types because they are instantiated to concrete types.
		// The output name is specified during instantiation.

		size_t numExpectedTemplateParams;	// number of template parameters expected by this type
		std::map<std::vector<ConcreteTypePtr>, ConcreteTypePtr> instantiatedConcreteTypes;		//the concrete types that are instantiated from this template type. Kept for reuse.
		ConcreteTypePtr parentType;																			// Parent type

		// Get the corresponding concrete type of this template type, given the template parameters.
		// If bCreateIfNotExist is true, a new concrete type will be instantiated from this template type if not already.
		ConcreteTypePtr GetConcreteTypeFromTemplateParams(const std::vector<ConcreteTypePtr> &templateParams);

		// implemented by each template to do the actually instantiation
		virtual ConcreteTypePtr InstantiateTemplate(const std::vector<ConcreteTypePtr> &templateParams) = 0;
	};

}
