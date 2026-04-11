## Spanning Tree Protocol
#### 1. Vấn đề mà STP giải quyết
Trong mạng Switch có dự phòng (redundancy), nếu không có STP sẽ xảy ra:
Broadcast storm	        Broadcast bị lặp vô tận giữa các switch → nghẽn mạng, switch treo
MAC address flapping	  MAC của máy tính liên tục nhảy giữa các cổng → bảng MAC bị rối
Multiple frame copies   Frame được copy nhiều lần → thiết bị đích nhận trùng lặp dữ liệu
#### 2. Nguyên lý hoạt động của STP (3 bước)
✅ Bước 1: Bầu chọn Root Bridge (Cây gốc)
Root bridge là switch "trung tâm" của toàn bộ mạng STP.
Tiêu chí: Bridge ID nhỏ nhất thắng.
Bridge ID = Priority (mặc định 32768) + MAC address.
Priority thấp hơn → thắng. Nếu bằng priority → MAC thấp hơn thắng.
💡 Để ép một switch làm Root, ta giảm priority (ví dụ spanning-tree vlan 1 priority 4096).
✅ Bước 2: Chọn Root Port (RP) trên mỗi non-root switch
Root port là cổng gần Root Bridge nhất (chi phí đường đi – path cost – nhỏ nhất).
Mỗi non-root switch có duy nhất 1 root port.
✅ Bước 3: Chọn Designated Port (DP) trên mỗi segment (đoạn dây)
Trên mỗi link (segment) giữa 2 switch, cổng nào có path cost đến Root nhỏ hơn sẽ là Designated Port.
DP ở trạng thái Forwarding (gửi dữ liệu bình thường).
✅ Kết quả: Các cổng còn lại (không phải RP, không phải DP) sẽ bị chặn (Blocking / Alternate port) → không gửi dữ liệu, chỉ nghe BPDU.
⏱️ Thời gian hội tụ STP: Blocking → Forwarding mất khoảng 30-50 giây (20s Max Age + 15s Listening + 15s Learning). Đây là lý do ra đời các phiên bản nhanh hơn (RSTP, RPVST+).
4. BPDU (Bridge Protocol Data Unit) – Ngôn ngữ của STP
Gửi mỗi 2 giây từ Root Bridge xuống các switch.
Chứa thông tin: Root Bridge ID, Path Cost, Sender Bridge ID, Port ID...
Nếu switch không nhận BPDU từ neighbor trong 20s → cho rằng link hỏng → chạy lại thuật toán STP.
#### Phần 2: PVST+ (Per-VLAN Spanning Tree Plus) – Cisco độc quyền
1. PVST+ là gì?
PVST+ chạy một STP riêng biệt cho mỗi VLAN. Nghĩa là mỗi VLAN có thể có Root Bridge, topology tree khác nhau.
2. Vấn đề của STP gốc (CST – Common Spanning Tree)
STP gốc (IEEE 802.1D) chỉ chạy một cây STP duy nhất cho tất cả VLAN.
Hệ quả: Nhiều VLAN bị chặn cùng một cổng → không thể tận dụng băng thông dự phòng.
3. Lợi ích của PVST+
Tiêu chí	CST (STP gốc)	PVST+
Số cây STP	1 cho mọi VLAN	1 cây riêng cho mỗi VLAN
Tận dụng băng thông	Kém (chỉ 1 đường active)	Tốt (load balancing giữa các VLAN)
Tương thích	Chuẩn mở	Cisco độc quyền
Tài nguyên	Ít (ít BPDU)	Nhiều (BPDU cho từng VLAN)
4. Ví dụ load balancing với PVST+
Switch A ---- Trunk ---- Switch B
VLAN 10: cổng trên Switch A là Root Port (active)
VLAN 20: cổng dưới Switch A là Root Port (active)
→ Cả 2 link đều được dùng (VLAN 10 đi link trên, VLAN 20 đi link dưới).
🔹 Phần 3: RPVST+ (Rapid Per-VLAN Spanning Tree Plus)
1. RPVST+ là gì?
RPVST+ = PVST+ + RSTP (Rapid Spanning Tree Protocol – IEEE 802.1w).
Nó kết hợp:
Mỗi VLAN có cây STP riêng (như PVST+).

Hội tụ nhanh (vài giây, thậm chí dưới 1 giây) thay vì 30-50 giây như STP cũ.

2. RSTP nhanh hơn nhờ cơ chế nào?
STP cũ (802.1D)	RSTP (802.1w)
Chỉ có 2 loại port: Root, Designated	Thêm Alternate port (backup cho Root) và Backup port (backup cho Designated)
Chờ 20s Max Age mới phản ứng	Proposal/Agreement – handshake nhanh giữa 2 switch
Chuyển trạng thái qua Listening → Learning → Forwarding (mất 30-50s)	Chuyển thẳng từ Discarding (thay thế Blocking/Listening) sang Forwarding nếu được bắt tay
3. Các loại port trong RSTP/RPVST+
Loại port	Vai trò
Root Port	Giống STP – cổng gần Root nhất
Designated Port	Giống STP – cổng chuyển tiếp trên mỗi segment
Alternate Port	Dự phòng cho Root Port – nếu Root chết, Alternate thành Root ngay
Backup Port	Dự phòng cho Designated Port (trên cùng switch, cùng segment – hiếm gặp)
Edge Port	Cổng kết nối với máy tính (không có switch khác) – chuyển Forwarding ngay lập tức, không qua RSTP handshake
4. Thời gian hội tụ so sánh
Sự cố	STP (802.1D)	RSTP / RPVST+
Link trực tiếp đứt	30-50 giây	Dưới 1 giây
Switch chết	30-50 giây	Vài giây (tùy topology)
Thêm link mới	30-50 giây	Dưới 1 giây (nếu proposal/agreement thành công)


🔹 Bảng so sánh tổng hợp STP, PVST+, RPVST+
Tiêu chí	STP (802.1D)	PVST+ (Cisco)	RPVST+ (Cisco)
Số cây STP	1 cho mọi VLAN	1 cây / VLAN	1 cây / VLAN
Tốc độ hội tụ	Chậm (30-50s)	Chậm (30-50s)	Nhanh (dưới 1s – vài giây)
Cơ chế	802.1D	802.1D + per-VLAN	802.1w (RSTP) + per-VLAN
Load balancing	Không	Có (mỗi VLAN chọn đường khác)	Có
Tương thích	Chuẩn mở	Cisco (nhưng hiểu với CST)	Cisco (cần đồng bộ RSTP)
Tiêu tốn CPU	Thấp	Trung bình (nhiều BPDU)	Trung bình
Dùng phổ biến trong	Mạng cũ, switch đa hãng	Mạng Cisco cũ	Mạng Cisco hiện đại (khuyến nghị)
🎯 Tóm gọn trong 1 câu (từng cái)
STP: Chống loop bằng cách chặn cổng thừa, nhưng hội tụ chậm (30-50s) và dùng chung 1 cây cho mọi VLAN.

PVST+: Chạy 1 STP riêng cho mỗi VLAN → load balancing được, nhưng vẫn chậm như STP.
RPVST+: Giống PVST+ nhưng dùng cơ chế RSTP → hội tụ cực nhanh (dưới 1s) – là lựa chọn hàng đầu trên mạng Cisco hiện nay.

Spanning-tree States:
Ports on switch running STP go through the five different states. During STP convergence,
switches will move their root and designated ports through the various states: blocking, listening,
learning, and forwarding, whereas any other ports will remain in a blocked state.
1- Blocking state
2- Listening state
3- Learning state
4- Forwarding state
Convergence is a state where all ports on switch have transitioned to either forwarding or blocking
modes. During the STP converging, all user data frames would be dropped. No user data frame will be
forwarded until convergence is complete. Usually convergence takes place in 30 seconds (15 seconds of
listing state + 15 seconds of learning state).
For fast convergence & only for connect a PC not for switch we can use the below
mentioned command :
#interface fa[ interface number ]
#spanning-tree port fast.
If we connect Switch on that port for which we have given the command of
Port-fast chances are that this port is go in the loop.
