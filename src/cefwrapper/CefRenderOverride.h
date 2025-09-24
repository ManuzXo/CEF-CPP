#pragma once
#include "include/cef_app.h"
#include "include/cef_v8.h"
#include "CefV8Override.h"

class CefRenderOverride : public CefRenderProcessHandler {
public:
    CefRenderOverride() {}

    void OnContextCreated(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefV8Context> context) override
    {
        CefRefPtr<CefV8Value> global = context->GetGlobal();
        CefRefPtr<CefV8Override> handler = new CefV8Override();
        global->SetValue("TestV8", CefV8Value::CreateFunction("TestV8", handler), V8_PROPERTY_ATTRIBUTE_NONE);
    }

private:
    IMPLEMENT_REFCOUNTING(CefRenderOverride);
};