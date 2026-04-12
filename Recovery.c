Quy trình khôi phục mật khẩu cho thiết bị Cisco
Dưới đây là hướng dẫn chi tiết cho từng dòng thiết bị Cisco phổ biến.

1. Router Cisco IOS và IOS XE
Đây là quy trình chuẩn cho các dòng router ISR (ISRG2, ISR4000, ASR1000, ISR1000) .

Các bước thực hiện:
Bước 1: Khởi động lại thiết bị

Ngắt nguồn và cấp nguồn lại router

Kết nối console vào thiết bị

Bước 2: Gửi Break sequence khi router đang boot

Trong Putty: Special Command > Break

Hoặc nhấn Ctrl + Break

Thời điểm gửi: Sau khi POST hoàn tất, trước khi IOS load xong

Bước 3: Vào ROMmon mode

text
rommon 1 >
Bước 4: Thay đổi configuration register

text
rommon 1 > confreg 0x2142
rommon 2 > reset
0x2142: Bỏ qua startup-config khi boot 

Bước 5: Router boot với cấu hình mặc định

Khôi phục lại cấu hình từ file startup-config

text
Router>enable
Router#copy startup-config running-config
Bước 6: Đặt lại mật khẩu mới

text
Router#configure terminal
Router(config)#enable secret PASSWORD_MOI
Router(config)#config-register 0x2102
Router(config)#exit
Router#write memory
Router#reload
0x2102: Khôi phục cấu hình register mặc định 

2. Switch Catalyst 9000 Series
Standalone Switch (Switch độc lập) 
Bước 1: Vào ROMMON mode

Khởi động lại switch

Khi thấy dòng Preparing to autoboot..., nhấn Ctrl + C

Hoặc nhấn giữ nút Mode trên mặt trước switch

Bước 2: Bypass startup configuration

text
switch: SWITCH_IGNORE_STARTUP_CFG=1
switch: boot
Bước 3: Khôi phục cấu hình

text
Switch>enable
Switch#copy startup-config running-config
Bước 4: Đặt mật khẩu mới và khôi phục cấu hình

text
Switch(config)#username admin privilege 15 secret PASSWORD_MOI
Switch(config)#no system ignore startupconfig switch all
Switch(config)#exit
Switch#copy running-config startup-config
StackWise Switch (Switch xếp chồng) 
Lưu ý quan trọng: Chỉ bật nguồn Master switch, tắt nguồn các switch thành viên khác.

Sau khi hoàn tất khôi phục, mới bật nguồn các switch còn lại.

3. Switch Catalyst 3560-X / 3750-X (Switch đời cũ)
Cách dùng nút Mode 
Bước 1: Chuẩn bị

Tắt nguồn switch

Kết nối console

Bước 2: Vào switch recovery mode

Bật nguồn

Trong vòng 10 giây, nhấn giữ nút Mode khi đèn System đang nhấp nháy xanh

Thả nút khi đèn chuyển xanh đậm (amber → solid green)

Bước 3: Rename file cấu hình

text
switch: flash_init
switch: dir flash:
switch: rename flash:config.text flash:config.text.old
switch: boot
Bước 4: Khôi phục và đặt lại mật khẩu

text
Switch>enable
Switch#rename flash:config.text.old flash:config.text
Switch#copy flash:config.text system:running-config
Switch#configure terminal
Switch(config)#enable secret PASSWORD_MOI
Switch(config)#exit
Switch#copy running-config startup-config
4. UCS Fabric Interconnect (6400, 6500, 6600, 9108)
Các bước thực hiện 
Bước 1: Kết nối console, khởi động lại thiết bị

Bước 2: Trong quá trình boot, nhấn Ctrl + C để vào loader prompt

Bước 3: Tìm và boot system image với recovery mode

text
loader > dir
loader > cmdline recoverymode=1
loader > boot ucs-6400-k9-system.<version>.bin
Bước 4: Reset mật khẩu admin

text
switch(boot)# config terminal
switch(boot)(config)# admin-password
<nhập mật khẩu mới>
switch(boot)(config)# exit
switch(boot)# load ucs-6400-k9-system.<version>.bin
5. Tắt/bật tính năng Password Recovery
Trên Catalyst Switch 
Tắt (tăng bảo mật):

text
Switch(config)# no service password-recovery
⚠️ Khi đã tắt, cách duy nhất để lấy lại quyền truy cập là xóa toàn bộ cấu hình (reset về factory default).

Bật lại:

text
Switch(config)# service password-recovery
Bảng tóm tắt nhanh
Thiết bị	Vào chế độ	Lệnh bypass config	Khôi phục config
Router IOS/XE	Break sequence	confreg 0x2142	copy start run
Cat 9000	Ctrl+C hoặc Mode button	SWITCH_IGNORE_STARTUP_CFG=1	copy start run
Cat 3560/3750-X	Mode button	rename config.text	copy flash:config.text system:running-config
UCS FI	Ctrl+C	cmdline recoverymode=1	admin-password
🎯 Tóm gọn trong 1 câu:
Quy trình khôi phục mật khẩu Cisco gồm 3 bước chính: (1) vào chế độ khôi phục (ROMmon/loader/switch recovery), (2) bypass hoặc rename file startup-config, (3) boot lại, copy config cũ vào running, đặt mật khẩu mới rồi save.

⚠️ Lưu ý quan trọng:
Bạn cần có quyền truy cập vật lý vào thiết bị và cáp console

Quy trình khác nhau tùy dòng thiết bị, hãy xác định đúng model trước khi thực hiện

Nếu no service password-recovery đã được bật, khôi phục mật khẩu sẽ xóa sạch cấu hình 
