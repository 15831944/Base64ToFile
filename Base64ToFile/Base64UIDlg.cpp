// Base64Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Base64UI.h"
#include "Base64UIDlg.h"
#include <string>
#include "base64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBase64Dlg �Ի���




CBase64UIDlg::CBase64UIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBase64UIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBase64UIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_pEdit);
	DDX_Control(pDX, IDC_STATI_TIP, m_pTip);
}

BEGIN_MESSAGE_MAP(CBase64UIDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CBase64UIDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CBase64Dlg ��Ϣ�������

BOOL CBase64UIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO_EN);
	radio->SetCheck(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBase64UIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBase64UIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int SaveToFile(const std::string & strData,bool bEncode)
{
	if (strData.empty())
	{
		printf("No File OutPut! \n");
		return -1;
	}

	const wchar_t* pFileName = NULL;
	if (bEncode)
	{
		pFileName = L"Base64����.dat";
	}
	else
	{
		pFileName = L"Base64����.dat";
	}
	FILE* pFile = _wfopen(pFileName,L"wb");
	if (pFile)
	{
		fwrite(strData.c_str(),1,strData.length(),pFile);
		fclose(pFile);
		return 0;
	}
	return -1;
}

void CBase64UIDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);

	m_pTip.SetWindowText(L"");
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO_EN);
	int m_nEncryption = radio->GetCheck();

	CString strData; 
	m_pEdit.GetWindowText(strData);
	if (strData.IsEmpty())
		return;
	DWORD nLen = m_pEdit.GetTextLength();
	int nMemSize = nLen *2 +10;
	char* pData = (char*)malloc(nMemSize);
	if (pData == NULL)
	{
		return ;
	}
	memset(pData,0,nMemSize);

	int nTextLen = GetWindowTextA(m_pEdit.m_hWnd,pData,nMemSize);
	if (m_nEncryption == 0)
	{
		std::string result = base64_decode(pData);
		if(result.empty())
		{
			AfxMessageBox(L"BASE64����ʧ��!");
		}
		else
		{
			SaveToFile(result,false);
			m_pTip.SetWindowText(L"������ɣ�");
		}
		free(pData);
		pData = NULL;
	}
	else if (m_nEncryption == 1)
	{
		std::string result = base64_encode(pData,nTextLen);
		if(result.empty())
		{
			AfxMessageBox(L"BASE64����ʧ��!");
		}
		else
		{
			SaveToFile(result,true);
			m_pTip.SetWindowText(L"������ɣ�");
		}
		free(pData);
		pData = NULL;
	}
	else
	{
		return ;
	}
	//OnOK();
}
