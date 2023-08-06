#pragma once

namespace GB
{
	struct WindowProperties
	{
		std::string m_Title;
		uint32_t m_Width;
		uint32_t m_Height;

		WindowProperties(const std::string& title = "GBEngine",
			uint32_t width = 1600,
			uint32_t height = 900) :
			m_Title(title),
			m_Width(width),
			m_Height(height)
		{}
	};

	class Window
	{
	public:
		static UniquePtr<Window> Create(const WindowProperties& properties = WindowProperties());
		
		Window(const WindowProperties& properties);
		~Window();

		void Begin();
		void Update();
		void End();
		
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void* GetNativeWindow() const = 0;

	protected:
		virtual void Init(const WindowProperties& properties) = 0;
		virtual void OnBegin() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEnd() = 0;
		virtual void Shutdown() = 0;
	};
}
