#### Virtual LAN (VLAN).
LAN (Local Area Network) là một mạng cục bộ – một nhóm các thiết bị (máy tính, máy in, điện thoại IP...) kết nối với nhau trong một phạm vi nhỏ (cùng tòa nhà, cùng phòng) và cùng chung một miền broadcast.
VLAN (Virtual LAN) là kỹ thuật chia một switch vật lý (hoặc nhiều switch) thành nhiều LAN logic (ảo) độc lập với nhau – mà không cần thay đổi dây cáp.
1. By-default VLAN’s Database is Stored in Flash –Memory, With File name
VLAN.dat
2. By-default VLAN1 is created , and all the ports are in VLAN1.
3. VLAN,s Range
1 to 1001 - Normal Range
1002 to 1005 - Reserved VLAN,s (not useable)
1006 to 4096 - Extended VLAN’s

Command to create a VLAN’s.
#en
#conf t
#show vlan ( to view vlan database)
#name Sales ( give what ever you want)

How to Assign multiple port’s in VLAN.
#int range fa0/1-10, fa0/16, fa0/19
#switchport mode access
#switchport access vlan 2 ( 2 is the Vlan number)

Trunk (cổng trung kế) là một cổng trên switch được cấu hình để vận chuyển lưu lượng của nhiều VLAN khác nhau qua cùng một sợi dây vật lý duy nhất.
Nói một cách hình ảnh: Access port giống như một làn đường cao tốc chỉ dành cho một loại xe (một VLAN). Trunk port giống như một cây cầu nhiều làn, cho phép nhiều loại xe (nhiều VLAN) cùng lưu thông.
This can be done with the following commands :
#interface fastethernet [interface number]
#switchport mode access
#switchport access vlan [vlan number]

Dynamic Trunking .
Dynamic Desirable : The 'dynamic desirable' will configure the port to try and become a trunk link by sending a request to the other end of the wire requesting to become a trunk port.
Dynamic Auto : The 'dynamic auto' will configure the port to accept incoming negotiation and will accept becoming either a trunk or an access port.

#### Trunk Encapsulation là gì?

Trunk Encapsulation là cách thức đóng gói (thêm tag) vào frame Ethernet để switch biết frame đó thuộc VLAN nào khi đi qua cổng Trunk.

Có 2 chuẩn chính:
ISL (Cisco cũ, gần như không dùng nữa)
802.1Q (dot1q) – chuẩn mở, dùng phổ biến nhất hiện nay.

#### Switch
VLAN Trunk Protocol (VTP) reduces administration in a switched network. When
you configure a new VLAN on one VTP server, the VLAN is distributed through
all switches in the domain. This reduces the need to configure the same VLAN
everywhere.
VTP is a Cisco-proprietary protocol that is available on most of the Cisco Catalyst
series products.
1. Server Mode :
By-default all the switches are in server mode. We can Create , Delete, or
Modify vlan’s.
Vlan database of VTP server is forwarded to it’s Trunk port.
2. Client Mode :
If we Change a switch into client mode we cannot Create , Delete, or Modify
vlan’s.
It just to get the vlan information (vlan database from server) so it’s copy it
to own vlan database & forward to it’s Trunk port.

3. Transparent Mode :
If we change a switch into VTP transparent mode it will not keep trhe vlan
information (vlan database) sent by the VTP server, but just forward it to its
trunk ports.
NOTE : VTP transparent mode can have it’s own VLAN database which
means we can Create, Delete, Modify Vlan’s but it will not be Propagated to
other switches on Domain.
