#pragma once
#include "include/cef_app.h"
#include "include/cef_v8.h"
#include "v8/CefV8Override.h"
#include "v8/TestV8.h"
class CefRenderOverride : public CefRenderProcessHandler {
public:
    CefRenderOverride() {}
    void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;
private:
    IMPLEMENT_REFCOUNTING(CefRenderOverride);
};