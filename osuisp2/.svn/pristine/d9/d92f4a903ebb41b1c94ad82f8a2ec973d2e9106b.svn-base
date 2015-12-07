/***************************************************************
 * Name:      widgetTestApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2010-06-19
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "widgetTestApp.h"

//(*AppHeaders
#include "widgetTestMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(widgetTestApp);

bool widgetTestApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	widgetTestFrame* Frame = new widgetTestFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
