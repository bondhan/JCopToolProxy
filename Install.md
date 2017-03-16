Installing the drivers manually
--------------------
* Install the certificate BixVReader.cer in local machine in Trusted Root Certification Authorities:
* Open Command prompt as administrator
* Find your devcon.exe, set the path to point to devcon.exe location, in my case: set PATH=%PATH%;”C:\Program Files (x86)\Windows Kits\10\Tools\x64?
* Makes sure the .ini file is inside the folder, refer to this repository\Driver\Debug for .ini file
* Run the install command: D:\GCC_WORK\WORKSPACE\GIT\vsmartcard\virtualsmartcard\win32\x64\Debug\BixVReader>devcon -r install BixVReader.inf root\BixVirtualReader

		Device node created. Install is complete when drivers are installed…
		Updating drivers for root\BixVirtualReader from D:\GCC_WORK\WORKSPACE\GIT\vsmartcard\virtualsmartcard\win32\x64\Debug\BixVReader\BixVReader.inf.
		Drivers installed successfully.

* It will show pop either to install the driver or no due to the certificate…

