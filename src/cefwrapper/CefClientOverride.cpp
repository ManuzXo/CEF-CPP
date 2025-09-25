#include "CefClientOverride.h"


CefRefPtr<CefLifeSpanHandler> CefClientOverride::GetLifeSpanHandler() {
	return this;
}

void CefClientOverride::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	m_cefBrowser = browser;
#if DEBUG
	CefWindowInfo devtools_window_info;
	CefBrowserSettings devtools_settings;
	devtools_window_info.SetAsPopup(nullptr, "DevTools");
	browser->GetHost()->ShowDevTools(devtools_window_info, nullptr, devtools_settings, CefPoint());
#endif
}

void CefClientOverride::Setup()
{
	SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
	RECT rect;
	GetClientRect(m_hwnd, &rect);
	CefRect cefRect(0, 0, rect.right - rect.left, rect.bottom - rect.top);
	m_windowInfo.SetAsChild(m_hwnd, cefRect);
}

void CefClientOverride::Run(const char* url)
{
	CefBrowserHost::CreateBrowser(
		m_windowInfo,
		this,
		url,
		m_browserSettings,
		nullptr,
		nullptr);
	MSG msg;
	if (m_cefSettings.multi_threaded_message_loop) {
		// CEF gestisce il suo loop da solo.
		// Se hai una finestra, tieni un loop messaggi standard.
		while (GetMessage(&msg, nullptr, 0, 0) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	else {
		// Devi tu gestire il loop di CEF.
		// Variante semplice: blocca qui finché non chiami CefQuitMessageLoop().
		CefRunMessageLoop();
		// Oppure, se vuoi controllo esplicito:
		// while (GetMessage(&msg, nullptr, 0, 0) > 0) {
		//     TranslateMessage(&msg);
		//     DispatchMessage(&msg);
		//     CefDoMessageLoopWork();
		// }
		// CefShutdown();
	}
	CefShutdown();
}

void CefClientOverride::ResizeBrowser() {
	if (m_cefBrowser) {
		HWND browser_hwnd = m_cefBrowser->GetHost()->GetWindowHandle();
		if (browser_hwnd) {
			RECT rect;
			GetClientRect(m_hwnd, &rect);
			SetWindowPos(browser_hwnd, nullptr,
				0, 0,
				rect.right - rect.left,
				rect.bottom - rect.top,
				SWP_NOZORDER);
		}
	}
}
LRESULT CALLBACK CefClientOverride::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	CefClientOverride* cefApp = (CefClientOverride*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	switch (msg) {
	case WM_SIZE:
	{
		if (cefApp)
			cefApp->ResizeBrowser();
	}
	break;
	case WM_CLOSE:
		if (cefApp) {
			if (cefApp->m_cefSettings.multi_threaded_message_loop)
				PostQuitMessage(0);
			else
				CefQuitMessageLoop();
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}