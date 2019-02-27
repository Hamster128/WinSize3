
// WinSize3Dlg.h : header file
//

#pragma once

typedef struct
{
  int left, top, width, height;
  CString csClass, csAutotype;
  bool bUseClass;
  int auto_delay;
  int cmp_mode;
} WINDOWDATA;


// CWinSize3Dlg dialog
class CWinSize3Dlg : public CDialogEx
{
// Construction
public:
	CWinSize3Dlg(CWnd* pParent = nullptr);
  // standard constructor
  void CheckWindow(HWND hwnd);


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINSIZE3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
  LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
  void SaveData();
  void LoadData();
  int FindThis(HWND hwnd, CString &csTitle, CString &csClass);
  void ClearComboBox();
  void Key(BYTE key, int press_release = 3);
  void Check4ClosedWindows();

	HICON m_hIcon;
  CSystemTray m_TrayIcon;
  RECT desktop;
  CXML xml;
  CPtrList *checkedWindows;
  bool bFirstShow, bNoAutotype;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
  CComboBox cbWindows;
  afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
  afx_msg
  void OnTimer(UINT_PTR nIDEvent);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  CEdit edTitle;
  afx_msg void OnSelchangeCbwindows();
  afx_msg void OnChangeEdtitle();
  CButton btnApply;
  afx_msg void OnBnClickedBtnapply();
//  CEdit edheight;
  CEdit edHeight;
  CEdit edLeft;
  CEdit edTop;
  CEdit edWidth;
  afx_msg void OnChangeEdheight();
  afx_msg void OnChangeEdleft();
  afx_msg void OnChangeEdtop();
  afx_msg void OnChangeEdwidth();
  afx_msg void OnBnClickedBtndelete();
  afx_msg void OnIconmenuRepositionall();
  CEdit edAutotype;
  afx_msg void OnEnChangeEdautotype();
  CButton cbUseClass;
  CEdit edClass;
  afx_msg void OnBnClickedCbuseclass();
  CEdit edAutoDelay;
  afx_msg void OnEnChangeEdautodelay();
  CComboBox cbCmpMode;
  afx_msg void OnCbnSelchangeCbcmpmode();
  afx_msg void OnIconmenuExit();
};
