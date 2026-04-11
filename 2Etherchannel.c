Etherchannel.
EtherChannel is a port link aggregation technology or port-channel architecture
used primarily on Cisco switches. It allows grouping of several physical Ethernet
links to create one logical Ethernet link for the purpose of providing fault-tolerance
and high-speed links between switches, routers and servers.
We need to create port channel with the help of negotiating protocols of
EtherChannel.
There are two protocols used for negotiating EtherChannel and Link Aggregation.

1- Port Aggregation Protocol (PAgP) - Cisco Proprietary protocol
Port Aggregation Protocol (PAgP) has two Channel modes and they are
"Desirable" and "Auto".
Auto Mode: Auto mode in Port Aggregation Protocol (PAgP) does not initiate the negotiation,
but responds to Port Aggregation Protocol (PAgP) packets initiated by other end
Desirable mode: Desirable mode in Port Aggregation Protocol (PAgP) initiates the negotiation
and tries to form EtherChannel with other end.

2- Link Aggregation Control Protocol (LACP) – IEEE- Open Standard
Link Aggregation Control Protocol (LACP) has two Channel modes and they
are "Active" and "Passive"
Active Mode: Active Mode in Link Aggregation Control Protocol (LACP) initiates the negotiation
and tries to form EtherChannel with other end.
Passive Mode: Passive Mode in Link Aggregation Control Protocol (LACP) does not initiate the
negotiation, but responds to Link Aggregation Control Protocol (LACP) packets initiated by other
end.

EtherChannel là gì?
EtherChannel là kỹ thuật **gộp nhiều cổng vật lý (từ 2 đến 8 cổng) song song giữa hai switch (hoặc giữa switch với server/router) thành một liên kết logic duy nhất (single logical link).

Mục đích: Tăng băng thông và dự phòng mà không tạo vòng lặp (loop) – vốn là vấn đề chết người trong mạng switch.

1. Vấn đề mà EtherChannel giải quyết
❌ Cách dùng nhiều dây song song thông thường (không EtherChannel):
Giữa Switch A và Switch B, bạn đi 2 dây cáp song song:

Vấn đề 1: Spanning Tree Protocol (STP) sẽ chặn (block) 1 trong 2 dây để tránh loop. Kết quả: bạn có dự phòng nhưng băng thông vẫn chỉ bằng 1 dây (dây còn lại chết chìm).

Vấn đề 2: Nếu dây chính đứt, STP mất 30-50s để kích hoạt dây dự phòng → gián đoạn mạng lâu.

✅ Dùng EtherChannel:
STP coi 2 dây vật lý đó như 1 dây logic duy nhất.

Cả 2 dây đều hoạt động song song → băng thông gộp lại (2 x 1 Gbps = 2 Gbps).

Khi 1 dây đứt, lưu lượng tự động chuyển sang dây còn lại ngay lập tức (không cần STP tính toán lại).

2. Các giao thức EtherChannel (quan trọng)
Có 2 giao thức để tự động thương lượng EtherChannel:

Giao thức	Hãng	Đặc điểm
PAgP (Port Aggregation Protocol)	Cisco độc quyền	Cũ hơn, chỉ chạy giữa 2 thiết bị Cisco. Có 2 chế độ: desirable (chủ động) và auto (thụ động).
LACP (Link Aggregation Control Protocol)	IEEE 802.3ad – chuẩn mở	Dùng được cho mọi hãng (Cisco, Huawei, Juniper, Server...). Có 2 chế độ: active (chủ động) và passive (thụ động).
💡 Khuyến nghị: Dùng LACP vì là chuẩn mở, tương thích đa thiết bị.

Chế độ hoạt động của LACP:
Chế độ	Hành vi
Active	Chủ động gửi gói tin LACP để thương lượng EtherChannel.
Passive	Thụ động, chỉ phản hồi khi nhận được LACP từ đầu bên kia.
⚠️ Lưu ý: Nếu cả 2 đầu đều passive → sẽ không ai gửi gói tin → EtherChannel không được thiết lập.

3. Cách EtherChannel phân phối tải (Load Balancing)
EtherChannel không đơn giản là "gói tin số 1 đi dây A, gói tin số 2 đi dây B" kiểu round-robin (vì sẽ gây rối thứ tự gói tin). Thay vào đó, nó dùng hash (băm) để quyết định dây.

Các thuật toán load balancing phổ biến (cấu hình được):
Thuật toán (dựa trên)	Ý nghĩa
src-mac	Theo địa chỉ MAC nguồn
dst-mac	Theo địa chỉ MAC đích
src-ip	Theo địa chỉ IP nguồn (thường dùng nhất)
dst-ip	Theo địa chỉ IP đích
src-dst-ip	Theo cặp (IP nguồn + IP đích) – đảm bảo luồng dữ liệu giữa 2 máy luôn đi cùng 1 dây (không bị xáo trộn thứ tự gói)
Ví dụ: Chọn src-dst-ip → luồng A (IP 10.0.0.1 ↔ 10.0.0.2) luôn đi dây 1; luồng B (10.0.0.1 ↔ 10.0.0.3) luôn đi dây 2.

4. Điều kiện để EtherChannel hoạt động
Tất cả các cổng vật lý trong cùng một EtherChannel phải giống hệt nhau:

Điều kiện	Yêu cầu
Tốc độ	Giống nhau (ví dụ tất cả đều 1 Gbps)
Duplex	Giống nhau (ví dụ full-duplex)
VLAN	Cùng cấu hình VLAN (cùng trunk mode hoặc cùng access VLAN)
STP	Cùng tham số spanning-tree (cost, priority...)
Loại cổng	Cùng là access hoặc cùng là trunk
5. Cấu hình ví dụ (Cisco)
Trên Switch A (cổng Gig0/1 và Gig0/2 nối sang Switch B):
text
interface range GigabitEthernet0/1-2
 channel-group 1 mode active   (dùng LACP active)
 switchport mode trunk
 switchport trunk allowed vlan 10,20,30
Trên Switch B:
text
interface range GigabitEthernet0/1-2
 channel-group 1 mode passive   (dùng LACP passive)
 switchport mode trunk
 switchport trunk allowed vlan 10,20,30
Kiểm tra:
text
show etherchannel summary
show etherchannel port-channel
Kết quả: Port-channel 1 (Po1) xuất hiện như một cổng logic duy nhất, gồm 2 cổng vật lý.

6. So sánh nhanh các khái niệm dễ nhầm
Khái niệm	Mục đích	Chống loop?
STP	Chống loop bằng cách chặn cổng thừa	Có (bằng cách tắt cổng)
EtherChannel	Gộp nhiều cổng vẫn dùng được tất cả (không bị chặn)	Không gây loop vì STP coi như 1 cổng
Load balancing	Chia tải giữa các dây trong EtherChannel	Không liên quan
🎯 Tóm gọn trong 1 câu:
EtherChannel là kỹ thuật "biến nhiều dây song song thành một dây ảo khỏe hơn" – vừa tăng băng thông vừa dự phòng, mà không bị STP chặn cổng.

EtherChannel "on" mode là gì ?
EtherChannel "on" mode là chế độ cấu hình thủ công hoàn toàn, không sử dụng bất kỳ giao thức thương lượng nào (không PAgP, không LACP).

Nói một cách hình ảnh: "On" mode giống như cưỡng ép hai switch bắt tay mà không cần nói chuyện – "Mày phải là EtherChannel, không cần hỏi han gì cả".

1. Đặc điểm chính của mode "on"
Đặc điểm	Mô tả
Không gửi gói tin thương lượng	Không gửi PAgP (Cisco) cũng không gửi LACP (chuẩn mở)
Cấu hình thủ công 100%	Cả 2 đầu switch phải được cấu hình mode "on"
Không phát hiện cấu hình sai	Nếu một đầu là "on", đầu kia là "desirable/active" → sẽ không hoạt động (vì không có giao thức chung)
Đơn giản, không lỗi thương lượng	Không bị lỗi do mismatch version PAgP/LACP

2. So sánh các mode EtherChannel
Mode	Giao thức	Hành vi	Tương thích
On	Không (thủ công)	Ép thành EtherChannel, không thương lượng	Chỉ với mode "on" ở đầu kia
PAgP desirable	PAgP (Cisco)	Chủ động gửi PAgP, muốn thành EtherChannel	Với desirable hoặc auto
PAgP auto	PAgP (Cisco)	Thụ động, đợi PAgP từ đầu kia	Với desirable
LACP active	LACP (IEEE)	Chủ động gửi LACP, muốn thành EtherChannel	Với active hoặc passive
LACP passive	LACP (IEEE)	Thụ động, đợi LACP từ đầu kia	Với active
⚠️ Quy tắc bất di bất dịch: Mode "on" chỉ nói chuyện được với mode "on". Nếu một đầu "on", đầu kia là bất kỳ mode nào khác (desirable/auto/active/passive) → EtherChannel không hoạt động.

3. Ví dụ cấu hình (Cisco)
Trên Switch A:
text
interface range GigabitEthernet0/1-2
 channel-group 1 mode on
 switchport mode trunk
Trên Switch B:
text
interface range GigabitEthernet0/1-2
 channel-group 1 mode on
 switchport mode trunk
→ Cả 2 đầu đều "on" → EtherChannel hoạt động.

❌ Sai (không hoạt động):
Switch A: mode on

Switch B: mode active (LACP) → không tạo được EtherChannel.

4. Ưu và nhược điểm của mode "on"
✅ Ưu điểm	❌ Nhược điểm
Cấu hình đơn giản, dễ hiểu	Không phát hiện cấu hình sai (nếu một đầu không phải "on", bạn sẽ không biết vì không có gói tin lỗi)
Không bị lỗi do version PAgP/LACP	Không hỗ trợ phát hiện lỗi cáp (nếu một dây trong EtherChannel bị đứt, mode "on" không báo động rõ như LACP)
Không tiêu tốn băng thông cho gói tin thương lượng	Cứng nhắc – khó khăn khi muốn thay đổi hoặc mở rộng
5. Khi nào nên dùng mode "on"?
Lab / mô phỏng: Nhanh, không cần cầu kỳ.

Kết nối với thiết bị không hỗ trợ PAgP/LACP: Một số switch cũ, server không có giao thức thương lượng.

Tình huống cần tránh lỗi thương lượng: Nếu bạn đã gặp vấn đề với LACP/PAgP (ví dụ mismatch timer, version...), mode "on" là giải pháp đơn giản.

🧠 Khuyến nghị thực tế: Trong mạng sản xuất (production), hầu như không dùng mode "on". Người ta dùng LACP active/passive vì nó có cơ chế phát hiện lỗi, báo cáo trạng thái, và linh hoạt hơn.

6. Lỗi thường gặp với mode "on"
Lỗi	Nguyên nhân	Khắc phục
EtherChannel không lên	Một đầu "on", đầu kia không phải "on"	Cấu hình cả 2 đầu đều "on"
Các cổng trong group không đồng bộ	Cổng trong group có tốc độ/duplex/VLAN khác nhau	Kiểm tra tất cả cổng trong group phải giống hệt cấu hình
STP vẫn chặn cổng	Quên cấu hình EtherChannel trước khi gộp	Cấu hình channel-group trên interface range trước khi cấu hình trunk/access
🎯 Tóm gọn trong 1 câu:
EtherChannel "on" mode là chế độ thủ công, không dùng giao thức thương lượng – chỉ hoạt động khi cả 2 đầu đều "on", đơn giản nhưng thiếu thông minh và không phát hiện lỗi. Trong thực tế, ưu tiên dùng LACP thay vì "on".

