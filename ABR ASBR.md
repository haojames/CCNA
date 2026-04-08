ABR (Area Border Router) và ASBR (Autonomous System Boundary Router) là hai loại router đặc biệt trong OSPF, đảm nhận vai trò "cầu nối" giữa các vùng (area) hoặc giữa OSPF với bên ngoài.

Dưới đây là định nghĩa rõ ràng và so sánh chi tiết.

1. ABR (Area Border Router)
Định nghĩa:
ABR là router kết nối Area 0 (Backbone) với một non-backbone area (ví dụ Area 1, Area 2...).

Đặc điểm chính:
Có ít nhất một interface thuộc Area 0 và một interface thuộc area khác.

Tóm tắt route (summary) giữa các area (ví dụ: gộp nhiều route từ Area 1 thành một route tổng quát hơn khi gửi sang Area 0).

Ngăn chặn LSA flood giữa các area – chỉ gửi LSA Type 3 (Summary LSA) thay vì flood toàn bộ LSA Type 1,2.

Là "cánh cửa" duy nhất để lưu lượng đi từ area này sang area khác.

Ví dụ trực quan:
Một công ty có 3 tòa nhà:

Area 0 (Tòa nhà chính – Backbone)

Area 1 (Tòa nhà A)

Area 2 (Tòa nhà B)

Router R1 nối Area 0 và Area 1 → R1 là ABR.
Router R2 nối Area 0 và Area 2 → R2 là ABR.

Nếu không có ABR, các area không thể giao tiếp được với nhau.

2. ASBR (Autonomous System Boundary Router)
Định nghĩa:
ASBR là router đưa route từ bên ngoài OSPF vào (tái phân phối – redistribution). Nó là "cánh cửa" giữa OSPF và thế giới bên ngoài.

Đặc điểm chính:
Kết nối OSPF với:

Một giao thức định tuyến khác (RIP, EIGRP, BGP, IS-IS...)

Route tĩnh (static route)

Mạng trực tiếp không chạy OSPF

Phát ra LSA Type 5 (External LSA) để quảng bá route ngoại lai vào toàn bộ OSPF domain.

Trong area đặc biệt (NSSA), nó phát ra LSA Type 7 (thay cho Type 5).

Ví dụ trực quan:
Công ty có hai hệ thống mạng:

Mạng A chạy OSPF (nội bộ)

Mạng B chạy EIGRP (của đối tác cũ)

Router R3 vừa chạy OSPF (mặt A) vừa chạy EIGRP (mặt B) và làm lệnh redistribute eigrp 100 subnets → R3 là ASBR.

Nhờ ASBR, router trong mạng OSPF có thể "nhìn thấy" route từ mạng EIGRP.

Bảng so sánh ABR vs ASBR
Tiêu chí	ABR	ASBR
Vai trò chính	Cầu nối giữa các area trong OSPF	Cầu nối giữa OSPF với thế giới bên ngoài
Kết nối	Area 0 + Non-backbone area	OSPF + (RIP/EIGRP/BGP/Static/Connected)
Loại LSA phát ra	Type 3 (Summary LSA)	Type 5 (External LSA) hoặc Type 7 (trong NSSA)
Có bắt buộc phải nối với Area 0?	✅ BẮT BUỘC (phải có interface thuộc Area 0)	❌ Không bắt buộc (có thể nằm bất kỳ area nào)
Có tóm tắt route không?	Có (summary giữa các area)	Có (summary route ngoại lai)
Ví dụ lệnh liên quan	area 1 range 192.168.0.0 255.255.252.0	redistribute eigrp 100 subnets
Hình minh họa (cấu trúc topology)
text
                    (Internet)
                        |
                   [ASBR] R5 (kết nối OSPF + BGP)
                        |
                    Area 0 (Backbone)
                    /        \
                   /          \
              [ABR] R1      [ABR] R2
                /              \
           Area 1            Area 2
        (R3, R4)           (R6, R7)
R1 và R2 là ABR (nối Area 0 với Area 1 và Area 2)

R5 là ASBR (nối OSPF ra Internet qua BGP)