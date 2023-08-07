#pragma once
#include <string>
#include <memory>

namespace kiko {

	class Resource
	{
	public:
		virtual ~Resource() = default;
		virtual bool Create(const std::string& filename, ...) = 0;
	};

	template <typename T>
	using res_t = std::shared_ptr<T>;
}