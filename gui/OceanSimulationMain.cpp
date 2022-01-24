/***************************************************************
 * Name:      OceanSimulationMain.cpp
 * Purpose:   Code for Application Frame
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

#include "OceanSimulationMain.h"
#include "sea.h"

const float Shark::max_hunger = 20.0;
float Shark::hunger_increment = 5.0;
string str;
wxTextCtrl* textbox;
Sea S;



BEGIN_EVENT_TABLE(OceanSimulationDialog, wxDialog)
    EVT_CLOSE(OceanSimulationDialog::OnClose)
    EVT_BUTTON(idBtnQuit, OceanSimulationDialog::OnQuit)
    EVT_BUTTON(idBtnAbout, OceanSimulationDialog::OnAbout)
END_EVENT_TABLE()

OceanSimulationDialog::OceanSimulationDialog(wxDialog *dlg, const wxString &title)
    : wxDialog(dlg, -1, title)
{
    int numfish = INIT_NUM_FISH;          // intialize the sea
    int numshark = INIT_NUM_SHARK;
    S.PopulationCensus(numfish, numshark);

    this->SetSizeHints(wxDefaultSize, wxDefaultSize);
    wxBoxSizer* bSizer1;
    bSizer1 = new wxBoxSizer(wxHORIZONTAL);
    m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("Fish Simulation"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText1->SetFont(wxFont(20, 74, 90, 90, false, wxT("Arial")));
    bSizer1->Add(m_staticText1, 0, wxALL|wxEXPAND, 5);
    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer(wxVERTICAL);
    BtnAbout = new wxButton(this, idBtnAbout, wxT("&Run"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer2->Add(BtnAbout, 0, wxALL, 5);
    m_staticline1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    bSizer2->Add(m_staticline1, 0, wxALL|wxEXPAND, 5);
    BtnQuit = new wxButton(this, idBtnQuit, wxT("&Quit"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer2->Add(BtnQuit, 0, wxALL, 5);
    bSizer1->Add(bSizer2, 1, wxEXPAND, 5);
    this->SetSizer(bSizer1);
    this->Layout();
    bSizer1->Fit(this);
    textbox = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(25, 25), 0); // text box for user input
    bSizer1->Add(textbox);



}


homework8Dialog::~homework8Dialog()
{
}

void homework8Dialog::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void homework8Dialog::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void OceanSimulationDialog::OnAbout(wxCommandEvent &event)
{
    string message = "";
    try{
        str = textbox->GetValue().ToStdString(); // find the number the user inputted and convert to int
        int x = std::stoi(str);

        for(int i = 0; i < x; i++){             // simulate that many number of steps
            S.SimulateOneStep();
        }
        int count = 0;                          // keeps track of number of fish in a cell
        int fishInCell [SIZE][SIZE] ;           // represents the cell and holds how many fish in a cell
        vector<Fish*> fishptrs;                 // holds a temporary vector for each cell
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < SIZE; k++){
                fishptrs = S.cells [j][k];
                for(const auto& f: fishptrs){   // increment count for each fish pointer in the vector
                    count++;
                }
                fishInCell[j][k] = count;       // set the number of fishes in the cell to the count
                count = 0;                      // reset count for next iteration
            }
        }
       for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < SIZE; k++){
                message += to_string(fishInCell[j][k]) ;  // print each cell with number of fish in format
                message += " ";
       }
       message += "\n";
    }
    }
    catch(...){
        message = "Incorrect format in text box"; // if there is something wrong in the try block, where the user didn't input a number, then print this out
    }
    wxMessageBox( message, ("Message"));   // display appropriate message


}
