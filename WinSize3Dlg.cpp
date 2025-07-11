// WinSize3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinSize3.h"
#include "WinSize3Dlg.h"
#include "afxdialogex.h"
#include "psapi.h"

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
  DDX_Control(pDX, IDC_EDHEIGHT, edHeight);
  DDX_Control(pDX, IDC_EDLEFT, edLeft);
  DDX_Control(pDX, IDC_EDTOP, edTop);
  DDX_Control(pDX, IDC_EDWIDTH, edWidth);
  DDX_Control(pDX, IDC_EDAUTOTYPE, edAutotype);
  DDX_Control(pDX, IDC_CBUSECLASS, cbUseClass);
  DDX_Control(pDX, IDC_EDCLASS, edClass);
  DDX_Control(pDX, IDC_EDAUTODELAY, edAutoDelay);
  DDX_Control(pDX, IDC_CBCMPMODE, cbCmpMode);
  DDX_Control(pDX, IDC_TAB1, tabTabs);
  DDX_Control(pDX, IDC_CBKEEP, cbKeep);
  DDX_Control(pDX, IDC_CB_SPECIAL_KEY, cbSpecialKey);
  DDX_Control(pDX, IDC_ACTIVATE_WINDOW, cbActivateWindow);
  DDX_Control(pDX, IDC_KEEP_DISPLAY_ON, cbKeepDisplayOn);
  DDX_Control(pDX, IDC_EDEXE, edExe);
  DDX_Control(pDX, IDC_CLOSE_WINDOW, cbCloseWindow);
  DDX_Control(pDX, IDC_EDDELAY, edDelay);
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
  ON_COMMAND(ID_STANDARD, &CWinSize3Dlg::OnMenuTab0)
  ON_EN_CHANGE(IDC_EDAUTOTYPE, &CWinSize3Dlg::OnEnChangeEdautotype)
  ON_BN_CLICKED(IDC_CBUSECLASS, &CWinSize3Dlg::OnBnClickedCbuseclass)
  ON_EN_CHANGE(IDC_EDAUTODELAY, &CWinSize3Dlg::OnEnChangeEdautodelay)
  ON_CBN_SELCHANGE(IDC_CBCMPMODE, &CWinSize3Dlg::OnCbnSelchangeCbcmpmode)
  ON_COMMAND(ID_ICONMENU_EXIT, &CWinSize3Dlg::OnIconmenuExit)
  ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CWinSize3Dlg::OnTcnSelchangeTab1)
  ON_NOTIFY(NM_RCLICK, IDC_TAB1, &CWinSize3Dlg::OnNMRClickTab1)
  ON_BN_CLICKED(IDC_CBKEEP, &CWinSize3Dlg::OnBnClickedCbkeep)
  ON_BN_CLICKED(IDC_CB_SPECIAL_KEY, &CWinSize3Dlg::OnClickedCbSpecialKey)
  ON_BN_CLICKED(IDC_ACTIVATE_WINDOW, &CWinSize3Dlg::OnClickedActivateWindow)
  ON_BN_CLICKED(IDC_KEEP_DISPLAY_ON, &CWinSize3Dlg::OnClickedKeepDisplayOn)
  ON_EN_CHANGE(IDC_EDEXE, &CWinSize3Dlg::OnEnChangeEdexe)
  ON_BN_CLICKED(IDC_CLOSE_WINDOW, &CWinSize3Dlg::OnBnClickedCloseWindow)
  ON_EN_CHANGE(IDC_EDDELAY, &CWinSize3Dlg::OnChangeEddelay)
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
  iCurTab = 0;
  pauseWindowChecks = 0;
  hideBalloon = 0;

  CreateDirectory(commonDocs__ + "\\WinSize3", NULL);

  SetTimer(0, 1, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::CustomizeMenu()
{
  while (m_TrayIcon.pMenu->GetMenuItemCount() > 2)
    m_TrayIcon.pMenu->RemoveMenu(1, MF_BYPOSITION);

  for (int i = 1; i < tabTabs.GetItemCount() - 1; i++)
  {
    MENUITEMINFO mi;
    memset(&mi, 0, sizeof(mi));
    mi.cbSize = sizeof(mi);
    mi.fMask = MIIM_ID | MIIM_STRING;
    mi.wID = 7000 + i;
    mi.dwTypeData = (LPSTR)(const char*)GetTabTitle(i);
    m_TrayIcon.pMenu->InsertMenuItem(i, &mi, TRUE);
  }

  CheckMenu();
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::CheckMenu()
{
  if (iCurTab == 0)  m_TrayIcon.pMenu->CheckMenuItem(ID_STANDARD, MF_CHECKED | MF_BYCOMMAND);
  else               m_TrayIcon.pMenu->CheckMenuItem(ID_STANDARD, MF_UNCHECKED | MF_BYCOMMAND);

  for (int i = 1; i < tabTabs.GetItemCount() - 1; i++)
  {
    if (iCurTab == i) m_TrayIcon.pMenu->CheckMenuItem(7000+i, MF_CHECKED | MF_BYCOMMAND);
    else              m_TrayIcon.pMenu->CheckMenuItem(7000+i, MF_UNCHECKED | MF_BYCOMMAND);
  }
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
    hideBalloon = 4;
    return;
  }

  CString csExecuteable = getExecuteableOfWindow(hwnd);

  CString csTitle, csClass;
  int i = FindThis(hwnd, csTitle, csClass, csExecuteable);

  WINDOWDATA *data;

  if (i == -1)
  {
    i = cbWindows.AddString(csTitle);
    data = new WINDOWDATA;
    data->csClass = csClass;
    data->bUseClass = true;
    data->csExecuteable = csExecuteable;
    data->cmp_mode = 1;
    data->delay = 0;
    data->auto_delay = 100;
    data->keep = false;
    data->activate = false;
    data->close = false;
    data->keepDisplayOn = false;
    cbWindows.SetItemDataPtr(i, data);

    m_TrayIcon.ShowBalloon("New " + csTitle);
    hideBalloon = 4;
  }
  else
  {
    data = (WINDOWDATA*)cbWindows.GetItemDataPtr(i);

    m_TrayIcon.ShowBalloon("Updated " + csTitle);
    hideBalloon = 4;
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

  cbWindows.ResetContent();
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::LoadData()
{
  CString key;
  FILE *fp;

  ClearComboBox();

  tabTabs.DeleteAllItems();
  tabTabs.InsertItem(0, "Standard");
  tabTabs.InsertItem(1, "   +");

  if (!xml.Open(commonDocs__ + "\\WinSize3\\Config.xml"))
    return;

  CXMLNode *node = xml.Root.FindByPath("groups");
  CString csGroup;

  if (node)
  {
    TCITEM item;
    int i = 1;

    for (CXMLNodeIterator w(node); w; w.NextChild())
    {
      item.mask = TCIF_TEXT | TCIF_PARAM;
      item.pszText = w->Data;
      item.lParam = atoi(w->Property("id"));
      tabTabs.InsertItem(i++, &item);
    }

    if (iCurTab > tabTabs.GetItemCount() - 2)
      iCurTab = tabTabs.GetItemCount() - 2;

    tabTabs.SetCurSel(iCurTab);

    if(iCurTab)
      csGroup.Format("_%d", GetTabLParam(iCurTab));
  }

  CustomizeMenu();

  key.Format("%dx%d%s", desktop.right, desktop.bottom, csGroup);
  node = xml.Root.FindByPath(key);

  if (!node)
    return;

  for (CXMLNodeIterator w(node); w; w.NextChild())
  {
    WINDOWDATA *data = new WINDOWDATA;

    data->left = atoi((*w)["left"]);
    data->top = atoi((*w)["top"]);
    data->width = atoi((*w)["width"]);
    data->height = atoi((*w)["height"]);
    data->csClass = (*w)["class"];
    data->csAutotype = (*w)["autotype"];
    data->bUseClass = atoi((*w)["use_class"]);
    data->delay = atoi((*w)["delay"]);
    data->auto_delay = atoi((*w)["auto_delay"]);
    data->cmp_mode = atoi((*w)["cmp_mode"]);
    data->keep = atoi((*w)["keep"]);
    data->activate = atoi((*w)["activate"]);
    data->close = atoi((*w)["close"]);
    data->keepDisplayOn = atoi((*w)["keep_display_on"]);
    data->csExecuteable = (*w)["executeable"];

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
CString CWinSize3Dlg::GetTabTitle(int idx)
{
  char buf[256];

  TCITEM ti;
  ti.mask = TCIF_TEXT;
  ti.pszText = buf;
  ti.cchTextMax = sizeof(buf);

  tabTabs.GetItem(idx, &ti);

  return buf;
}

//------------------------------------------------------------------------------------------
LPARAM CWinSize3Dlg::GetTabLParam(int idx)
{
  TCITEM ti;
  ti.mask = TCIF_PARAM;

  tabTabs.GetItem(idx, &ti);

  return ti.lParam;
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::SaveData()
{
  CString key, text;

  xml.Root.SetName("WinSize3");

  CXMLNode *node = xml.Root.FindByPath("groups");
  CString csGroup;

  if (node)
    node->Delete();

  node = xml.Root.AddChild("groups");
  for (int i = 1; i < tabTabs.GetItemCount() - 1; i++)
  {
    CString csTitle = GetTabTitle(i);

    CXMLNode *w = node->AddChild("name", csTitle);
    w->SetProperty("id", GetTabLParam(i));

    if (i == tabTabs.GetCurSel())
      csGroup.Format("_%d", GetTabLParam(i));
  }

  key.Format("%dx%d%s", desktop.right, desktop.bottom, csGroup);
  node = xml.Root.FindByPath(key);

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
    w->AddChild("delay", data->delay);
    w->AddChild("auto_delay", data->auto_delay);
    w->AddChild("cmp_mode", data->cmp_mode);
    w->AddChild("keep", data->keep);
    w->AddChild("activate", data->activate);
    w->AddChild("close", data->close);
    w->AddChild("keep_display_on", data->keepDisplayOn);
    w->AddChild("executeable", data->csExecuteable);
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
int CWinSize3Dlg::FindThis(HWND hwnd, CString &csTitle, CString &csClass, CString &csExecuteable)
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
         (data->cmp_mode == 1 && csTitle==csEntry)           ||
          data->cmp_mode == 2                                   )                   &&
        (csClass == data->csClass || !data->bUseClass)                              &&
        (!data->csExecuteable.GetLength() || data->csExecuteable == csExecuteable)      )
      return i;
  }

  return -1;
}

//------------------------------------------------------------------------------------------
void Key(BYTE key, int press_release = 3)
{
  if (press_release & 1)
    keybd_event(key, 0, 0, 0);

  if (press_release & 2)
    keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
}

//------------------------------------------------------------------------------------------
UINT AFX_CDECL windowPositionThread(LPVOID pParam)
{
  WINDOWDATA* data = (WINDOWDATA*)pParam;

  ::ShowWindow(data->hwnd, SW_SHOWNOACTIVATE);

  RECT rect;
  ::GetWindowRect(data->hwnd, &rect);

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

  if (left != rect.left || top != rect.top || width != rect.right - rect.left || height != rect.bottom - rect.top || data->activate)
  {
    Sleep(data->delay);
    ::SetWindowPos(data->hwnd, NULL, left, top, width, height, SWP_NOZORDER | SWP_NOACTIVATE);
  }

  return 0;
}

//------------------------------------------------------------------------------------------
CString CWinSize3Dlg::getExecuteableOfWindow(const HWND &hwnd)
{
  TCHAR buffer[MAX_PATH] = { 0 };
  DWORD dwProcId = 0;

  GetWindowThreadProcessId(hwnd, &dwProcId);

  HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcId);

  if (!hProc)
    return "";

  GetModuleFileNameEx(hProc, NULL, buffer, MAX_PATH);

  CloseHandle(hProc);

  return buffer;
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::CheckWindow(HWND hwnd)
{
  WINDOWPLACEMENT wp;
  wp.length = sizeof(wp);

  if (!::IsWindowVisible(hwnd))
    return;

  if (::IsIconic(hwnd))
    return;

  if (::GetWindowPlacement(hwnd, &wp) && wp.showCmd == SW_HIDE)
    return;

  if (!wp.rcNormalPosition.right)
    return;

  CString csExecuteable = getExecuteableOfWindow(hwnd);

  CString csTitle, csClass;
  int i = FindThis(hwnd, csTitle, csClass, csExecuteable);

  if (i == -1)
    return;

  WINDOWDATA *data = (WINDOWDATA*)cbWindows.GetItemDataPtr(i);

  if (data->close)
  {
    ::PostMessage(hwnd, WM_CLOSE, 0, 0);
    return;
  }

  bool bAlreadyPositioned = false;

  for (POSITION pos = checkedWindows->GetHeadPosition(); pos;)
  {
    if (checkedWindows->GetNext(pos) == hwnd)
    {
      bAlreadyPositioned = true;
      break;
    }
  }

  if (data->keepDisplayOn)
    bDisplayRequired = true;

  if (bAlreadyPositioned && !data->keep)
    return;

  // position window in a background thread, some windows are not respondig, so we don`t want to hang too
  if (!data->Thread.WasStarted())
  {
    data->hwnd = hwnd;
    data->Thread.Begin(&windowPositionThread, data);
    return;
  }

  if (!data->Thread.Join(0))
    return;

  if (!bAlreadyPositioned)
    checkedWindows->AddTail(data->hwnd);

  if (bNoAutotype || bAlreadyPositioned)
    return;

  if (!data->csAutotype.GetLength() && !data->activate)
    return;

  Sleep(data->auto_delay);

  ::ShowWindow(data->hwnd, SW_SHOW);
  ::SetForegroundWindow(data->hwnd);
  ::SetActiveWindow(data->hwnd);

  if (!data->csAutotype.GetLength())
    return;

  CString &asKeys = data->csAutotype;

  INPUT inp;

  memset(&inp, 0, sizeof(inp));
  inp.type = INPUT_KEYBOARD;
  inp.ki.dwFlags = KEYEVENTF_UNICODE;

  for (int i = 0; i < asKeys.GetLength(); i++)
  {
    char c = asKeys[i];

    Sleep(50);

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
      else if (asKey == "ALT DOWN") Key(VK_LMENU, 1);
      else if (asKey == "ALT UP") Key(VK_LMENU, 2);

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
void CWinSize3Dlg::OnTimer(UINT_PTR nIDEvent)
{
  RECT rect;

  if (bFirstShow)
  {
    KillTimer(0);
    ShowWindow(SW_HIDE);
    SetTimer(0, 500, NULL);
  }

  if (hideBalloon)
  {
    hideBalloon--;

    if (!hideBalloon)
      m_TrayIcon.HideBalloon();
  }

  // check for desktop resolution changes
  const HWND hDesktop = ::GetDesktopWindow();
  ::GetWindowRect(hDesktop, &rect);

  if (memcmp(&rect, &desktop, sizeof(rect)) != 0)
  {
    memmove(&desktop, &rect, sizeof(rect));
    iCurTab = 0;

    LoadData();
    CustomizeMenu();

    checkedWindows->RemoveAll();

    if(bFirstShow)
      bNoAutotype = true;

    CXMLNode *n = xml.Root.FindByPath("newResolutionTimeoutSecs");

    if (n)
      pauseWindowChecks = n->asInt() * 2;
  }

  if (pauseWindowChecks) 
  {
    pauseWindowChecks--;
    return;
  }

  bDisplayRequired = false;

  EnumWindows(EnumWindowsProc, (LPARAM)this);

  if(bDisplayRequired)
    SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);
  else
    SetThreadExecutionState(ES_CONTINUOUS);

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

    if (!IsWindow(hwnd))
    {
      checkedWindows->RemoveAt(apos);
      continue;
    }

    WINDOWPLACEMENT wp;
    wp.length = sizeof(wp);

    if (::IsIconic(hwnd))
    {
      checkedWindows->RemoveAt(apos);
      continue;
    }

    if(!::IsWindowVisible(hwnd))
    {
      checkedWindows->RemoveAt(apos);
      continue;
    }

    if (::GetWindowPlacement(hwnd, &wp) && wp.showCmd == SW_HIDE)
    {
      checkedWindows->RemoveAt(apos);
      continue;
    }

    if (!wp.rcNormalPosition.right)
    {
      checkedWindows->RemoveAt(apos);
      continue;
    }
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
    edDelay.SetWindowTextA("");
    edAutotype.SetWindowTextA("");
    edClass.SetWindowTextA("");
    edExe.SetWindowTextA("");
    cbUseClass.SetCheck(true);
    edAutoDelay.SetWindowTextA("");
    cbCmpMode.SetCurSel(0);
    cbKeep.SetCheck(0);
    cbActivateWindow.SetCheck(0);
    cbCloseWindow.SetCheck(0);
    cbKeepDisplayOn.SetCheck(0);

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

  text.Format("%d", data->delay);
  edDelay.SetWindowTextA(text);

  text.Format("%d", data->auto_delay);
  edAutoDelay.SetWindowTextA(text);

  edAutotype.SetWindowTextA(data->csAutotype);

  edClass.SetWindowTextA(data->csClass);

  cbUseClass.SetCheck(data->bUseClass);

  edExe.SetWindowTextA(data->csExecuteable);

  cbCmpMode.SetCurSel(data->cmp_mode);

  cbKeep.SetCheck(data->keep);

  cbActivateWindow.SetCheck(data->activate);

  cbCloseWindow.SetCheck(data->close);

  cbKeepDisplayOn.SetCheck(data->keepDisplayOn);

  btnApply.EnableWindow(false);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnChangeEdtitle()
{
  btnApply.EnableWindow(true);

  if(cbCmpMode.GetCurSel() == 1)
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

  edDelay.GetWindowTextA(text);
  data->delay = atoi(text);

  edAutoDelay.GetWindowTextA(text);
  data->auto_delay = atoi(text);

  edExe.GetWindowTextA(text);
  data->csExecuteable = text;

  edAutotype.GetWindowTextA(data->csAutotype);

  data->bUseClass = cbUseClass.GetCheck();

  data->cmp_mode = cbCmpMode.GetCurSel();

  data->keep = cbKeep.GetCheck();

  data->activate = cbActivateWindow.GetCheck();

  data->close = cbCloseWindow.GetCheck();

  data->keepDisplayOn = cbKeepDisplayOn.GetCheck();

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
void CWinSize3Dlg::OnMenuTab0()
{
  tabTabs.SetCurSel(0);
  OnTcnSelchangeTab1(NULL, NULL);
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

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
  if (tabTabs.GetCurSel() == tabTabs.GetItemCount() - 1)
  {
    dlgName dlg;

    if (dlg.DoModal() == IDCANCEL)
    {
      tabTabs.SetCurSel(0);
      return;
    }

    iCurTab = tabTabs.GetCurSel();

    TCITEM item;
    item.mask = TCIF_TEXT | TCIF_PARAM;
    item.pszText = dlg.csName.GetBuffer(0);
    item.lParam = rand();
    tabTabs.SetItem(iCurTab, &item);

    tabTabs.InsertItem(iCurTab + 1, "  +");
    CustomizeMenu();

    ClearComboBox();
    OnSelchangeCbwindows();

    SaveData();
    return;
  }

  iCurTab = tabTabs.GetCurSel();
  LoadData();
  OnSelchangeCbwindows();
  CheckMenu();

  bNoAutotype = true;
  checkedWindows->RemoveAll();
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnNMRClickTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
  *pResult = 0;

  int idx = tabTabs.GetCurSel();

  if (idx == 0 || idx == tabTabs.GetItemCount() - 1)
    return;

  dlgName dlg;
  CString csOldName;

  dlg.csName = GetTabTitle(idx);

  if (dlg.DoModal() == IDCANCEL)
    return;

  if (!dlg.csName.GetLength())
  {
    if (AfxMessageBox("Delete Tab?", MB_OKCANCEL) != IDOK)
      return;

    int id = GetTabLParam(idx);

    iCurTab--;
    LoadData();
    OnSelchangeCbwindows();

    bNoAutotype = true;
    checkedWindows->RemoveAll();

    CString key;
    key.Format("%dx%d_%d", desktop.right, desktop.bottom, id);
    CXMLNode *node = xml.Root.FindByPath(key);

    if (node)
      node->Delete();

    tabTabs.DeleteItem(idx);
    CustomizeMenu();

    SaveData();

    return;
  }

  TCITEM item;
  item.mask = TCIF_TEXT;
  item.pszText = dlg.csName.GetBuffer(0);
  tabTabs.SetItem(idx, &item);
  CustomizeMenu();

  SaveData();
}

//------------------------------------------------------------------------------------------
LRESULT CWinSize3Dlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  if (message == WM_COMMAND && wParam >= 7000 && wParam <= 7100)
  {
    tabTabs.SetCurSel(wParam-7000);
    OnTcnSelchangeTab1(NULL, NULL);
  }

  return CDialogEx::WindowProc(message, wParam, lParam);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnBnClickedCbkeep()
{
  btnApply.EnableWindow(true);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnClickedKeepDisplayOn()
{
  btnApply.EnableWindow(true);
}

//------------------------------------------------------------------------------------------
BOOL CWinSize3Dlg::PreTranslateMessage(MSG* pMsg)
{
  if (GetFocus() == &edAutotype)
  {
    if (pMsg->message == WM_KEYDOWN && (pMsg->lParam & 0x40000000) == 0 && cbSpecialKey.GetCheck())
    {
      CString csText;
      edAutotype.GetWindowTextA(csText);

      BOOL bCtrl = ::GetKeyState(VK_CONTROL) & 0x8000;
      BOOL bShift = ::GetKeyState(VK_SHIFT) & 0x8000;
      BOOL bAlt = ::GetKeyState(VK_MENU) & 0x8000;

      switch (pMsg->wParam)
      {
      case VK_CONTROL: return(true);
      case VK_MENU: return(true);
      case VK_TAB: edAutotype.SetWindowTextA(csText + "{TAB}"); edAutotype.SetSel(-1); return(true);
      case VK_RETURN: edAutotype.SetWindowTextA(csText + "{RETURN}"); edAutotype.SetSel(-1); return(true);
      case VK_LWIN: edAutotype.SetWindowTextA(csText + "{LWIN DOWN}"); edAutotype.SetSel(-1); return(true);
      case VK_LEFT: edAutotype.SetWindowTextA(csText + "{LEFT}"); edAutotype.SetSel(-1); return(true);
      case VK_UP: edAutotype.SetWindowTextA(csText + "{UP}"); edAutotype.SetSel(-1); return(true);
      case VK_RIGHT: edAutotype.SetWindowTextA(csText + "{RIGHT}"); edAutotype.SetSel(-1); return(true);
      case VK_DOWN: edAutotype.SetWindowTextA(csText + "{DOWN}"); edAutotype.SetSel(-1); return(true);
      }

      if (bCtrl && pMsg->wParam != 219)
      {
        edAutotype.SetWindowTextA(csText + "{CTRL DOWN}" + (char)tolower(pMsg->wParam) + "{CTRL UP}"); 
        edAutotype.SetSel(-1);
      }
      
      if (bAlt && pMsg->wParam!=219)
      {
        edAutotype.SetWindowTextA(csText + "{ALT DOWN}" + (char)tolower(pMsg->wParam) + "{ALT UP}"); 
        edAutotype.SetSel(-1);
      }
    }

    if (pMsg->message == WM_KEYUP)
    {
      CString csText;
      edAutotype.GetWindowTextA(csText);

      switch (pMsg->wParam)
      {
      case VK_CONTROL: return(true);
      case VK_MENU: return(true);
      case VK_LWIN: edAutotype.SetWindowTextA(csText + "{LWIN UP}"); edAutotype.SetSel(-1); return(true);
      }
    }
  }


  return CDialogEx::PreTranslateMessage(pMsg);
}


//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnClickedCbSpecialKey()
{
  // TODO: Add your control notification handler code here
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnClickedActivateWindow()
{
  btnApply.EnableWindow(true);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnEnChangeEdexe()
{
  btnApply.EnableWindow(true);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnBnClickedCloseWindow()
{
  btnApply.EnableWindow(true);
}

//------------------------------------------------------------------------------------------
void CWinSize3Dlg::OnChangeEddelay()
{
  btnApply.EnableWindow(true);
}
