#pragma once
#include <Windows.h>
#include "../win/Application.h"
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_life_span_handler.h"
#include "include/cef_browser.h"
#include "include/wrapper/cef_helpers.h"
class CefOverride : public CefClient, public CefLifeSpanHandler {
public:
	CefOverride(HINSTANCE hInstance);
    ~CefOverride();
    bool Setup();
	void Run(const char* url);

    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
        return this;
    }
 
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {
        CEF_REQUIRE_UI_THREAD();
        m_cefBrowser = browser;
    }

    void ResizeBrowser();
private:
	HINSTANCE m_hInstance;
    std::unique_ptr <Application>m_app;
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	CefRefPtr<CefApp> m_cefApp;
    CefSettings m_settings;
	CefWindowInfo m_windowInfo;
	CefBrowserSettings m_browserSettings;

	CefRefPtr<CefBrowser> m_cefBrowser;
    IMPLEMENT_REFCOUNTING(CefOverride);
};