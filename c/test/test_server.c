#include <assert.h>
#include <pthread.h>

#include <CUnit/CUnit.h>
#include <sqlite3.h>

#include "dqlite.h"
#include "suite.h"
#include "server.h"
#include "client.h"
#include "cluster.h"

static dqlite_server *server = NULL;

void test_dqlite_server_setup(){
	int err;
	FILE *log = test_suite_dqlite_log();

	server = dqlite_server_alloc();
	CU_ASSERT_PTR_NOT_NULL(server);

	err = dqlite_server_init(server, log, test_cluster());

	CU_ASSERT_EQUAL(err, 0);
}

void test_dqlite_server_teardown(){
	dqlite_server_close(server);
	dqlite_server_free(server);
}

/*
 * dqlite_server_config_test
 */

void test_dqlite_server_config_vfs()
{
	int err;

	err = dqlite_server_config(server, DQLITE_CONFIG_VFS, "foo");
	CU_ASSERT_EQUAL(err, 0);
}

void test_dqlite_server_config_vfs_twice()
{
	int err;

	err = dqlite_server_config(server, DQLITE_CONFIG_VFS, "foo");
	CU_ASSERT_EQUAL(err, 0);

	err = dqlite_server_config(server, DQLITE_CONFIG_VFS, "bar");
	CU_ASSERT_EQUAL(err, 0);
}