#pragma once

#include "ColumnTreeView.h"

class CDemoView : public CColumnTreeView
{
	DECLARE_DYNCREATE(CDemoView)
protected:
	CDemoView();
public:
	virtual ~CDemoView();

public:
	CDemoDoc* GetDocument() const;

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate();

protected:
	CImageList m_ImgList;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
};

#ifndef _DEBUG
inline CDemoDoc* CDemoView::GetDocument() const
   { return reinterpret_cast<CDemoDoc*>(m_pDocument); }
#endif

