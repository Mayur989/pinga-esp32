#ifndef __IOTCONFIG_H__
#define __IOTCONFIG_H__
// This file contains your configuration used to connect to Cloud IoT Core

// Cloud iot details.
const char project_id[] = "pinga-256611";
const char location[] = "europe-west1";
const char registry_id[] = "pinga-registry";
const char device_id[] = "pinga";

// Configuration for NTP
const char ntp_primary[] = "pool.ntp.org";
const char ntp_secondary[] = "time.nist.gov";

const char private_key_str[] =
    "03:8c:d2:69:eb:b9:9f:0e:d8:dc:32:53:bd:2c:d0:"
    "37:99:ae:b8:ee:52:3f:44:06:6f:92:41:40:30:a8:"
    "38:22";

// Time (seconds) to expire token += 20 minutes for drift
const int jwt_exp_secs = 3600 * 24; // Maximum 24H (3600*24)

const char root_cert[] =
  "-----BEGIN CERTIFICATE-----\n"
  "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\n"
  "uJp1lynw1aN5nCUPrLKZPBkb9Q==\n"
  "-----END CERTIFICATE-----\n";


//const int ex_num_topics = 1;
//const char* ex_topics[ex_num_topics] = {
//  "/devices/my-device/tbd/#"
//};

#endif //__IOTCONFIG_H__