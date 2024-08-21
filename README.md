# TRC_ROUTE
## about
trc_route: A network tracing utility designed to map the path that data packets take to reach a specified destination. By sending packets with increasing time-to-live (TTL) values, trc_route identifies the routers along the path, providing valuable insights into network topology and potential issues. While offering a fundamental tracing capability, trc_route may have limitations compared to fully featured traceroute tools, such as missing advanced options or detailed hop information.
## requirements
- linux
- root privilege
## usage
```
$ ./trc_route DESTINATION [-i=INTERFACE] [-t=TIMEOUT]
DESTINATION: domain_name/ip_address of the target host
-i: optional name of the interface to be used, default enp0s3
-t: optional number of seconds till network response, default 3
```
## example output
```
# ./trc_route 1337.ma -t=1
TRC_route to 1337.ma (104.18.32.248)
 ,  from enp0s3 (10.13.100.30)
 1  10.13.254.254 [10.13.254.254] 0.526 ms
 2  10.21.1.1 [nat.1337.ma] 0.398 ms
 3  197.230.30.145 [197.230.30.145] 0.317 ms
 4  10.43.88.105 [10.43.88.105] 1.775 ms
 5  10.43.82.105 [10.43.82.105] 18.264 ms
 6  10.43.82.106 [10.43.82.106] 18.919 ms
 7  197.230.41.102 [197.230.41.102] 39.752 ms
 8  104.18.32.248 [104.18.32.248] 20.677 ms
```
