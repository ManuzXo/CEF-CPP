#pragma once
#include <Windows.h>
#include "include/cef_client.h"
#include "include/cef_life_span_handler.h"
#include "include/cef_browser.h"
#include "include/wrapper/cef_helpers.h"
#include "CefAppOverride.h"

class CefClientOverride : public CefClient, public CefLifeSpanHandler {
public:
    CefClientOverride(HINSTANCE hInstance, HWND hwnd) : m_hInstance(hInstance), m_hwnd(hwnd) {};
    ~CefClientOverride() {};

    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;

    void Setup();
	void Run(const char* url);
    void ResizeBrowser();
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	HINSTANCE m_hInstance;
    HWND m_hwnd;
	CefWindowInfo m_windowInfo;
	CefBrowserSettings m_browserSettings;

	CefRefPtr<CefBrowser> m_cefBrowser;
    IMPLEMENT_REFCOUNTING(CefClientOverride);
};