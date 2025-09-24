#include "CefOverride.h"

CefOverride::CefOverride(HINSTANCE hInstance) {
	this->m_hInstance = hInstance;
}
CefOverride::~CefOverride() {

}

bool CefOverride::Setup()
{

	CefMainArgs main_args(this->m_hInstance);
	m_cefApp = nullptr;
	int exit_code = CefExecuteProcess(main_args, m_cefApp, nullptr);
	if (exit_code >= 0) {
		return false;
	}

	m_settings.no_sandbox = true;
	m_settings.multi_threaded_message_loop = true;
	CefInitialize(main_args, m_settings, m_cefApp, nullptr);

	this->m_app = std::make_unique<Application>(this->m_hInstance, L"CefOverrideApp", &WndProc);
	auto hwndApp = this->m_app->GetHwnd();
	// Salva il puntatore all’istanza in GWLP_USERDATA
	SetWindowLongPtr(hwndApp, GWLP_USERDATA, (LONG_PTR)this);

	RECT rect;
	GetClientRect(hwndApp, &rect);
	CefRect cefRect(0, 0, rect.right - rect.left, rect.bottom - rect.top);
	m_windowInfo.SetAsChild(hwndApp, cefRect);
	return true;
}

void CefOverride::Run(const char* url)
{
	CefBrowserHost::CreateBrowser(
		m_windowInfo,
		this,
		url,
		m_browserSettings,
		nullptr,
		nullptr);
	this->m_app->Run();
	CefShutdown();
}
void CefOverride::ResizeBrowser() {
	if (m_cefBrowser) {
		HWND browser_hwnd = m_cefBrowser->GetHost()->GetWindowHandle();
		if (browser_hwnd) {
			auto hwndApp = this->m_app->GetHwnd();
			RECT rect;
			GetClientRect(hwndApp, &rect);
			SetWindowPos(browser_hwnd, nullptr,
				0, 0,
				rect.right - rect.left,
				rect.bottom - rect.top,
				SWP_NOZORDER);
		}
	}
}
LRESULT CALLBACK CefOverride::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_SIZE:
	{
		CefOverride* cefApp = (CefOverride*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (cefApp) {
			cefApp->ResizeBrowser();
		}
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}