#pragma once
#include "include/cef_v8.h"
class TestV8 : public CefV8Handler {
public:
    virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) override;
private:
    IMPLEMENT_REFCOUNTING(TestV8);
};