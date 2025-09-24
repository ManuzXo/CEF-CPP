#include <windows.h>
#include "cefwrapper/CefOverride.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
	CefRefPtr<CefOverride> g_client = new CefOverride(hInstance);
    if (g_client->Setup()) {
#if DEBUG
        g_client->Run("file:///C:/Users/e.rispoli/Documents/cpp/CEF_CPP/cef_binary/Resources/web/index.html");
        //g_client->Run("http://localhost:5173/");
#else 
        g_client->Run("https://google.com");
#endif
    }
    return 0;
}

