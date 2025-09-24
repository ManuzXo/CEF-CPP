#include "CefV8Override.h"

void CefV8Override::RegisterFunction(const CefString& name, CefRefPtr<CefV8Handler> handler) {
    m_functions[name] = handler;
}

bool CefV8Override::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) {
    auto it = m_functions.find(name);
    if (it != m_functions.end()) {
        return it->second->Execute(name, object, arguments, retval, exception);
    }
    exception = "Funzione non trovata: " + name.ToString();
    return false;
}
