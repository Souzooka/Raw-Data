#ifndef WXFRAME_H
#define WXFRAME_H

//(*Headers(wxFrame)
#include <wx/frame.h>
//*)

class wxFrame: public wxFrame
{
	public:

		wxFrame(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~wxFrame();

		//(*Declarations(wxFrame)
		//*)

	protected:

		//(*Identifiers(wxFrame)
		//*)

	private:

		//(*Handlers(wxFrame)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
