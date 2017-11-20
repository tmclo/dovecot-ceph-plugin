/*
 * Copyright (c) 2017 Tallence AG and the authors
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software
 * Foundation.  See file COPYING.
 */
#ifndef SRC_TESTS_MOCKS_MOCK_TEST_H_
#define SRC_TESTS_MOCKS_MOCK_TEST_H_

#include <map>
#include <string>

#include "../../librmb/rados-cluster.h"
#include "../../librmb/rados-dictionary.h"
#include "../../librmb/rados-storage.h"
#include "../../librmb/rados-config.h"

#include "gmock/gmock.h"

namespace librmbtest {
using librmb::RadosStorage;
using librmb::RadosMailObject;
using librmb::RadosMetadata;

class RadosStorageMock : public RadosStorage {
 public:
  MOCK_METHOD0(get_io_ctx, librados::IoCtx &());
  MOCK_METHOD3(stat_mail, int(const std::string &oid, uint64_t *psize, time_t *pmtime));
  MOCK_METHOD1(set_namespace, void(const std::string &nspace));
  MOCK_METHOD0(get_namespace, std::string());
  MOCK_METHOD0(get_max_write_size, int());
  MOCK_METHOD0(get_max_write_size_bytes, int());
  MOCK_METHOD5(split_buffer_and_exec_op, int(const char *buffer, size_t buffer_length, RadosMailObject *current_object,
                                             librados::ObjectWriteOperation *write_op_xattr, uint64_t max_write));
  MOCK_METHOD1(load_metadata, int(RadosMailObject *mail));
  MOCK_METHOD2(set_metadata, int(const std::string &oid, const RadosMetadata &xattr));

  MOCK_METHOD1(delete_mail, int(RadosMailObject *mail));
  MOCK_METHOD1(delete_mail, int(std::string oid));
  MOCK_METHOD4(aio_operate, int(librados::IoCtx *io_ctx_, const std::string &oid, librados::AioCompletion *c,
                                librados::ObjectWriteOperation *op));
  MOCK_METHOD1(find_mails, librados::NObjectIterator(const RadosMetadata *attr));
  MOCK_METHOD1(open_connection, int(const std::string &poolname));
  MOCK_METHOD1(wait_for_write_operations_complete,
               bool(std::map<librados::AioCompletion *, librados::ObjectWriteOperation *> *completion_op_map));
  MOCK_METHOD1(wait_for_rados_operations, bool(const std::vector<librmb::RadosMailObject *> &object_list));

  MOCK_METHOD2(read_mail, int(librados::bufferlist *buffer, const std::string &oid));
  MOCK_METHOD2(update_metadata, bool(std::string oid, std::list<RadosMetadata> &to_update));
  MOCK_METHOD6(move, bool(std::string &src_oid, const char *src_ns, std::string &dest_oid, const char *dest_ns,
                          std::list<RadosMetadata> &to_update, bool delete_source));
  MOCK_METHOD5(copy, bool(std::string &src_oid, const char *src_ns, std::string &dest_oid, const char *dest_ns,
                          std::list<RadosMetadata> &to_update));
  MOCK_METHOD2(save_mail, bool(RadosMailObject *mail, bool &save_async));
  MOCK_METHOD0(alloc_mail_object, librmb::RadosMailObject *());
  MOCK_METHOD1(free_mail_object, void(librmb::RadosMailObject *mail));
  MOCK_METHOD0(get_rados_config, librmb::RadosConfig *());

  MOCK_METHOD2(update_extended_metadata, int(std::string &oid, librmb::RadosMetadata *metadata));
  MOCK_METHOD2(remove_extended_metadata, int(std::string &oid, std::string &key));
};

using librmb::RadosDictionary;

class RadosDictionaryMock : public RadosDictionary {
 public:
  MOCK_METHOD1(get_full_oid, const std::string(const std::string &key));
  MOCK_METHOD0(get_shared_oid, const std::string());
  MOCK_METHOD0(get_private_oid, const std::string());
  MOCK_METHOD0(get_oid, const std::string &());
  MOCK_METHOD0(get_username, const std::string &());
  MOCK_METHOD0(get_io_ctx, librados::IoCtx &());
  MOCK_METHOD1(remove_completion, void(librados::AioCompletion *c));
  MOCK_METHOD1(push_back_completion, void(librados::AioCompletion *c));
  MOCK_METHOD0(wait_for_completions, void());
  MOCK_METHOD2(get, int(const std::string &key, std::string *value_r));
};

using librmb::RadosCluster;

class RadosClusterMock : public RadosCluster {
 public:
  MOCK_METHOD0(init, int());
  MOCK_METHOD0(deinit, void());
  MOCK_METHOD1(pool_create, int(const std::string &pool));
  MOCK_METHOD2(io_ctx_create, int(const std::string &pool, librados::IoCtx *io_ctx));
  MOCK_METHOD2(get_config_option, int(const char *option, std::string *value));
  MOCK_METHOD0(is_connected, bool());
};

}  // namespace librmbtest

#endif  // SRC_TESTS_MOCKS_MOCK_TEST_H_
