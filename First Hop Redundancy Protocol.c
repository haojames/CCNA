First Hop Redundancy Protocol (FHRP) là một nhóm các giao thức được thiết kế để cung cấp dự phòng cho cổng gateway mặc định (default gateway) trong mạng LAN.
Hãy tưởng tượng thế này: Mạng LAN của bạn có một router duy nhất làm cửa ngõ ra ngoài (Internet hoặc mạng khác). Nếu router đó hỏng, cả mạng LAN sẽ mất kết nối hoàn toàn vì không ai biết đi ra đâu. FHRP là giải pháp cho vấn đề đó.

1. Vấn đề mà FHRP giải quyết

❌ Cấu hình mặc định (dễ hỏng):
Bạn đặt default gateway cho tất cả máy tính trong mạng là 192.168.1.1 (Router A).
Nếu Router A chết → không máy nào ra ngoài được → tê liệt mạng.

✅ Với FHRP:
Bạn đặt default gateway ảo (ví dụ 192.168.1.254) cho các máy tính.
Có 2 router vật lý (Router A và Router B) cùng chia sẻ địa chỉ ảo đó.
Một router là Active (chính), router kia là Standby (dự phòng).
Nếu Active chết → Standby tự động thay thế trong vài giây → máy tính không biết gì vẫn dùng gateway ảo.

2. Nguyên lý hoạt động chung của FHRP
Thành phần	Vai trò
Virtual IP address	Địa chỉ IP ảo (ví dụ 192.168.1.254) – đây là gateway máy tính dùng.
Virtual MAC address	Địa chỉ MAC ảo – được Active router quảng bá để hút lưu lượng.
Active router	Router đang giữ vai trò gateway thực tế (xử lý toàn bộ lưu lượng ra ngoài).
Standby router	Router dự phòng, sẵn sàng thay thế khi Active chết.
Hello messages	Các router gửi gói tin cho nhau qua link mạng để kiểm tra "còn sống không" (mỗi vài giây).


3. Các giao thức FHRP phổ biến
Có 3 giao thức chính, khác nhau về chuẩn và khả năng:

Giao thức	Hãng	Đặc điểm chính	Load balancing (cân bằng tải)?
HSRP (Hot Standby Router Protocol)	Cisco độc quyền	- 1 Active, 1 Standby (các router khác không dùng) - Virtual IP và Virtual MAC	❌ Không (chỉ 1 router hoạt động)
VRRP (Virtual Router Redundancy Protocol)	Mở (IETF) – đa hãng	- Gần giống HSRP nhưng chuẩn mở - 1 Master, nhiều Backup	❌ Không (chỉ 1 router hoạt động)
GLBP (Gateway Load Balancing Protocol)	Cisco độc quyền	- Nhiều router đều active - Mỗi máy tính nhận gateway ảo khác nhau (AVF)	✅ Có (tự động cân bằng tải)

💡 Khuyến nghị: Dùng HSRP nếu mạng toàn Cisco và chỉ cần dự phòng. Dùng VRRP nếu có nhiều hãng switch/router (Juniper, Huawei, Cisco...). Dùng GLBP nếu muốn tận dụng cả 2 router cùng lúc để cân bằng tải.

