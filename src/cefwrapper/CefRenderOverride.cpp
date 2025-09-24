#include "CefRenderOverride.h"

void CefRenderOverride::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context){
    CefRefPtr<CefV8Value> global = context->GetGlobal();
    CefRefPtr<CefV8Override> handler = new CefV8Override();

    handler->RegisterFunction("TestV8", new TestV8());
    global->SetValue("TestV8", CefV8Value::CreateFunction("TestV8", handler), V8_PROPERTY_ATTRIBUTE_NONE);
}
