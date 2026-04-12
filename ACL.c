ACL (Access Control List – Danh sách kiểm soát truy cập) là một bảng các quy tắc (rules) được cấu hình trên router hoặc switch, dùng để cho phép (permit) hoặc từ chối (deny) lưu lượng mạng dựa trên các tiêu chí như địa chỉ IP nguồn/đích, cổng (port), giao thức (TCP/UDP/ICMP)...
Hãy tưởng tượng ACL như một "người gác cổng có danh sách đen/trắng": gói tin nào vào đến cổng router sẽ được so với danh sách lần lượt từ trên xuống dưới, gặp rule đầu tiên khớp thì thực thi (permit hoặc deny) và dừng lại.
1. Cấu trúc cơ bản của một ACL entry
Mỗi dòng (entry) trong ACL có dạng:
text
<permit | deny> <giao thức> <địa chỉ nguồn> <wildcard mask> <địa chỉ đích> <wildcard mask> [port]
Ví dụ:
text
access-list 100 permit ip 192.168.1.0 0.0.0.255 any
(Giải thích: Cho phép gói tin IP từ mạng 192.168.1.0/24 đi đến bất kỳ đâu)

2. Hai loại ACL chính (quan trọng nhất)
Loại ACL	Số hiệu (Cisco)	Kiểm tra dựa trên	Tiêu tốn CPU	Ghi chú
Standard ACL	1–99, 1300–1999	Địa chỉ IP nguồn	Rất ít	Thô sơ, chỉ lọc theo "ai gửi"
Extended ACL	100–199, 2000–2699	IP nguồn + IP đích + cổng (port) + giao thức	Nhiều hơn	Linh hoạt, lọc chi tiết

💡 Mẹo nhớ: Standard = "S" = Source (chỉ kiểm tra nguồn). Extended = "E" = Everything (kiểm tra mọi thứ).

3. Cách ACL hoạt động (nguyên lý "first match")
1. Router nhận một gói tin trên interface.
2. Nếu ACL được áp dụng inbound (hướng vào), router kiểm tra ACL ngay khi nhận.
3. Nếu ACL áp dụng outbound (hướng ra), router định tuyến xong rồi mới kiểm tra ACL trước khi gửi ra.
4. Router dò ACL từ trên xuống dưới, theo số thứ tự (sequence number).
5. Gặp rule đầu tiên khớp → thực hiện permit (cho qua) hoặc deny (chặn) → dừng lại, không xét rule tiếp theo.
6. Nếu không có rule nào khớp → áp dụng implicit deny (từ chối ngầm) ở cuối → gói tin bị chặn.
⚠️ Quy tắc vàng: Cuối mỗi ACL luôn có một deny any any ngầm. Nếu bạn quên permit rule, mọi thứ sẽ bị chặn.

  4. Ví dụ minh họa
Ví dụ 1: Standard ACL – chặn một máy cụ thể
Yêu cầu: Chặn máy 192.168.1.10 (nguồn) ra Internet, cho phép tất cả các máy khác.

text
access-list 1 deny host 192.168.1.10
access-list 1 permit any
interface GigabitEthernet0/0 (cổng WAN ra Internet)
 ip access-group 1 out
Ví dụ 2: Extended ACL – chỉ cho phép web (port 80, 443)
Yêu cầu: Cho phép mạng nội bộ 192.168.1.0/24 truy cập web (HTTP, HTTPS) ra ngoài, chặn mọi thứ khác (SSH, FTP, ping...).

text
access-list 100 permit tcp 192.168.1.0 0.0.0.255 any eq 80
access-list 100 permit tcp 192.168.1.0 0.0.0.255 any eq 443
access-list 100 deny ip any any
interface GigabitEthernet0/0
 ip access-group 100 out
Ví dụ 3: Extended ACL – chặn SSH vào router
Yêu cầu: Chỉ cho phép quản trị viên từ 10.0.0.5 được SSH vào router, chặn tất cả các SSH khác.

text
access-list 101 permit tcp host 10.0.0.5 host 192.168.1.1 eq 22
access-list 101 deny tcp any host 192.168.1.1 eq 22
access-list 101 permit ip any any
line vty 0 4
 access-class 101 in
5. Hướng áp dụng ACL (Inbound vs Outbound)
Hướng	Thời điểm kiểm tra	Tiết kiệm CPU?	Khi nào dùng
Inbound	Khi gói tin vào interface	Có (chặn sớm)	Muốn chặn ngay từ đầu, tránh xử lý không cần thiết
Outbound	Sau khi routing, trước khi gói tin ra khỏi interface	Không (tốn CPU hơn)	Cần lọc dựa trên địa chỉ đích (vì chưa biết đích khi chưa routing)
💡 Thông thường: Dùng inbound cho Standard ACL, dùng outbound cho Extended ACL nếu cần lọc theo địa chỉ đích.

6. Các loại ACL đặc biệt khác
Loại ACL	Số hiệu	Dùng trong
Named ACL	Không có số (dùng tên)	Thay thế numbered ACL, dễ quản lý
Reflexive ACL	(đặc biệt)	Cho phép traffic "trả lời" nhưng chặn traffic "chủ động" từ ngoài vào
Time-based ACL	(đặc biệt)	ACL chỉ có hiệu lực trong khung giờ nhất định
IPv6 ACL	Không dùng số	Tương tự Extended ACL nhưng dùng cho IPv6
Ví dụ Named ACL:
text
ip access-list extended BLOCK_SALES
 deny tcp 192.168.10.0 0.0.0.255 any eq 22
 permit ip any any
interface GigabitEthernet0/0
 ip access-group BLOCK_SALES in

7. Các bước cấu hình ACL trên Cisco (tổng quát)
Bước	Hành động	Lệnh ví dụ
1	Tạo ACL	access-list 100 permit tcp 192.168.1.0 0.0.0.255 any eq 80
2	(Tùy chọn) Chèn rule vào giữa	ip access-list extended 100 → 15 permit ...
3	Áp dụng ACL vào interface	interface GigabitEthernet0/0
4	Xác định hướng	ip access-group 100 out
5	Kiểm tra	show access-list, show ip interface GigabitEthernet0/0
8. Lỗi thường gặp với ACL
Lỗi	Nguyên nhân	Khắc phục
Mất kết nối hoàn toàn	Quên permit any ở cuối (chỉ có deny) → implicit deny chặn hết	Thêm permit ip any any (nếu muốn)
ACL không có tác dụng	Quên áp dụng ip access-group vào interface	Kiểm tra bằng show run interface Gi0/0
Sai wildcard mask	Dùng subnet mask (255.255.255.0) thay vì wildcard (0.0.0.255)	Nhớ: wildcard = 255.255.255.255 - subnet mask
Thứ tự rule sai	Rule cụ thể để sau rule tổng quát	Đặt rule cụ thể (ví dụ deny host) lên trên rule tổng quát (permit any)


9. ACL trên switch (VACL, RACL) – nâng cao
Loại ACL trên switch	Vị trí áp dụng	Tác dụng
RACL (Router ACL)	Trên SVI (VLAN interface) hoặc cổng routed	Lọc giữa các VLAN (giống router)
VACL (VLAN ACL)	Trên toàn bộ VLAN (áp dụng cho cả switch)	Lọc cả traffic trong cùng VLAN (mà RACL không làm được)
🎯 Tóm gọn trong 1 câu:
ACL là danh sách quy tắc "cho qua hay chặn lại" đặt trên router/switch – duyệt lần lượt từ trên xuống, gặp rule khớp đầu tiên thì dừng; nếu không khớp rule nào, ngầm chặn hết (implicit deny).

