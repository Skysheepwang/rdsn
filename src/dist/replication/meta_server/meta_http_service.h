// Copyright (c) 2017-present, Xiaomi, Inc.  All rights reserved.
// This source code is licensed under the Apache License Version 2.0, which
// can be found in the LICENSE file in the root directory of this source tree.

#pragma once

#include <dsn/tool-api/http_server.h>
#include "dist/replication/common/replication_common.h"
#include "dist/replication/meta_server/meta_options.h"

namespace dsn {

namespace replication {
class server_state;
class replication_options;
class meta_options;
struct meta_function_level;
class server_load_balancer;

class meta_http_service : public http_service
{
public:
    meta_http_service(meta_service *s) : _service(s)
    {
        // GET ip:port/meta/app?app_name=temp
        register_handler("app",
                         std::bind(&meta_http_service::get_app_handler,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2));
        // GET ip:port/meta/apps
        register_handler("apps",
                         std::bind(&meta_http_service::list_app_handler,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2));
        // GET ip:port/meta/nodes
        register_handler("nodes",
                         std::bind(&meta_http_service::list_node_handler,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2));
        // GET ip:port/meta/cluster
        register_handler("cluster",
                         std::bind(&meta_http_service::get_cluster_info_handler,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2));
    }

    std::string path() const override { return "meta"; }

    void get_app_handler(const http_request &req, http_response &resp);
    void list_app_handler(const http_request &req, http_response &resp);
    void list_node_handler(const http_request &req, http_response &resp);
    void get_cluster_info_handler(const http_request &req, http_response &resp);

private:
    meta_service *_service;
};
} // namespace replication
} // namespace dsn
