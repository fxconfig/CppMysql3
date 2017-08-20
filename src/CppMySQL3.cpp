
#include "cppmysql3.h"
//#include <stdlib.h>
//#include <stdio.h>
#ifdef _WIN32  //static link to mysqlclient.lib, static MFC need this two lib
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "User32.lib")
#endif


CppMySQLException::CppMySQLException(const int nErrCode,
	const char* szErrMess,
	bool bDeleteMsg/*=true*/) :
	mnErrCode(nErrCode),msg(szErrMess),std::exception(szErrMess)
{
}

CppMySQLException::CppMySQLException(const CppMySQLException& e) :
	mnErrCode(e.mnErrCode)
{
	msg = std::move(e.msg);
}

const char* CppMySQLException::errorCodeAsString(int nErrCode)
{
	switch (nErrCode)
	{
	case CR_UNKNOWN_ERROR: return "CR_UNKNOWN_ERROR";
	case CR_SOCKET_CREATE_ERROR: return "CR_SOCKET_CREATE_ERROR";
	case CR_CONNECTION_ERROR: return "CR_CONNECTION_ERROR";
	case CR_CONN_HOST_ERROR: return "CR_CONN_HOST_ERROR";
	case CR_IPSOCK_ERROR: return "CR_IPSOCK_ERROR";
	case CR_UNKNOWN_HOST: return "CR_UNKNOWN_HOST";
	case CR_SERVER_GONE_ERROR: return "CR_SERVER_GONE_ERROR";
	case CR_VERSION_ERROR: return "CR_VERSION_ERROR";
	case CR_OUT_OF_MEMORY: return "CR_OUT_OF_MEMORY";
	case CR_WRONG_HOST_INFO: return "CR_WRONG_HOST_INFO";
	case CR_LOCALHOST_CONNECTION: return "CR_LOCALHOST_CONNECTION";
	case CR_TCP_CONNECTION: return "CR_TCP_CONNECTION";
	case CR_SERVER_HANDSHAKE_ERR: return "CR_SERVER_HANDSHAKE_ERR";
	case CR_SERVER_LOST: return "CR_SERVER_LOST";
	case CR_COMMANDS_OUT_OF_SYNC: return "CR_COMMANDS_OUT_OF_SYNC";
	case CR_NAMEDPIPE_CONNECTION: return "CR_NAMEDPIPE_CONNECTION";
	case CR_NAMEDPIPEWAIT_ERROR: return "CR_NAMEDPIPEWAIT_ERROR";
	case CR_NAMEDPIPEOPEN_ERROR: return "CR_NAMEDPIPEOPEN_ERROR";
	case CR_NAMEDPIPESETSTATE_ERROR: return "CR_NAMEDPIPESETSTATE_ERROR";
	case CR_CANT_READ_CHARSET: return "CR_CANT_READ_CHARSET";
	case CR_NET_PACKET_TOO_LARGE: return "CR_NET_PACKET_TOO_LARGE";
	case CR_EMBEDDED_CONNECTION: return "CR_EMBEDDED_CONNECTION";
	case CR_PROBE_SLAVE_STATUS: return "CR_PROBE_SLAVE_STATUS";
	case CR_PROBE_SLAVE_HOSTS: return "CR_PROBE_SLAVE_HOSTS";
	case CR_PROBE_SLAVE_CONNECT: return "CR_PROBE_SLAVE_CONNECT";
	case CR_PROBE_MASTER_CONNECT: return "CR_PROBE_MASTER_CONNECT";
	case CR_SSL_CONNECTION_ERROR: return "CR_SSL_CONNECTION_ERROR";
	case CR_MALFORMED_PACKET: return "CR_MALFORMED_PACKET";
	case CR_WRONG_LICENSE: return "CR_WRONG_LICENSE";
	case CR_NULL_POINTER: return "CR_NULL_POINTER";
	case CR_NO_PREPARE_STMT: return "CR_NO_PREPARE_STMT";
	case CR_PARAMS_NOT_BOUND: return "CR_PARAMS_NOT_BOUND";
	case CR_DATA_TRUNCATED: return "CR_DATA_TRUNCATED";
	case CR_NO_PARAMETERS_EXISTS: return "CR_NO_PARAMETERS_EXISTS";
	case CR_INVALID_PARAMETER_NO: return "CR_INVALID_PARAMETER_NO";
	case CR_INVALID_BUFFER_USE: return "CR_INVALID_BUFFER_USE";
	case CR_UNSUPPORTED_PARAM_TYPE: return "CR_UNSUPPORTED_PARAM_TYPE";
	case CR_SHARED_MEMORY_CONNECTION: return "CR_SHARED_MEMORY_CONNECTION";
	case CR_SHARED_MEMORY_CONNECT_REQUEST_ERROR: return "CR_SHARED_MEMORY_CONNECT_REQUEST_ERROR";
	case CR_SHARED_MEMORY_CONNECT_ANSWER_ERROR: return "CR_SHARED_MEMORY_CONNECT_ANSWER_ERROR";
	case CR_SHARED_MEMORY_CONNECT_FILE_MAP_ERROR: return "CR_SHARED_MEMORY_CONNECT_FILE_MAP_ERROR";
	case CR_SHARED_MEMORY_CONNECT_MAP_ERROR: return "CR_SHARED_MEMORY_CONNECT_MAP_ERROR";
	case CR_SHARED_MEMORY_FILE_MAP_ERROR: return "CR_SHARED_MEMORY_FILE_MAP_ERROR";
	case CR_SHARED_MEMORY_MAP_ERROR: return "CR_SHARED_MEMORY_MAP_ERROR";
	case CR_SHARED_MEMORY_EVENT_ERROR: return "CR_SHARED_MEMORY_EVENT_ERROR";
	case CR_SHARED_MEMORY_CONNECT_ABANDONED_ERROR: return "CR_SHARED_MEMORY_CONNECT_ABANDONED_ERROR";
	case CR_SHARED_MEMORY_CONNECT_SET_ERROR: return "CR_SHARED_MEMORY_CONNECT_SET_ERROR";
	case CR_CONN_UNKNOW_PROTOCOL: return "CR_CONN_UNKNOW_PROTOCOL";
	case CR_INVALID_CONN_HANDLE: return "CR_INVALID_CONN_HANDLE";
	case CR_UNUSED_1: return "CR_UNUSED_1";
	case CR_FETCH_CANCELED: return "CR_FETCH_CANCELED";
	case CR_NO_DATA: return "CR_NO_DATA";
	case CR_NO_STMT_METADATA: return "CR_NO_STMT_METADATA";
	case CR_NO_RESULT_SET: return "CR_NO_RESULT_SET";
	case CR_NOT_IMPLEMENTED: return "CR_NOT_IMPLEMENTED";
	case CR_SERVER_LOST_EXTENDED: return "CR_SERVER_LOST_EXTENDED";
	case CR_STMT_CLOSED: return "CR_STMT_CLOSED";
	case CR_NEW_STMT_METADATA: return "CR_NEW_STMT_METADATA";
	case CR_ALREADY_CONNECTED: return "CR_ALREADY_CONNECTED";
	case CR_AUTH_PLUGIN_CANNOT_LOAD: return "CR_AUTH_PLUGIN_CANNOT_LOAD";
	case CR_DUPLICATE_CONNECTION_ATTR: return "CR_DUPLICATE_CONNECTION_ATTR";
	case CR_AUTH_PLUGIN_ERR: return "CR_AUTH_PLUGIN_ERR";
	case CR_INSECURE_API_ERR: return "CR_INSECURE_API_ERR";
	default: return "UNKNOWN_ERROR";
	}
}

CppMySQLException::~CppMySQLException()
{
}



/////////////////////////////////////////////////////////////////////////
CppMySQLQuery::CppMySQLQuery()
{
	_mysql_res = NULL;
	_field = NULL;
	_row = NULL;
	_row_count = 0;
	_field_count = 0;
}
CppMySQLQuery::CppMySQLQuery(CppMySQLQuery& rQuery)
{
	*this = rQuery;
}
CppMySQLQuery::CppMySQLQuery(MYSQL_RES *res):_mysql_res(res)
{
	mysql_data_seek(_mysql_res, 0);
	_field = mysql_fetch_fields(_mysql_res);
	_row = mysql_fetch_row(_mysql_res);
	_row_count = (u_long)mysql_num_rows(_mysql_res);
	_field_count = mysql_num_fields(_mysql_res);
}
CppMySQLQuery& CppMySQLQuery::operator=(CppMySQLQuery& rQuery)
{
	if (this == &rQuery)
		return *this;
	_mysql_res = rQuery._mysql_res;
	_row = NULL;
	_row_count = 0;
	_field_count = 0;
	_field = NULL;
	if (_mysql_res != NULL)
	{
		//定位游标位置到第一个位置
		mysql_data_seek(_mysql_res, 0);
		_row = mysql_fetch_row(_mysql_res);
		_row_count = (u_long)mysql_num_rows(_mysql_res);
		//得到字段数量
		_field_count = mysql_num_fields(_mysql_res);
	}
	rQuery._mysql_res = NULL;
	rQuery._field = NULL;
	rQuery._row = NULL;
	rQuery._row_count = 0;
	rQuery._field_count = 0;
	return *this;
}
CppMySQLQuery::~CppMySQLQuery()
{
	freeRes();
}
void CppMySQLQuery::freeRes()
{
	if (_mysql_res != NULL)
	{
		mysql_free_result(_mysql_res);
		_mysql_res = NULL;
	}
}
u_long CppMySQLQuery::numRow()
{
	return _row_count;
}
int CppMySQLQuery::numFields()
{
	return _field_count;
}
u_long CppMySQLQuery::seekRow(u_long offerset)
{
	if (offerset < 0)
		offerset = 0;
	if (offerset >= _row_count)
		offerset = _row_count - 1;
	mysql_data_seek(_mysql_res, offerset);
	_row = mysql_fetch_row(_mysql_res);
	return offerset;
}
int CppMySQLQuery::fieldIndex(const char* szField)
{
	if (NULL == _mysql_res)
		return -1;
	if (NULL == szField)
		return -1;
	mysql_field_seek(_mysql_res, 0);//定位到第0列
	u_int i = 0;
	while (i < _field_count)
	{
		_field = mysql_fetch_field(_mysql_res);
		if (_field != NULL && strcmp(_field->name, szField) == 0)//找到
			return i;
		i++;
	}
	return -1;
}
const char* CppMySQLQuery::fieldName(int nCol)
{
	if (_mysql_res == NULL)
		return NULL;
	mysql_field_seek(_mysql_res, nCol);
	_field = mysql_fetch_field(_mysql_res);
	if (_field != NULL)
		return _field->name;
	else
		return  NULL;
}
int CppMySQLQuery::getIntField(int nField, int nNullValue/*=0*/)
{
	if (NULL == _mysql_res)
		return nNullValue;
	if (nField + 1 > (int)_field_count)
		return nNullValue;
	if (NULL == _row || !_row[nField])
		return nNullValue;
	return std::stoi(_row[nField]);
}
int CppMySQLQuery::getIntField(const char* szField, int nNullValue/*=0*/)
{
	if (NULL == _mysql_res || NULL == szField)
		return nNullValue;
	if (NULL == _row)
		return nNullValue;
	const char* filed = getStringField(szField);
	if (NULL == filed)
		return nNullValue;
	return std::stoi(filed);
}
const char* CppMySQLQuery::getStringField(int nField, const char* szNullValue/*=""*/)
{
	if (NULL == _mysql_res)
		return szNullValue;
	if (nField + 1 > (int)_field_count)
		return szNullValue;
	if (NULL == _row)
		return szNullValue;
	return _row[nField] ? _row[nField]: szNullValue;
}

const char* CppMySQLQuery::getStringField(const char* szField, const char* szNullValue/*=""*/)
{
	if (NULL == _mysql_res)
		return szNullValue;
	int nField = fieldIndex(szField);
	if (nField == -1)
		return szNullValue;
	return getStringField(nField);
}
double CppMySQLQuery::getFloatField(int nField, double fNullValue/*=0.0*/)
{
	const char* field = getStringField(nField);
	if (NULL == field)
		return fNullValue;
	return std::stod(field);
}

double CppMySQLQuery::getFloatField(const char* szField, double fNullValue/*=0.0*/)
{
	const char* field = getStringField(szField);
	if (NULL == field)
		return fNullValue;
	return std::stod(field);
}
void CppMySQLQuery::nextRow()
{
	if (NULL == _mysql_res)
		return;
	_row = mysql_fetch_row(_mysql_res);
}
bool CppMySQLQuery::eof()
{
	if (_row == NULL)
		return true;
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////
CppMySQLDB::CppMySQLDB()
{
	_db_ptr = NULL;
}
CppMySQLDB::~CppMySQLDB()
{
	close();
}

int CppMySQLDB::open(const char* host, const char* user, const char* passwd, const char* db,
	unsigned int port /*= 0*/, const char* charset /*= "GBK"*/)
{
	int res = 0;
	_db_ptr = mysql_init(NULL);
	if (NULL == _db_ptr)
		throw CppMySQLException(mysql_errno(_db_ptr), mysql_error(_db_ptr));	
	//如果连接失败，返回NULL。对于成功的连接，返回值与第1个参数的值相同。
	if (NULL == mysql_real_connect(_db_ptr, host, user, passwd, db, port, NULL, CLIENT_REMEMBER_OPTIONS))
		throw CppMySQLException(mysql_errno(_db_ptr), mysql_error(_db_ptr));
	char query[64] = "SET NAMES ";
	strcat(query, charset);
	if (mysql_real_query(_db_ptr, query, strlen(query)) != 0)
		throw CppMySQLException(mysql_errno(_db_ptr), mysql_error(_db_ptr));
	return 0 ;
}
void CppMySQLDB::close()
{
	if (_db_ptr != NULL)
	{
		mysql_close(_db_ptr);
		_db_ptr = NULL;
	}
}
MYSQL* CppMySQLDB::getMysql()
{
	return _db_ptr;
}
/* 处理返回多行的查询，返回影响的行数 */
CppMySQLQuery CppMySQLDB::execQuery(const char *sql)
{
	int res = mysql_real_query(_db_ptr, sql, strlen(sql));
	if (0 == res)
	{
		//_db_query._mysql_res = mysql_store_result(_db_ptr);
		return std::move(CppMySQLQuery(mysql_store_result(_db_ptr)) );
	}
	else
		throw CppMySQLException(mysql_errno(_db_ptr), mysql_error(_db_ptr));
}
/* 执行非返回结果查询 */
int CppMySQLDB::execDML(const char* sql)
{
	if (!mysql_real_query(_db_ptr, sql, strlen(sql)))
	{
		//得到受影响的行数
		return (int)mysql_affected_rows(_db_ptr);
	}
	else throw CppMySQLException(mysql_errno(_db_ptr), mysql_error(_db_ptr));
}

/*执行 count 之类的查询*/
int CppMySQLDB::execScalar(const char* sql, int nNullValue )
{
	if (!mysql_real_query(_db_ptr, sql, strlen(sql)))
	{
		//得到受影响的行数
		_db_query._mysql_res = mysql_store_result(_db_ptr);
		unsigned int num_fields = mysql_num_fields(_db_query._mysql_res);
		MYSQL_ROW t_row = mysql_fetch_row(_db_query._mysql_res);
		if (num_fields < 1 || NULL == t_row)
			return -1;
		else
			return std::stoi(t_row[0]);
	}
	else throw CppMySQLException(mysql_errno(_db_ptr), mysql_error(_db_ptr));
}

/* 测试mysql服务器是否存活 */
int CppMySQLDB::ping()
{
	if (mysql_ping(_db_ptr) == 0)
		return 0;
	else throw CppMySQLException(mysql_errno(_db_ptr), mysql_error(_db_ptr));
}
/* 关闭mysql 服务器 */
int CppMySQLDB::shutDown()
{
	if (mysql_shutdown(_db_ptr, SHUTDOWN_DEFAULT) == 0)
		return 0;
	else throw CppMySQLException(mysql_errno(_db_ptr), mysql_error(_db_ptr));
}
/* 主要功能:重新启动mysql 服务器 */
int CppMySQLDB::reboot()
{
	if (!mysql_reload(_db_ptr))
		return 0;
	else throw CppMySQLException(mysql_errno(_db_ptr), mysql_error(_db_ptr));
}
/*
* 说明:事务支持InnoDB or BDB表类型
*/
/* 主要功能:开始事务 */
int CppMySQLDB::startTransaction()
{
	if (!mysql_real_query(_db_ptr, "START TRANSACTION",
		(unsigned long)strlen("START TRANSACTION")))
	{
		return 0;
	}
	else throw CppMySQLException(mysql_errno(_db_ptr), mysql_error(_db_ptr));
}
/* 主要功能:提交事务 */
int CppMySQLDB::commit()
{
	if (!mysql_real_query(_db_ptr, "COMMIT",
		(unsigned long)strlen("COMMIT")))
	{
		return 0;
	}
	else throw CppMySQLException(mysql_errno(_db_ptr), mysql_error(_db_ptr));
}
/* 主要功能:回滚事务 */
int CppMySQLDB::rollback()
{
	if (!mysql_real_query(_db_ptr, "ROLLBACK",
		(unsigned long)strlen("ROLLBACK")))
		return 0;
	else throw CppMySQLException(mysql_errno(_db_ptr), mysql_error(_db_ptr));
}
/* 得到客户信息 */
const char * CppMySQLDB::getClientInfo()
{
	return mysql_get_client_info();
}
/* 主要功能:得到客户版本信息 */
const unsigned long  CppMySQLDB::getClientVersion()
{
	return mysql_get_client_version();
}
/* 主要功能:得到主机信息 */
const char * CppMySQLDB::getHostInfo()
{
	return mysql_get_host_info(_db_ptr);
}
/* 主要功能:得到服务器信息 */
const char * CppMySQLDB::getServerInfo()
{
	return mysql_get_server_info(_db_ptr);
}
/*主要功能:得到服务器版本信息*/
const unsigned long  CppMySQLDB::getServerVersion()
{
	return mysql_get_server_version(_db_ptr);
}
/*主要功能:得到 当前连接的默认字符集*/
const char *  CppMySQLDB::getCharacterSetName()
{
	return mysql_character_set_name(_db_ptr);
}

/* 建立新数据库 */
int CppMySQLDB::createDB(const char* name)
{
	char temp[1024];
	sprintf(temp, "CREATE DATABASE IF NOT EXIST %s", name);
	if (!mysql_real_query(_db_ptr, temp, strlen(temp)))
		return 0;
	else
		//执行查询失败
		return -1;
}
/* 删除制定的数据库*/
int CppMySQLDB::dropDB(const char*  name)
{
	char temp[1024];
	sprintf(temp, "DROP DATABASE %s", name);
	if (!mysql_real_query(_db_ptr, temp, strlen(temp)))
		return 0;
	else
		//执行查询失败
		return -1;
}
bool CppMySQLDB::tableExists(const char* table)
{
	return false;
}
u_int CppMySQLDB::lastRowId()
{
	return 0;
}
