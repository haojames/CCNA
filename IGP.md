1. RIP (Routing Information Protocol)
Định nghĩa:
RIP là giao thức distance-vector cổ điển, dùng hop count (số bước nhảy) làm metric. RIP có hai phiên bản: RIPv1 (classful, không hỗ trợ VLSM) và RIPv2 (classless, hỗ trợ VLSM và xác thực).

Đặc điểm chính:
Đặc điểm	Giá trị
Loại thuật toán	Distance Vector (Bellman-Ford)
Metric	Hop count (tối đa 15, hop 16 là unreachable)
Cập nhật	Gửi toàn bộ bảng định tuyến mỗi 30 giây
Vùng (Area)	Không hỗ trợ
Tốc độ hội tụ	Chậm (hàng phút)
Vấn đề	Counting to infinity, vòng lặp
Port	UDP 520
Sử dụng phổ biến	Mạng rất nhỏ, phòng lab, thiết bị cũ
Ưu điểm: Đơn giản, dễ cấu hình.
Nhược điểm: Hội tụ chậm, metric nghèo nàn, không mở rộng được.

2. EIGRP (Enhanced Interior Gateway Routing Protocol)
Định nghĩa:
EIGRP là giao thức advanced distance-vector độc quyền của Cisco (nay được công bố một phần là IETF Standard Track). Nó kết hợp ưu điểm của distance-vector (dễ cấu hình) và link-state (hội tụ nhanh) nhờ thuật toán DUAL (Diffusing Update Algorithm).

Đặc điểm chính:
Đặc điểm	Giá trị
Loại thuật toán	Advanced Distance Vector (DUAL)
Metric	Composite (Bandwidth + Delay + Load + Reliability + MTU) – mặc định dùng BW và Delay
Cập nhật	Chỉ gửi khi có thay đổi (triggered), không gửi định kỳ
Vùng (Area)	Không hỗ trợ (dùng phân cấp qua route summarization)
Tốc độ hội tụ	Rất nhanh (dưới giây, có backup route sẵn)
Vấn đề	Chủ yếu trên thiết bị Cisco (hỗ trợ đa vendor hạn chế)
Port	IP protocol 88
Sử dụng phổ biến	Mạng Cisco thuần, doanh nghiệp vừa và lớn
Ưu điểm: Hội tụ cực nhanh, tiết kiệm băng thông, metric linh hoạt.
Nhược điểm: Gần như chỉ dùng được cho Cisco, cấu hình phức tạp hơn RIP.

3. OSPF (Open Shortest Path First)
Định nghĩa:
OSPF là giao thức link-state tiêu chuẩn mở (IETF), dùng thuật toán Dijkstra (SPF) để tính đường đi ngắn nhất. OSPF hỗ trợ phân vùng (area) để giảm tải cho router và tăng khả năng mở rộng.

Đặc điểm chính:
Đặc điểm	Giá trị
Loại thuật toán	Link State (Dijkstra/SPF)
Metric	Cost (thường = 10^8 / bandwidth)
Cập nhật	Gửi LSA khi có thay đổi, flood trong toàn vùng
Vùng (Area)	Có (hỗ trợ phân cấp mạnh mẽ: Backbone area 0, stub, NSSA, v.v.)
Tốc độ hội tụ	Nhanh (giây, tùy kích thước mạng)
Vấn đề	Tốn CPU/RAM khi tính toán SPF trên mạng lớn
Port	IP protocol 89
Sử dụng phổ biến	Mạng doanh nghiệp lớn, ISP, đa vendor
Ưu điểm: Chuẩn mở, hỗ trợ đa thiết bị, phân cấp area, metric linh hoạt, hội tụ nhanh.
Nhược điểm: Cấu hình phức tạp hơn RIP/EIGRP, cần hiểu về LSA và area.

4. IS-IS (Intermediate System to Intermediate System)
Định nghĩa:
IS-IS là giao thức link-state được phát triển bởi ISO (không phải IETF), thường dùng trong mạng của các ISP lớn và nhà cung cấp dịch vụ. Nó chạy trực tiếp trên Layer 2 (không dùng IP) và có cấu trúc phân cấp với Level 1 (trong vùng) và Level 2 (giữa các vùng).

Đặc điểm chính:
Đặc điểm	Giá trị
Loại thuật toán	Link State (Dijkstra/SPF)
Metric	Default cost (mặc định 10, có thể tùy chỉnh), hỗ trợ wide metric (24 bit)
Cập nhật	Gửi LSP (Link State Packet) khi có thay đổi, flood
Vùng (Area)	Có (Level 1, Level 2, Level 1-2) – phân cấp rất linh hoạt
Tốc độ hội tụ	Rất nhanh, tương đương OSPF
Vấn đề	Ít phổ biến trong doanh nghiệp, khó tìm tài liệu hơn OSPF
Port	Chạy trực tiếp trên Layer 2 (Ethernet, HDLC, PPP) – không dùng IP
Sử dụng phổ biến	ISP, mạng viễn thông, mạng lớn (hỗ trợ IPv4 và IPv6 rất tốt)
Ưu điểm: Không phụ thuộc IP, mở rộng tốt hơn OSPF cho mạng cực lớn, hỗ trợ IPv6 native.
Nhược điểm: Khó cấu hình, ít dùng trong doanh nghiệp vừa và nhỏ.

LSA
LSA là một thông báo được gửi bởi bộ định tuyến (router) để mô tả trạng thái của các liên kết (interface, mạng lân cận, chi phí đường đi...) của nó đến tất cả các router khác trong cùng một vùng (area) của mạng.
Các router nhận được LSA sẽ lưu chúng vào cơ sở dữ liệu LSDB (Link State Database), sau đó chạy thuật toán SPF (Shortest Path First - thường gọi là thuật toán Dijkstra) để tính ra đường đi ngắn nhất đến mọi đích đến

Đặc điểm chính:
Đặc điểm	Mô tả
Phạm vi gửi	Flood (lan tỏa) đến toàn bộ router trong cùng một vùng OSPF
Tần suất	Gửi lại khi có sự thay đổi topology (không gửi định kỳ như RIP)
Nội dung	Router ID, trạng thái interface, neighbor, metric (cost), subnet mask...
Xác nhận	Có cơ chế bắt tay (LSAck) đảm bảo tin cậy

Các loại LSA trong OSPF (quan trọng nhất):
Loại	Tên	Mô tả ngắn
LSA Type 1	Router LSA	Mỗi router phát ra, mô tả các link trực tiếp của nó trong cùng area
LSA Type 2	Network LSA	Phát ra bởi DR (Designated Router) trên mạng multi-access (Ethernet), liệt kê tất cả router trong segment đó
LSA Type 3	Summary LSA	Phát ra bởi ABR (Area Border Router), tóm tắt route từ area này sang area khác
LSA Type 4	ASBR Summary LSA	Phát ra bởi ABR, chỉ đường đến ASBR (Autonomous System Boundary Router)
LSA Type 5	External LSA	Phát ra bởi ASBR, quảng bá route từ bên ngoài OSPF (ví dụ route tĩnh, BGP, RIP) vào OSPF