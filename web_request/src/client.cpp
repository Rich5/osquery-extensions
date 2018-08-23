/**
 *  Copyright (c) 2014-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under both the Apache 2.0 license (found in the
 *  LICENSE file in the root directory of this source tree) and the GPLv2 (found
 *  in the COPYING file in the root directory of this source tree).
 *  You may select, at your option, one of the above-listed licenses.
 */

#include "client.h"
#include <curl/curl.h>


namespace osquery {
long WebRequestClient::get(const std::string &url) const{

  CURL *curl;
  CURLcode res;
  long http_code = 0;
  curl = curl_easy_init();

  if(curl) {

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    
    /* Check for errors */ 
    if(res == CURLE_OK){
	
      curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);

    } else {

      //VLOG(1) <<  "curl_easy_perform() failed:" << std::string(curl_easy_strerror(res));
      curl_easy_cleanup(curl);
      return -1;

    }

    
    /* always cleanup */ 
    curl_easy_cleanup(curl);

    return http_code;

   }

  return -1;

}
}
