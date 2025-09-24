#pragma once
#include "include/cef_app.h"
#include "CefRenderOverride.h"
class CefAppOverride : public CefApp {
public:
	CefAppOverride(HINSTANCE hInstance) : m_hInstance(hInstance) {};
	~CefAppOverride() {};

	CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override {
		return new CefRenderOverride();
	}

	void OnBeforeCommandLineProcessing(
		const CefString& process_type,
		CefRefPtr<CefCommandLine> command_line) override
	{
		command_line->AppendSwitch("allow-file-access-from-files");
		command_line->AppendSwitch("disable-web-security");
	}

private:
	HINSTANCE m_hInstance;
	IMPLEMENT_REFCOUNTING(CefAppOverride);
};