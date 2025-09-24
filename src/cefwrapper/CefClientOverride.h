#pragma once
#include <Windows.h>
#include "../win/Application.h"
#include "include/cef_client.h"
#include "include/cef_life_span_handler.h"
#include "include/cef_browser.h"
#include "include/wrapper/cef_helpers.h"
#include "CefAppOverride.h"

class CefClientOverride : public CefClient, public CefLifeSpanHandler {
public:
	CefClientOverride(HINSTANCE hInstance);
    ~CefClientOverride();

    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;

    void Setup(const wchar_t* appName);
	void Run(const char* url);
    void ResizeBrowser();
private:
	HINSTANCE m_hInstance;
    std::unique_ptr <Application>m_app;
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	CefRefPtr<CefAppOverride> m_cefApp;
	CefWindowInfo m_windowInfo;
	CefBrowserSettings m_browserSettings;

	CefRefPtr<CefBrowser> m_cefBrowser;
    IMPLEMENT_REFCOUNTING(CefClientOverride);
};