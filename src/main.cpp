#include <windows.h>
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_life_span_handler.h"
#include "include/cef_browser.h"
#include "include/wrapper/cef_helpers.h"
class SimpleClient : public CefClient, public CefLifeSpanHandler {
public:
    SimpleClient(HWND parent) : hwnd_(parent) {}

    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
        return this;
    }

    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {
        CEF_REQUIRE_UI_THREAD();
        browser_ = browser;
    }

    // funzione helper per il resize
    void ResizeBrowser() {
        if (browser_) {
            HWND browser_hwnd = browser_->GetHost()->GetWindowHandle();
            if (browser_hwnd) {
                RECT rect;
                GetClientRect(hwnd_, &rect);
                SetWindowPos(browser_hwnd, nullptr,
                    0, 0,
                    rect.right - rect.left,
                    rect.bottom - rect.top,
                    SWP_NOZORDER);
            }
        }
    }

private:
    HWND hwnd_;
    CefRefPtr<CefBrowser> browser_;
    IMPLEMENT_REFCOUNTING(SimpleClient);
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Variabile globale per il client
CefRefPtr<SimpleClient> g_client;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
    CefMainArgs main_args(hInstance);
    CefRefPtr<CefApp> app = nullptr;
    int exit_code = CefExecuteProcess(main_args, app, nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }

    CefSettings settings;
    settings.no_sandbox = true;
    settings.multi_threaded_message_loop = true;
    CefInitialize(main_args, settings, app, nullptr);

    const wchar_t CLASS_NAME[] = L"MyCEFFenster";
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"CEF Browser",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
        nullptr, nullptr, hInstance, nullptr
    );

    RECT rect;
    GetClientRect(hwnd, &rect);
    CefRect cefRect(0, 0, rect.right - rect.left, rect.bottom - rect.top);

    CefWindowInfo window_info;
    window_info.SetAsChild(hwnd, cefRect);

    CefBrowserSettings browser_settings;
    g_client = new SimpleClient(hwnd);

    CefBrowserHost::CreateBrowser(
        window_info,
        g_client,
        "https://www.google.com",
        browser_settings,
        nullptr,
        nullptr);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CefShutdown();
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_SIZE:
        if (g_client)
            g_client->ResizeBrowser();
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
