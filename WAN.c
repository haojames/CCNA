WAN (Wide Area Network) là mạng diện rộng, kết nối các thiết bị mạng với nhau trên một phạm vi địa lý lớn, có thể là giữa các tòa nhà trong một thành phố, giữa các thành phố khác nhau, hoặc thậm chí xuyên quốc gia và xuyên lục địa.
Nói một cách dễ hiểu: Nếu LAN (Mạng cục bộ) là mạng nội bộ trong một ngôi nhà, một trường học hay một tòa nhà văn phòng, thì WAN là mạng kết nối các LAN ở các địa điểm khác nhau lại với nhau.
Hãy tưởng tượng:
LAN là một căn phòng trong ngôi nhà của bạn.
WAN là hệ thống đường xá, cầu cống cho phép bạn đi từ ngôi nhà này (LAN Hà Nội) đến ngôi nhà khác (LAN TP. Hồ Chí Minh).

1. So sánh nhanh LAN vs WAN
Tiêu chí	LAN (Mạng cục bộ)	                                        WAN (Mạng diện rộng)
Phạm vi	  Nhỏ, trong một tòa nhà, khuôn viên (vài trăm mét)	        Rất lớn, giữa các thành phố, quốc gia (hàng nghìn km)
Sở hữu	  Doanh nghiệp hoặc cá nhân tự đầu tư (cáp, switch, router)	Thuê từ nhà cung cấp dịch vụ (ISP, VNPT, Viettel, FPT...)
Tốc độ	  Rất cao (1 Gbps, 10 Gbps, 100 Gbps)	                      Thấp hơn và phụ thuộc vào gói cước (thường từ 10 Mbps đến 10 Gbps)
Chi phí	  Một lần đầu tư ban đầu, chi phí vận hành thấp	            Chi phí thuê bao hàng tháng rất cao
Công nghệ	Ethernet, Wi-Fi	                                          Leased Line, MPLS, VPN qua Internet, Cáp quang thuê riêng
Độ trễ	  Rất thấp (< 1 mili giây)	                                Cao hơn (từ 10 đến 100+ mili giây)
2. Các kết nối WAN phổ biến trong thực tế
Khi bạn muốn kết nối văn phòng chi nhánh ở tỉnh A với trụ sở chính ở tỉnh B, bạn có thể thuê các dịch vụ sau từ nhà mạng:

1. Leased Line (Đường thuê riêng)
Công nghệ: T1 (1.544 Mbps) hoặc E1 (2.048 Mbps)
Đặc điểm: Một đường cáp vật lý dành riêng cho bạn, kết nối điểm-điểm.
Ưu điểm: Rất ổn định, bảo mật cao.
Nhược điểm: Cực kỳ đắt đỏ, băng thông thấp so với giá thành.
2. MPLS (Multiprotocol Label Switching)
Đặc điểm: Mạng riêng ảo do nhà cung cấp dịch vụ quản lý. Các chi nhánh kết nối với nhau qua mạng lõi của nhà mạng.
Ưu điểm: Linh hoạt (kết nối nhiều điểm với nhau), hỗ trợ QoS (ưu tiên lưu lượng thoại, video).
Nhược điểm: Chi phí vẫn cao hơn so với Internet.
3.  Site-to-Site VPN (Virtual Private Network)
Đặc điểm: Tận dụng đường Internet sẵn có. Dữ liệu được mã hóa (IPsec) và đóng gói để truyền qua Internet công cộng.
Ưu điểm: Rẻ nhất, tận dụng hạ tầng Internet sẵn có.
Nhược điểm: Chất lượng phụ thuộc hoàn toàn vào đường Internet (có thể bị chập chờn, độ trễ cao).
4. SD-WAN (Software-Defined WAN)
Đặc điểm: Một công nghệ thông minh hơn. Nó có thể kết hợp nhiều đường truyền cùng lúc (ví dụ: 1 đường MPLS + 2 đường Internet) và tự động chọn đường đi tốt nhất cho từng loại dữ liệu.
Ưu điểm: Tiết kiệm chi phí, tận dụng tối đa băng thông, hoạt động ổn định.
Nhược điểm: Đòi hỏi kiến thức và thiết bị chuyên dụng hơn.

Tình huống: Công ty ABC có:
Trụ sở chính tại Hà Nội (LAN HN)
Chi nhánh tại Đà Nẵng (LAN ĐN)
Chi nhánh tại TP. Hồ Chí Minh (LAN HCM)
Yêu cầu: Cả 3 LAN này phải "nói chuyện" được với nhau (chia sẻ file, dùng phần mềm quản lý tập trung, gọi điện nội bộ...).
Giải pháp WAN:
Công ty thuê dịch vụ MPLS của VNPT để kết nối 3 điểm HN - ĐN - HCM.
Hoặc, nếu muốn tiết kiệm, công ty lắp 3 đường Internet cáp quang (Viettel, FPT) và tạo VPN (IPsec) giữa các router với nhau.

5. Tóm gọn trong một câu
WAN là mạng kết nối các mạng LAN ở xa nhau về mặt địa lý, sử dụng dịch vụ thuê từ nhà cung cấp (như MPLS, Leased Line, hoặc VPN qua Internet) thay vì tự kéo cáp.
