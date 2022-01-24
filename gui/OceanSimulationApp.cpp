


/***************************************************************
 * Name:      OceanSimulationApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2021-04-21
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "homework8App.h"
#include "homework8Main.h"

IMPLEMENT_APP(OceanSimulationApp);

bool homework8App::OnInit()
{

    homework8Dialog* dlg = new homework8Dialog(0L, _("CS 144 Project"));
    dlg->SetIcon(wxICON(aaaa)); // To Set App Icon
    dlg->Show();
    return true;
}
