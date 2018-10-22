PRIMARY
=======================

    This file describes the installation and configuration for WDT-DIO Linux Driver.

    Note that some release packages have binary files without source code only support
    linux distributions listed as follow :

    Distribution Version :
        - kernel = $(uname -r)
        - glibc  = $(ldd --version)
        - gcc    = $(gcc --version)

    Ubuntu 18.04.0 x86_64 :
        - kernel = 4.15.0-20-generic
        - glibc  = 2.27-3
        - gcc    = 7.3.0-16

    Fedora 27-1.6 x86_64 :
        - kernel = 4.13.9-300.fc27.x86_64
        - glibc  = 2.26
        - gcc    = 7.3.1-5

    Debian 9.4 x86_64 :
        - kernel = 4.9.0-6-amd64
        - glibc  = 2.24-11
        - gcc    = 6.3.0-18

    CentOS 7.4 x86_64 :
        - kernel = 3.10.0-693.el7.x86_64
        - glibc  = 2.17
        - gcc    = 4.8.5-16


STEP 1: UNPACK
=======================

    Decompress the WDT_DIO.YYYYMMDD.tgz :

    $ tar xvzf WDT_DIO.YYYYMMDD.tgz

    where 'YYYYMMDD' is the release number of this library core.

    This will extract the 'WDT_DIO/linux/' directory with the following subdirectories:
    --------------------------------------------------------------------------------------
    deploy/     contains the device modules (wdt_dio.ko) and shared library (libwdt_dio.so)
    driver/     contains the driver source code (*)
    sample/     contains some sample programs with source code
    include/    contains the header file used for samples
    manual/     documentation

    (*) The driver source code may not be contained in some release packages.

    Additionally special kernel supported :

    $ tar xvzf $(uname -r).$(uname -m).tgz -C ./WDT_DIO/linux/deploy/


STEP 2: INSTALL DRIVER
=======================

    2.1
    Load the kernel modules on linux systems :

    $ sudo insmod ./WDT_DIO/linux/deploy/$(uname -r).$(uname -m)/wdt_dio.ko

    Displaying the loaded WDT-DIO kernel modules :

    $ sudo lsmod | grep wdt_dio

    2.2
    This is an example if you want the driver that has -rw-r--r-- permissions, then

    $ sudo chmod 644 /dev/wdt_dio

    Therefore, add above commands into "rc.local" in order to setup when linux system start.

    Ubuntu : /etc/rcS.d/S90rc.local
    Fedora : /etc/rc.d/rc.local

    CentOS : /etc/rc.d/rc.local
    Please note that you must run 'chmod +x /etc/rc.d/rc.local' to ensure that this script will be executed during boot.

    2.3
    The kernel modules and the configuration files are stored in your /lib/modules/$(uname -r) directory.

    $ sudo cp -f ./WDT_DIO/linux/deploy/$(uname -r).$(uname -m)/wdt_dio.ko /lib/modules/$(uname -r)/kernel/drivers

    Automatically loading when linux system start :

    Ubuntu :
    $ echo 'wdt_dio' | sudo tee -a /etc/modules

    Fedora :
    $ echo 'wdt_dio' > /etc/modules-load.d/wdt_dio.conf

    Sometimes you could try these commands when not automatically loading :

    $ sudo depmod -a
    $ sudo modprobe wdt_dio


STEP 3: INSTALL LIBRARY
=======================

    This library is provided as a shared library.
    To install this library into linux system, type the following command :

    Ubuntu :
    $ sudo cp ./WDT_DIO/linux/deploy/$(uname -r).$(uname -m)/libwdt_dio.so /usr/lib

    Fedora x64 :
    $ sudo cp ./WDT_DIO/linux/deploy/$(uname -r).$(uname -m)/libwdt_dio.so /usr/lib64

    There are one or two internal serial ports used in this library, usually be the last one or two.

    $ dmesg | grep ttyS*

    In addition, you could modify proper permissions of these internal serial ports used in this library.
    It is an easy way :

    POC-120 serious :
    $ sudo chmod 666 /dev/ttyS3

    Nuvo-2500 serious :
    $ sudo chmod 666 /dev/ttyS4
    $ sudo chmod 666 /dev/ttyS5

    Nuvo-5000 + D220/D230 :
    $ sudo chmod 666 /dev/ttyS3

    Nuvo-5100VTC :
    $ sudo chmod 666 /dev/ttyS3
    $ sudo chmod 666 /dev/ttyUSB0

    Therefore, add above commands into "rc.local" in order to setup when linux system start.

    Remark :
    Sometimes, you need to enable more than 4 serial ports by adding "8250.nr_uarts=8" into kernel command line.
    For some distributions, the ModemManager crashes on special serial ports. It is an fast way by removing ModemManager packages.


STEP 4: SAMPLES
=======================

    The WDT_DIO function reference of linux system is the same with windows system.
    You could download the lastest WDT_DIO windows driver package and extract the file named "ApplicationNote_WDT_DIO_v#.#.#.pdf".

    4.1 Console samples ( text mode only )

    test_wdt : watch dog sample program
    test_dio : digital input/output sample program
    test_cos : change-of-state sample program

    4.2 Qt samples ( development with Qt support )

    QtDIO : digital input/output sample program
    QtCAN : can bus sample program



BUILD 1: DRIVER
=======================

    Change to the directory which contain WDT-DIO driver source code.

    $ cd ./WDT_DIO/linux/driver

    Always clean the project at first.

    $ make clean

    Then build it.

    $ make

    Copy the binary file into system.

    $ make install

    Manually install the module.

    $ make insmod

    Displaying the loaded information about WDT-DIO kernel module.

    $ make lsmod


BUILD 2: LIBRARY
=======================

    Change to the directory which contain this library source code.

    $ cd ./WDT_DIO

    Always clean the project at first.

    $ make clean

    Then build it.

    $ make

    Copy the binary file into system.

    $ make install

    Copy the binary file into deploy directory.

    $ make deploy



REVISION
=======================
20180502 :
  + Ubuntu 18.04.0 x86_64
  + Fedora 27-1.6 x86_64
  + Debian 9.4 x86_64
  + CentOS 7.4 x86_64
  - Ubuntu 12.04.3 x86_64
  - Ubuntu 14.04.4 x86_64
  - Ubuntu 16.04.2 x86_64
  - Fedora 21-5 x86_64
  - Fedora 24-1.2 x86_64
  - Debian 8.7.1 x86_64
  - Debian 9.3 x86_64
  - CentOS 7.2 x86_64

20170306 :
  + CentOS 7 x86_64

20170222 :
  + Ubuntu 16.04.2 x86_64
  - Ubuntu 16.04.1 x86_64

20170203 :
  + Debian 8.7.1 x86_64

20161201 :
  + Fedora 24-1.2 x86_64
  - Ubuntu 14.04.4 x86_64

20161116 :
  + Bugfix: standard input stream permission for normal user account
  + Fedora 21-5 x86_64 
  - Ubuntu 16.04.0 x86_64

20160919 :
  + Ubuntu 16.04.1 x86_64

20160901 :
  + Ubuntu 16.04.0 x86_64

20160623 :
  + Ubuntu 10.04.0 i686
  + Ubuntu 12.04.3 x86_64
  + Ubuntu 14.04.4 x86_64
