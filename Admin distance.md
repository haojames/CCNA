1. Administrative Distance:
Administrative distance is the feature that routers use in order to select the best path when there
are two or more different routes to the same destination from two different routing protocols.
Administrative distance defines the reliability of a routing protocol.

2. Floating Static Route
Floating Static Route (Đường tĩnh nổi) là một route tĩnh được cấu hình với Administrative Distance (AD) lớn hơn AD mặc định của giao thức định tuyến động đang chạy trên router.

Mục đích duy nhất:
Làm đường dự phòng. Nó chỉ xuất hiện trong bảng định tuyến khi đường chính (học qua giao thức động) bị hỏng.

Cơ chế hoạt động (2 bước)
Bình thường: Giao thức động (VD: OSPF, AD=110) có đường đến đích. Floating route (VD: AD=150) nằm im trong cấu hình, không được đưa vào bảng định tuyến.

Khi đường chính hỏng: Router mất route từ giao thức động → nó "thấy" Floating route có AD=150 là đường khả thi duy nhất → đưa nó vào bảng định tuyến để cứu mạng.

💡 Nguyên lý: Router luôn chọn đường có AD nhỏ nhất. Floating route có AD càng lớn thì càng "chịu thua" đường động.

Cấu hình trên router:

text
Router(config)# ip route 192.168.10.0 255.255.255.0 10.1.1.2
Router(config)# ip route 192.168.10.0 255.255.255.0 10.2.2.2 150
(Giải thích: Đường thứ 2 có số 150 ở cuối là AD)

Kết quả:
Bình thường: Router dùng đường động học được (AD=110) để đi đến mạng 192.168.10.0.
Khi đường động chết: Floating route (AD=150) được kích hoạt, chuyển lưu lượng qua cổng 10.2.2.2 (đường cáp quang dự phòng).
Tóm gọn trong 1 câu:
Floating Static Route là "người thợ lặn cứu hộ" – chỉ nổi lên bảng định tuyến khi đường chính (giao thức động) bị chìm.