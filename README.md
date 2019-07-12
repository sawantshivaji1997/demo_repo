# List of Assignments

## Git commands
1.  Create a git repository using a free account on github.
    - Create a file
    - Make some changes to it
    - commit the changes.
    - push to remote branch.
    - Also try git rm, git clone and git merge etc.

## Google Protobuf [:link:](https://developers.google.com/protocol-buffers/docs/cpptutorial)
1.  Install the protocol buffer [Installation](https://askubuntu.com/questions/1072683/how-can-i-install-protoc-on-ubuntu-16-04)
1.  Write a sample program using google protobuff.  Read and write a message to a file.
    - Make a protoc file protocfilename.protoc 
    - Compile with ```protoc --cpp_out=./ ./protocfilename.protoc```
    - Write the main code and add the generated header file from compilation of protoc file in the main code.
    - Compile and run the main code with following commands
      - ``` c++ -std=c++11 mainfile.cpp protocfilename.pb.cc `pkg-config --cflags --libs protobuf` -o mainfile```
      - ``` ./mainfile filenametowrite ```
      
## Virtualization
- Study different types of Hypervisors, Clouds.

## Linux LVM, LVMsnapshots, device mapper
1.  Add a disk to your linux vm
1.  Create PVs, then VGs and then LVs.
    - ``` pvcreate /dev/sd{b,c,...}``` 
    - ``` pvs # to display physical volume```
    - ``` vgcreate <vgname> /dev/sd{b,c,...}```
    - ``` vgs # to display all volume group```
    - ``` lvcreate -L <size> -n <lvname> <vgname> ``` ```-n``` : name flag , ```-L``` : for size in MB, GB, etc.
1.  Mount them by adding them to /etc/fstab and create few files on them.
    - ``` mkfs.ext4 /dev/<vgname>/<lvname>```
    - ``` mkdir /mnt/<lvname>```
    - ``` mount /dev/<vgname>/<lvname> /mnt/<lvname>```
    - Add entry in /etc/fstab ```/dev/<vgname>/<lvname> /mnt/lvname ext4 defaults, nofail 0 0```
    - Reboot
1. LVM Snapshot
    - LVM snapshot ``` lvcreate -L <size> -s -n <snapshotname> /dev/<vgname>/<lvname> ``` ```-s``` : snapshot flag. 
    - Mount the snapshot
    
## Windows Volume Shadow Copy Service (VSS) [:link:](https://docs.microsoft.com/en-us/windows/win32/vss/volume-shadow-copy-service-portal)
1.  Create a shadow copy of one of the drives of your windows VM. On powershell type ```wmic shadowcopy call create Volume='C:\' ``` 
1.  Expose it using vssadmin/diskshadow and access it
1.  Cleanup after you are done. 

## Windows Management Instrumentation (WMI) [:link:](https://docs.microsoft.com/en-us/windows/win32/wmisdk/wmi-start-page)
- Write a small powershell script to sort your logical disks on the basis of used space.
  - Run following commands on powershell
  - ``` $obj= gwmi win32_logicaldisk |?{$_.drivetype -eq 3}```
  - ``` $usedspace=@()```
  - ``` ForEach($ob in $obj){ $usedspace+=[math]::Round(($ob.Size-$ob.FreeSpace)/1GB,2) }```
  - ``` $usedspace | Sort-Object```
  
## SSH, winexe, Rsync, Bash, samba share. 
- Write a script to check all the reachable machines from a given list (Windows + Linux). (Used Ping in bash script and took the output of ping command)
- Print the OS and OS-version for reachable Machines.(Used **namp** for detecting OS) 
- Dump this os information to a file with that ip in its name.
- Copy this file to that specific machine. (Used **Rsync**)

## Socket programming with Protobuf
- Write a program to get a Message from user, fill it into a protobuff msg. Send this info over socket to a socket server that calls a script to dump this to a file. The script will count the number of letters in that message and send it back. The socket server will send back this data using protobuff msgs to the main interface that will show it to user. [server code](https://github.com/sawantshivaji1997/demo_repo/blob/master/protobuf/server.cpp) [client code](https://github.com/sawantshivaji1997/demo_repo/blob/master/protobuf/client.cpp)

## ZFS + Loopback device
1.  Create a zfs volume and mount it.
    - ``` zpool create <poolname> /dev/vdb```
    - ``` zfs create -V 10G <poolname>/<volumename>```
    - ``` zfs set mountpoint=/mnt/<volumename> /<poolname>/<volumename>```
1.  Create a sparse vdisk using dd inside the zfs volume.
    - ``` dd if=/mnt/<volumename> of=sparse_file.img bs=1 count=0 seek=<size>```
    - ``` du -sh sparse_file.img``` To confirm created file
1.  Format this vdisk into multiple partitions and mount them. (Using loopback devices)
    - ``` losetup /dev/loop0 sparse_file.img```
    - ``` losetup /dev/loop0``` To confirm created loopback device
    - ``` mkfs.ext4 /dev/loop0``` Format the device
    - ``` mkdir /mnt/loop0/``` For mounting
    - ``` mount -t ext4 /dev/loop0 /mnt/loop0```
    
