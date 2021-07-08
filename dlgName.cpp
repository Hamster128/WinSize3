// dlgName.cpp : implementation file
//

#include "stdafx.h"
#include "WinSize3.h"
#include "dlgName.h"
#include "afxdialogex.h"


// dlgName dialog

//------------------------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(dlgName, CDialogEx)

//------------------------------------------------------------------------------------------
dlgName::dlgName(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLGNAME, pParent)
  , csName(_T(""))
{

}

//------------------------------------------------------------------------------------------
dlgName::~dlgName()
{
}

//------------------------------------------------------------------------------------------
void dlgName::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDNAME, csName);
}

//------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(dlgName, CDialogEx)
END_MESSAGE_MAP()


// dlgName message handlers

