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
$ ./trc_route 162.252.205.130
TRC_route to 162.252.205.130 (162.252.205.130)
 ,  from enp0s3 (10.13.100.30)
 1  10.13.254.254 [10.13.254.254] 0.808 ms
 2  10.21.1.1 [nat.1337.ma] 0.376 ms
 3  197.230.30.145 [197.230.30.145] 0.336 ms
 4  10.43.88.105 [10.43.88.105] 4.440 ms
 5  10.43.82.105 [10.43.82.105] 18.278 ms
 6  10.43.82.106 [10.43.82.106] 18.819 ms
 7  10.43.250.213 [10.43.250.213] 39.742 ms
 8  #  #  #  #  #
 9  #  130.117.14.46 [centurylink.mad05.atlas.cogentco.com] 0.052 ms
10  #  130.117.14.46 [centurylink.mad05.atlas.cogentco.com] 0.046 ms
11  4.69.140.130 [ae3.3.bar4.Toronto1.net.lumen.tech] 0.011 ms
12  4.69.140.130 [ae3.3.bar4.Toronto1.net.lumen.tech] 0.024 ms
13  4.16.51.30 [level3-gw.core02.tor1.prioritycolo.com] 0.010 ms
14  67.223.96.90 [67.223.96.90] 0.037 ms
15  162.252.205.130 [bad.horse] 0.036 ms
16  162.252.205.131 [bad.horse] 0.024 ms
17  162.252.205.132 [bad.horse] 0.023 ms
18  162.252.205.133 [bad.horse] 0.037 ms
19  162.252.205.134 [he.rides.across.the.nation] 0.023 ms
20  162.252.205.135 [the.thoroughbred.of.sin] 0.071 ms
21  162.252.205.136 [he.got.the.application] 0.111 ms
22  162.252.205.137 [that.you.just.sent.in] 0.079 ms
23  162.252.205.138 [it.needs.evaluation] 0.021 ms
24  #  162.252.205.139 [so.let.the.games.begin] 0.099 ms
25  162.252.205.140 [a.heinous.crime] 0.070 ms
26  162.252.205.141 [a.show.of.force] 0.075 ms
27  162.252.205.141 [a.show.of.force] 0.083 ms
28  162.252.205.142 [a.murder.would.be.nice.of.course] 0.012 ms
29  #  162.252.205.143 [bad.horse] 0.045 ms
30  162.252.205.144 [bad.horse] 0.072 ms
31  162.252.205.145 [bad.horse] 0.027 ms
32  162.252.205.146 [he-s.bad] 0.087 ms
33  162.252.205.146 [he-s.bad] 0.108 ms
34  162.252.205.147 [the.evil.league.of.evil] 0.011 ms
35  162.252.205.148 [is.watching.so.beware] 0.085 ms
36  162.252.205.149 [the.grade.that.you.receive] 0.020 ms
37  162.252.205.150 [will.be.your.last.we.swear] 0.019 ms
38  162.252.205.151 [so.make.the.bad.horse.gleeful] 0.079 ms
39  162.252.205.152 [or.he-ll.make.you.his.mare] 0.026 ms
40  162.252.205.153 [o_o] 0.158 ms
41  162.252.205.154 [you-re.saddled.up] 0.077 ms
42  162.252.205.155 [there-s.no.recourse] 0.026 ms
43  162.252.205.156 [it-s.hi-ho.silver] 0.077 ms
44  162.252.205.130 [bad.horse] 0.027 ms
```
