#pragma once
// CDlgScreenCapturer 
#include "connection_wrapper.h"
#include "AGVideoWnd.h"
#include <map>
#include <string>
#include <vector>
#define IDC_SCREENCAPTURER_VIDEO      10030

class CMonitors {
public:
	typedef struct _MonitorInformation {
		MONITORINFOEX monitorInfo;
		int scale_num = 4;
		int scale_den = 4;
		std::string monitorName = "";
		bool canShare = true;
		HMONITOR hMonitor;
	}MonitorInformation, *PMonitorInformation, *LPMonitorInformation;
	CMonitors();
	~CMonitors();
	static BOOL MonitorFunc(HMONITOR hMonitor, HDC hDc, LPRECT lpRect, LPARAM lParam);
	void EnumMonitor();
	agora::rtc::Rectangle RectToRectangle(RECT rc);
	std::vector<MonitorInformation> GetMonitors() { return m_vecMonitorInfos; }
	MonitorInformation GetMonitorInformation(int index);
	agora::rtc::Rectangle GetMonitorRectangle(int index);
	bool GetMonitorRectangle(HMONITOR hMonitor, agora::rtc::Rectangle& screenRegion);
	agora::rtc::Rectangle GetScreenRect();
	int GetMonitorCount() { return m_vecMonitorInfos.size(); }
	bool IsValid();
	bool CheckMonitorValid(HMONITOR hMonitor);
	bool GetWindowRect(HWND hWnd, agora::rtc::Rectangle& regionRect);
private:
	void Clear();
	std::vector<MonitorInformation> m_vecMonitorInfos;
	std::vector<MonitorInformation> m_vecEffectiveMonitorInfos;
	RECT m_screenRegion;

};

class CDlgScreenCapturer : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgScreenCapturer)

public:
	CDlgScreenCapturer(CWnd* pParent = nullptr);   // 
	virtual ~CDlgScreenCapturer();

	enum { IDD = IDD_DIALOG_SCREENCAPTURER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	static BOOL CALLBACK WndEnumProc(HWND hWnd, LPARAM lParam);
	afx_msg void OnBnClickedButtonJoinchannel();
	afx_msg LRESULT OnEIDConnected(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDDisConnected(WPARAM wParam, LPARAM lParam);
public:
	//Initialize the Agora SDK
	bool InitAgora();
	//UnInitialize the Agora SDK
	void UnInitAgora();

	void JoinChannel();
	void LeaveChannel();
private:
	void InitMonitorInfos();
	//refresh window to show.
	void ReFreshWnd();
	//resume window
	void ResumeStatus();
	std::unique_ptr<LowlevelSdk> sdk_ptr;
	//Connections, one connection for one camera track
	std::shared_ptr<ConnectionWrapper> m_connection;
	//Only one audio track
	agora::agora_refptr<agora::rtc::ILocalAudioTrack> m_localAudioTrack;
	//Local video tracks for screen capture
	agora::agora_refptr<agora::rtc::ILocalVideoTrack> m_screenCaptureVideoTrack;
	//Local video renders for screen capture
	agora::agora_refptr<agora::rtc::IVideoRenderer> m_localScreenCaptureRender;
	agora::agora_refptr<agora::rtc::IScreenCapturer> m_localScreenCapture;
	std::map<std::string, HWND> m_mapUserVideoTrack;
	int m_maxVideoCount = 0;
	CAGVideoWnd m_videoWnd;
	bool m_bConnected = false;
	std::vector<HWND> m_vecWnd;
	CMonitors m_monitors;
public:
	CListBox m_lstInfo;
	virtual BOOL OnInitDialog();
	CStatic m_videoArea;
	CEdit m_edtChannelName;
	CButton m_btnJoinChannel;
	CComboBox m_cmbRole;
	CComboBox m_cmbScreenCap;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	
};
