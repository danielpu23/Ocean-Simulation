/***************************************************************
 * Name:      OceanSimulationMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2021-04-21
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef OCEANSIMULATIONMAIN_H
#define OCEANSIMULATIONMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "homework8App.h"


#include <wx/button.h>
#include <wx/statline.h>
class homework8Dialog: public wxDialog
{
    public:
        homework8Dialog(wxDialog *dlg, const wxString& title);
        ~homework8Dialog();

    protected:
        enum
        {
            idBtnQuit = 1000,
            idBtnAbout
        };
        wxStaticText* m_staticText1;
        wxButton* BtnAbout;
        wxStaticLine* m_staticline1;
        wxButton* BtnQuit;

    private:
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};

#endif // OCEANSIMULATIONMAIN_H
