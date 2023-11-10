#pragma once
#include <stdexcept>
#include <string>
#include "runtime_interface.h"

namespace prlrt {

	class preda_exception : public std::runtime_error {
	private:
		ExceptionType id;
	public:
		explicit preda_exception(const std::string& _Message, ExceptionType _Id) noexcept
			: std::runtime_error(_Message)
			, id(_Id)
		{
		}

		void operator= (const preda_exception& rhs) noexcept
		{
			*(std::runtime_error*) this = *(std::runtime_error*)&rhs;
			id = rhs.id;
		}

		ExceptionType type() const noexcept
		{
			return id;
		}

		static void throw_exception(const std::string& _Message, ExceptionType _Id)
		{
#if defined(__wasm32__)
			PREDA_CALL(Event_Exception, _Message.data(), _Id);
#endif
			throw preda_exception(_Message.data(), _Id);
		}
	};

}
