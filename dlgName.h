#pragma once


// dlgName dialog

class dlgName : public CDialogEx
{
	DECLARE_DYNAMIC(dlgName)

public:
	dlgName(CWnd* pParent = nullptr);   // standard constructor
	virtual ~dlgName();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGNAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  CString csName;
};
