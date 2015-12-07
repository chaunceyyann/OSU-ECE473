/***************************************************************
 * Name:      widgetTestMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2010-06-19
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "widgetTestMain.h"
#include <wx/msgdlg.h>


#include "Tiny26Interface.h"


//(*InternalHeaders(widgetTestFrame)
#include <wx/bitmap.h>
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

USBDevice device;
volatile unsigned char busy = 0;
void BeginBusy()
{
    while (busy){}
    busy = 1;
}
void EndBusy()
{
    busy = 0;
}

//(*IdInit(widgetTestFrame)
const long widgetTestFrame::ID_STATICBITMAP11 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX47 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX48 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX49 = wxNewId();
const long widgetTestFrame::ID_PANEL13 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP2 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX25 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX26 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX27 = wxNewId();
const long widgetTestFrame::ID_PANEL2 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP10 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX44 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX45 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX46 = wxNewId();
const long widgetTestFrame::ID_PANEL12 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP3 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX28 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX29 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX30 = wxNewId();
const long widgetTestFrame::ID_PANEL3 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP12 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX50 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX51 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX52 = wxNewId();
const long widgetTestFrame::ID_PANEL14 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP4 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX2 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX4 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX6 = wxNewId();
const long widgetTestFrame::ID_PANEL4 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP9 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX41 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX42 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX43 = wxNewId();
const long widgetTestFrame::ID_PANEL9 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP8 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX16 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX17 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX18 = wxNewId();
const long widgetTestFrame::ID_PANEL8 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP16 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX62 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX63 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX64 = wxNewId();
const long widgetTestFrame::ID_PANEL18 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP7 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX13 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX14 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX15 = wxNewId();
const long widgetTestFrame::ID_PANEL7 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP15 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX59 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX60 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX61 = wxNewId();
const long widgetTestFrame::ID_PANEL17 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP6 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX10 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX11 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX12 = wxNewId();
const long widgetTestFrame::ID_PANEL6 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP14 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX56 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX57 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX58 = wxNewId();
const long widgetTestFrame::ID_PANEL16 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP5 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX7 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX8 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX9 = wxNewId();
const long widgetTestFrame::ID_PANEL5 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP13 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX53 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX54 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX55 = wxNewId();
const long widgetTestFrame::ID_PANEL15 = wxNewId();
const long widgetTestFrame::ID_STATICBITMAP1 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX1 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX3 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX5 = wxNewId();
const long widgetTestFrame::ID_PANEL1 = wxNewId();
const long widgetTestFrame::ID_BUTTON2 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT6 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT5 = wxNewId();
const long widgetTestFrame::ID_SLIDER3 = wxNewId();
const long widgetTestFrame::ID_SLIDER2 = wxNewId();
const long widgetTestFrame::ID_SLIDER1 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT7 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT4 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT8 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX33 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX34 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX35 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX36 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX37 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX38 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX39 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX40 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX19 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX20 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX23 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX24 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX31 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX32 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX21 = wxNewId();
const long widgetTestFrame::ID_CHECKBOX22 = wxNewId();
const long widgetTestFrame::ID_PANEL19 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT17 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT24 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT23 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT22 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT21 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT20 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT19 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT18 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT10 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT16 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT15 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT14 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT13 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT12 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT11 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT9 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT1 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT2 = wxNewId();
const long widgetTestFrame::ID_STATICTEXT3 = wxNewId();
const long widgetTestFrame::ID_GAUGE1 = wxNewId();
const long widgetTestFrame::ID_RADIOBUTTON1 = wxNewId();
const long widgetTestFrame::ID_RADIOBUTTON2 = wxNewId();
const long widgetTestFrame::ID_RADIOBUTTON3 = wxNewId();
const long widgetTestFrame::ID_RADIOBUTTON5 = wxNewId();
const long widgetTestFrame::ID_RADIOBUTTON6 = wxNewId();
const long widgetTestFrame::ID_RADIOBUTTON7 = wxNewId();
const long widgetTestFrame::ID_RADIOBUTTON8 = wxNewId();
const long widgetTestFrame::ID_PANEL10 = wxNewId();
const long widgetTestFrame::idMenuQuit = wxNewId();
const long widgetTestFrame::idMenuAbout = wxNewId();
const long widgetTestFrame::ID_STATUSBAR1 = wxNewId();
const long widgetTestFrame::ID_TIMER1 = wxNewId();
const long widgetTestFrame::ID_TIMER2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(widgetTestFrame,wxFrame)
    //(*EventTable(widgetTestFrame)
    //*)
END_EVENT_TABLE()

widgetTestFrame::widgetTestFrame(wxWindow* parent,wxWindowID id)
{
    EndBusy();
    //(*Initialize(widgetTestFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(592,446));
    SetMinSize(wxSize(600,480));
    SetMaxSize(wxSize(600,480));
    SetForegroundColour(wxColour(255,255,255));
    SetBackgroundColour(wxColour(255,255,255));
    Panel12 = new wxPanel(this, ID_PANEL13, wxPoint(8,120), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL13"));
    Panel12->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap11 = new wxStaticBitmap(Panel12, ID_STATICBITMAP11, wxBitmap(wxImage(_T("images\\buffer.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP11"));
    StaticBitmap11->SetMinSize(wxSize(43,26));
    StaticBitmap11->SetMaxSize(wxSize(43,26));
    PORTB2 = new wxCheckBox(Panel12, ID_CHECKBOX47, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX47"));
    PORTB2->SetValue(false);
    PORTB2->SetMinSize(wxSize(20,20));
    PORTB2->SetMaxSize(wxSize(20,20));
    PORTB2->Disable();
    PINB2 = new wxCheckBox(Panel12, ID_CHECKBOX48, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX48"));
    PINB2->SetValue(false);
    PINB2->Disable();
    DDRB2 = new wxCheckBox(Panel12, ID_CHECKBOX49, wxEmptyString, wxPoint(31,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX49"));
    DDRB2->SetValue(false);
    DDRB2->Disable();
    Panel1 = new wxPanel(this, ID_PANEL2, wxPoint(472,120), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Panel1->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap2 = new wxStaticBitmap(Panel1, ID_STATICBITMAP2, wxBitmap(wxImage(_T("images\\buffer2.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP2"));
    StaticBitmap2->SetMinSize(wxSize(43,26));
    StaticBitmap2->SetMaxSize(wxSize(43,26));
    PORTA2 = new wxCheckBox(Panel1, ID_CHECKBOX25, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX25"));
    PORTA2->SetValue(false);
    PORTA2->SetMinSize(wxSize(20,20));
    PORTA2->SetMaxSize(wxSize(20,20));
    PINA2 = new wxCheckBox(Panel1, ID_CHECKBOX26, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX26"));
    PINA2->SetValue(false);
    PINA2->Disable();
    DDRA2 = new wxCheckBox(Panel1, ID_CHECKBOX27, wxEmptyString, wxPoint(25,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX27"));
    DDRA2->SetValue(false);
    Panel11 = new wxPanel(this, ID_PANEL12, wxPoint(8,72), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL12"));
    Panel11->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap10 = new wxStaticBitmap(Panel11, ID_STATICBITMAP10, wxBitmap(wxImage(_T("images\\buffer.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP10"));
    StaticBitmap10->SetMinSize(wxSize(43,26));
    StaticBitmap10->SetMaxSize(wxSize(43,26));
    PORTB1 = new wxCheckBox(Panel11, ID_CHECKBOX44, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX44"));
    PORTB1->SetValue(false);
    PORTB1->SetMinSize(wxSize(20,20));
    PORTB1->SetMaxSize(wxSize(20,20));
    PORTB1->Disable();
    PINB1 = new wxCheckBox(Panel11, ID_CHECKBOX45, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX45"));
    PINB1->SetValue(false);
    PINB1->Disable();
    DDRB1 = new wxCheckBox(Panel11, ID_CHECKBOX46, wxEmptyString, wxPoint(31,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX46"));
    DDRB1->SetValue(false);
    DDRB1->Disable();
    Panel2 = new wxPanel(this, ID_PANEL3, wxPoint(472,72), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Panel2->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap3 = new wxStaticBitmap(Panel2, ID_STATICBITMAP3, wxBitmap(wxImage(_T("images\\buffer2.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP3"));
    StaticBitmap3->SetMinSize(wxSize(43,26));
    StaticBitmap3->SetMaxSize(wxSize(43,26));
    PORTA1 = new wxCheckBox(Panel2, ID_CHECKBOX28, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX28"));
    PORTA1->SetValue(false);
    PORTA1->SetMinSize(wxSize(20,20));
    PORTA1->SetMaxSize(wxSize(20,20));
    PINA1 = new wxCheckBox(Panel2, ID_CHECKBOX29, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX29"));
    PINA1->SetValue(false);
    PINA1->Disable();
    DDRA1 = new wxCheckBox(Panel2, ID_CHECKBOX30, wxEmptyString, wxPoint(25,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX30"));
    DDRA1->SetValue(false);
    Panel13 = new wxPanel(this, ID_PANEL14, wxPoint(8,168), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL14"));
    Panel13->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap12 = new wxStaticBitmap(Panel13, ID_STATICBITMAP12, wxBitmap(wxImage(_T("images\\buffer.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP12"));
    StaticBitmap12->SetMinSize(wxSize(43,26));
    StaticBitmap12->SetMaxSize(wxSize(43,26));
    PORTB3 = new wxCheckBox(Panel13, ID_CHECKBOX50, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX50"));
    PORTB3->SetValue(false);
    PORTB3->SetMinSize(wxSize(20,20));
    PORTB3->SetMaxSize(wxSize(20,20));
    PINB3 = new wxCheckBox(Panel13, ID_CHECKBOX51, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX51"));
    PINB3->SetValue(false);
    PINB3->Disable();
    DDRB3 = new wxCheckBox(Panel13, ID_CHECKBOX52, wxEmptyString, wxPoint(31,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX52"));
    DDRB3->SetValue(false);
    Panel3 = new wxPanel(this, ID_PANEL4, wxPoint(472,168), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    Panel3->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap4 = new wxStaticBitmap(Panel3, ID_STATICBITMAP4, wxBitmap(wxImage(_T("images\\buffer2.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP4"));
    StaticBitmap4->SetMinSize(wxSize(43,26));
    StaticBitmap4->SetMaxSize(wxSize(43,26));
    PORTA3 = new wxCheckBox(Panel3, ID_CHECKBOX2, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    PORTA3->SetValue(false);
    PORTA3->SetMinSize(wxSize(20,20));
    PORTA3->SetMaxSize(wxSize(20,20));
    PINA3 = new wxCheckBox(Panel3, ID_CHECKBOX4, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    PINA3->SetValue(false);
    PINA3->Disable();
    DDRA3 = new wxCheckBox(Panel3, ID_CHECKBOX6, wxEmptyString, wxPoint(25,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    DDRA3->SetValue(false);
    Panel10 = new wxPanel(this, ID_PANEL9, wxPoint(8,24), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL9"));
    Panel10->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap9 = new wxStaticBitmap(Panel10, ID_STATICBITMAP9, wxBitmap(wxImage(_T("images\\buffer.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP9"));
    StaticBitmap9->SetMinSize(wxSize(43,26));
    StaticBitmap9->SetMaxSize(wxSize(43,26));
    PORTB0 = new wxCheckBox(Panel10, ID_CHECKBOX41, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX41"));
    PORTB0->SetValue(false);
    PORTB0->SetMinSize(wxSize(20,20));
    PORTB0->SetMaxSize(wxSize(20,20));
    PORTB0->Disable();
    PINB0 = new wxCheckBox(Panel10, ID_CHECKBOX42, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX42"));
    PINB0->SetValue(false);
    PINB0->Disable();
    DDRB0 = new wxCheckBox(Panel10, ID_CHECKBOX43, wxEmptyString, wxPoint(31,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX43"));
    DDRB0->SetValue(false);
    DDRB0->Disable();
    Panel7 = new wxPanel(this, ID_PANEL8, wxPoint(472,24), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL8"));
    Panel7->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap8 = new wxStaticBitmap(Panel7, ID_STATICBITMAP8, wxBitmap(wxImage(_T("images\\buffer2.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP8"));
    StaticBitmap8->SetMinSize(wxSize(43,26));
    StaticBitmap8->SetMaxSize(wxSize(43,26));
    PORTA0 = new wxCheckBox(Panel7, ID_CHECKBOX16, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX16"));
    PORTA0->SetValue(false);
    PORTA0->SetMinSize(wxSize(20,20));
    PORTA0->SetMaxSize(wxSize(20,20));
    PINA0 = new wxCheckBox(Panel7, ID_CHECKBOX17, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX17"));
    PINA0->SetValue(false);
    PINA0->Disable();
    DDRA0 = new wxCheckBox(Panel7, ID_CHECKBOX18, wxEmptyString, wxPoint(25,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX18"));
    DDRA0->SetValue(false);
    Panel17 = new wxPanel(this, ID_PANEL18, wxPoint(8,360), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL18"));
    Panel17->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap16 = new wxStaticBitmap(Panel17, ID_STATICBITMAP16, wxBitmap(wxImage(_T("images\\buffer.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP16"));
    StaticBitmap16->SetMinSize(wxSize(43,26));
    StaticBitmap16->SetMaxSize(wxSize(43,26));
    PORTB7 = new wxCheckBox(Panel17, ID_CHECKBOX62, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX62"));
    PORTB7->SetValue(false);
    PORTB7->SetMinSize(wxSize(20,20));
    PORTB7->SetMaxSize(wxSize(20,20));
    PORTB7->Disable();
    PINB7 = new wxCheckBox(Panel17, ID_CHECKBOX63, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX63"));
    PINB7->SetValue(false);
    PINB7->Disable();
    DDRB7 = new wxCheckBox(Panel17, ID_CHECKBOX64, wxEmptyString, wxPoint(31,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX64"));
    DDRB7->SetValue(false);
    DDRB7->Disable();
    Panel6 = new wxPanel(this, ID_PANEL7, wxPoint(472,360), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL7"));
    Panel6->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap7 = new wxStaticBitmap(Panel6, ID_STATICBITMAP7, wxBitmap(wxImage(_T("images\\buffer2.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP7"));
    StaticBitmap7->SetMinSize(wxSize(43,26));
    StaticBitmap7->SetMaxSize(wxSize(43,26));
    PORTA7 = new wxCheckBox(Panel6, ID_CHECKBOX13, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
    PORTA7->SetValue(false);
    PORTA7->SetMinSize(wxSize(20,20));
    PORTA7->SetMaxSize(wxSize(20,20));
    PINA7 = new wxCheckBox(Panel6, ID_CHECKBOX14, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
    PINA7->SetValue(false);
    PINA7->Disable();
    DDRA7 = new wxCheckBox(Panel6, ID_CHECKBOX15, wxEmptyString, wxPoint(25,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX15"));
    DDRA7->SetValue(false);
    Panel16 = new wxPanel(this, ID_PANEL17, wxPoint(8,312), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL17"));
    Panel16->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap15 = new wxStaticBitmap(Panel16, ID_STATICBITMAP15, wxBitmap(wxImage(_T("images\\buffer.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP15"));
    StaticBitmap15->SetMinSize(wxSize(43,26));
    StaticBitmap15->SetMaxSize(wxSize(43,26));
    PORTB6 = new wxCheckBox(Panel16, ID_CHECKBOX59, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX59"));
    PORTB6->SetValue(false);
    PORTB6->SetMinSize(wxSize(20,20));
    PORTB6->SetMaxSize(wxSize(20,20));
    PINB6 = new wxCheckBox(Panel16, ID_CHECKBOX60, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX60"));
    PINB6->SetValue(false);
    PINB6->Disable();
    DDRB6 = new wxCheckBox(Panel16, ID_CHECKBOX61, wxEmptyString, wxPoint(31,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX61"));
    DDRB6->SetValue(false);
    Panel5 = new wxPanel(this, ID_PANEL6, wxPoint(472,312), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL6"));
    Panel5->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap6 = new wxStaticBitmap(Panel5, ID_STATICBITMAP6, wxBitmap(wxImage(_T("images\\buffer2.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP6"));
    StaticBitmap6->SetMinSize(wxSize(43,26));
    StaticBitmap6->SetMaxSize(wxSize(43,26));
    PORTA6 = new wxCheckBox(Panel5, ID_CHECKBOX10, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
    PORTA6->SetValue(false);
    PORTA6->SetMinSize(wxSize(20,20));
    PORTA6->SetMaxSize(wxSize(20,20));
    PINA6 = new wxCheckBox(Panel5, ID_CHECKBOX11, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
    PINA6->SetValue(false);
    PINA6->Disable();
    DDRA6 = new wxCheckBox(Panel5, ID_CHECKBOX12, wxEmptyString, wxPoint(25,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
    DDRA6->SetValue(false);
    Panel15 = new wxPanel(this, ID_PANEL16, wxPoint(8,264), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL16"));
    Panel15->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap14 = new wxStaticBitmap(Panel15, ID_STATICBITMAP14, wxBitmap(wxImage(_T("images\\buffer.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP14"));
    StaticBitmap14->SetMinSize(wxSize(43,26));
    StaticBitmap14->SetMaxSize(wxSize(43,26));
    PORTB5 = new wxCheckBox(Panel15, ID_CHECKBOX56, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX56"));
    PORTB5->SetValue(false);
    PORTB5->SetMinSize(wxSize(20,20));
    PORTB5->SetMaxSize(wxSize(20,20));
    PINB5 = new wxCheckBox(Panel15, ID_CHECKBOX57, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX57"));
    PINB5->SetValue(false);
    PINB5->Disable();
    DDRB5 = new wxCheckBox(Panel15, ID_CHECKBOX58, wxEmptyString, wxPoint(31,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX58"));
    DDRB5->SetValue(false);
    Panel4 = new wxPanel(this, ID_PANEL5, wxPoint(472,264), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    Panel4->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap5 = new wxStaticBitmap(Panel4, ID_STATICBITMAP5, wxBitmap(wxImage(_T("images\\buffer2.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP5"));
    StaticBitmap5->SetMinSize(wxSize(43,26));
    StaticBitmap5->SetMaxSize(wxSize(43,26));
    PORTA5 = new wxCheckBox(Panel4, ID_CHECKBOX7, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    PORTA5->SetValue(false);
    PORTA5->SetMinSize(wxSize(20,20));
    PORTA5->SetMaxSize(wxSize(20,20));
    PINA5 = new wxCheckBox(Panel4, ID_CHECKBOX8, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
    PINA5->SetValue(false);
    PINA5->Disable();
    DDRA5 = new wxCheckBox(Panel4, ID_CHECKBOX9, wxEmptyString, wxPoint(25,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
    DDRA5->SetValue(false);
    Panel14 = new wxPanel(this, ID_PANEL15, wxPoint(8,216), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL15"));
    Panel14->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap13 = new wxStaticBitmap(Panel14, ID_STATICBITMAP13, wxBitmap(wxImage(_T("images\\buffer.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP13"));
    StaticBitmap13->SetMinSize(wxSize(43,26));
    StaticBitmap13->SetMaxSize(wxSize(43,26));
    PORTB4 = new wxCheckBox(Panel14, ID_CHECKBOX53, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX53"));
    PORTB4->SetValue(false);
    PORTB4->SetMinSize(wxSize(20,20));
    PORTB4->SetMaxSize(wxSize(20,20));
    PINB4 = new wxCheckBox(Panel14, ID_CHECKBOX54, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX54"));
    PINB4->SetValue(false);
    PINB4->Disable();
    DDRB4 = new wxCheckBox(Panel14, ID_CHECKBOX55, wxEmptyString, wxPoint(31,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX55"));
    DDRB4->SetValue(false);
    PA0_PANEL = new wxPanel(this, ID_PANEL1, wxPoint(472,216), wxSize(72,40), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    PA0_PANEL->SetBackgroundColour(wxColour(255,255,255));
    StaticBitmap1 = new wxStaticBitmap(PA0_PANEL, ID_STATICBITMAP1, wxBitmap(wxImage(_T("images\\buffer2.bmp")).Rescale(wxSize(43,26).GetWidth(),wxSize(43,26).GetHeight())), wxPoint(13,13), wxSize(43,26), 0, _T("ID_STATICBITMAP1"));
    StaticBitmap1->SetMinSize(wxSize(43,26));
    StaticBitmap1->SetMaxSize(wxSize(43,26));
    PORTA4 = new wxCheckBox(PA0_PANEL, ID_CHECKBOX1, wxEmptyString, wxPoint(0,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    PORTA4->SetValue(false);
    PORTA4->SetMinSize(wxSize(20,20));
    PORTA4->SetMaxSize(wxSize(20,20));
    PINA4 = new wxCheckBox(PA0_PANEL, ID_CHECKBOX3, wxEmptyString, wxPoint(56,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    PINA4->SetValue(false);
    PINA4->Disable();
    DDRA4 = new wxCheckBox(PA0_PANEL, ID_CHECKBOX5, wxEmptyString, wxPoint(25,0), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    DDRA4->SetValue(false);
    Button_Connect = new wxButton(this, ID_BUTTON2, _("Connect"), wxPoint(256,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Panel18 = new wxPanel(this, ID_PANEL19, wxPoint(144,152), wxSize(264,240), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL19"));
    OCR1C_Text = new wxStaticText(Panel18, ID_STATICTEXT6, _("OCR1C = 0"), wxPoint(8,16), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    OCR1C_Text->SetForegroundColour(wxColour(128,0,64));
    TCCR1B_Text = new wxStaticText(Panel18, ID_STATICTEXT5, _("TCCR1B=0x00"), wxPoint(144,88), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    TCCR1B_Text->SetForegroundColour(wxColour(128,64,0));
    wxFont TCCR1B_TextFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    TCCR1B_Text->SetFont(TCCR1B_TextFont);
    OCR1C_Slider = new wxSlider(Panel18, ID_SLIDER3, 0, 0, 255, wxPoint(80,10), wxSize(166,24), 0, wxDefaultValidator, _T("ID_SLIDER3"));
    OCR1B_Slider = new wxSlider(Panel18, ID_SLIDER2, 0, 0, 255, wxPoint(80,34), wxSize(166,24), 0, wxDefaultValidator, _T("ID_SLIDER2"));
    TCNT1_Slider = new wxSlider(Panel18, ID_SLIDER1, 0, 0, 255, wxPoint(80,60), wxSize(166,24), 0, wxDefaultValidator, _T("ID_SLIDER1"));
    TCNT1_Slider->Disable();
    OCR1B_Text = new wxStaticText(Panel18, ID_STATICTEXT7, _("OCR1B = 0"), wxPoint(8,40), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    OCR1B_Text->SetForegroundColour(wxColour(128,0,64));
    TCCR1A_Text = new wxStaticText(Panel18, ID_STATICTEXT4, _("TCCR1A=0x00"), wxPoint(24,88), wxSize(162,16), 0, _T("ID_STATICTEXT4"));
    TCCR1A_Text->SetForegroundColour(wxColour(128,64,0));
    wxFont TCCR1A_TextFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    TCCR1A_Text->SetFont(TCCR1A_TextFont);
    TCNT1_Text = new wxStaticText(Panel18, ID_STATICTEXT8, _("TCNT1 = 0"), wxPoint(8,64), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    TCNT1_Text->SetForegroundColour(wxColour(128,0,64));
    TCCR1A7 = new wxCheckBox(Panel18, ID_CHECKBOX33, _("COM1A1"), wxPoint(32,104), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX33"));
    TCCR1A7->SetValue(false);
    TCCR1A7->Disable();
    TCCR1A6 = new wxCheckBox(Panel18, ID_CHECKBOX34, _("COM1A0"), wxPoint(32,120), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX34"));
    TCCR1A6->SetValue(false);
    TCCR1A6->Disable();
    TCCR1A5 = new wxCheckBox(Panel18, ID_CHECKBOX35, _("COM1B1"), wxPoint(32,136), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX35"));
    TCCR1A5->SetValue(false);
    TCCR1A4 = new wxCheckBox(Panel18, ID_CHECKBOX36, _("COM1B0"), wxPoint(32,152), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX36"));
    TCCR1A4->SetValue(false);
    TCCR1A3 = new wxCheckBox(Panel18, ID_CHECKBOX37, _("FOC1A"), wxPoint(32,168), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX37"));
    TCCR1A3->SetValue(false);
    TCCR1A3->Disable();
    TCCR1A2 = new wxCheckBox(Panel18, ID_CHECKBOX38, _("FOC1B"), wxPoint(32,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX38"));
    TCCR1A2->SetValue(false);
    TCCR1A2->Disable();
    TCCR1A1 = new wxCheckBox(Panel18, ID_CHECKBOX39, _("PWM1A"), wxPoint(32,200), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX39"));
    TCCR1A1->SetValue(false);
    TCCR1A0 = new wxCheckBox(Panel18, ID_CHECKBOX40, _("PWM1B"), wxPoint(32,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX40"));
    TCCR1A0->SetValue(false);
    TCCR1B7 = new wxCheckBox(Panel18, ID_CHECKBOX19, _("CTC1"), wxPoint(152,104), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX19"));
    TCCR1B7->SetValue(false);
    TCCR1B6 = new wxCheckBox(Panel18, ID_CHECKBOX20, _("PSR1"), wxPoint(152,120), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX20"));
    TCCR1B6->SetValue(false);
    TCCR1B3 = new wxCheckBox(Panel18, ID_CHECKBOX23, _("CS13"), wxPoint(152,168), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX23"));
    TCCR1B3->SetValue(false);
    TCCR1B2 = new wxCheckBox(Panel18, ID_CHECKBOX24, _("CS12"), wxPoint(152,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX24"));
    TCCR1B2->SetValue(false);
    TCCR1B1 = new wxCheckBox(Panel18, ID_CHECKBOX31, _("CS11"), wxPoint(152,200), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX31"));
    TCCR1B1->SetValue(false);
    TCCR1B0 = new wxCheckBox(Panel18, ID_CHECKBOX32, _("CS10"), wxPoint(152,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX32"));
    TCCR1B0->SetValue(false);
    TCCR1B5 = new wxCheckBox(Panel18, ID_CHECKBOX21, _("-"), wxPoint(152,136), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX21"));
    TCCR1B5->SetValue(false);
    TCCR1B5->Disable();
    TCCR1B4 = new wxCheckBox(Panel18, ID_CHECKBOX22, _("-"), wxPoint(152,152), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX22"));
    TCCR1B4->SetValue(false);
    TCCR1B4->Disable();
    StaticText10 = new wxStaticText(this, ID_STATICTEXT17, _("PA0"), wxPoint(432,40), wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    StaticText10->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText10Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText10->SetFont(StaticText10Font);
    StaticText17 = new wxStaticText(this, ID_STATICTEXT24, _("PB7"), wxPoint(88,376), wxDefaultSize, 0, _T("ID_STATICTEXT24"));
    StaticText17->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText17Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText17->SetFont(StaticText17Font);
    StaticText16 = new wxStaticText(this, ID_STATICTEXT23, _("PB6"), wxPoint(88,328), wxDefaultSize, 0, _T("ID_STATICTEXT23"));
    StaticText16->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText16Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText16->SetFont(StaticText16Font);
    StaticText15 = new wxStaticText(this, ID_STATICTEXT22, _("PB5"), wxPoint(88,280), wxDefaultSize, 0, _T("ID_STATICTEXT22"));
    StaticText15->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText15Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText15->SetFont(StaticText15Font);
    StaticText14 = new wxStaticText(this, ID_STATICTEXT21, _("PB4"), wxPoint(88,232), wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    StaticText14->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText14Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText14->SetFont(StaticText14Font);
    StaticText13 = new wxStaticText(this, ID_STATICTEXT20, _("PB3"), wxPoint(88,184), wxDefaultSize, 0, _T("ID_STATICTEXT20"));
    StaticText13->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText13Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText13->SetFont(StaticText13Font);
    StaticText12 = new wxStaticText(this, ID_STATICTEXT19, _("PB2"), wxPoint(88,136), wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    StaticText12->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText12Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText12->SetFont(StaticText12Font);
    StaticText11 = new wxStaticText(this, ID_STATICTEXT18, _("PB1"), wxPoint(88,88), wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    StaticText11->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText11Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText11->SetFont(StaticText11Font);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT10, _("PB0"), wxPoint(88,40), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    StaticText3->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText3Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText3->SetFont(StaticText3Font);
    StaticText9 = new wxStaticText(this, ID_STATICTEXT16, _("PA7"), wxPoint(432,376), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    StaticText9->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText9Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText9->SetFont(StaticText9Font);
    StaticText8 = new wxStaticText(this, ID_STATICTEXT15, _("PA6"), wxPoint(432,328), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    StaticText8->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText8Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText8->SetFont(StaticText8Font);
    StaticText7 = new wxStaticText(this, ID_STATICTEXT14, _("PA5"), wxPoint(432,280), wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    StaticText7->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText7Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText7->SetFont(StaticText7Font);
    StaticText6 = new wxStaticText(this, ID_STATICTEXT13, _("PA4"), wxPoint(432,232), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    StaticText6->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText6Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText6->SetFont(StaticText6Font);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT12, _("PA3"), wxPoint(432,184), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    StaticText5->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText5Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText5->SetFont(StaticText5Font);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT11, _("PA2"), wxPoint(432,136), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    StaticText4->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText4Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText4->SetFont(StaticText4Font);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT9, _("PA1"), wxPoint(432,88), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    StaticText2->SetForegroundColour(wxColour(0,128,64));
    wxFont StaticText2Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    Panel8 = new wxPanel(this, ID_PANEL10, wxPoint(144,48), wxSize(264,96), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL10"));
    StaticText1 = new wxStaticText(Panel8, ID_STATICTEXT1, _("ADC:"), wxPoint(32,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUTEXT));
    ADC_Digital = new wxStaticText(Panel8, ID_STATICTEXT2, _("0"), wxPoint(8,24), wxSize(56,13), 0, _T("ID_STATICTEXT2"));
    ADC_Digital->SetForegroundColour(wxColour(0,64,128));
    ADC_Voltage = new wxStaticText(Panel8, ID_STATICTEXT3, _("0"), wxPoint(8,40), wxSize(56,13), 0, _T("ID_STATICTEXT3"));
    ADC_Voltage->SetForegroundColour(wxColour(0,128,0));
    ADCGauge = new wxGauge(Panel8, ID_GAUGE1, 256, wxPoint(8,56), wxSize(86,30), 0, wxDefaultValidator, _T("ID_GAUGE1"));
    RadioButton_ADC0 = new wxRadioButton(Panel8, ID_RADIOBUTTON1, _("ADC 0 (PA0)"), wxPoint(96,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
    RadioButton_ADC0->SetValue(true);
    RadioButton_ADC1 = new wxRadioButton(Panel8, ID_RADIOBUTTON2, _("ADC 1 (PA1)"), wxPoint(96,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
    RadioButton_ADC2 = new wxRadioButton(Panel8, ID_RADIOBUTTON3, _("ADC 2 (PA2)"), wxPoint(96,40), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON3"));
    RadioButton_ADC3 = new wxRadioButton(Panel8, ID_RADIOBUTTON5, _("ADC 3 (PA4)"), wxPoint(96,56), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON5"));
    RadioButton_ADC4 = new wxRadioButton(Panel8, ID_RADIOBUTTON6, _("ADC 4 (PA5)"), wxPoint(96,72), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON6"));
    RadioButton_ADC5 = new wxRadioButton(Panel8, ID_RADIOBUTTON7, _("ADC 5 (PA6)"), wxPoint(176,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON7"));
    RadioButton_ADC6 = new wxRadioButton(Panel8, ID_RADIOBUTTON8, _("ADC 6 (PA7)"), wxPoint(176,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON8"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    Timer1.SetOwner(this, ID_TIMER1);
    Timer1.Start(75, false);
    Timer2.SetOwner(this, ID_TIMER2);
    Timer2.Start(30, false);

    Connect(ID_CHECKBOX47,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX49,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA2Click);
    Connect(ID_CHECKBOX25,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX27,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA2Click);
    Connect(ID_CHECKBOX44,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX46,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA1Click);
    Connect(ID_CHECKBOX28,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX30,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA1Click);
    Connect(ID_CHECKBOX50,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX52,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA3Click);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA3Click);
    Connect(ID_CHECKBOX41,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX42,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnPINA0Click);
    Connect(ID_CHECKBOX43,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click1);
    Connect(ID_CHECKBOX16,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX17,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnPINA0Click);
    Connect(ID_CHECKBOX18,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click1);
    Connect(ID_CHECKBOX62,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX64,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA7Click);
    Connect(ID_CHECKBOX13,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX15,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA7Click);
    Connect(ID_CHECKBOX59,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX61,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA6Click);
    Connect(ID_CHECKBOX10,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX11,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnPINA6Click);
    Connect(ID_CHECKBOX12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA6Click);
    Connect(ID_CHECKBOX56,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX58,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA5Click);
    Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA5Click);
    Connect(ID_CHECKBOX53,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX55,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA4Click);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA0Click);
    Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnDDRA4Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnButton_ConnectClick);
    Connect(ID_SLIDER2,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&widgetTestFrame::OnOCR1B_SliderCmdScroll);
    Connect(ID_CHECKBOX35,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnTCCR1A5Click1);
    Connect(ID_CHECKBOX36,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnTCCR1A4Click1);
    Connect(ID_CHECKBOX37,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnTCCR1A4Click);
    Connect(ID_CHECKBOX38,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnTCCR1A5Click);
    Connect(ID_CHECKBOX39,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnTCCR1A1Click);
    Connect(ID_CHECKBOX40,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnTCCR1A0Click);
    Connect(ID_CHECKBOX19,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnTCCR1B0Click);
    Connect(ID_CHECKBOX20,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnTCCR1B1Click);
    Connect(ID_CHECKBOX23,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnTCCR1A4Click);
    Connect(ID_CHECKBOX24,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnTCCR1A5Click);
    Connect(ID_CHECKBOX31,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnTCCR1B1Click1);
    Connect(ID_CHECKBOX32,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnTCCR1B7Click);
    Connect(ID_CHECKBOX21,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&widgetTestFrame::OnTCCR1B2Click);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&widgetTestFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&widgetTestFrame::OnAbout);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&widgetTestFrame::OnTimer1Trigger);
    Connect(ID_TIMER2,wxEVT_TIMER,(wxObjectEventFunction)&widgetTestFrame::OnTimer2Trigger);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&widgetTestFrame::OnClose);
    //*)

    BeginBusy();
    if (!device.Connect())
    {
        Button_Connect->Enable(false);
    }
    EndBusy();
}

widgetTestFrame::~widgetTestFrame()
{
    //(*Destroy(widgetTestFrame)
    //*)
    BeginBusy();
    device.Disconnect(); // Ensure device is turned off
    EndBusy();
}

void widgetTestFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void widgetTestFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void widgetTestFrame::OnClose(wxCloseEvent& event)
{
    BeginBusy();
    device.Disconnect();
    EndBusy();
    exit(0);
}

void widgetTestFrame::OnButton1Click(wxCommandEvent& event)
{

}

void widgetTestFrame::OnCheckBox1Click(wxCommandEvent& event)
{
}

void widgetTestFrame::OnDDRA0Click(wxCommandEvent& event)
{
    SetPortA();
}


void widgetTestFrame::OnButton_DisconnectClick(wxCommandEvent& event)
{
    BeginBusy();
    device.Disconnect();
    EndBusy();
}

void widgetTestFrame::OnButton_ConnectClick(wxCommandEvent& event)
{
    BeginBusy();
    int code = device.Connect();
    EndBusy();

    if (code == 0)
    {
        Button_Connect->Enable(false);
    }
    if (code != 0)
    {
        wxString s;
        s.Printf(_("Could not connect: Error Code = %d\nEnsure:\n1. The programmer is connected\n2. The Tiny26 is connected\n3. The Tiny26 is running the correct firmware"), code);
        wxMessageBox(s, _("Error connecting to device"));
    }
}

void widgetTestFrame::SetPortA ()
{
    //device.Send();


}

void widgetTestFrame::OnButton1Click2(wxCommandEvent& event)
{
    SetPortA();
}



void widgetTestFrame::OnDDRA0Click1(wxCommandEvent& event)
{
    SetPortA();
}

void widgetTestFrame::OnButton2Click1(wxCommandEvent& event)
{
    SetPortA();
}

void widgetTestFrame::OnPINA0Click(wxCommandEvent& event)
{
}

void widgetTestFrame::OnDDRA1Click(wxCommandEvent& event)
{
    SetPortA();
}

void widgetTestFrame::OnDDRA2Click(wxCommandEvent& event)
{
    SetPortA();
}

void widgetTestFrame::OnDDRA3Click(wxCommandEvent& event)
{
    SetPortA();
}

void widgetTestFrame::OnDDRA4Click(wxCommandEvent& event)
{
    SetPortA();
}

void widgetTestFrame::OnDDRA5Click(wxCommandEvent& event)
{
    SetPortA();
}

void widgetTestFrame::OnDDRA6Click(wxCommandEvent& event)
{
    SetPortA();
}

void widgetTestFrame::OnDDRA7Click(wxCommandEvent& event)
{
    SetPortA();
}

// Called every 100 ms
void widgetTestFrame::OnTimer1Trigger(wxTimerEvent& event)
{
    // Set and Get PortA Registers
    Port portA;
    portA.PORT = 0x00;
    portA.PORT_Mask = 0xFF;
    portA.DDR = 0x00;
    portA.DDR_Mask = 0xFF;
    portA.PIN = 0x00;

    if (PORTA0->IsChecked()) portA.PORT |= (1<<0);
    if (PORTA1->IsChecked()) portA.PORT |= (1<<1);
    if (PORTA2->IsChecked()) portA.PORT |= (1<<2);
    if (PORTA3->IsChecked()) portA.PORT |= (1<<3);
    if (PORTA4->IsChecked()) portA.PORT |= (1<<4);
    if (PORTA5->IsChecked()) portA.PORT |= (1<<5);
    if (PORTA6->IsChecked()) portA.PORT |= (1<<6);
    if (PORTA7->IsChecked()) portA.PORT |= (1<<7);

    if (DDRA0->IsChecked()) portA.DDR |= (1<<0);
    if (DDRA1->IsChecked()) portA.DDR |= (1<<1);
    if (DDRA2->IsChecked()) portA.DDR |= (1<<2);
    if (DDRA3->IsChecked()) portA.DDR |= (1<<3);
    if (DDRA4->IsChecked()) portA.DDR |= (1<<4);
    if (DDRA5->IsChecked()) portA.DDR |= (1<<5);
    if (DDRA6->IsChecked()) portA.DDR |= (1<<6);
    if (DDRA7->IsChecked()) portA.DDR |= (1<<7);

    if (Button_Connect->IsEnabled() == false)
    {
        BeginBusy();
        if (device.GetSetPortA(portA))
        {
            Button_Connect->Enable(true);
            EndBusy();
            return;
        }
        EndBusy();
    }

    PINA0->SetValue(portA.PIN & (1<<0));
    PINA1->SetValue(portA.PIN & (1<<1));
    PINA2->SetValue(portA.PIN & (1<<2));
    PINA3->SetValue(portA.PIN & (1<<3));
    PINA4->SetValue(portA.PIN & (1<<4));
    PINA5->SetValue(portA.PIN & (1<<5));
    PINA6->SetValue(portA.PIN & (1<<6));
    PINA7->SetValue(portA.PIN & (1<<7));



    // Set and Get PortB Registers
    Port portB;
    portB.PORT = 0x00;
    portB.PORT_Mask = 0xFF;
    portB.DDR = 0x00;
    portB.DDR_Mask = 0xFF;
    portB.PIN = 0x00;

    if (PORTB0->IsChecked()) portB.PORT |= (1<<0);
    if (PORTB1->IsChecked()) portB.PORT |= (1<<1);
    if (PORTB2->IsChecked()) portB.PORT |= (1<<2);
    if (PORTB3->IsChecked()) portB.PORT |= (1<<3);
    if (PORTB4->IsChecked()) portB.PORT |= (1<<4);
    if (PORTB5->IsChecked()) portB.PORT |= (1<<5);
    if (PORTB6->IsChecked()) portB.PORT |= (1<<6);
    if (PORTB7->IsChecked()) portB.PORT |= (1<<7);

    if (DDRB0->IsChecked()) portB.DDR |= (1<<0);
    if (DDRB1->IsChecked()) portB.DDR |= (1<<1);
    if (DDRB2->IsChecked()) portB.DDR |= (1<<2);
    if (DDRB3->IsChecked()) portB.DDR |= (1<<3);
    if (DDRB4->IsChecked()) portB.DDR |= (1<<4);
    if (DDRB5->IsChecked()) portB.DDR |= (1<<5);
    if (DDRB6->IsChecked()) portB.DDR |= (1<<6);
    if (DDRB7->IsChecked()) portB.DDR |= (1<<7);

    if (Button_Connect->IsEnabled() == false)
    {
        BeginBusy();
        if (device.GetSetPortB(portB))
        {
            Button_Connect->Enable(true);
            EndBusy();
            return;
        }
        EndBusy();
    }

    PINB0->SetValue(portB.PIN & (1<<0));
    PINB1->SetValue(portB.PIN & (1<<1));
    PINB2->SetValue(portB.PIN & (1<<2));
    PINB3->SetValue(portB.PIN & (1<<3));
    PINB4->SetValue(portB.PIN & (1<<4));
    PINB5->SetValue(portB.PIN & (1<<5));
    PINB6->SetValue(portB.PIN & (1<<6));
    PINB7->SetValue(portB.PIN & (1<<7));

    // Get ADC
    unsigned char adcValue = 0;
    unsigned char adcNumber = 0;

    if (RadioButton_ADC0->GetValue()) adcNumber = 0;
    if (RadioButton_ADC1->GetValue()) adcNumber = 1;
    if (RadioButton_ADC2->GetValue()) adcNumber = 2;
    if (RadioButton_ADC3->GetValue()) adcNumber = 3;
    if (RadioButton_ADC4->GetValue()) adcNumber = 4;
    if (RadioButton_ADC5->GetValue()) adcNumber = 5;
    if (RadioButton_ADC6->GetValue()) adcNumber = 6;

    if (Button_Connect->IsEnabled() == false)
    {
        BeginBusy();

        if (device.Get_ADC(adcNumber, adcValue))
        {
            Button_Connect->Enable(true);
            EndBusy();
            return;
        }
        EndBusy();
    }

    wxString s;
    s.Printf(_("Digital: %d"), adcValue);
    if (ADC_Digital->GetLabelText()!=s)
        ADC_Digital->SetLabel(s);

    float volts = (5.0f * adcValue / 255);

    wxString voltage;
    voltage.Printf(_("Volts: %1.2f"), volts);
    if (ADC_Voltage->GetLabelText()!=voltage)
    {
        ADC_Voltage->SetLabel(voltage);
        ADCGauge->SetValue(adcValue);
    }

    // Set timer/counters
    unsigned char tccr1a, tccr1b, ocr1b, ocr1c, tcnt1;
    tcnt1 = 0;
    tccr1b = 0;
    tccr1a = 0;
    ocr1b = OCR1B_Slider->GetValue();
    ocr1c = OCR1C_Slider->GetValue();

    if (TCCR1B0->IsChecked()) tccr1b |= (1<<0);
    if (TCCR1B1->IsChecked()) tccr1b |= (1<<1);
    if (TCCR1B2->IsChecked()) tccr1b |= (1<<2);
    if (TCCR1B3->IsChecked()) tccr1b |= (1<<3);
    if (TCCR1B4->IsChecked()) tccr1b |= (1<<4);
    if (TCCR1B5->IsChecked()) tccr1b |= (1<<5);
    if (TCCR1B6->IsChecked()) tccr1b |= (1<<6);
    if (TCCR1B7->IsChecked()) tccr1b |= (1<<7);

    if (TCCR1A0->IsChecked()) tccr1a |= (1<<0);
    if (TCCR1A1->IsChecked()) tccr1a |= (1<<1);
    if (TCCR1A2->IsChecked()) tccr1a |= (1<<2);
    if (TCCR1A3->IsChecked()) tccr1a |= (1<<3);
    if (TCCR1A4->IsChecked()) tccr1a |= (1<<4);
    if (TCCR1A5->IsChecked()) tccr1a |= (1<<5);
    if (TCCR1A6->IsChecked()) tccr1a |= (1<<6);
    if (TCCR1A7->IsChecked()) tccr1a |= (1<<7);


    if (Button_Connect->IsEnabled() == false)
    {
        BeginBusy();

        if (device.Set_Timers(tccr1a, tccr1b, ocr1b, ocr1c, tcnt1))
        {
            Button_Connect->Enable(true);
            EndBusy();
            return;
        }

        EndBusy();
    }

    wxString str1;
    str1.Printf(_("TCNT1 = %d"), tcnt1);
    if (TCNT1_Text->GetLabelText()!=str1)
    {
        TCNT1_Text->SetLabel(str1);
        TCNT1_Slider->SetValue(tcnt1);
    }
}

void widgetTestFrame::OnCheckListBox1Toggled(wxCommandEvent& event)
{
}

void widgetTestFrame::UpdateTCCR1B ()
{
    unsigned char tccr1b = 0x00;

    if (TCCR1B0->IsChecked()) tccr1b |= (1<<0);
    if (TCCR1B1->IsChecked()) tccr1b |= (1<<1);
    if (TCCR1B2->IsChecked()) tccr1b |= (1<<2);
    if (TCCR1B3->IsChecked()) tccr1b |= (1<<3);
    if (TCCR1B4->IsChecked()) tccr1b |= (1<<4);
    if (TCCR1B5->IsChecked()) tccr1b |= (1<<5);
    if (TCCR1B6->IsChecked()) tccr1b |= (1<<6);
    if (TCCR1B7->IsChecked()) tccr1b |= (1<<7);

    wxString s;
    s.Printf(_("TCCR1B=0x%02X"), tccr1b);
    TCCR1B_Text->SetLabel(s);
}

void widgetTestFrame::UpdateTCCR1A ()
{
    unsigned char tccr1a = 0x00;

    if (TCCR1A0->IsChecked()) tccr1a |= (1<<0);
    if (TCCR1A1->IsChecked()) tccr1a |= (1<<1);
    if (TCCR1A2->IsChecked()) tccr1a |= (1<<2);
    if (TCCR1A3->IsChecked()) tccr1a |= (1<<3);
    if (TCCR1A4->IsChecked()) tccr1a |= (1<<4);
    if (TCCR1A5->IsChecked()) tccr1a |= (1<<5);
    if (TCCR1A6->IsChecked()) tccr1a |= (1<<6);
    if (TCCR1A7->IsChecked()) tccr1a |= (1<<7);

    wxString s;
    s.Printf(_("TCCR1B=0x%02X"), tccr1a);
    TCCR1A_Text->SetLabel(s);
}

void widgetTestFrame::OnTCCR1A4Click(wxCommandEvent& event)
{
    UpdateTCCR1B ();
}

void widgetTestFrame::OnTCCR1A5Click(wxCommandEvent& event)
{
    UpdateTCCR1B ();
}

void widgetTestFrame::OnTCCR1B2Click(wxCommandEvent& event)
{
}


void widgetTestFrame::OnTCCR1B7Click(wxCommandEvent& event)
{
    UpdateTCCR1B ();
}

void widgetTestFrame::OnTCCR1B0Click(wxCommandEvent& event)
{
    UpdateTCCR1B ();
}

void widgetTestFrame::OnTCCR1B1Click(wxCommandEvent& event)
{
    UpdateTCCR1B ();
}

void widgetTestFrame::OnPanel8Paint(wxPaintEvent& event)
{
    UpdateTCCR1B ();
}

void widgetTestFrame::OnTCCR1B1Click1(wxCommandEvent& event)
{
    UpdateTCCR1B ();
}

void widgetTestFrame::OnTCCR1A5Click1(wxCommandEvent& event)
{
    UpdateTCCR1A ();
}

void widgetTestFrame::OnTCCR1A4Click1(wxCommandEvent& event)
{
    UpdateTCCR1A ();
}

void widgetTestFrame::OnTCCR1A1Click(wxCommandEvent& event)
{
    UpdateTCCR1A ();
}

void widgetTestFrame::OnTCCR1A0Click(wxCommandEvent& event)
{
    UpdateTCCR1A ();
}

void widgetTestFrame::OnOCR1B_SliderCmdScroll(wxScrollEvent& event)
{
}

void widgetTestFrame::OnTimer2Trigger(wxTimerEvent& event)
{

    // Update the lame sliders that don't update themselves

    wxString value;
    value.Printf(_("OCR1B = %d"), OCR1B_Slider->GetValue());
    if (OCR1B_Text->GetLabelText() != value)
        OCR1B_Text->SetLabel(value);

    value.Clear();
    value.Printf(_("OCR1C = %d"), OCR1C_Slider->GetValue());
    if (OCR1C_Text->GetLabelText() != value)
        OCR1C_Text->SetLabel(value);
}

void widgetTestFrame::OnPINA6Click(wxCommandEvent& event)
{
}
