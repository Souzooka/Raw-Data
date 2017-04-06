#include "wxFrame.h"

//(*InternalHeaders(wxFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(wxFrame)
//*)

BEGIN_EVENT_TABLE(wxFrame,wxFrame)
	//(*EventTable(wxFrame)
	//*)
END_EVENT_TABLE()

wxFrame::wxFrame(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(wxFrame)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	//*)
}

wxFrame::~wxFrame()
{
	//(*Destroy(wxFrame)
	//*)
}

