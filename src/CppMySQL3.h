#pragma once


#ifndef _CPP_MYSQL_1_H_
#define _CPP_MYSQL_1_H_
#include <string>
#include <mysql/mysql.h>
#include <mysql/errmsg.h>

typedef unsigned int u_int;
typedef unsigned long long u_longlong;


class CppMySQLException : public std::exception
{
private:
	int mnErrCode;
	std::string msg;

public:

	CppMySQLException(const int nErrCode,
		const char* szErrMess,
		bool bDeleteMsg = false);

	CppMySQLException(const CppMySQLException&  e);

	virtual ~CppMySQLException();

	const int errorCode() { return mnErrCode; }

	const char* what() { return msg.c_str(); }

	static const char* errorCodeAsString(int nErrCode);
};

class CppMySQLDB;
class CppMySQLQuery
{
	friend class CppMySQLDB;
private:
	MYSQL_RES*	_mysql_res;
	MYSQL_FIELD*	_field;
	MYSQL_ROW	_row;
	u_long	_row_count;
	u_int	_field_count;

public:
	CppMySQLQuery();
	//当执行拷贝构造函数后，括号里的类已经无效，不能再使用
	CppMySQLQuery(CppMySQLQuery& rQuery);
	//当执行赋值构造函数后，=右边的类已经无效，不能再使用
	CppMySQLQuery(MYSQL_RES *res);
	CppMySQLQuery& operator=(CppMySQLQuery& rQuery);
	virtual ~CppMySQLQuery();
	u_long numRow();//多少行
	int numFields();//多少列
	int fieldIndex(const char* szField);
	//0...n-1列
	const char* fieldName(int nCol);
	u_long seekRow(u_long offerset);
	int getIntField(int nField, int nNullValue = 0);
	int getIntField(const char* szField, int nNullValue = 0);
	double getFloatField(int nField, double fNullValue = 0.0);
	double getFloatField(const char* szField, double fNullValue = 0.0);
	//0...n-1列
	const char* getStringField(int nField, const char* szNullValue = "");
	const char* getStringField(const char* szField, const char* szNullValue = "");
	//const unsigned char* getBlobField(int nField, int& nLen);
	//const unsigned char* getBlobField(const char* szField, int& nLen);
	//bool fieldIsNull(int nField);
	//bool fieldIsNull(const char* szField);
	bool eof();
	void nextRow();
	/*void finalize();*/
private:
	void freeRes();
	/*void checkVM();*/

};



class CppMySQLDB
{
public:
	CppMySQLDB();
	virtual ~CppMySQLDB();
	int open(const char* host, const char* user, const char* passwd, const char* db,
		unsigned int port = 3306, const char* charset = "GBK");
	void close();
	/* 返回句柄 */
	MYSQL* getMysql();
	/* 处理返回多行的查询，返回影响的行数 */
	//返回引用是因为在CppMySQLQuery的赋值构造函数中要把成员变量_mysql_res置为空
	CppMySQLQuery execQuery(const char *sql);
	/* 执行非返回结果查询 */
	int execDML(const char* sql);
	/*执行 count 之类的查询*/
	int execScalar(const char* szSQL, int nNullValue = 0);

	/* 测试mysql服务器是否存活 */
	int ping();
	/* 关闭mysql 服务器 */
	int shutDown();
	/* 主要功能:重新启动mysql 服务器 */
	int reboot();
	/*
	* 说明:事务支持InnoDB or BDB表类型
	*/
	/* 主要功能:开始事务 */
	int startTransaction();
	/* 主要功能:提交事务 */
	int commit();
	/* 主要功能:回滚事务 */
	int rollback();
	/* 得到客户信息 */
	const char * getClientInfo();
	/* 主要功能:得到客户版本信息 */
	const unsigned long  getClientVersion();
	/* 主要功能:得到主机信息 */
	const char * getHostInfo();
	/* 主要功能:得到服务器信息 */
	const char * getServerInfo();
	/*主要功能:得到服务器版本信息*/
	const unsigned long  getServerVersion();
	/*主要功能:得到 当前连接的默认字符集*/
	const char *  getCharacterSetName();

	/* 建立新数据库 */
	int createDB(const char* name);
	/* 删除制定的数据库*/
	int dropDB(const char* name);
	bool tableExists(const char* table);
	u_int lastRowId();
	void setBusyTimeout(int nMillisecs) {};
private:
	CppMySQLDB(const CppMySQLDB& db);
	/*CppMySQLDB& operator=(const CppMySQLDB& db);
	void checkDB();*/
private:
	/* msyql 连接句柄 */
	MYSQL* _db_ptr;
	CppMySQLQuery _db_query;
};
#endif
