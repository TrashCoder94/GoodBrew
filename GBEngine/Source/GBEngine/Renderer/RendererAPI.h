#pragma once

namespace GB
{
	class RendererAPI
	{
	public:
		enum class EAPI
		{
			None,
			BGFX
		};

		static void SetAPI(const EAPI api)	{ s_API = api; }
		inline static const EAPI GetAPI()	{ return s_API; }

	private:
		static EAPI s_API;
	};
}