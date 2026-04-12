Port Security là tính năng bảo mật tầng 2 (Layer 2) trên switch, dùng để kiểm soát thiết bị nào được phép kết nối vào một cổng switch dựa trên địa chỉ MAC address.
Nói một cách hình ảnh: Port Security giống như "bảo vệ cổng ra vào" – chỉ cho phép những người (MAC) đã đăng ký mới được vào, người lạ sẽ bị chặn hoặc báo động.

1. Vấn đề mà Port Security giải quyết
❌ Mặc định (không có Port Security):
Bất kỳ ai cắm laptop vào cổng switch đều truy cập mạng ngay lập tức.
Kẻ tấn công có thể cắm vào cổng trống trong phòng họp, phòng server, hoặc thậm chí phòng kỹ thuật → truy cập trái phép.

✅ Có Port Security:
Mỗi cổng switch chỉ cho phép một hoặc một vài MAC cụ thể.
Nếu thiết bị lạ cắm vào → cổng tự động tắt (shutdown) hoặc chỉ báo động, không cho truy cập.

2. Các tham số cấu hình chính
Tham số	Ý nghĩa	Ví dụ
Maximum MAC addresses	Số lượng MAC tối đa được phép trên cổng	switchport port-security maximum 1 (chỉ 1 máy)
Violation mode	Hành vi khi vi phạm (thiết bị lạ cắm vào)	shutdown / restrict / protect
Sticky MAC	Tự động học và "dính" MAC đầu tiên cắm vào	switchport port-security mac-address sticky
Aging	Tự động xóa MAC sau thời gian không hoạt động	switchport port-security aging time 10


Violation Mode	Hành vi	Có log?	Có đếm violation count?	Phục hồi
Shutdown (mặc định)	Tắt hẳn cổng (error-disabled)	✅ Có	✅ Có	Phải shutdown rồi no shutdown bằng tay
Restrict	Chặn gói tin từ MAC lạ, nhưng cổng vẫn bật	✅ Có (gửi log, SNMP trap)	✅ Có (tăng counter)	Tự động (không cần can thiệp)
Protect	Chặn gói tin từ MAC lạ, không báo cáo gì cả	❌ Không	❌ Không	Tự động

4. Ví dụ cấu hình (Cisco)
Trường hợp 1: Cổng chỉ cho phép 1 máy (máy in, máy tính quan trọng)
text
interface GigabitEthernet0/1
 switchport mode access
 switchport port-security
 switchport port-security maximum 1
 switchport port-security violation shutdown
 switchport port-security mac-address sticky
sticky → tự học MAC đầu tiên cắm vào và "dính" nó vào cấu hình.

Trường hợp 2: Cổng phòng họp (nhiều người dùng luân phiên, tối đa 5 máy)
text
interface GigabitEthernet0/2
 switchport mode access
 switchport port-security
 switchport port-security maximum 5
 switchport port-security violation restrict
 switchport port-security aging time 120
 switchport port-security aging type inactivity
aging time 120 → xóa MAC sau 120 phút không hoạt động.

aging type inactivity → chỉ xóa khi không có traffic.

Trường hợp 3: Cổng trunk (không nên bật port security vì mỗi VLAN có thể có nhiều MAC)
5. Cách xử lý khi cổng bị shutdown (error-disabled)
Kiểm tra:

text
show interface status | include err-disabled
show port-security interface GigabitEthernet0/1
Phục hồi thủ công:

text
interface GigabitEthernet0/1
 shutdown
 no shutdown
Phục hồi tự động (cấu hình errdisable recovery):

text
errdisable recovery cause psecure-violation
errdisable recovery interval 300   (tự động mở lại sau 300 giây)

6. Kiểm tra và giám sát Port Security
Lệnh	Ý nghĩa
show port-security	Tổng quan port security trên toàn switch
show port-security interface GigabitEthernet0/1	Chi tiết một cổng
show port-security address	Danh sách các MAC được học/được cấu hình
show interfaces status err-disabled	Các cổng đang bị tắt do violation
  
7. Các tấn công mà Port Security ngăn chặn được
Tấn công	Mô tả	Port Security ngăn?
MAC flooding	Gửi hàng nghìn MAC giả để làm tràn bảng MAC switch	✅ Có (giới hạn số MAC trên cổng)
CAM table overflow	Dạng khác của MAC flooding	✅ Có (maximum MAC)
Rogue device cắm trực tiếp	Kẻ tấn công cắm laptop vào cổng switch	✅ Có (MAC lạ bị chặn)
MAC spoofing	Giả mạo MAC hợp lệ	❌ Không (vì MAC vẫn đúng)
ARP spoofing	Giả mạo ARP	❌ Không (đây là vấn đề tầng 3)

8. Hạn chế của Port Security
Hạn chế	Giải thích
Quản lý MAC thủ công	Với sticky MAC thì ổn, nhưng nếu thay máy tính → phải xóa MAC cũ.
Không ngăn được MAC spoofing	Kẻ tấn công có thể đổi MAC máy nó thành MAC đã được phép.
Tốn tài nguyên	Nếu bật trên hàng trăm cổng, switch phải lưu nhiều MAC.
Không dùng được trên trunk port	Trunk port thường có nhiều VLAN, mỗi VLAN có nhiều MAC → không kiểm soát nổi.
🎯 Tóm gọn trong 1 câu:
Port Security là "khóa cửa cho từng cổng switch" – chỉ cho phép những địa chỉ MAC đã đăng ký (tối đa N máy) truy cập; nếu khách lạ cắm vào, cổng có thể tự động tắt (shutdown) hoặc chặn (restrict/protect).
