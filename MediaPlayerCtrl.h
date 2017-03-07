/* @file
*
* ʹ�÷���
* 1������ ITMS_CCTV_MediaInit ��ʼ��28181SDK
* 2������ ITMS_CCTV_ScreenSwitch ���÷�����
* 3������ ITMS_CCTV_DeviceControl ��������д EXOSIP_CTRL_DEV_CATALOG �� 13,���豸Ŀ¼��ѯ
* 4���ɵ��� ITMS_CCTV_PTZ_Command�� ITMS_CCTV_Guard�� ITMS_CCTV_DeviceControl��ITMS_CCTV_Preview, �����ĵ���˳��
* 5���˳�ǰ, ���� ITMS_CCTV_MediaFree �ͷ� ITMS_CCTV_MediaInit�������Դ
*/

#pragma once
#include <objsafe.h> 
#include"CommonType.h"
#include"DlgVideo.h"

#include"..\28181SDK\GB28181SDK.h"���ε�
#include"curl\curl.h"
#include"UserPtzLock.h"
// MediaPlayerCtrl.h : CMediaPlayerCtrl ActiveX �ؼ����������


// CMediaPlayerCtrl : �й�ʵ�ֵ���Ϣ������� MediaPlayerCtrl.cpp��

class CMediaPlayerCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMediaPlayerCtrl)

	//=============ISafeObject begin==============
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(ObjSafe, IObjectSafety)
		STDMETHOD_(HRESULT, GetInterfaceSafetyOptions) (
		REFIID riid,
		DWORD __RPC_FAR *pdwSupportedOptions,
		DWORD __RPC_FAR *pdwEnabledOptions
		);

		STDMETHOD_(HRESULT, SetInterfaceSafetyOptions) (
			REFIID riid,
			DWORD dwOptionSetMask,
			DWORD dwEnabledOptions
			);
	END_INTERFACE_PART(ObjSafe);
	//==============ISafeObject end==============
	
	// ���캯��
public:
	CMediaPlayerCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

public:
	afx_msg LRESULT OnMyClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReconn(WPARAM wParam, LPARAM lParam);
// ʵ��
protected:
	~CMediaPlayerCtrl();

	DECLARE_OLECREATE_EX(CMediaPlayerCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CMediaPlayerCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMediaPlayerCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CMediaPlayerCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
		dispidITMS_CCTV_HttpInit = 43L,
		dispidITMS_28181_GetVersion = 42L,
		dispidITMS_CCTV_PTZ_CommandWithDlg = 41L,
		dispidITMS_CCTV_28181_GetDeviceIDinDlg = 41L,
		dispidITMS_CCTV_RegisterAndPreview = 40L,
		dispidITMS_CCTV_GetFrameCnt = 39L,
		dispidITMS_CCTV_ResetRecordFps = 38L,
		dispidITMS_CCTV_ReSizeVideoDlg = 37L,
		dispidITMS_CCTV_GetCurSelectVideoDlg = 36L,
		dispidITMS_CCTV_GetRecordState = 35L,
		dispidITMS_CCTV_PauseLocalRecord = 34L,
		dispidITMS_CCTV_Record2Mp4 = 33L,
		dispidITMS_CCTV_SetRecordFps = 32L,
		dispidITMS_CCTV_FreeScreen = 31L,
		dispidITMS_CCTV_GetCurRecordFrameIndex = 30L,
		dispidITMS_CCTV_SetRecordFilePath = 29L,
		dispidITMS_CCTV_LocalRecordResetPos = 28L,
		dispidITMS_CCTV_PlayLocalRecord = 27L,
		dispidITMS_CCTV_GetSnapShot = 25L,
		dispidITMS_CCTV_Download = 24L,
		dispidITMS_CCTV_BeginLocalRecord = 22L,
		dispidITMS_CCTV_RecordQuery = 21L,
		dispidITMS_CCTV_RecordControl = 20L,
		dispidITMS_CCTV_PlaybackStop = 19L,
		dispidITMS_CCTV_PlaybackSlow = 18L,
		dispidITMS_CCTV_PlaybackFast = 17L,
		dispidITMS_CCTV_PlaybackPause = 16L,
		dispidITMS_CCTV_PlaybackPlay = 15L,
		dispidITMS_CCTV_Playback = 14L,
		dispidITMS_CCTV_StopPreview = 13L,
		dispidITMS_CCTV_DeviceControl = 12L,
		dispidITMS_CCTV_Guard = 11L,
		eventidOnGB28181_eXosip_getInviteInfo = 6L,
		eventidOnGB28181_eXosip_getDeviceCatalog = 5L,
		eventidOnGB28181_eXosip_getDeviceControlMsgResult = 4L,
		eventidOnGB_eXosip_getDeviceStatus = 3L,
		eventidOnGB28181_eXosip_getDeviceInfo = 2L,
		eventidOnTest = 1L,
		eventidOnGB28181_eXosip_getPresets = 7L,
		dispidITMS_CCTV_Preview = 9L,
		dispidITMS_CCTV_PTZ_Command = 8L,
		dispidITMS_CCTV_MediaRegister = 6L,
		dispidITMS_CCTV_ScreenSwitch = 5L,
		dispidITMS_CCTV_MediaUnRegister = 4L,
		dispidITMS_CCTV_MediaFree = 2L,
		dispidITMS_CCTV_MediaInit = 1L
	};

private:
	void CreateScreens(int nScreenCnt, LONG nLayout);
	int InitSplitScreen(LONG nCnt, LONG nLayout);
	void ReleaseScreens();
	int FreeSplitScreen();
private:
	int m_nWantedDlgVideoCnt;
	int m_nWantedLayout;
	int m_nDlgVideoCnt; /*������Ŀ*/
	int m_nLayout; //���ƴ��ڲ��� ���� ���� ����
	CDlgVideo m_DlgVideo[ITMS_CCTV_MAX_SCREEN_CNT];
	PlayInfo m_PlayInfo[ITMS_CCTV_MAX_SCREEN_CNT];
	CRITICAL_SECTION m_PlayInfoCs;

	GB28181_eXosip_callback m_GB28181_eXosip_callback;
	GB28181SDK* m_pGB28181SDK;
	GB28181_device_info m_ClientInfo;
	SipContext* m_pMyCtx;
	int         m_nCurSelectVideoDlg;

	bool        m_bClickPreviewed;
	bool        m_bPreview;
	bool        m_bPreviewStoped;

	bool        m_bAuthority;  /**<! ��ʶ�Ƿ��PTZ����������֤*/
protected:
	/**
	* ocx��ʼ��������osip��ĳ�ʼ��
	*
	* @param pOurID ��ǰ������������豸��ID
	* @param nOurIP ��ǰ���������е��Ե�IP
	* @param nOurPort ��ǰ��������Ķ˿�
	* @param pOurPwd ��ǰ�����������豸������(��ǰ�豸����ע�ᵽSIP��������ʱʹ��)
	* @param pServerIP SIP������IP
	* @param nServerPort SIP�������˿�
	* @param pVideoRecvIP ������Ƶ��IP
	* @param nVideoRecvPort  ������Ƶ�Ķ˿�
	* @param pVideoSSRC ��ʶ��Ƶ��SSRC,�Ա��汾��ΪNULL
	* @param pAudioRecvIP������Ƶ��IP���Ա��汾��ΪNULL
	* @param nAudioRecvPort ������Ƶ�Ķ˿ڣ��Ա��汾��ΪNULL
	* @param pAudioSSRC ��ʶ��Ƶ��SSRC���Ա��汾��ΪNULL
	**/
	LONG ITMS_CCTV_MediaInit(LPCTSTR pOurID, LPCTSTR pOurIP, SHORT nOurPort,
			LPCTSTR pOurPwd, LPCTSTR pServerIP, LPCTSTR pServerID, SHORT nServerPort);

	LONG ITMS_CCTV_RegisterAndPreview(LONG nExpires, LONG nViewDlgHandle, LPCTSTR pToDeviceID, SHORT nVideoPort, LPCTSTR pVideoSsrc, SHORT nAudioPort, LPCTSTR pAudioSsrc);
	
	/**
	* @brief ����http�����url��userid�������豸����Ȩ����֤
	*/
	LONG ITMS_CCTV_HttpInit(LPCTSTR pUrlPath, LPCTSTR pUserID);

	/**
	* ������Ƶ��ʾ�ķ���,��ITMS_CCTV_MediaInit֮�����
	*
	* @param nScreenCnt ������
	* @param nLayout ���ڷֲ� 0 ���� 1 ���� 2 ����
	*/
	LONG ITMS_CCTV_ScreenSwitch(LONG nScreenCnt, LONG nLayout = 2);

	/**
	* ��Ƶ���ſؼ�����ע������������������Ʒ�����������Ƶ,��ITMS_CCTV_ScreenSwitch�����
	*
	* @param nExpiresע������ʱ��
	*/
	LONG ITMS_CCTV_MediaRegister(LONG nExpires);

	/*
	* �豸 Ŀ¼����Ϣ��״̬��ѯ�Լ��豸����
	*
	*	Ŀ¼��ѯ���ؽ��:
	*		"<?xml version=\"1.0\"?>"
	*		"<Response>"
	*		"<CmdType>Catalog</CmdType>"
	*		"<SN>248</SN>"
	*		"<DeviceID>34020000001320000001</DeviceID>"
	*		"<SumNum>1</SumNum>"
	*		"<DeviceList Num=\"1\">"
	*		"<Item>"
	*		"<DeviceID>34020000001320000001</DeviceID>"
	*		"<Name>IPC</Name>"
	*		"<Manufacturer>itms</Manufacturer>"
	*		"<Model>TEST001</Model>"
	*		"<Owner>Owner1</Owner>"
	*		"<CivilCode>CivilCode1</CivilCode>"
	*		"<Block>Block1</Block>"
	*		"<Address>Address1</Address>"
	*		"<Parental>0</Parental>"
	*		"<ParentID>34020000001320000001</ParentID>"
	*		"<SafetyWay>0</SafetyWay>"
	*		"<RegisterWay>1</RegisterWay>"
	*		"<CertNum>CertNum1</CertNum>"
	*		"<Certifiable>0</Certifiable>"
	*		"<ErrCode>400</ErrCode>"
	*		"<EndTime>2099-12-31T23:59:59</EndTime>"
	*		"<Secrecy>0</Secrecy>"
	*		"<IPAddress>10.11.1.164</IPAddress>"
	*		"<Port>5080</Port>"
	*		"<Password>Password1</Password>"
	*		"<Status>OK</Status>"
	*		"<Longitude>171.3</Longitude>"
	*		"<Latitude>34.2</Latitude>"
	*		"</Item>"
	*		"</DeviceList>"
	*		"</Response>"
	*	
	*	�豸��Ϣ��ѯ���ؽ��:
	*		"<?xml version=\"1.0\"?>"
	*		"<Response>"
	*		"<CmdType>DeviceInfo</CmdType>"
	*		"<SN>17430</SN>"
	*		"<DeviceID>34020000001320000001</DeviceID>"
	*		"<Result>OK</Result>"
	*		"<Manufacturer>itms</Manufacturer>"
	*		"<Model>TEST001</Model>"
	*		"<Firmware>V1.0</Firmware>"
	*		"</Response>"
	*				
	*	�豸״̬��ѯ���ؽ��:
	*		"<?xml version=\"1.0\"?>"
	*		"<Response>"
	*		"<CmdType>DeviceStatus</CmdType>"
	*		"<SN>248</SN>"
	*		"<DeviceID>34020000001320000001</DeviceID>"
	*		"<Result>OK</Result>"
	*		"<Online>ONLINE</Online>"
	*		"<Status>OK</Status>"
	*		"<Encode>ON</Encode>"
	*		"<Record>OFF</Record>"
	*		"<DeviceTime>2013-05-08T13:12:20</DeviceTime>"
	*		"<Alarmstatus Num=\"1\">"
	*		"<Item>"
	*		"<DeviceID>34020000001320000001</DeviceID>"
	*		"<DutyStatus>OFFDUTY</DutyStatus>"
	*		"</Item>"
	*		"</Alarmstatus>"
	*		"</Response>"
	*
	* @nEnumPtz ������, ���ȡֵ������������ ö�� GB28181_enum_device_control
	* @param pDeviceID�豸ID
	*/
	LONG ITMS_CCTV_DeviceControl(LONG nEnumCommon, LPCTSTR pDeviceID);

	//typedef enum _GB28181_enum_device_control
	//{
	//	EXOSIP_CTRL_RMT_LEFT = 0,/*����*/
	//	EXOSIP_CTRL_RMT_RIGHT,   /*����*/1
	//	EXOSIP_CTRL_RMT_UP,      /*����*/2
	//	EXOSIP_CTRL_RMT_DOWN,    /*����*/3
	//	EXOSIP_CTRL_RMT_LARGE,   /*�Ŵ�*/4
	//	EXOSIP_CTRL_RMT_SMALL,   /*��С*/5
	//	EXOSIP_CTRL_RMT_STOP,    /*ֹͣң��*/6
	//	EXOSIP_CTRL_REC_START,   /*��ʼ�ֶ�¼��*/7
	//	EXOSIP_CTRL_REC_STOP,    /*ֹͣ�ֶ�¼��*/8
	//	EXOSIP_CTRL_REC_ADDRESSL,/*¼���ļ�����*/9
	//	EXOSIP_CTRL_GUD_START,   /*����*/10
	//	EXOSIP_CTRL_GUD_STOP,    /*����*/11
	//	EXOSIP_CTRL_ALM_RESET,   /*������λ*/12
	//	EXOSIP_CTRL_DEV_CATALOG, /*�豸Ŀ¼��ѯ*/13
	//	EXOSIP_CTRL_DEV_DEVICE_INFO,   /*�豸��Ϣ��ѯ*/14
	//	EXOSIP_CTRL_DEV_DEVICE_STATUS, /*�豸״̬��ѯ*/15
	//	EXOSIP_CTRL_TEL_BOOT,          /*�豸Զ������*/16
	//
	// EXOSIP_CTRL_PRE_POS_SET,	    /*����Ԥ��λ*/17
	// EXOSIP_CTRL_PRE_POS_CALL,	/*����Ԥ��λ*/18
	// EXOSIP_CTRL_PRE_POS_QUERY,   /*��ѯԤ��λ*/19
	// EXOSIP_CTRL_PRE_POS_DELETE,  /*ɾ��Ԥ��λ*/20

	// EXOSIP_CTRL_FI_IRIS_L,	/*��Ȧ�Ŵ�*/21
	// EXOSIP_CTRL_FI_IRIS_S,	/*��Ȧ��С*/22
	// EXOSIP_CTRL_FI_FOCUS_F,  /*������Զ*/23
	// EXOSIP_CTRL_FI_FOCUS_N, /*��������*/24
	// EXOSIP_CTRL_FI_FOCUS_STOP /*ָ��FIָ��*/25

	//}GB28181_enum_device_control;

	/*
	* ��̨��������
	*
	* @nEnumPtz ��̨����������, ���ȡֵ������������ ö�� GB28181_enum_device_control
	* @param pDeviceID�豸ID
	*/
	LONG ITMS_CCTV_PTZ_Command(LONG nEnumPtz, LPCTSTR pDeviceID, LONG nPreSetPos, LPCTSTR pDeviceNo);

	/*
	* ��̨��������
	*
	* @nEnumPtz ��̨����������, ���ȡֵ������������ ö�� GB28181_enum_device_control
	* @param nDlgIndex��������
	*/
	LONG ITMS_CCTV_PTZ_CommandWithDlg(LONG nEnumPtz, LONG nDlgIndex, LONG nPreSetPos);
	/**
	*��ƵԤ��
	*
	* @param nViewDlgHandle ��ʶ��ʾ��Ƶ�Ĵ���,���ֻ��һ������,����д0
	* @param pToDeviceID ������Ƶ���ݵ��豸��ID
	* @param nVideoPort ��Ƶ���ն˿�
	* @param pVideoSsrc NULL
	* @param 0
	* @param pAudioSsrc NULL
	*/
	LONG ITMS_CCTV_Preview(int nViewDlgHandle, LPCTSTR pToDeviceID,
		SHORT nVideoPort, LPCTSTR pVideoSsrc, SHORT nAudioPort, LPCTSTR pAudioSsrc);

	/*
	* ֹͣʵʱԤ��,���ֻ��һ������,����д0
	*/
	LONG ITMS_CCTV_StopPreview(LONG nDialogHandleIndex);

	/**
	* ��Ƶ�طż���,�����洢����¼��,�ȼ������ڻط�
	* 
	* @param nViewDlgHandle ��ʾ��Ƶ�Ĵ��ھ��,���ֻ��һ����������д0
	* @param pToDeviceID Ҫ������¼������Ӧ���豸ID����ĳһ·�����¼��
	* @param nVideoPort ������Ƶ�Ķ˿�
	* @param pVideoSsrc SSRC�����ﴫNULL
	* @param nAudioPort ������Ƶ�Ķ˿�
	* @param pAudioSsrc SSRC��������дNULL
	* @param pBeginTime ����ʱ��εĿ�ʼʱ��
	* @param pEndTime ����ʱ��εĽ���ʱ��
	*/
	LONG ITMS_CCTV_Playback(LONG nViewDlgHandle, LPCTSTR pToDeviceID, SHORT nVideoPort, LPCTSTR pVideoSsrc, SHORT nAudioPort, LPCTSTR pAudioSsrc, LPCTSTR pBeginTime, LPCTSTR pEndTime);
	
	/**
	* �ط����ĵ�¼��,��ITMS_CCTV_Playback֮�����
	*
	* @param nPlayDlgHandle �ط�¼��Ĵ��ھ��,��ֻ��һ������,����д0
	*/
	LONG ITMS_CCTV_PlaybackPlay(LONG nPlayDlgHandle);

	/**
	* �ط���ͣ,��ITMS_CCTV_PlaybackPlay֮�����
	* @param nDialogHandle ���ڲ���¼��Ĵ��ھ��,���ֻ��һ������,������0
	* @param nPauseTime ��ͣʱ�䳤�ȣ���Ϊ��λ
	*/
	LONG ITMS_CCTV_PlaybackPause(LONG nDialogHandle, LONG nPauseTime);

	/**
	* ¼����
	* @param nDialogHandle ��ǰ���ڲ��Ŵ�¼��Ĵ��ھ��,���һ������,����Ϊ0
	*/
	LONG ITMS_CCTV_PlaybackFast(LONG nDialogHandle);

	/**
	* ¼������
	* @param nDialogHandle ��ǰ���ڲ��Ŵ�¼��Ĵ��ھ��,���һ������,����Ϊ0
	*/
	LONG ITMS_CCTV_PlaybackSlow(LONG nDialogHandle);

	/**
	* ¼��ֹͣ
	* @param nDialogHandle ��ǰ���ڲ��Ŵ�¼��Ĵ��ھ��,���һ������,����Ϊ0
	*/
	LONG ITMS_CCTV_PlaybackStop(LONG nDialogHandle);

	/*
	* ���� ���� ������������
	*
	* @nEnumPtz ������, ���ȡֵ������������ ö�� GB28181_enum_device_control
	* @param pDeviceID�豸ID
	*/
	LONG ITMS_CCTV_Guard(LONG nEnumCommon, LPCTSTR pDeviceID);

	
	LONG ITMS_CCTV_RecordControl(LONG nEnumCommon, LPCTSTR pDeviceID);
	LONG ITMS_CCTV_RecordQuery(LONG nEnmuCommon, LPCTSTR pDeviceID, LPCTSTR pStartTime, LPCTSTR pEndTime, LPCTSTR pFilePath, LPCTSTR pAddress, LPCTSTR pRecorderID, LONG nEnmuType, LONG nEnmuSecrecy);
	LONG ITMS_CCTV_Download(LONG nViewDlgHandle, LONG nRecordType, LPCTSTR pToDeviceID, SHORT nVideoPort, LPCTSTR pVideoSsrc, SHORT nAudioPort, LPCTSTR pAudioSsrc, LPCTSTR pBeginTime, LPCTSTR pEndTime);
	
	/**
	* @param hWinHandle ����ʵʱ��Ƶ�Ĵ��ھ��
	* @param nBegin = 0 ֹͣ����¼�� 1 ��ʼ����¼��
	*/
	LONG ITMS_CCTV_BeginLocalRecord(LONG hWinHandle, LONG nBegin);
	
	/**
	* �����ļ�����·��
	* @param pRecordFilePath¼�񱣴���ļ�Ŀ¼,�����߱�֤�ļ�Ŀ¼����
	*/
	LONG ITMS_CCTV_SetRecordFilePath(LONG hWinHandle, LPCTSTR pRecordFilePath);

	/**
	* ���ű���¼��
	* @param nHandle ���ű���¼��Ĵ��ھ��,���һ������,��nHandleΪ0
	* @param pchRecordFileName ¼���ļ���,�����߱�֤�ļ�����
	* @param nPlay 0 ֹͣ 1 ��ʼ
	* @return ¼����֡��
	*/
	LONG ITMS_CCTV_PlayLocalRecord(LONG nHandle, LONG nPlay, LPCTSTR pchRecordFileName);

	/**
	* ����¼���ǰ�������ˡ��϶�����
	* @param nHandle ���ű���¼��Ĵ��ھ��,���һ������,��nHandleΪ0
	* @param nPos ¼���ļ��ض�λ, nPos > 0��ǰ nPos < 0 ���,��������,���enumPosType��������
	* @param enumPosType 0 ��ʾnPos����ڵ�ǰ��λ�� != 0 ��ʾ����λ��
	*/
	LONG ITMS_CCTV_LocalRecordResetPos(LONG nHandle, LONG nPos, LONG enumPosType);
	
	/**
	* ץͼ���ڴ�,bmp��jpeg
	* @param pbBuf ����ץͼ��buf
	* @param nBufLen    pbBuf�ĳ���
	* @param nFmtץͼ�ĸ�ʽ 0 bmp 1 jpeg
	* @param nWidth����ͼ��ĸ߶�
	* @param nHeight
	* @param pbParamBuf out������ͼƬ��һЩ��Ϣ
	* @param nHandle ����¼��Ĵ��ڵľ��
	* @param nTimeOut ��ʱֵ
	*/
	LONG ITMS_CCTV_GetSnapShot(void* pbBuf, LONG nBufLen, void* pbParamBuf, LONG nParamBufLen, LONG nFmt, LONG nWidth, LONG nHeight, LONG nHandle, LONG nTimeOut);
	/**
	* �����˳�ǰҪע��
	*/
	LONG ITMS_CCTV_MediaUnRegister(void);

	/**
	* �ͷŴ�����Դ,��ITMS_CCTV_ScreenSwitch��Ӧ
	*/
	LONG ITMS_CCTV_FreeScreen(void);

	/**
	*
	* �� ITMS_CCTV_MediaInit ���Ӧ,�����˳�ǰ���ͷ�ITMS_CCTV_MediaInit���������Դ
	**/
	LONG ITMS_CCTV_MediaFree(void);
	
	/**
	* ����ָ��¼��ǰ���ŵ�֡��index
	*/
	LONG ITMS_CCTV_GetCurRecordFrameIndex(LONG nHandle);
	
	/*
	* ����֡��,����¼��ʱ,�����������ƿ�š�����
	*
	* @param nHandle ����¼��Ĵ��ھ��
	* @param nFps ֡�� 5 10 15 25 30 50 60 120
	* @return �ɹ�����ԭ֡�ʣ�ʧ�ܷ���-1
	*/
	LONG ITMS_CCTV_SetRecordFps(LONG nHandle, LONG nFps);

	/*
	* �ظ�֡��Ϊ��������֡��
	*
	* @param nHandle ����¼��Ĵ��ھ��
	* @return �ɹ�����ԭ֡�ʣ�ʧ�ܷ���-1
	*/
	LONG ITMS_CCTV_ResetRecordFps(LONG nHandle);

	/**
	* ��ȡ��nBeginIndex֡����nEndIndex֡��¼�񱣴��MP4
	*
	* @param nHandle ����¼��Ĵ��ھ��
	* @param pRecordFile ¼���ļ����ƿ���дNULL
	* @param pToRecordFile Ŀ��¼��ȫ·��(��������),�粻��Ҫ,
	* @param nBeginIndex ��nBeginIndex֡��ʼ
	* @param ��nEndIndex֡����
	*/
	LONG ITMS_CCTV_Record2Mp4(LONG nHandle, LPCTSTR pRecordFile, LPCTSTR pToRecordFile, LONG nBeginIndex, LONG nEndIndex);

	/**
	* ����¼��Ŀ�ʼ�����
	*
	* @param nHandle ����¼��Ĵ��ھ��
	* @nPlayFlag 0 ����¼�� 1 ��ʼ¼��
	*/
	LONG ITMS_CCTV_PauseLocalRecord(LONG nHandle, LONG nPlayFlag);

	/**
	* ���¼���״̬
	*
	* @param nHandle ����¼��Ĵ��ھ��
	* @return 0 û��¼�� 1 ����¼��
	*/
	LONG ITMS_CCTV_GetRecordState(LONG nHandle);

	/**
	* ���ص�ǰѡ�е���Ƶ���ڵľ��
	*/
	LONG ITMS_CCTV_GetCurSelectVideoDlg(void);

	/**
	* �������ô��ڵ�λ�á���С
	*/
	LONG ITMS_CCTV_ReSizeVideoDlg(LONG nX, LONG nY, LONG nWidth, LONG nHeight);

	/**
	* @brief �ñ������ʱ���ʱ����������ĸ�ʽ��ʾ�汾��Ϣ
	*/
	BSTR ITMS_28181_GetVersion(void);
public:
	bool SetCurPlayInfo(int nCallID, int nDialogID);

	void OnTest(LONG nVal)
	{
		FireEvent(eventidOnTest, EVENT_PARAM(VTS_I4), nVal);
	}

	/*
	* �¼�
	* �����豸��Ϣ
	*/
	void OnGB28181_eXosip_getDeviceInfo(LPCTSTR pXmlDeviceInfo)
	{
		FireEvent(eventidOnGB28181_eXosip_getDeviceInfo, EVENT_PARAM(VTS_BSTR), pXmlDeviceInfo);
	}

	/*
	* �¼�
	* �����豸״̬
	*/
	void OnGB_eXosip_getDeviceStatus(LPCTSTR pXmlDeviceInfo)
	{
		FireEvent(eventidOnGB_eXosip_getDeviceStatus, EVENT_PARAM(VTS_BSTR), pXmlDeviceInfo);
	}

	/*
	* �¼�
	* ���ؿ��ƽ�� OK or ERROR
	*/
	void OnGB28181_eXosip_getDeviceControlMsgResult(LPCTSTR pXmlDevCtrMsgRet)
	{
		FireEvent(eventidOnGB28181_eXosip_getDeviceControlMsgResult, EVENT_PARAM(VTS_BSTR), pXmlDevCtrMsgRet);
	}

	/*
	* �¼�
	* �����豸Ŀ¼
	*/
	void OnGB28181_eXosip_getDeviceCatalog(LPCTSTR pXmlDeviceCatalog)
	{
		FireEvent(eventidOnGB28181_eXosip_getDeviceCatalog, EVENT_PARAM(VTS_BSTR), pXmlDeviceCatalog);
	}

	/**�¼�,����ý����,������IP,�������˿�
	* 
	*/
	void OnGB28181_eXosip_getInviteInfo(LONG nMediaNo, LPCTSTR pMediaServerIP, LPCTSTR pMediaServerPort)
	{
		FireEvent(eventidOnGB28181_eXosip_getInviteInfo, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_BSTR), nMediaNo, pMediaServerIP, pMediaServerPort);
	}

	/**�¼�,�������е�Ԥ��λ��Ϣ
	* 
	*/
	void OnGB28181_eXosip_getPresets(LPCTSTR pXmlPresets)
	{
		FireEvent(eventidOnGB28181_eXosip_getPresets, EVENT_PARAM(VTS_BSTR), pXmlPresets);
	}
private:
	HANDLE m_hKeepLiveThd;
	bool   m_bKeepLiveRun;
	static unsigned int __stdcall KeepLive(void* pParam);
protected:
	LONG ITMS_CCTV_GetFrameCnt(LONG nHandle);

private:
	void WriteLog(const char* pLog, int nLen);
	FILE* m_pLogFile;
	
	UserPtzLock* m_pUserLock;
public:
	bool   m_bCreated;
	HANDLE m_hCreateThd;
	static unsigned int __stdcall MyOnCreateFun(void* pParam);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

int GB28181_eXosip_getDeviceInfo(const char* pXmlDeviceInfo);
int GB_eXosip_getDeviceStatus(const char* pXmlDeviceStatus);
int GB28181_eXosip_getDeviceControlMsgResult(const char* pXmlDeviceControlMsgResult);
int GB28181_eXosip_getDeviceCatalog(const char* pXmlDeviceList);
int GB28181_eXosip_getInviteInfo(int nMediaNo, const char* pMediaServerIP, const char*  pMediaServerPort, int nCallID, int nDialogID);
int GB28181_eXosip_RegsiterRet(int nRet);
int GB28181_eXosip_getPtzPresets(const char* pXmlPtzPresets);

/**
* ���Ե���
*/
