#pragma once
#include "include/cef_app.h"
class CefAppOverride : public CefApp {
public:
	CefAppOverride() {};
	~CefAppOverride() {};
	void OnBeforeCommandLineProcessing(
		const CefString& process_type,
		CefRefPtr<CefCommandLine> command_line) override
	{
		command_line->AppendSwitch("allow-file-access-from-files");
		command_line->AppendSwitch("disable-web-security");
	}

private:
	IMPLEMENT_REFCOUNTING(CefAppOverride);
};