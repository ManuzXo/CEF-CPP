#include "Application.h"
#include <string>
Application::Application(HINSTANCE hInstance, const wchar_t* appName, WndProcType fn)
    : m_hInstance(hInstance), m_appName(appName)
{
    std::wstring CLASS_NAME = std::wstring(appName) + L"CLASS";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = fn;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME.c_str();
    RegisterClassW(&wc);

    this->m_hwnd = CreateWindowExW(
        0,
        CLASS_NAME.c_str(),
        appName,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
        nullptr, nullptr, hInstance, nullptr
    );
}
Application::~Application(){
    m_hwnd = nullptr;
}
