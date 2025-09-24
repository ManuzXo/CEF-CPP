#pragma once
#include "include/cef_v8.h"
#include <map>

class CefV8Override : public CefV8Handler {
public:
	CefV8Override() {}
    void RegisterFunction(const CefString& name, CefRefPtr<CefV8Handler> handler);
    virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) override;
private:
    std::map<CefString, CefRefPtr<CefV8Handler>> m_functions;
    IMPLEMENT_REFCOUNTING(CefV8Override);
};