// WinSize3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinSize3.h"
#include "WinSize3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define WM_ICON_NOTIFY  WM_APP+10

CString commonDocs__;

//------------------------------------------------------------------------------------------
// CWinSize3Dlg dialog
CWinSize3Dlg::CWinSize3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WINSIZE3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_CBWINDOWS, cbWindows);
  DDX_Control(pDX, IDC_EDTITLE, edTitle);
  DDX_Control(pDX, IDC_BTNAPPLY, btnApply);
  //  DDX_Control(pDX, IDC_EDHEIGHT, edheight);
  DDX_Control(pDX, IDC_EDHEIGHT, edHeight);
  DDX_Control(pDX, IDC_EDLEFT, edLeft);
  DDX_Control(pDX, IDC_EDTOP, edTop);
  DDX_Control(pDX, IDC_EDWIDTH, edWidth);
  DDX_Control(pDX, IDC_EDAUTOTYPE, edAutotype);
  DDX_Control(pDX, IDC_CBUSECLASS, cbUseClass);
  DDX_Control(pDX, IDC_EDCLASS, edClass);
  DDX_Control(pDX, IDC_EDAUTODELAY, edAutoDelay);
  DDX_Control(pDX, IDC_CBCMPMODE, cbCmpMode);
}

//------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CWinSize3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_WM_HOTKEY()
  ON_WM_TIMER()
  ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
  ON_WM_SIZE()
  ON_CBN_SELCHANGE(IDC_CBWINDOWS, &CWinSize3Dlg::OnSelchangeCbwindows)
  ON_EN_CHANGE(IDC_EDTITLE, &CWinSize3Dlg::OnChangeEdtitle)
  ON_BN_CLICKED(IDC_BTNAPPLY, &CWinSize3Dlg::OnBnClickedBtnapply)
  ON_EN_CHANGE(IDC_EDHEIGHT, &CWinSize3Dlg::OnChangeEdheight)
  ON_EN_CHANGE(IDC_EDLEFT, &CWinSize3Dlg::OnChangeEdleft)
  ON_EN_CHANGE(IDC_EDTOP, &CWinSize3Dlg::OnChangeEdtop)
  ON_EN_CHANGE(IDC_EDWIDTH, &CWinSize3Dlg::OnChangeEdwidth)
  ON_BN_CLICKED(IDC_BTNDELETE, &CWinSize3Dlg::OnBnClickedBtndelete)
  ON_COMMAND(ID_ICONMENU_REPOSITIONALL, &CWinSize3Dlg::OnIconmenuRepositionall)
  ON_EN_CHANGE(IDC_EDAUTOTYPE, &CWinSize3Dlg::OnEnChangeEdautotype)
  ON_BN_CLICKED(IDC_CBUSECLASS, &CWinSize3Dlg::OnBnClickedCbuseclass)
  ON_EN_CHANGE(IDC_EDAUTODELAY, &CWinSize3Dlg::OnEnChangeEdautodelay)
  ON_CBN_SELCHANGE(IDC_CBCMPMODE, &CWinSize3Dlg::OnCbnSelchangeCbcmpmode)
  ON_COMMAND(ID_ICONMENU_EXIT, &CWinSize3Dlg::OnIconmenuExit)
END_MESSAGE_MAP()

//---------------------------------------------------------------------------------------
LRESULT CWinSize3Dlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
  // Delegate all the work back to the default implementation in CSystemTray.
  return m_TrayIcon.OnTrayNotification(wParam, lParam);
}

//------------------------------------------------------------------------------------------
// CWinSize3Dlg message handlers
BOOL CWinSize3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
  HICON hIcon = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));  // Icon to use
  m_TrayIcon.Create(this, WM_ICON_NOTIFY, "WinSize3", hIcon, IDR_MENU1);

  if (!RegisterHotKey(m_hWnd, 0, MOD_CONTROL | MOD_ALT, 0x5A)) // Z
  {
    AfxMessageBox("Can`t register hot key CTRL+ALT+Z!", MB_OK);
  }

  char path[MAX_PATH];
  SHGetSpecialFolderPath(NULL, path, CSIDL_COMMON_DOCUMENTS, true);
  commonDocs__ = path;

  memset(&desktop, 0, sizeof(desktop));
  checkedWindows = new CPtrList();
  bFirstShow = true;
  bNoAutotype = false;

  CreateDirectory(commonDocs__ + "\\WinSize3", NULL);

  SetTimer(0, 1, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//------------------------------------------------------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CWinSize3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//------------------------------------------------------------------------------------------
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWinSize3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
  HWND hwnd = ::GetForegroundWindow();

  if(!hwnd)
  {
    m_TrayIcon.ShowBalloon("No active window!");
    return;
  }

  CString csTitle, csClass;
  int i = FindThis(hwnd, csTitle, csClass);

  WINDOWDATA *data;

  if (i == -1)
  {
    i = cbWindows.AddString(csTitle);
    data = new WINDOWDATA;
    data->csClass = csClass;
    data->bUseClass = true;
    data->cmp_mode = 1;
    data->auto_delay = 100;
    cbWindows.SetItemDataPtr(i, data);

    m_TrayIcon.ShowBalloon("New " + csTitle);
  }
  else
  {
    data = (WINDOWDATA*)cbWindows.GetItemDataPtr(i);

    m_TrayIcon.ShowBalloon("Updated " + csTitle);
  }

  RECT rect;
  ::GetWindowRect(hwnd, &rect);

  if(data->left != -1)
    data->left = rect.left;

  if(data->top != -1)
    data->top = rect.top;

  if(data->width != -1)
    data->width = rect.right - rect.left;

  if(data->height != -1)
  data->height = rect.bottom - rect.top;

  SaveData();

  cbWindows.SetCurSel(i);
  OnSelchangeCbwindows();
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::ClearComboBox()
{
  for (int i = 0; i < cbWindows.GetCount(); i++)
  {
    WINDOWDATA *data = (WINDOWDATA*)cbWindows.GetItemDataPtr(i);
    delete data;
  }

  cbWindows.Clear();
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::LoadData()
{
  CString key;
  FILE *fp;

  ClearComboBox();

  if (!xml.Open(commonDocs__ + "\\WinSize3\\Config.xml"))
    return;

  key.Format("%dx%d", desktop.right, desktop.bottom);

  CXMLNode *node = xml.Root.FindByPath(key);

  if (!node)
    return;

  for (CXMLNode *w = node->FirstChild(); w; w = node->NextChild())
  {
    WINDOWDATA *data = new WINDOWDATA;

    data->left = atoi((*w)["left"]);
    data->top = atoi((*w)["top"]);
    data->width = atoi((*w)["width"]);
    data->height = atoi((*w)["height"]);
    data->csClass = (*w)["class"];
    data->csAutotype = (*w)["autotype"];
    data->bUseClass = atoi((*w)["use_class"]);
    data->auto_delay = atoi((*w)["auto_delay"]);
    data->cmp_mode = atoi((*w)["cmp_mode"]);

    int i = cbWindows.AddString(w->Property("text"));
    cbWindows.SetItemDataPtr(i, data);
  }

  if (cbWindows.GetCount())
  {
    cbWindows.SetCurSel(0);
    OnSelchangeCbwindows();
  }

}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::SaveData()
{
  CString key, text;
  key.Format("%dx%d", desktop.right, desktop.bottom);

  xml.Root.SetName("WinSize3");

  CXMLNode *node = xml.Root.FindByPath(key);

  if (node)
    node->Delete();

  node = xml.Root.AddChild(key);
  
  int i;
  for (i = 0; i < cbWindows.GetCount(); i++)
  {
    cbWindows.GetLBText(i, text);
    WINDOWDATA *data = (WINDOWDATA*)cbWindows.GetItemDataPtr(i);

    CXMLNode *w = node->AddChild("window");
    w->SetProperty("text", text);
    w->AddChild("left", data->left);
    w->AddChild("top", data->top);
    w->AddChild("width", data->width);
    w->AddChild("height", data->height);
    w->AddChild("class", data->csClass);
    w->AddChild("autotype", data->csAutotype);
    w->AddChild("use_class", data->bUseClass);
    w->AddChild("auto_delay", data->auto_delay);
    w->AddChild("cmp_mode", data->cmp_mode);
  }

  xml.Save(commonDocs__ + "\\WinSize3\\Config.xml");
}

//------------------------------------------------------------------------------------------
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
  CWinSize3Dlg* self = (CWinSize3Dlg*)lParam;

  self->CheckWindow(hwnd);

  return TRUE;
}

//------------------------------------------------------------------------------------------
int CWinSize3Dlg::FindThis(HWND hwnd, CString &csTitle, CString &csClass)
{
  char title[1024];
  CString csEntry;

  ::GetWindowText(hwnd, title, sizeof(title));
  csTitle = title;

  GetClassName(hwnd, title, sizeof(title));
  csClass = title;

  for (int i = 0; i < cbWindows.GetCount(); i++)
  {
    cbWindows.GetLBText(i, csEntry);
    WINDOWDATA *data = (WINDOWDATA*)cbWindows.GetItemDataPtr(i);

    if( ((data->cmp_mode == 0 && csTitle.Find(csEntry) > -1) ||
         (data->cmp_mode == 1 && csTitle==csEntry)              ) &&
        (csClass == data->csClass || !data->bUseClass)                )
      return i;
  }

  return -1;
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::CheckWindow(HWND hwnd)
{
  WINDOWPLACEMENT wp;

  wp.length = sizeof(wp);

  if (::IsIconic(hwnd))
    return;

  if (::GetWindowPlacement(hwnd, &wp) && wp.showCmd == SW_HIDE)
    return;

  if (!wp.rcNormalPosition.right)
    return;

  for (POSITION pos = checkedWindows->GetHeadPosition(); pos;)
  {
    if (checkedWindows->GetNext(pos) == hwnd)
      return;
  }

  CString csTitle, csClass;
  int i = FindThis(hwnd, csTitle, csClass);

  if (i == -1)
    return;

  WINDOWDATA *data = (WINDOWDATA*)cbWindows.GetItemDataPtr(i);

  RECT rect;
  ::GetWindowRect(hwnd, &rect);

  int left = data->left;

  if (left == -1)
    left = rect.left;

  int top = data->top;

  if (top == -1)
    top = rect.top;

  int width = data->width;

  if (width == -1)
    width = rect.right - rect.left;

  int height = data->height;

  if (height == -1)
    height = rect.bottom - rect.top;

  ::SetWindowPos(hwnd, NULL, left, top, width, height, SWP_NOACTIVATE | SWP_NOZORDER);

  checkedWindows->AddTail(hwnd);

  if (!data->csAutotype.GetLength() || bNoAutotype)
    return;

  Sleep(data->auto_delay);

  CString &asKeys = data->csAutotype;

  INPUT inp;

  memset(&inp, 0, sizeof(inp));
  inp.type = INPUT_KEYBOARD;
  inp.ki.dwFlags = KEYEVENTF_UNICODE;

  for (int i = 0; i < asKeys.GetLength(); i++)
  {
    char c = asKeys[i];

    Sleep(50);
    ::ShowWindow(hwnd, SW_SHOW);
    ::SetForegroundWindow(hwnd);
    ::SetActiveWindow(hwnd);

    if (c == '{')
    {
      CString asKey;
      for (i++; i < asKeys.GetLength(); i++)
      {
        if (asKeys[i] == '}')
          break;

        asKey += asKeys[i];
      }

      asKey.MakeUpper();

      if (asKey == "TAB")  Key(VK_TAB);
      else if (asKey == "RETURN") Key(VK_RETURN);
      else if (asKey == "LWIN DOWN") Key(VK_LWIN, 1);
      else if (asKey == "LWIN UP") Key(VK_LWIN, 2);
      else if (asKey == "DOWN") Key(VK_DOWN);
      else if (asKey == "UP") Key(VK_UP);
      else if (asKey == "LEFT") Key(VK_LEFT);
      else if (asKey == "RIGHT") Key(VK_RIGHT);
      else if (asKey == "CTRL DOWN") Key(VK_LCONTROL, 1);
      else if (asKey == "CTRL UP") Key(VK_LCONTROL, 2);

      continue;
    }

    inp.ki.dwFlags = KEYEVENTF_UNICODE;
    inp.ki.wScan = c;
    SendInput(1, &inp, sizeof(inp));

    inp.ki.dwFlags |= KEYEVENTF_KEYUP;
    SendInput(1, &inp, sizeof(inp));
  }
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::Key(BYTE key, int press_release)
{
  if(press_release & 1)
    keybd_event(key, 0, 0, 0);

  if (press_release & 2)
    keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnTimer(UINT_PTR nIDEvent)
{
  RECT rect;

  if (bFirstShow)
  {
    KillTimer(0);
    ShowWindow(SW_HIDE);
    SetTimer(0, 500, NULL);
  }

  const HWND hDesktop = ::GetDesktopWindow();
  ::GetWindowRect(hDesktop, &rect);

  if (memcmp(&rect, &desktop, sizeof(rect)) != 0)
  {
    memmove(&desktop, &rect, sizeof(rect));
    LoadData();
    checkedWindows->RemoveAll();

    if(bFirstShow)
      bNoAutotype = true;
  }

  EnumWindows(EnumWindowsProc, (LPARAM)this);

  Check4ClosedWindows();

  bFirstShow = false;
  bNoAutotype = false;
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::Check4ClosedWindows()
{
  for (POSITION pos = checkedWindows->GetHeadPosition(); pos;)
  {
    POSITION apos = pos;
    HWND hwnd = (HWND)checkedWindows->GetNext(pos);

    if (IsWindow(hwnd))
      continue;

    checkedWindows->RemoveAt(apos);
  }
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnSize(UINT nType, int cx, int cy)
{
  CDialogEx::OnSize(nType, cx, cy);

  if (nType == SIZE_MINIMIZED)
  {
    ShowWindow(SW_HIDE);
  }
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnSelchangeCbwindows()
{
  int i = cbWindows.GetCurSel();

  if (i == -1)
  {
    edTitle.SetWindowTextA("");
    edLeft.SetWindowTextA("");
    edTop.SetWindowTextA("");
    edWidth.SetWindowTextA("");
    edHeight.SetWindowTextA("");
    edAutotype.SetWindowTextA("");
    edClass.SetWindowTextA("");
    cbUseClass.SetCheck(true);
    edAutoDelay.SetWindowTextA("");
    cbCmpMode.SetCurSel(0);

    return;
  }

  CString title;
  cbWindows.GetLBText(i, title);
  edTitle.SetWindowTextA(title);

  WINDOWDATA *data = (WINDOWDATA*)cbWindows.GetItemDataPtr(i);

  CString text;

  if (data->left == -1) text = "";
  else text.Format("%d", data->left);
  edLeft.SetWindowTextA(text);

  if (data->top == -1) text = "";
  else text.Format("%d", data->top);
  edTop.SetWindowTextA(text);

  if (data->width == -1) text = "";
  else text.Format("%d", data->width);
  edWidth.SetWindowTextA(text);

  if (data->height == -1) text = "";
  else text.Format("%d", data->height);
  edHeight.SetWindowTextA(text);

  text.Format("%d", data->auto_delay);
  edAutoDelay.SetWindowTextA(text);

  edAutotype.SetWindowTextA(data->csAutotype);

  edClass.SetWindowTextA(data->csClass);

  cbUseClass.SetCheck(data->bUseClass);

  cbCmpMode.SetCurSel(data->cmp_mode);

  btnApply.EnableWindow(false);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnChangeEdtitle()
{
  btnApply.EnableWindow(true);
  cbCmpMode.SetCurSel(0);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnBnClickedBtnapply()
{
  CString text;
  int i = cbWindows.GetCurSel();

  btnApply.EnableWindow(false);

  if (i == -1)
    return;

  edTitle.GetWindowTextA(text);

  WINDOWDATA *data = (WINDOWDATA*)cbWindows.GetItemDataPtr(i);
  cbWindows.DeleteString(i);

  i = cbWindows.AddString(text);
  cbWindows.SetItemDataPtr(i, data);

  edLeft.GetWindowTextA(text);
  if (text == "") data->left = -1;
  else            data->left = atoi(text);

  edTop.GetWindowTextA(text);
  if (text == "") data->top = -1;
  else            data->top= atoi(text);

  edWidth.GetWindowTextA(text);
  if (text == "") data->width = -1;
  else            data->width= atoi(text);

  edHeight.GetWindowTextA(text);
  if (text == "") data->height = -1;
  else            data->height = atoi(text);

  edAutoDelay.GetWindowTextA(text);
  data->auto_delay = atoi(text);

  edAutotype.GetWindowTextA(data->csAutotype);

  data->bUseClass = cbUseClass.GetCheck();

  data->cmp_mode = cbCmpMode.GetCurSel();

  cbWindows.SetCurSel(i);

  SaveData();
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnChangeEdheight()
{
  btnApply.EnableWindow(true);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnChangeEdleft()
{
  btnApply.EnableWindow(true);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnChangeEdtop()
{
  btnApply.EnableWindow(true);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnChangeEdwidth()
{
  btnApply.EnableWindow(true);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnBnClickedBtndelete()
{
  int i = cbWindows.GetCurSel();

  if (i == -1)
    return;

  WINDOWDATA *data = (WINDOWDATA*)cbWindows.GetItemDataPtr(i); 
  delete data;

  cbWindows.DeleteString(i);
  cbWindows.SetCurSel(-1);
  OnSelchangeCbwindows();
  SaveData();
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnIconmenuRepositionall()
{
  bNoAutotype = true;
  checkedWindows->RemoveAll();
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnEnChangeEdautotype()
{
  btnApply.EnableWindow(true);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnBnClickedCbuseclass()
{
  btnApply.EnableWindow(true);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnEnChangeEdautodelay()
{
  btnApply.EnableWindow(true);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnCbnSelchangeCbcmpmode()
{
  btnApply.EnableWindow(true);
}


//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnIconmenuExit()
{
  PostMessage(WM_CLOSE, 0, NULL);
}
