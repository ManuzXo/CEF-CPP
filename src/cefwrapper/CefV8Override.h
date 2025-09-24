#pragma once
#include "include/cef_v8.h"

class CefV8Override : public CefV8Handler {
public:
	CefV8Override() {}
    virtual bool Execute(const CefString& name,
        CefRefPtr<CefV8Value> object,
        const CefV8ValueList& arguments,
        CefRefPtr<CefV8Value>& retval,
        CefString& exception) override {
        if (name == "TestV8") {
            // Creiamo un oggetto JS
            CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(nullptr, nullptr);

            // Aggiungiamo delle chiavi/valori
            obj->SetValue("id", CefV8Value::CreateInt(123), V8_PROPERTY_ATTRIBUTE_NONE);
            obj->SetValue("name", CefV8Value::CreateString("CEF Example"), V8_PROPERTY_ATTRIBUTE_NONE);
            obj->SetValue("active", CefV8Value::CreateBool(true), V8_PROPERTY_ATTRIBUTE_NONE);

            // Oggetto annidato
            CefRefPtr<CefV8Value> nested = CefV8Value::CreateObject(nullptr, nullptr);
            nested->SetValue("version", CefV8Value::CreateString("1.0"), V8_PROPERTY_ATTRIBUTE_NONE);
            nested->SetValue("platform", CefV8Value::CreateString("Windows/Linux"), V8_PROPERTY_ATTRIBUTE_NONE);

            obj->SetValue("info", nested, V8_PROPERTY_ATTRIBUTE_NONE);

            // ritorniamo l'oggetto
            retval = obj;
            return true;
        }
        return false;
    }
private:
    IMPLEMENT_REFCOUNTING(CefV8Override);
};