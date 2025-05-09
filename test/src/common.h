#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef WIN32
#include <windows.h>
#else
#include "config.h"
#ifndef TRUE
#define TRUE    (BOOL)1
#endif /* TRUE */
#ifndef FALSE
#define FALSE   (BOOL)0
#endif /* FALSE */
#endif

#include <sql.h>
#include <sqlext.h>

#ifdef WIN32
#define snprintf _snprintf
#define pg_memset(dest, ch, count)  SecureZeroMemory(dest, count)
#else
#define pg_memset(dest, ch, count)	memset_s(dest, count, ch, count)
#endif /* WIN32 */

extern SQLHENV env;
extern SQLHDBC conn;

#define CHECK_STMT_RESULT(rc, msg, hstmt)	\
	if (!SQL_SUCCEEDED(rc)) \
	{ \
		print_diag(msg, SQL_HANDLE_STMT, hstmt);	\
		exit(1);									\
    }

#define CHECK_CONN_RESULT(rc, msg, hconn)	\
	if (!SQL_SUCCEEDED(rc)) \
	{ \
		print_diag(msg, SQL_HANDLE_DBC, hconn);	\
		exit(1);									\
    }

extern void print_diag(char *msg, SQLSMALLINT htype, SQLHANDLE handle);
extern const char *get_test_dsn(void);
extern int  IsAnsi(void);
extern void test_connect_ext(char *extraparams);
extern void test_connect(void);
extern void test_disconnect(void);
extern void print_result_meta_series(HSTMT hstmt,
									 SQLSMALLINT *colids,
									 SQLSMALLINT numcols);
extern void print_result_series(HSTMT hstmt,
								SQLSMALLINT *colids,
								SQLSMALLINT numcols,
								SQLINTEGER rowcount,
								BOOL printcolnames);
extern void print_result_meta(HSTMT hstmt);
extern void print_result(HSTMT hstmt);
extern void print_result_with_column_names(HSTMT hstmt);
extern const char *datatype_str(SQLSMALLINT datatype);
extern const char *nullable_str(SQLSMALLINT nullable);
