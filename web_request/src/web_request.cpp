/**
 *  Copyright (c) 2014-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under both the Apache 2.0 license (found in the
 *  LICENSE file in the root directory of this source tree) and the GPLv2 (found
 *  in the COPYING file in the root directory of this source tree).
 *  You may select, at your option, one of the above-listed licenses.
 */

#include "web_request.h"
#include "client.h"

namespace osquery {
TableColumns WebRequestTable::columns() const {
  return {
      std::make_tuple("url", TEXT_TYPE, ColumnOptions::DEFAULT),
      std::make_tuple("response_code", INTEGER_TYPE, ColumnOptions::DEFAULT),
  };
}

QueryData WebRequestTable::generate(QueryContext& context) {
  QueryData results;
  WebRequestClient client;

  
  auto urls = context.constraints["url"].getAll(EQUALS);

 // Using the like clause for urls wouldn't make sense
  if (context.constraints["url"].getAll(LIKE).size()) {
    LOG(WARNING) << "Using LIKE clause for url is not supported";
  }

  for (const auto& url : urls) {
      
     auto response_code = client.get(url);

     Row r;
     r["url"] = TEXT(url);
     r["response_code"] = INTEGER(response_code);

      results.push_back(r);

  }

  return results;
}
} // namespace osquery
