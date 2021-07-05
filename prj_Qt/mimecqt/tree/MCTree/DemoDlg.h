#pragma once

#include "ColumnTreeWnd.h"


class CDemoDlg : public CDialog
{
	DECLARE_DYNAMIC(CDemoDlg)

public:
	CDemoDlg(CWnd* pParent = NULL);
	virtual ~CDemoDlg();

	enum { IDD = IDD_DEMODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

protected:
	CColumnTreeWnd m_TreeWnd;
	CImageList m_ImgList;
public:
	virtual BOOL OnInitDialog();

protected:
	afx_msg void OnTreeSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTreeDblclk(NMHDR* pNMHDR, LRESULT* pResult);
};
