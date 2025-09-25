#include <Windows.h>
#include "cefwrapper/CefAppOverride.h"
#include "cefwrapper/CefClientOverride.h"
#include "win/Application.h"
int InitCef(HINSTANCE hInstance) {
	CefMainArgs main_args(hInstance);
	CefRefPtr<CefAppOverride> app = new CefAppOverride(hInstance);

	int exit_code = CefExecuteProcess(main_args, app, nullptr);
	if (exit_code >= 0) {
		return exit_code;
	}
	CefSettings settings;
	settings.no_sandbox = true;
	settings.multi_threaded_message_loop = true;
	CefInitialize(main_args, settings, app, nullptr);

	std::unique_ptr <Application>m_app = std::make_unique<Application>(hInstance, L"Fantasia", &CefClientOverride::WndProc);
	CefRefPtr<CefClientOverride> g_client = new CefClientOverride(hInstance, m_app->GetHwnd());
	g_client->Setup();
#if DEBUG
	g_client->Run("file:///C:/Users/emanu/Documents/Informatica/CEF-CPP/cef_binary/Resources/web/index.html");
	//g_client->Run("http://localhost:5173/");
#else 
	g_client->Run("https://google.com");
#endif
	return 0;
}


#ifdef BUILD_DLL
// ===== DLL MODE =====
DWORD WINAPI MainThread(LPVOID lpParam)
{
	HINSTANCE hModule = (HINSTANCE)lpParam;

	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	return InitCef(hModule);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hinstDLL);
		CreateThread(nullptr, 0, MainThread, hinstDLL, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#else
// ===== EXE MODE =====
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
	return InitCef(hInstance);
}
#endif