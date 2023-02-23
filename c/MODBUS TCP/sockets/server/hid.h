#ifndef HID_H_INCLUDED
#define HID_H_INCLUDED

#endif // HID_H_INCLUDED
#define DEV_NUM 10		// ������������ ���������� ��������
//---------------------------------------------------------------------------
BOOL	Running;					// ����������, ��� �����-�� ���������� ����������
BYTE	*InReport;					// ����� ��� ����� ������� IN (�� ����������)
BYTE	*OutReport;					// ����� ��� �������� ������� OUT (� ����������)
BYTE	*FeatureReport;				// ����� ��� �������� ������� FEATURE (����������� ������� � ����������, ����� EP0)
int		InReportSz;					// ������ ������� In ������������� ����������
int		OutReportSz;                // ������ ������� Out ������������� ����������
int		FeatureReportSz;			// ������ ������� Feature ������������� ����������
//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------
int                                DevCount;									// ���������� ��������� ��������
int                                DevSelected;									// ��������� ������
PSP_DEVICE_INTERFACE_DETAIL_DATA   DevDetailData[DEV_NUM];						// ��������� ������ �� ����������� (���� � ��������� �����������)
int                                DevDetailDataSz[DEV_NUM];					// ������� �������� � ���������� ������� �� ����������� (����� �����)
int                                DevInputReportSz[DEV_NUM];					// ������� �������� IN ��������� ��������
int                                DevOutputReportSz[DEV_NUM];					// ������� �������� OUT ��������� ��������
int                                DevFeatureReportSz[DEV_NUM];					// ������� �������� FEATURE ��������� ��������
HANDLE                             DevHandle;									// ��������� �� �������� ������
OVERLAPPED                         DevWriteOverlapped;							// ��������� ��� �������� ������������ ������
OVERLAPPED                         DevReadOverlapped;							// ��������� ��� �������� ������������ �����
BOOL                               DevReadPending;								// ���� �������� ������ ��� ������� �������� ������
//---------------------------------------------------------------------------
void	HID_Init();							// ��������� ���������� ��������� ���������, ������ ������ ����������, ����� ���� ����������
											// �� ���������, ��������������� ��� �������� ����� � �����������
void	HID_UnInit();						// �������� ������ ���� ��������, ��������������� ��� �������� ����� � �����������
int		HID_FindDevices();	  				// ����� ���� ������������ hid-���������
BOOL	HID_Open(int);						// �������� ������� �������
void	HID_Close();						// �������� ������� �������
BOOL	HID_Write(BYTE*, DWORD, DWORD*);	// �������� ������ ����������
BOOL	HID_Read(BYTE*, DWORD, DWORD*);		// ������ ������ �� ����������
void	OnInput();							// ��������� ����������� ������
void	OnError();						   	// �������� ��� ������ �� ����� ������ / ������
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
