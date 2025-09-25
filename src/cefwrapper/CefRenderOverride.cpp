#include "CefRenderOverride.h"

void CefRenderOverride::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context){
    CefRefPtr<CefV8Value> global = context->GetGlobal();
    CefRefPtr<CefV8Override> handler = new CefV8Override();

    handler->RegisterFunction("V8_Test", new TestV8());
    global->SetValue("V8_Test", CefV8Value::CreateFunction("V8_Test", handler), V8_PROPERTY_ATTRIBUTE_NONE);
}
