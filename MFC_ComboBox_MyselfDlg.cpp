
// MFC_ComboBox_MyselfDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC_ComboBox_Myself.h"
#include "MFC_ComboBox_MyselfDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCComboBoxMyselfDlg 对话框



CMFCComboBoxMyselfDlg::CMFCComboBoxMyselfDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_COMBOBOX_MYSELF_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCComboBoxMyselfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cdx);
}

BEGIN_MESSAGE_MAP(CMFCComboBoxMyselfDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCComboBoxMyselfDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CMFCComboBoxMyselfDlg 消息处理程序

BOOL CMFCComboBoxMyselfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//这里使用了combox控件对象的自带的成员函数Addstring来处理，会自动在已有的菜单栏最后添加
	m_cdx.AddString(TEXT("松下宋荣子"));
	//这里采用combox的Deletestring成员函数
	//这里需要传入菜单栏的项目的索引来删除，采用从0开始计数
	m_cdx.DeleteString(0);//表示删除第一个
	//插入，采用InsertString函数，第一个参数表示插入的位置，第二个参数表示插入的内容
	m_cdx.InsertString(1, TEXT("泷泽萝拉"));

	//这里采用成员函数SetCurSel来设置当前菜单栏的默认选项，第一个参数是表示索引的位置
	m_cdx.SetCurSel(1);

	//采用GetCurSel来获取当前选择的菜单栏,该函数的返回值为当前选项的索引，所以可以通过索引来取得后续
	int index = m_cdx.GetCurSel();
	//采用GetLBText函数来根据索引来得到对应的内容，函数的第二个参数是CString的变量
	CString str;
	m_cdx.GetLBText(index, str);
	//再用messageBox来显示得到的默认子菜单的内容
	MessageBox(str, TEXT("默认子菜单"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCComboBoxMyselfDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCComboBoxMyselfDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCComboBoxMyselfDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCComboBoxMyselfDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_cdx.GetCurSel();//得到选择的索引
	CString str;
	m_cdx.GetLBText(index, str);//将索引对应的内容传递给CString字符串
	MessageBox(str, TEXT("你选定的内容为"));
}
