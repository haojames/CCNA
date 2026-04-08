🔹 STEP 1: NỀN TẢNG ĐỊNH TUYẾN
Khái niệm Định tuyến là gì? (Router hoạt động ra sao)

Bảng định tuyến (Routing Table) – cách nó được xây dựng

Static Route (định tuyến tĩnh) – cấu hình, ưu/nhược điểm

Default Route (0.0.0.0/0) – dùng khi nào?

Floating Static Route – kỹ thuật dự phòng với AD lớn hơn

Administrative Distance (AD) – thang đo độ tin cậy giữa các giao thức

🔹 STEP 2: GIAO THỨC ĐỘNG (TỔNG QUAN)
Dynamic Routing – khái niệm, lợi ích so với static

Distance Vector vs Link State – nguyên lý hoạt động khác nhau

Các thuật toán: Bellman-Ford (RIP), Dijkstra (OSPF/IS-IS), DUAL (EIGRP)

Contiguous Network – điều kiện để tóm tắt route

Route Summarization – gộp nhiều route nhỏ thành route lớn

🔹 STEP 3: RIP (Dễ nhất, làm quen)
RIP v1 vs v2 (classful/classless, VLSM)

Hop count metric (tối đa 15)

Cập nhật định kỳ 30s – vấn đề hội tụ chậm

Cấu hình cơ bản router rip / network

🔹 STEP 4: EIGRP (Advanced Distance Vector)
Cách hoạt động của EIGRP (Hello, Update, Query, Reply, ACK)

3 bảng: Neighbor / Topology / Routing

Feasible Successor (FS) & Feasibility Condition (FC)

Composite metric (Bandwidth + Delay + ...)

Không có khái niệm area (nhưng có thể tóm tắt thủ công)

Hội tụ cực nhanh (dưới 1s nếu có FS)

Cấu hình cơ bản: router eigrp AS_number / network

🔹 STEP 5: OSPF (Link State – Quan trọng nhất)
5.1 – Cơ bản
Cách hoạt động của OSPF (Hello, DD, LSR, LSU, LSAck)

DR/BDR (bầu chọn trên mạng broadcast)

3 bảng: Neighbor / LSDB (Link State Database) / Routing

Metric = Cost (mặc định 10⁸ / bandwidth)

Các trạng thái adjacency (Down → Init → 2-Way → Exstart → Exchange → Loading → Full)

5.2 – Nâng cao (Phân vùng - Area)
Khái niệm Area (vùng) – tại sao cần chia area

Area 0 (Backbone) – bắt buộc phải có

ABR (Area Border Router) – nối Area 0 với area khác

ASBR (AS Boundary Router) – nối OSPF ra bên ngoài (route tĩnh, giao thức khác)

Các loại LSA cơ bản:

Type 1 (Router LSA)

Type 2 (Network LSA)

Type 3 (Summary LSA) – do ABR phát

Type 5 (External LSA) – do ASBR phát

Cấu hình OSPF multi-area

5.3 – Các loại area đặc biệt
Stub area

Totally Stubby area

NSSA (Not-So-Stubby Area) – cho phép ASBR nằm trong area đặc biệt (Type 7 LSA)

🔹 STEP 6: IS-IS (Link State nhưng khác OSPF)
Chạy trực tiếp trên Layer 2 (không dùng IP)

Level 1 (trong vùng) / Level 2 (giữa vùng) / Level 1-2

Dùng phổ biến trong mạng ISP, viễn thông

So sánh nhanh OSPF vs IS-IS (nếu cần)

🔹 STEP 7: SO SÁNH TỔNG HỢP
Bảng so sánh RIP – EIGRP – OSPF – IS-IS

Bảng so sánh OSPF vs EIGRP chi tiết

Khi nào dùng giao thức nào?

🔹 STEP 8: THỰC HÀNH & MÔ PHỎNG
Cấu hình trên Cisco Packet Tracer hoặc GNS3/EVE-NG

Kiểm tra lệnh: show ip route, show ip ospf neighbor, show ip eigrp topology, show ip protocols

Debug lỗi cơ bản: mismatched area, hello/dead interval, authentication

Lab tóm tắt route (summary) trên ABR (OSPF) hoặc bất kỳ router (EIGRP)

Lab tái phân phối (redistribution) giữa OSPF và EIGRP (có ASBR)

