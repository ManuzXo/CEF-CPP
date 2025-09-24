#include <windows.h>
#include "cefwrapper/CefAppOverride.h"
#include "cefwrapper/CefClientOverride.h"



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {

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

	CefRefPtr<CefClientOverride> g_client = new CefClientOverride(hInstance);
	g_client->Setup(L"Fantasia");
#if DEBUG
	g_client->Run("file:///C:/Users/emanu/Documents/Informatica/CEF-CPP/cef_binary/Resources/web/index.html");
	//g_client->Run("http://localhost:5173/");
#else 
	g_client->Run("https://google.com");
#endif
	return 0;
}

