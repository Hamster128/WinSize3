
// WinSize3Dlg.h : header file
//

#pragma once

#include "dlgName.h"
#include "ThreadControl.h"

class CWinSize3Dlg;

typedef struct
{
  int left, top, width, height;
  CString csClass, csAutotype;
  CString csExecuteable;
  bool bUseClass;
  int auto_delay;
  int cmp_mode;
  bool keep, activate, keepDisplayOn;

  HWND hwnd;
  CThreadControl Thread;
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

  HICON m_hIcon;
  CSystemTray m_TrayIcon;
  RECT desktop;
  CXML xml;
  int iCurTab;
  CPtrList *checkedWindows;
  bool bFirstShow, bNoAutotype;
  int pauseWindowChecks;
  int hideBalloon;
  bool bDisplayRequired;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
  LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
  void SaveData();
  void LoadData();
  CString GetTabTitle(int idx);
  LPARAM GetTabLParam(int idx);
  int FindThis(HWND hwnd, CString &csTitle, CString &csClass, CString &csExecuteable);
  void ClearComboBox();
  void Check4ClosedWindows();
  CString getExecuteableOfWindow(const HWND &hwnd);

	// Generated message map functions
	virtual BOOL OnInitDialog();
  void CustomizeMenu();
  void CheckMenu();
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
  afx_msg void OnMenuTab0();
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
  CTabCtrl tabTabs;
  afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnNMRClickTab1(NMHDR *pNMHDR, LRESULT *pResult);
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  CButton cbKeep;
  afx_msg void OnBnClickedCbkeep();
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  afx_msg void OnClickedCbSpecialKey();
  CButton cbSpecialKey;
  afx_msg void OnClickedActivateWindow();
  CButton cbActivateWindow;
  CButton cbKeepDisplayOn;
  afx_msg void OnClickedKeepDisplayOn();
  CEdit edExe;
  afx_msg void OnEnChangeEdexe();
};
