#include <windows.h>
#include "cefwrapper/CefOverride.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
	CefRefPtr<CefOverride> g_client = new CefOverride(hInstance);
    if (g_client->Setup()) {
        g_client->Run("https://google.com");
    }
    return 0;
}
