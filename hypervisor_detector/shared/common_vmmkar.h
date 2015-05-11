#ifndef __COMMON_RDTSC_H_
#define __COMMON_RDTSC_H_

#define		KARVMM_SYS				L"karvmm.sys"
#define		KARVMM_DEVICENAME_DRV	L"\\Device\\KarVMMDev"
#define		KARVMM_LINKNAME_DRV 	L"\\DosDevices\\"KARVMM_SYS
#define		KARVMM_LINKNAME_GUI 	L"\\\\.\\"KARVMM_SYS
#define		KARVMM_SERVICENAME_GUI	KARVMM_SYS

extern const wchar_t *g_MethodDetectionName[];

//Type of a method of detection
enum MethodDetectingType 
{
	BlockOfCPUID  = 0, // ������� ����� ������ � ������������ ����, ������ �� 10 ���������� CPUID
	CPUIDwithDisabledCache, // ��������� ������ ����������� ������� ����������  �������������� ������, ������ �� 10 ���������� CPUID
	BlockOfVMXON, // ������� ����� ������ � ������������ ����, ������ �� ���������� VMXON
	VMXONwithDisabledCache, // ��������� ������ ����������� ������� ����������  �������������� ������, ������ �� ���������� VMXON	
	WalkThroughMemory, // ��������� ������� ������ ��� ��������� � ������
};

#define FILE_DEVICE_IOCTL  0x00008301
#define IOCTL_BLOCK_OF_CPUID	CTL_CODE(FILE_DEVICE_IOCTL, 0x800 + 1, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_BLOCK_OF_CPUID_WITH_DISABLED_CACHE		CTL_CODE(FILE_DEVICE_IOCTL, 0x800 + 2, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_BLOCK_OF_VMXON	CTL_CODE(FILE_DEVICE_IOCTL, 0x800 + 11, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_BLOCK_OF_VMXON_WITH_DISABLED_CACHE		CTL_CODE(FILE_DEVICE_IOCTL, 0x800 + 12, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_WALK_MEM_NEITHER	CTL_CODE(FILE_DEVICE_IOCTL, 0x800 + 21, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_ONECPUID_CACHE		CTL_CODE(FILE_DEVICE_IOCTL, 0x800 + 31, METHOD_NEITHER, FILE_ANY_ACCESS)



///////////////////////////////////////////////////////////////
// GUI --> DRIVER
/* ��������� ������� ��� �������� */
typedef struct _TaskForMeasurement
{
	// ���� ������������ ����� ��������
	MethodDetectingType method_type; // ����� ���������
	unsigned long ctrl_code; // ����������� ��� ��� ���������

	// ���� ������������ ��������, ������������� ��������� ������� �����
	unsigned int affinity; // ����� ����, �� ������� ������������ ����������� ��������
	unsigned int trace_length; // ����� ������ (const = 10) // <- ����� ������ (�� ��������� 10 ����������)
	unsigned int num_measurements; // ����� ��������� (1000) // < - ����� ��������� (�� ��������� 1000 ���������)
	unsigned int num_repetitions; // ����� �������� ��������� (10)
	unsigned int delay_between_rep; // �������� ����� ��������� ���������
	unsigned int num_experiment; // ����� ������ (1-2-3)
	unsigned int delay_between_exp; // // �������� ����� �������
	
	// ���� ������������ ������ ��� ����������� �� ������
	__int64 start_low_phys_addr; //= 0 ��������� ����� ������� ��� ������
	__int64 start_high_phys_addr; //= PAGE_SIZE  ��������� ����� ������� ��� ������
	__int64 phys_mem_offset; //= PAGE_SIZE ��� ������� �� ��� ������
	
	// ��� ������� MmAllocatePagesForMdl
	__int64 skipbytes; //= {PAGE_SIZE} �������� ������� MmAllocatePagesForMdl 	
	unsigned long totalbytes; //= PAGE_SIZE �������� ������� MmAllocatePagesForMdl

	// ��� ������� ZwMapViewOfSection
	size_t viewsize; //= 0x20 ������ ������������ ������

}TaskForMeasurement, *PTaskForMeasurement;


#define MAX_PHYS_MEM_ADDR 0xFFFFFFFF

// Define the page size for the Intel 386 as 4096 (0x1000).
#define PHYSMEM_PAGE_SIZE 0x1000

//////////////////////////////////////////////////////////////////////////
//  GUI <-- DRIVER

/* ��������� ���������� ��� ����������� ��������� */
typedef struct _TimeInterval
{	
	// ���� ������������ ����� �������� ��� �������� ��������� �������
	unsigned int cycles_high_start; 
	unsigned int cycles_low_start;
	unsigned int cycles_high_finish;
	unsigned int cycles_low_finish;

	// ���� ������������ ������ ��� ����������� �� ������
	__int64 low_phys_addr; // ����� ������� ������� ��� ������
	__int64 high_phys_addr; // ����� ������� ������� ��� ������
	unsigned int valid_address; // ���������� ���������� ������ ��� ������
	long nt_status; // ������ ������� ��� ���������



}TimeInterval, *PTimeInterval;

/* ��������� ���������� ��� ����������� ��������� � ������ ������������� ������� */
typedef struct _TimeIntervalRes
{	
	// ���� ������������ ����� �������� ��� �������� ��������� �������
	unsigned __int64 trace_duration;

	// ���� ������������ ������ ��� ����������� �� ������
	__int64 low_phys_addr; // ����� ������� ������� ��� ������
	__int64 high_phys_addr; // ����� ������� ������� ��� ������
	unsigned int valid_address; // ���������� ���������� ������ ��� ������
	long nt_status; // ������ ������� ��� ���������

}TimeIntervalRes, *PTimeIntervalRes;

#endif // __COMMON_RDTSC_H_