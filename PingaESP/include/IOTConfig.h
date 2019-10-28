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

const char private_key_str[] = "03:8c:d2:69:eb:b9:9f:0e:d8:dc:32:53:bd:2c:d0:37:99:ae:b8:ee:52:3f:44:06:6f:92:41:40:30:a8:38:22";

// Time (seconds) to expire token += 20 minutes for drift
const int jwt_exp_secs = 3600 * 24; // Maximum 24H (3600*24)

const char root_cert[] =
  "-----BEGIN CERTIFICATE-----\n"
  "MIIFrTCCBJWgAwIBAgIQOnoLuBUOnzACAAAAAEfYnzANBgkqhkiG9w0BAQsFADBC\n"
  "MQswCQYDVQQGEwJVUzEeMBwGA1UEChMVR29vZ2xlIFRydXN0IFNlcnZpY2VzMRMw\n"
  "EQYDVQQDEwpHVFMgQ0EgMU8xMB4XDTE5MTAxMDIwNTgxNFoXDTIwMDEwMjIwNTgx\n"
  "NFowbTELMAkGA1UEBhMCVVMxEzARBgNVBAgTCkNhbGlmb3JuaWExFjAUBgNVBAcT\n"
  "DU1vdW50YWluIFZpZXcxEzARBgNVBAoTCkdvb2dsZSBMTEMxHDAaBgNVBAMTE21x\n"
  "dHQuZ29vZ2xlYXBpcy5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIB\n"
  "AQCXeQ8GgWy+/KYPtVOZJkSgvCVtLz95VhFicoY4WAAdKa9zjDjrLO9J+AZv/ebA\n"
  "stFR6/cKWMirojZgkMx/47iKdoo0ea/wM8B4Lct2Teg3WG0Vtmhv/FKUACKslQWW\n"
  "P56/zjRmMILHJ8YHf5KzFPgoOaZoypBcz2bHu++Zh959Su9qBvyA3MZy8u25s822\n"
  "ZuNHUmxawX1JYwE5sUOVaZ1S+NNa90sGpObHsdFbqhSBtTv1GZ5TNmdTPOt1Q7dR\n"
  "ewKOhQM6lVeMfIcvP2YLL1xj9gwzj+aMB+NHCuk/scaQjHOkWTD1mkULufbn7QQo\n"
  "ppcJF9lCgW++SbECYhXqRb5VAgMBAAGjggJyMIICbjAOBgNVHQ8BAf8EBAMCBaAw\n"
  "EwYDVR0lBAwwCgYIKwYBBQUHAwEwDAYDVR0TAQH/BAIwADAdBgNVHQ4EFgQUaxwq\n"
  "sfzClLRFkL1picHPQnWRlG4wHwYDVR0jBBgwFoAUmNH4bhDrz5vsYJ8YkBug630J\n"
  "/SswZAYIKwYBBQUHAQEEWDBWMCcGCCsGAQUFBzABhhtodHRwOi8vb2NzcC5wa2ku\n"
  "Z29vZy9ndHMxbzEwKwYIKwYBBQUHMAKGH2h0dHA6Ly9wa2kuZ29vZy9nc3IyL0dU\n"
  "UzFPMS5jcnQwOAYDVR0RBDEwL4ITbXF0dC5nb29nbGVhcGlzLmNvbYIYbXF0dC1t\n"
  "dGxzLmdvb2dsZWFwaXMuY29tMCEGA1UdIAQaMBgwCAYGZ4EMAQICMAwGCisGAQQB\n"
  "1nkCBQMwLwYDVR0fBCgwJjAkoCKgIIYeaHR0cDovL2NybC5wa2kuZ29vZy9HVFMx\n"
  "TzEuY3JsMIIBAwYKKwYBBAHWeQIEAgSB9ASB8QDvAHYAsh4FzIuizYogTodm+Su5\n"
  "iiUgZ2va+nDnsklTLe+LkF4AAAFtt636NQAABAMARzBFAiBg/TiPknytEFkn49hJ\n"
  "AOmqJwXumBfSQmssRdBk9x4fywIhALLS8l3EbDQg5Dom3SfiIPABK7K8tb1JI+iY\n"
  "VaRqdx44AHUAXqdz+d9WwOe1Nkh90EngMnqRmgyEoRIShBh1loFxRVgAAAFtt636\n"
  "VQAABAMARjBEAiB8fauP4jB1l2nFXNoSbvRt8MPRs2N39QaD8+M4GR830AIgfJw4\n"
  "X977s9h/nSFzXGPYfhsdqD3ePAaSfDhaPxRNpBAwDQYJKoZIhvcNAQELBQADggEB\n"
  "AB6JmWugYApTob5rBwV/d5e7S3n1VLWCBSp1/WC/viflur9G1bgGU/adg/TgAoci\n"
  "exvq66Xczhllcr5xOO0p9Y9JGDqUu8GTqSzVJ3XpiK5kQ0JYL1RACk5OPLXVLYgd\n"
  "0HhRfxxQeDE6zJ+stOUcc9ULnLwwKF/ncpwrEQuKAuqhgdp2GgoXty8QS+hJu2IF\n"
  "Nj+WcT4+ls+8/jFOkkbrrFkxFvaKwbRZpDInw1eHVyu9L736bxyBxvH2a1GTNOGl\n"
  "hv6S9dTlUhTwmlHG8G/g5W2UvLVfb2SGxXfI1F8MjG/NWWXMQeFKUiqTu9NoF2dr\n"
  "igm711LORqHs2tZ6qvQAkZQ=\n"
  "-----END CERTIFICATE-----\n";


//const int ex_num_topics = 1;
//const char* ex_topics[ex_num_topics] = {
//  "/devices/my-device/tbd/#"
//};

#endif //__IOTCONFIG_H__