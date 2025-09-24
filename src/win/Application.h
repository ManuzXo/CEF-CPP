#pragma once
#include <windows.h>
#include <string>
class Application {
public:
	typedef LRESULT(CALLBACK* WndProcType)(HWND, UINT, WPARAM, LPARAM);
	Application(HINSTANCE hInstance, const wchar_t *appName, WndProcType fn);
	~Application();
	void Run();

	HINSTANCE GetHinstance() const { return m_hInstance; };
	std::wstring GetAppName() const { return m_appName; };
	HWND GetHwnd() const { return m_hwnd; };
private:
	HINSTANCE m_hInstance;
	std::wstring m_appName;
	HWND m_hwnd;
};