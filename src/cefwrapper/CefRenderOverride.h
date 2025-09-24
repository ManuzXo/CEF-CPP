#pragma once
#include "include/cef_app.h"
#include "include/cef_v8.h"
#include "v8/CefV8Override.h"
#include "v8/TestV8.h"
class CefRenderOverride : public CefRenderProcessHandler {
public:
    CefRenderOverride() {}

    void OnContextCreated(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefV8Context> context) override
    {
        CefRefPtr<CefV8Value> global = context->GetGlobal();
        CefRefPtr<CefV8Override> handler = new CefV8Override();

        handler->RegisterFunction("TestV8", new TestV8());
        global->SetValue("TestV8", CefV8Value::CreateFunction("TestV8", handler), V8_PROPERTY_ATTRIBUTE_NONE);
    }

private:
    IMPLEMENT_REFCOUNTING(CefRenderOverride);
};