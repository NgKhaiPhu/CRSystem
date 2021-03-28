# CRSystem
ĐỒ ÁN CUỐI KỲ

Hệ thống đăng ký học phần

Hệ thống chia user làm 2 nhóm: sinh viên & nhân viên

Ví dụ cho tên user của nhân viên:
•	Ms. Le Thi Anh Thao
•	Ms. Nguyen Thi Minh Phuc
•	Ms. Hoang Thanh Tu

Các sinh viên có thể đến từ các lớp APCS, CLC, VP,…

User này trước hết phải đăng nhập vào hệ thống

Khi đã đăng nhập, user có thể xem profile cá nhân, đổi mật khẩu, hoặc đăng xuất

Đầu năm học (bắt đầu từ tháng 9), một nhân viên sẽ:

1.	Tạo một năm học mới (vd: 2020-2021).
2.	Tạo lớp học cho sv năm nhất (vd: 20APCS1, 20APCS2, 20CLC1, 20VP).
3.	Thêm các sinh viên năm nhất vào các lớp năm nhất.
4.	Để input, nhân viên sẽ import 1 file CSV chứa các thông tin của tất cả học viên trong một lớp học cụ thể nào đó (thay vì gõ tay từng người một). Các thông tin bao gồm: STT, MSSV, tên, họ, giới tính, ngày sinh, CCCD.
5.	Không cần thêm thông tin của sinh viên các năm học sau.
Đầu học kỳ, một nhân viên sẽ:
6.	Tạo học kỳ. Một năm học gồm ba loại học kỳ: HKI (thu), HKII (hè), HKIII (thu???????).  Chọn một loại học kỳ, năm học, ngày bắt đầu, kết thúc. Học kỳ được tạo mới sẽ trở thành học kỳ mặc định cho các chức năng bên dưới.
7.	Tạo khung thời gian ĐKHP: ngày bắt đầu, kết thúc.
8.	Thêm học phần cho học kỳ: mã học phần, tên học phần, tên giảng viên, số tín chỉ, sĩ số tối đa (mặc định 50), ngày học trong tuần và ca học (2/3/4/5/6/7, ca 1-07:30, ca 2-09:30, ca 3-13:30, ca 4-15:30). Một học phần được dạy trong 2 ca.
9.	Xem danh sách học phần.
10.	Cập nhật thông tin học phần.
11.	Xóa học phần.

Khi còn thời hạn ĐKHP, sinh viên có thể:

12.	Đăng nhập.
13.	ĐKHP. Nếu học phần mới trùng giờ một học phần đã đăng ký, sinh viên không thể đăng ký học phần đó. Một sinh viên được đăng ký tối đa 5 học phần cho một học kỳ.
14.	Xem danh sách các học phần đã đăng ký.
15.	Xóa một học phần khỏi danh sách.

Khi hết thời hạn ĐKHP, sinh viên có thể:

16.	Xem danh sách học phần.
Tại một thời điểm bất kỳ, một nhân viên có thể:
17.	Xem danh sách các lớp học.
18.	Xem danh sách sinh viên trong một lớp.
19.	Xem danh sách học phần.
20.	Xem danh sách sinh viên trong một học phần.

Tại thời điểm kết thúc học phần, một nhân viên có thể:

21.	Export danh sách sinh viên của một học phần vào một file CSV.
22.	Import bảng điểm của học phần. Một học phần gồm các cột sau: STT, MSSV, họ tên đầy đủ của sinh viên, tổng điểm, điểm cuối kỳ, điểm giữa kỳ, các điểm khác. (Nhân viên sẽ export danh sách ở 21, gửi file CSV cho giảng viên. Giảng viên nhập kết quả, gửi lại cho nhân viên. Nhân viên import bảng điểm vào hệ thống).
23.	Xem bảng điểm một học phần.
24.	Cập nhật kết quả của một sinh viên.
25.	Xem bảng điểm của một lớp, bao gồm điểm cuối kỳ của toàn bộ các khóa học trong học kỳ, GPA của học kỳ, overall GPA.

Khi bảng điểm được xuất ra, sinh viên có thể:

26.	Xem bảng điểm.

Các yêu cầu cho bài làm:

1.	Text file, Binary file đều ok. Không sử dụng database (???).
2.	C++.
3.	Chỉ sử dụng mảng động & linked list.
4.	Cho phép sử dụng char[], char* và string.
5.	Dùng GitHub để quản lý source code. Mỗi thành viên phải có ít nhất 20 commit, thực hiện trong ít nhất 15 ngày.
