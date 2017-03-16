Introduction
========

This a simple application which connect the virtual smart card reader (VPCD) with JCOP Tool.

Virtual Smart Card Architecture Virtual PCD 2 	<==> JCopToolProxy <==> 	JCOP Tool

			(localhost:35963)	<==> JCopToolProxy <==> 	(localhost:8050)

It is written based on the log file of TCP/IP trace.

One important idea of this tool is to help Java Card applet developer to work faster and more efficient on their development (if they are using JCOP Tool)


Log
------------

Please check in the log folder


Installation
------------
- [Install] the VPCD (https://bono02.wordpress.com/2017/02/28/install-bixvreader-on-windows-10/)
- Run the JCop Tool with port setting is 8050 and send /close command
- Dowload from the JCTP_Deliverables and Run the JCopToolProxy, click connect, you can File->Hide to hide it in system tray

License
------------

* MIT License
* Others are belong to their respective owner and copyright.
* Icon is taken from [flaticon](http://www.flaticon.com/)

References
------------
1. VPCD from [vsmartcard] (https://github.com/bondhan/vsmartcard)
2. [UMDF Virtual Smart Card Reader] (https://www.codeproject.com/articles/134010/an-umdf-driver-for-a-virtual-smart-card-reader)
3. JCOP Tool proprietary of NXP
4. Qt 5.5
