#ifndef __MEASURING_TRACE_H_
#define __MEASURING_TRACE_H_

#include "vector"

#include "service_functions.h"

#include "shared/common_vmmkar.h"
// #include "making_decision.h"
// #include "processing_data.h"

/************************************************************************/
/* 
//  [9/18/2010 ik]
		
		������ ��������� �������:
		- ��������� � ������, ���������� ����� �� ��������
		- ����������� �������� �������� � ������������
		- ��������� ������� � ����
*/
/************************************************************************/

namespace measuring_trace
{
	/* ��������� �� �������� ����� ������ � ��������� ���������������� */
	bool get_one_trace(IN service_functions :: ServiceManager &csmgr, IN HANDLE hNeither, IN TaskForMeasurement & Task, OUT std :: vector <TimeInterval> &timeIntervals );

	/* ����������� �������� �������� ������ � ������������ ���������� ������ ����������  (unsigned __int64) */	
	void convert_counts_to_duration(IN std :: vector <TimeInterval> &timeIntervals, OUT std :: vector <unsigned __int64> & traceDuration);

	/* ����������� �������� �������� ������ � ������������ ���������� ������ ���������� (TimeIntervalRes) */
	void convert_counts_to_duration(IN std :: vector <TimeInterval> &timeIntervals, OUT std :: vector <TimeIntervalRes> & traceDuration);

	/* ���������� ���� � ���������� ����� � ������ ����������, ������ ����� */
	bool set_file_name(TaskForMeasurement &Task, PTCHAR fileTsc, TCHAR ext[]);

	/* ���������� ���� � ���������� ����� ��� ����� ����������, ������ ����� */
	bool set_file_name(TaskForMeasurement &Task, PTCHAR fileTsc);

	bool get_one_matrix(service_functions :: ServiceManager &csmgr, HANDLE hNeither, TaskForMeasurement Task, bool & bVirt);


	//////////////////////////////////////////////////////////////////////////


	/* ��������� ������� ��������� � ���� (unsigned __int64) */
	void save_matrix( TaskForMeasurement &Task, std :: vector < std :: vector<unsigned __int64> > &matrixDuration );

	/* ��������� ������� � csv ���� */
	void save_matrix_to_csv( TaskForMeasurement &Task, std :: vector < std :: vector<unsigned __int64> > &matrixDuration );
	
	/* ��������� ������� � csv ���� */
	void save_matrix_to_csv( TaskForMeasurement &Task, std :: vector < std :: vector<unsigned __int64> > &matrixDuration, PTCHAR fileName);
	
	/* ��������� ������� � �������� ���� */
	void save_matrix_to_bin( TaskForMeasurement &Task, std :: vector < std :: vector<unsigned __int64> > &matrixDuration, PTCHAR fileName);
	//////////////////////////////////////////////////////////////////////////

	/* ��������� ���������� ������ � ���� (TimeIntervalRes) */
	void save_matrix( TaskForMeasurement &Task, std :: vector < std :: vector<TimeIntervalRes> > &matrixDuration );

	/* ��������� ������� ������� ��������� � ���� (TimeIntervalRes) */
	void save_column( TaskForMeasurement &Task, std :: vector < std :: vector<TimeIntervalRes> > &matrixDuration );

	/* ������ ������� �� �����*/
	void read_matrix(PTCHAR fileName, std :: vector < std :: vector<unsigned __int64> > &matrixDuration);
}

#endif // __MEASURING_TRACE_H_