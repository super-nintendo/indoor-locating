# Indoor Positioning System (IPS)


![build](https://img.shields.io/appveyor/ci/:user/:repo.svg)
![chat](https://img.shields.io/discord/:serverId.svg)

## Table of Contents

## Beginners Guide

If you are a total beginner to this, start here!

1. Visit "Build a Beacon controlled by MCS Lite" [(Mediatek reference)](https://docs.labs.mediatek.com/resource/linkit7697-arduino/en/developer-guide/using-mcs-library/connecting-to-mcslite/build-a-beacon-controlled-by-mcs-lite#BuildaBeaconcontrolledbyMCSLite-appendix)
2. Explore [MQTT](http://mqtt.org/) protocol
3. Choose a way to sign in
4. Start writing note!

Linkit 7688 common commands
---

Once the initial 7688 Duo setup has been achieved following the recommendations of [Mediatek Labs](https://docs.labs.mediatek.com/resource/linkit-smart-7688/en/tutorials/cloud-services/mediatek-cloud-sandbox/setup-linkit-smart-7688-as-a-mcs-lite-server), the following command should be excecuted in order to activate the MCS Lite Cloud Service.

1. Power on the 7688 and connect to its console interface (SSH or Serial Port).

```gherkin=
user@terminal:~$ ssh root@mylinkit.com
```

2. Once you introduce both user and password, access the default folder where the node.js file is located

```gherkin=
root@mylinkit:~# cd /Media/SD-P1
root@mylinkit:/tmp/run/mountd/mmcblk0p1# cd 7688
```
3. Launch the MCS Lite Server

```gherkin=
root@mylinkit:/tmp/run/mountd/mmcblk0p1/7688# node server.js &
```
Once the previous steps have been excecuted, the console will indicate which IP belongs to the MCS Lite services.

```gherkin=
+-+-+-+ +-+-+-+-+
 M C S   L I T E 
+-+-+-+ +-+-+-+-+

MCS Lite server IP: 

'192.168.100.110:3000'

/tmp/node_rtsp_rtmp_videoControl
2017-07-05 02:42:00.000 [rtmp] server started on port 1935
2017-07-05 02:42:00.015 [rtsp/http/rtmpt] server started on port 8888
WoT/WebSocket server is listening at ws://0.0.0.0:8000
```
> Note: The IP address will be different for every setup, please, check your own MCSLite IP address.


User flows
---

Under development


## Appendix and FAQ

If you need more information regarding the different points exposed, please visit the following extra information.

>[Exploring MQTT Protocol](https://kokonatt.com/embedded/mqtt-with-esp8266#two-devices) 
[Adrian Benavides]


###### tags: `Indoor Location` `IoT` `Cloud` `LAN`  `MCS` `MQTT` `Eddystone` 
