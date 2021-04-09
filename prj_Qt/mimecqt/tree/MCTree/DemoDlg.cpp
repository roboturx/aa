// DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"
#include ".\demodlg.h"

// CDemoDlg dialog

IMPLEMENT_DYNAMIC(CDemoDlg, CDialog)
CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent)
{
}

CDemoDlg::~CDemoDlg()
{
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_COLUMNTREE, OnTreeSelchanged)
	ON_NOTIFY(NM_DBLCLK, IDC_COLUMNTREE, OnTreeDblclk)
END_MESSAGE_MAP()

// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// find the placeholder, get its position and destroy it
	CRect rcTreeWnd;
	CWnd* pPlaceholderWnd = GetDlgItem(IDC_COLUMNTREE);
	pPlaceholderWnd->GetWindowRect(&rcTreeWnd);
	ScreenToClient(&rcTreeWnd);
	pPlaceholderWnd->DestroyWindow();

	// create the multi-column tree window
	m_TreeWnd.CreateEx(WS_EX_CLIENTEDGE, NULL, NULL, WS_CHILD | WS_VISIBLE,
		rcTreeWnd, this, IDC_COLUMNTREE);

	CTreeCtrl& tree = m_TreeWnd.GetTreeCtrl();
	CHeaderCtrl& header = m_TreeWnd.GetHeaderCtrl();

	DWORD dwStyle = GetWindowLong(tree, GWL_STYLE);
	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_FULLROWSELECT | TVS_DISABLEDRAGDROP;
	SetWindowLong(tree, GWL_STYLE, dwStyle);

	m_ImgList.Create(IDB_IMAGES, 16, 1, RGB(255,0,255));
	tree.SetImageList(&m_ImgList, TVSIL_NORMAL);

	HDITEM hditem;
	hditem.mask = HDI_TEXT | HDI_WIDTH | HDI_FORMAT;
	hditem.fmt = HDF_LEFT | HDF_STRING;
	hditem.cxy = 200;
	hditem.pszText = "Employee";
	header.InsertItem(0, &hditem);
	hditem.cxy = 100;
	hditem.pszText = "ID Code";
	header.InsertItem(1, &hditem);
	hditem.cxy = 100;
	hditem.pszText = "Salary";
	header.InsertItem(2, &hditem);
	m_TreeWnd.UpdateColumns();

	HTREEITEM hRoot = tree.InsertItem("All Employees", 0, 0, TVI_ROOT);
	HTREEITEM hCat = tree.InsertItem("New York", 0, 0, hRoot);
	tree.InsertItem("John Smith\tA00012\t40,000 USD", 1, 1, hCat);
	tree.InsertItem("Julia Brown\tA00235\t36,000 USD", 1, 1, hCat);
	tree.InsertItem("Kevin Jones\tA00720\t28,000 USD", 1, 1, hCat);
	tree.Expand(hCat, TVE_EXPAND);
	hCat = tree.InsertItem("Warsaw", 0, 0, hRoot);
	tree.InsertItem("Jan Kowalski\tB00241\t50,000 PLN", 1, 1, hCat);
	tree.InsertItem("Maria Nowak\tB00532\t34,000 PLN", 1, 1, hCat);
	tree.InsertItem("Adam Jaworek\tB00855\t31,500 PLN", 1, 1, hCat);
	tree.Expand(hCat, TVE_EXPAND);
	tree.Expand(hRoot, TVE_EXPAND);

	return TRUE;
}

void CDemoDlg::OnTreeSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMTREEVIEW* pNMTreeView = (NMTREEVIEW*)pNMHDR;

	// find the label of the selected item
	CString strLabel;
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	if (hItem)
	{
		CTreeCtrl& tree = m_TreeWnd.GetTreeCtrl();
		strLabel = tree.GetItemText(hItem);
		int nPos = strLabel.Find('\t');
		if (nPos >= 0)
			strLabel = strLabel.Left(nPos);
	}

	// display it on the static control
	SetDlgItemText(IDC_LABEL, strLabel);

	*pResult = 0;
}

void CDemoDlg::OnTreeDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	AfxMessageBox("NM_DBLCLK Handler");
}
