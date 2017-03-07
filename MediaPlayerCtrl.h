/* @file
*
* 使用方法
* 1、调用 ITMS_CCTV_MediaInit 初始化28181SDK
* 2、调用 ITMS_CCTV_ScreenSwitch 设置分屏数
* 3、调用 ITMS_CCTV_DeviceControl 命令编号填写 EXOSIP_CTRL_DEV_CATALOG 或 13,即设备目录查询
* 4、可调用 ITMS_CCTV_PTZ_Command、 ITMS_CCTV_Guard、 ITMS_CCTV_DeviceControl、ITMS_CCTV_Preview, 不关心调用顺序
* 5、退出前, 调用 ITMS_CCTV_MediaFree 释放 ITMS_CCTV_MediaInit分配的资源
*/

#pragma once
#include <objsafe.h> 
#include"CommonType.h"
#include"DlgVideo.h"

#include"..\28181SDK\GB28181SDK.h"点点滴滴
#include"curl\curl.h"
#include"UserPtzLock.h"
// MediaPlayerCtrl.h : CMediaPlayerCtrl ActiveX 控件类的声明。


// CMediaPlayerCtrl : 有关实现的信息，请参阅 MediaPlayerCtrl.cpp。

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
	
	// 构造函数
public:
	CMediaPlayerCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

public:
	afx_msg LRESULT OnMyClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReconn(WPARAM wParam, LPARAM lParam);
// 实现
protected:
	~CMediaPlayerCtrl();

	DECLARE_OLECREATE_EX(CMediaPlayerCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CMediaPlayerCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMediaPlayerCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CMediaPlayerCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
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
	int m_nDlgVideoCnt; /*分屏数目*/
	int m_nLayout; //控制窗口布局 横向 纵向 均匀
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

	bool        m_bAuthority;  /**<! 标识是否对PTZ锁定进行验证*/
protected:
	/**
	* ocx初始化，包括osip库的初始化
	*
	* @param pOurID 当前程序所代表的设备的ID
	* @param nOurIP 当前程序所运行电脑的IP
	* @param nOurPort 当前程序监听的端口
	* @param pOurPwd 当前程序所代表设备的密码(当前设备主动注册到SIP服务器上时使用)
	* @param pServerIP SIP服务器IP
	* @param nServerPort SIP服务器端口
	* @param pVideoRecvIP 接受视频的IP
	* @param nVideoRecvPort  接收视频的端口
	* @param pVideoSSRC 标识视频的SSRC,对本版本设为NULL
	* @param pAudioRecvIP接收音频的IP，对本版本设为NULL
	* @param nAudioRecvPort 接收音频的端口，对本版本设为NULL
	* @param pAudioSSRC 标识音频的SSRC，对本版本设为NULL
	**/
	LONG ITMS_CCTV_MediaInit(LPCTSTR pOurID, LPCTSTR pOurIP, SHORT nOurPort,
			LPCTSTR pOurPwd, LPCTSTR pServerIP, LPCTSTR pServerID, SHORT nServerPort);

	LONG ITMS_CCTV_RegisterAndPreview(LONG nExpires, LONG nViewDlgHandle, LPCTSTR pToDeviceID, SHORT nVideoPort, LPCTSTR pVideoSsrc, SHORT nAudioPort, LPCTSTR pAudioSsrc);
	
	/**
	* @brief 设置http请求的url和userid，用于设备控制权限验证
	*/
	LONG ITMS_CCTV_HttpInit(LPCTSTR pUrlPath, LPCTSTR pUserID);

	/**
	* 控制视频显示的分屏,在ITMS_CCTV_MediaInit之后调用
	*
	* @param nScreenCnt 分屏数
	* @param nLayout 窗口分布 0 横向 1 纵向 2 均匀
	*/
	LONG ITMS_CCTV_ScreenSwitch(LONG nScreenCnt, LONG nLayout = 2);

	/**
	* 视频播放控件，在注册后才能想中心信令控制服务器请求视频,在ITMS_CCTV_ScreenSwitch后调用
	*
	* @param nExpires注销过期时间
	*/
	LONG ITMS_CCTV_MediaRegister(LONG nExpires);

	/*
	* 设备 目录、信息、状态查询以及设备重启
	*
	*	目录查询返回结果:
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
	*	设备信息查询返回结果:
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
	*	设备状态查询返回结果:
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
	* @nEnumPtz 命令编号, 编号取值及代表的意义见 枚举 GB28181_enum_device_control
	* @param pDeviceID设备ID
	*/
	LONG ITMS_CCTV_DeviceControl(LONG nEnumCommon, LPCTSTR pDeviceID);

	//typedef enum _GB28181_enum_device_control
	//{
	//	EXOSIP_CTRL_RMT_LEFT = 0,/*向左*/
	//	EXOSIP_CTRL_RMT_RIGHT,   /*向右*/1
	//	EXOSIP_CTRL_RMT_UP,      /*向上*/2
	//	EXOSIP_CTRL_RMT_DOWN,    /*向下*/3
	//	EXOSIP_CTRL_RMT_LARGE,   /*放大*/4
	//	EXOSIP_CTRL_RMT_SMALL,   /*缩小*/5
	//	EXOSIP_CTRL_RMT_STOP,    /*停止遥控*/6
	//	EXOSIP_CTRL_REC_START,   /*开始手动录像*/7
	//	EXOSIP_CTRL_REC_STOP,    /*停止手动录像*/8
	//	EXOSIP_CTRL_REC_ADDRESSL,/*录像文件检索*/9
	//	EXOSIP_CTRL_GUD_START,   /*布防*/10
	//	EXOSIP_CTRL_GUD_STOP,    /*撤防*/11
	//	EXOSIP_CTRL_ALM_RESET,   /*报警复位*/12
	//	EXOSIP_CTRL_DEV_CATALOG, /*设备目录查询*/13
	//	EXOSIP_CTRL_DEV_DEVICE_INFO,   /*设备信息查询*/14
	//	EXOSIP_CTRL_DEV_DEVICE_STATUS, /*设备状态查询*/15
	//	EXOSIP_CTRL_TEL_BOOT,          /*设备远程启动*/16
	//
	// EXOSIP_CTRL_PRE_POS_SET,	    /*设置预置位*/17
	// EXOSIP_CTRL_PRE_POS_CALL,	/*调用预置位*/18
	// EXOSIP_CTRL_PRE_POS_QUERY,   /*查询预置位*/19
	// EXOSIP_CTRL_PRE_POS_DELETE,  /*删除预置位*/20

	// EXOSIP_CTRL_FI_IRIS_L,	/*光圈放大*/21
	// EXOSIP_CTRL_FI_IRIS_S,	/*光圈缩小*/22
	// EXOSIP_CTRL_FI_FOCUS_F,  /*焦距拉远*/23
	// EXOSIP_CTRL_FI_FOCUS_N, /*焦距拉近*/24
	// EXOSIP_CTRL_FI_FOCUS_STOP /*指令FI指令*/25

	//}GB28181_enum_device_control;

	/*
	* 云台控制命令
	*
	* @nEnumPtz 云台控制命令编号, 编号取值及代表的意义见 枚举 GB28181_enum_device_control
	* @param pDeviceID设备ID
	*/
	LONG ITMS_CCTV_PTZ_Command(LONG nEnumPtz, LPCTSTR pDeviceID, LONG nPreSetPos, LPCTSTR pDeviceNo);

	/*
	* 云台控制命令
	*
	* @nEnumPtz 云台控制命令编号, 编号取值及代表的意义见 枚举 GB28181_enum_device_control
	* @param nDlgIndex窗口索引
	*/
	LONG ITMS_CCTV_PTZ_CommandWithDlg(LONG nEnumPtz, LONG nDlgIndex, LONG nPreSetPos);
	/**
	*视频预览
	*
	* @param nViewDlgHandle 标识显示视频的窗口,如果只有一个窗口,则填写0
	* @param pToDeviceID 发送视频数据的设备的ID
	* @param nVideoPort 视频接收端口
	* @param pVideoSsrc NULL
	* @param 0
	* @param pAudioSsrc NULL
	*/
	LONG ITMS_CCTV_Preview(int nViewDlgHandle, LPCTSTR pToDeviceID,
		SHORT nVideoPort, LPCTSTR pVideoSsrc, SHORT nAudioPort, LPCTSTR pAudioSsrc);

	/*
	* 停止实时预览,如果只有一个窗口,则填写0
	*/
	LONG ITMS_CCTV_StopPreview(LONG nDialogHandleIndex);

	/**
	* 视频回放检索,检索存储中心录像,先检索，在回放
	* 
	* @param nViewDlgHandle 显示视频的窗口句柄,如果只有一个窗口则填写0
	* @param pToDeviceID 要检索的录像所对应的设备ID，如某一路像机的录像
	* @param nVideoPort 接收视频的端口
	* @param pVideoSsrc SSRC，这里传NULL
	* @param nAudioPort 接收音频的端口
	* @param pAudioSsrc SSRC，这里填写NULL
	* @param pBeginTime 检索时间段的开始时间
	* @param pEndTime 检索时间段的结束时间
	*/
	LONG ITMS_CCTV_Playback(LONG nViewDlgHandle, LPCTSTR pToDeviceID, SHORT nVideoPort, LPCTSTR pVideoSsrc, SHORT nAudioPort, LPCTSTR pAudioSsrc, LPCTSTR pBeginTime, LPCTSTR pEndTime);
	
	/**
	* 回放中心的录像,在ITMS_CCTV_Playback之后调用
	*
	* @param nPlayDlgHandle 回放录像的窗口句柄,如只有一个窗口,则填写0
	*/
	LONG ITMS_CCTV_PlaybackPlay(LONG nPlayDlgHandle);

	/**
	* 回放暂停,在ITMS_CCTV_PlaybackPlay之后调用
	* @param nDialogHandle 正在播放录像的窗口句柄,如果只有一个窗口,它就是0
	* @param nPauseTime 暂停时间长度，秒为单位
	*/
	LONG ITMS_CCTV_PlaybackPause(LONG nDialogHandle, LONG nPauseTime);

	/**
	* 录像快放
	* @param nDialogHandle 当前正在播放此录像的窗口句柄,如第一个窗口,它就为0
	*/
	LONG ITMS_CCTV_PlaybackFast(LONG nDialogHandle);

	/**
	* 录像慢放
	* @param nDialogHandle 当前正在播放此录像的窗口句柄,如第一个窗口,它就为0
	*/
	LONG ITMS_CCTV_PlaybackSlow(LONG nDialogHandle);

	/**
	* 录像停止
	* @param nDialogHandle 当前正在播放此录像的窗口句柄,如第一个窗口,它就为0
	*/
	LONG ITMS_CCTV_PlaybackStop(LONG nDialogHandle);

	/*
	* 布防 撤防 报警重置命令
	*
	* @nEnumPtz 命令编号, 编号取值及代表的意义见 枚举 GB28181_enum_device_control
	* @param pDeviceID设备ID
	*/
	LONG ITMS_CCTV_Guard(LONG nEnumCommon, LPCTSTR pDeviceID);

	
	LONG ITMS_CCTV_RecordControl(LONG nEnumCommon, LPCTSTR pDeviceID);
	LONG ITMS_CCTV_RecordQuery(LONG nEnmuCommon, LPCTSTR pDeviceID, LPCTSTR pStartTime, LPCTSTR pEndTime, LPCTSTR pFilePath, LPCTSTR pAddress, LPCTSTR pRecorderID, LONG nEnmuType, LONG nEnmuSecrecy);
	LONG ITMS_CCTV_Download(LONG nViewDlgHandle, LONG nRecordType, LPCTSTR pToDeviceID, SHORT nVideoPort, LPCTSTR pVideoSsrc, SHORT nAudioPort, LPCTSTR pAudioSsrc, LPCTSTR pBeginTime, LPCTSTR pEndTime);
	
	/**
	* @param hWinHandle 播放实时视频的窗口句柄
	* @param nBegin = 0 停止本地录像 1 开始本地录像
	*/
	LONG ITMS_CCTV_BeginLocalRecord(LONG hWinHandle, LONG nBegin);
	
	/**
	* 设置文件保存路径
	* @param pRecordFilePath录像保存的文件目录,调用者保证文件目录存在
	*/
	LONG ITMS_CCTV_SetRecordFilePath(LONG hWinHandle, LPCTSTR pRecordFilePath);

	/**
	* 播放本地录像
	* @param nHandle 播放本地录像的窗口句柄,如第一个窗口,则nHandle为0
	* @param pchRecordFileName 录像文件名,调用者保证文件存在
	* @param nPlay 0 停止 1 开始
	* @return 录像总帧数
	*/
	LONG ITMS_CCTV_PlayLocalRecord(LONG nHandle, LONG nPlay, LPCTSTR pchRecordFileName);

	/**
	* 用于录像的前进、后退、拖动播放
	* @param nHandle 播放本地录像的窗口句柄,如第一个窗口,则nHandle为0
	* @param nPos 录像文件重定位, nPos > 0向前 nPos < 0 向后,具体意义,配合enumPosType才有意义
	* @param enumPosType 0 表示nPos相对于当前的位置 != 0 表示绝对位置
	*/
	LONG ITMS_CCTV_LocalRecordResetPos(LONG nHandle, LONG nPos, LONG enumPosType);
	
	/**
	* 抓图到内存,bmp或jpeg
	* @param pbBuf 保存抓图的buf
	* @param nBufLen    pbBuf的长度
	* @param nFmt抓图的格式 0 bmp 1 jpeg
	* @param nWidth保存图像的高度
	* @param nHeight
	* @param pbParamBuf out，返回图片的一些信息
	* @param nHandle 播放录像的窗口的句柄
	* @param nTimeOut 超时值
	*/
	LONG ITMS_CCTV_GetSnapShot(void* pbBuf, LONG nBufLen, void* pbParamBuf, LONG nParamBufLen, LONG nFmt, LONG nWidth, LONG nHeight, LONG nHandle, LONG nTimeOut);
	/**
	* 程序退出前要注销
	*/
	LONG ITMS_CCTV_MediaUnRegister(void);

	/**
	* 释放窗口资源,与ITMS_CCTV_ScreenSwitch对应
	*/
	LONG ITMS_CCTV_FreeScreen(void);

	/**
	*
	* 与 ITMS_CCTV_MediaInit 相对应,程序退出前，释放ITMS_CCTV_MediaInit所分配的资源
	**/
	LONG ITMS_CCTV_MediaFree(void);
	
	/**
	* 返回指定录像当前播放的帧的index
	*/
	LONG ITMS_CCTV_GetCurRecordFrameIndex(LONG nHandle);
	
	/*
	* 设置帧率,播放录像时,可以用来控制快放、慢放
	*
	* @param nHandle 播放录像的窗口句柄
	* @param nFps 帧率 5 10 15 25 30 50 60 120
	* @return 成功返回原帧率，失败返回-1
	*/
	LONG ITMS_CCTV_SetRecordFps(LONG nHandle, LONG nFps);

	/*
	* 回复帧率为正常播放帧率
	*
	* @param nHandle 播放录像的窗口句柄
	* @return 成功返回原帧率，失败返回-1
	*/
	LONG ITMS_CCTV_ResetRecordFps(LONG nHandle);

	/**
	* 截取第nBeginIndex帧到底nEndIndex帧的录像保存成MP4
	*
	* @param nHandle 播放录像的窗口句柄
	* @param pRecordFile 录像文件名称可填写NULL
	* @param pToRecordFile 目标录像全路径(包含名称),如不需要,
	* @param nBeginIndex 从nBeginIndex帧开始
	* @param 到nEndIndex帧结束
	*/
	LONG ITMS_CCTV_Record2Mp4(LONG nHandle, LPCTSTR pRecordFile, LPCTSTR pToRecordFile, LONG nBeginIndex, LONG nEndIndex);

	/**
	* 控制录像的开始或结束
	*
	* @param nHandle 播放录像的窗口句柄
	* @nPlayFlag 0 结束录像 1 开始录像
	*/
	LONG ITMS_CCTV_PauseLocalRecord(LONG nHandle, LONG nPlayFlag);

	/**
	* 获得录像的状态
	*
	* @param nHandle 播放录像的窗口句柄
	* @return 0 没有录像 1 正在录像
	*/
	LONG ITMS_CCTV_GetRecordState(LONG nHandle);

	/**
	* 返回当前选中的视频窗口的句柄
	*/
	LONG ITMS_CCTV_GetCurSelectVideoDlg(void);

	/**
	* 重新设置窗口的位置、大小
	*/
	LONG ITMS_CCTV_ReSizeVideoDlg(LONG nX, LONG nY, LONG nWidth, LONG nHeight);

	/**
	* @brief 用编译程序时候的时分秒月日年的格式表示版本信息
	*/
	BSTR ITMS_28181_GetVersion(void);
public:
	bool SetCurPlayInfo(int nCallID, int nDialogID);

	void OnTest(LONG nVal)
	{
		FireEvent(eventidOnTest, EVENT_PARAM(VTS_I4), nVal);
	}

	/*
	* 事件
	* 返回设备信息
	*/
	void OnGB28181_eXosip_getDeviceInfo(LPCTSTR pXmlDeviceInfo)
	{
		FireEvent(eventidOnGB28181_eXosip_getDeviceInfo, EVENT_PARAM(VTS_BSTR), pXmlDeviceInfo);
	}

	/*
	* 事件
	* 返回设备状态
	*/
	void OnGB_eXosip_getDeviceStatus(LPCTSTR pXmlDeviceInfo)
	{
		FireEvent(eventidOnGB_eXosip_getDeviceStatus, EVENT_PARAM(VTS_BSTR), pXmlDeviceInfo);
	}

	/*
	* 事件
	* 返回控制结果 OK or ERROR
	*/
	void OnGB28181_eXosip_getDeviceControlMsgResult(LPCTSTR pXmlDevCtrMsgRet)
	{
		FireEvent(eventidOnGB28181_eXosip_getDeviceControlMsgResult, EVENT_PARAM(VTS_BSTR), pXmlDevCtrMsgRet);
	}

	/*
	* 事件
	* 返回设备目录
	*/
	void OnGB28181_eXosip_getDeviceCatalog(LPCTSTR pXmlDeviceCatalog)
	{
		FireEvent(eventidOnGB28181_eXosip_getDeviceCatalog, EVENT_PARAM(VTS_BSTR), pXmlDeviceCatalog);
	}

	/**事件,返回媒体编号,服务器IP,服务器端口
	* 
	*/
	void OnGB28181_eXosip_getInviteInfo(LONG nMediaNo, LPCTSTR pMediaServerIP, LPCTSTR pMediaServerPort)
	{
		FireEvent(eventidOnGB28181_eXosip_getInviteInfo, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_BSTR), nMediaNo, pMediaServerIP, pMediaServerPort);
	}

	/**事件,返回现有的预置位信息
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
* 测试的行
*/
