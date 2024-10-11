#include <afxwin.h>
#include "Graph.h"

class CMyApp : public CWinApp {
public:
    virtual BOOL InitInstance();
};

class CMyFrame : public CFrameWnd {
public:
    CMyFrame();
    afx_msg void OnFileOpen();
    afx_msg void OnFileSaveAs();
    DECLARE_MESSAGE_MAP()

private:
    Graph* graph;
};

BEGIN_MESSAGE_MAP(CMyFrame, CFrameWnd)
    ON_COMMAND(ID_FILE_OPEN, &CMyFrame::OnFileOpen)
    ON_COMMAND(ID_FILE_SAVE_AS, &CMyFrame::OnFileSaveAs)
END_MESSAGE_MAP()

BOOL CMyApp::InitInstance() {
    m_pMainWnd = new CMyFrame();
    m_pMainWnd->ShowWindow(SW_NORMAL);
    return TRUE;
}

CMyFrame::CMyFrame() : graph(nullptr) {
    Create(NULL, _T("Graph Minimum Spanning Tree Application"));
}

void CMyFrame::OnFileOpen() {
    CFileDialog dlg(TRUE);
    if (dlg.DoModal() == IDOK) {
        CString path = dlg.GetPathName();
        try {
            graph = new Graph(std::string(path));
            AfxMessageBox(_T("Graph successfully loaded"));
        } catch (const std::exception& e) {
            AfxMessageBox(CString(e.what()));
        }
    }
}

void CMyFrame::OnFileSaveAs() {
    if (graph) {
        CFileDialog dlg(FALSE);
        if (dlg.DoModal() == IDOK) {
            CString path = dlg.GetPathName();
            try {
                graph->findMinimumSpanningTree(std::string(path));
                AfxMessageBox(_T("Minimum spanning tree saved"));
            } catch (const std::exception& e) {
                AfxMessageBox(CString(e.what()));
            }
        }
    } else {
        AfxMessageBox(_T("No graph loaded"));
    }
}

CMyApp theApp;
