#pragma once

namespace GB
{
	class Texture2D;

	class RendererAPI
	{
	public:
		enum class EAPI
		{
			None,
			SFML
		};

		virtual ~RendererAPI() = default;
		virtual void Initialize() = 0;
		virtual void DrawTexture(Texture2D* pTexture) = 0;
		virtual void Deinitialize() = 0;

		static UniquePtr<RendererAPI> Create(void* pWindow);

		static void SetAPI(const EAPI api)	{ s_API = api; }
		inline static const EAPI GetAPI()	{ return s_API; }

	private:
		static EAPI s_API;
	};
}