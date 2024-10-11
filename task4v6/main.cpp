#include <wx/wx.h>
#include "graph.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnOpenFile(wxCommandEvent& event);
    void OnSaveFile(wxCommandEvent& event);

    Graph* graph;
    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_OpenFile = 1,
    ID_SaveFile
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_OpenFile, MyFrame::OnOpenFile)
    EVT_MENU(ID_SaveFile, MyFrame::OnSaveFile)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("Graph Minimum Spanning Tree Application");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title), graph(nullptr) {
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_OpenFile, "&Open...\tCtrl-O", "Open graph file");
    menuFile->Append(ID_SaveFile, "&Save As...\tCtrl-S", "Save minimum spanning tree");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");

    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to Graph Minimum Spanning Tree Application!");
}

void MyFrame::OnOpenFile(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, _("Open Graph file"), "", "",
                                "Graph files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString path = openFileDialog.GetPath();
    try {
        graph = new Graph(std::string(path.mb_str()));
        SetStatusText("Graph successfully loaded");
    } catch (const std::exception& e) {
        wxMessageBox(e.what(), "Error", wxOK | wxICON_ERROR);
    }
}

void MyFrame::OnSaveFile(wxCommandEvent& event) {
    if (graph) {
        wxFileDialog saveFileDialog(this, _("Save Graph file"), "", "",
                                    "Graph files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

        if (saveFileDialog.ShowModal() == wxID_CANCEL) {
            return;
        }

        wxString path = saveFileDialog.GetPath();
        try {
            graph->findMinimumSpanningTree(std::string(path.mb_str()));
            SetStatusText("Minimum spanning tree saved");
        } catch (const std::exception& e) {
            wxMessageBox(e.what(), "Error", wxOK | wxICON_ERROR);
        }
    } else {
        wxMessageBox("No graph loaded", "Error", wxOK | wxICON_ERROR);
    }
}
