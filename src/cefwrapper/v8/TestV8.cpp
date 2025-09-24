#include "TestV8.h"

bool TestV8::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(nullptr, nullptr);
    obj->SetValue("id", CefV8Value::CreateInt(123), V8_PROPERTY_ATTRIBUTE_NONE);
    obj->SetValue("name", CefV8Value::CreateString("CEF Example"), V8_PROPERTY_ATTRIBUTE_NONE);
    obj->SetValue("active", CefV8Value::CreateBool(true), V8_PROPERTY_ATTRIBUTE_NONE);

    CefRefPtr<CefV8Value> nested = CefV8Value::CreateObject(nullptr, nullptr);
    nested->SetValue("version", CefV8Value::CreateString("1.0"), V8_PROPERTY_ATTRIBUTE_NONE);
    nested->SetValue("platform", CefV8Value::CreateString("Windows/Linux"), V8_PROPERTY_ATTRIBUTE_NONE);

    obj->SetValue("info", nested, V8_PROPERTY_ATTRIBUTE_NONE);
    retval = obj;
    return true;
}
