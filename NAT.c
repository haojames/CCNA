NAT (Network Address Translation – Dịch địa chỉ mạng) là kỹ thuật ánh xạ địa chỉ IP này thành địa chỉ IP khác khi gói tin đi qua router hoặc firewall. NAT cho phép nhiều thiết bị trong mạng riêng (private) dùng chung một hoặc vài địa chỉ công cộng (public) để ra Internet.
Hãy tưởng tượng NAT như một "lễ tân của tòa nhà" : Mỗi người trong tòa nhà có số phòng riêng (IP private), nhưng khi gửi thư ra ngoài, lễ tân sẽ ghi địa chỉ tòa nhà (IP public) và đánh dấu thư đó là của phòng nào. Khi thư trả lời về, lễ tân dựa vào dấu hiệu để chuyển đúng phòng.

1. Tại sao cần NAT?
Vấn đề	Giải pháp của NAT
Thiếu địa chỉ IPv4 công cộng	Hàng nghìn máy trong công ty dùng chung 1 hoặc vài IP public.
Bảo mật mặc định	IP private (192.168.x.x, 10.x.x.x, 172.16.x.x) không thể bị truy cập trực tiếp từ Internet.
Linh hoạt chuyển đổi ISP	Thay đổi IP public mà không cần cấu hình lại từng máy trong mạng nội bộ.
💡 Các dải IP private (RFC 1918):

10.0.0.0 – 10.255.255.255 (10.0.0.0/8)

172.16.0.0 – 172.31.255.255 (172.16.0.0/12)

192.168.0.0 – 192.168.255.255 (192.168.0.0/16)

2. Ba loại NAT chính (quan trọng nhất)
Loại NAT	Tên khác	Hoạt động	Ánh xạ	Dùng trong
Static NAT	NAT 1:1	Một IP private ⇔ Một IP public (cố định)	1:1	Server cần truy cập từ ngoài (web, mail)
Dynamic NAT	NAT nhiều: nhiều	Pool IP public, khi cần lấy một IP từ pool	N:M (số public < số private)	Mạng cũ, ít dùng
PAT	NAT Overload, NAT 1:N	Nhiều IP private dùng chung một IP public nhưng khác port	N:1 (hàng nghìn máy / 1 IP)	Phổ biến nhất – mọi router gia đình, doanh nghiệp
🧠 PAT là "NAT mà bạn dùng hàng ngày" – modem WiFi nhà bạn cho 10 máy dùng chung 1 IP public ra Internet.

3. Ví dụ cụ thể (PAT – dễ hiểu nhất)
Topology:

Mạng nội bộ: 192.168.1.0/24

Router NAT có IP public: 203.0.113.5

Máy A: 192.168.1.10, cổng nguồn 12345

Máy B: 192.168.1.20, cổng nguồn 12345 (trùng số port)

Khi máy A gửi gói tin ra Internet:

Gói tin gốc:

Nguồn: 192.168.1.10:12345

Đích: 8.8.8.8:80 (Google DNS)

Router NAT thay đổi:

IP nguồn → 203.0.113.5

Port nguồn → 55001 (chọn port ngẫu nhiên chưa dùng)

Lưu vào bảng NAT:

text
Inside Local         Inside Global
192.168.1.10:12345 ↔ 203.0.113.5:55001
Google gửi trả lời đến 203.0.113.5:55001.

Router NAT tra bảng → biết gói này dành cho 192.168.1.10:12345 → đổi địa chỉ đích và port về đúng máy.

Máy A nhận được gói trả lời.
Máy B cũng dùng port 12345 nhưng NAT sẽ ánh xạ sang port công cộng khác (ví dụ 55002), không xung đột.

4. Các khái niệm "Inside" và "Outside" (quan trọng để cấu hình)
Thuật ngữ	Ý nghĩa	Ví dụ
Inside Local	Địa chỉ IP của thiết bị bên trong mạng nội bộ	192.168.1.10
Inside Global	Địa chỉ IP công cộng đại diện cho thiết bị nội bộ khi ra ngoài	203.0.113.5 (hoặc 203.0.113.5:55001)
Outside Local	Địa chỉ IP của thiết bị bên ngoài nhìn từ bên trong (ít dùng)	(thường trùng với Outside Global)
Outside Global	Địa chỉ thực của thiết bị bên ngoài Internet	8.8.8.8

5. Cấu hình NAT trên Cisco (ví dụ)
PAT (phổ biến nhất) – cho mạng nội bộ ra Internet:
text
interface GigabitEthernet0/0
 ip address 192.168.1.1 255.255.255.0
 ip nat inside
!
interface GigabitEthernet0/1
 ip address 203.0.113.5 255.255.255.248
 ip nat outside
!
ip access-list standard INSIDE_NET
 permit 192.168.1.0 0.0.0.255
!
ip nat inside source list INSIDE_NET interface GigabitEthernet0/1 overload
Static NAT (cho server web):
text
ip nat inside source static 192.168.1.100 203.0.113.10
Dynamic NAT (dùng pool IP public):
text
ip nat pool MY_POOL 203.0.113.10 203.0.113.20 netmask 255.255.255.248
ip nat inside source list INSIDE_NET pool MY_POOL

6. Ưu và nhược điểm của NAT
✅ Ưu điểm	❌ Nhược điểm
Tiết kiệm địa chỉ IPv4 (hàng nghìn máy dùng chung vài IP)	Phá vỡ tính end-to-end của Internet (khó host server từ nội bộ)
Tăng bảo mật mặc định (IP private không bị truy cập trực tiếp từ ngoài)	Một số giao thức không qua NAT được (IPsec, FTP active, SIP...) cần helper
Linh hoạt thay đổi ISP (chỉ sửa NAT, không sửa từng máy)	Tăng độ phức tạp cho debugging (trace đường đi khó hơn)

7. Các lệnh kiểm tra NAT trên Cisco
Lệnh	Ý nghĩa
show ip nat translations	Xem bảng NAT đang hoạt động
show ip nat statistics	Xem thống kê (hits, misses, expired translations)
debug ip nat	Theo dõi real-time quá trình NAT (cẩn thận trên production)
clear ip nat translation *	Xóa toàn bộ bảng NAT

🎯 Tóm gọn trong 1 câu:
NAT là "phiên dịch viên địa chỉ" – biến IP private (như 192.168.1.x) thành IP public (như 203.0.113.5) để máy trong mạng nội bộ ra Internet được, và PAT là hình thức NAT phổ biến nhất (nhiều máy dùng chung 1 IP public nhờ phân biệt qua cổng port).
