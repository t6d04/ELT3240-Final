# HỆ THỐNG PHÁT HIỆN VÀ CẢNH BÁO RÒ RỊ KHÍ GAS

## 🔢 Thông tin chung

Dự án nhằm thiết kế và triển khai hệ thống nhúng giám sát khí gas (MQ-6) nhằm cảnh báo rò rỉ nhà bếp/đốt ngãn. Hệ thống hoạt động trên STM32 Nucleo-F411RE, giao tiếp với ESP32 để gửi thông báo từ xa.

---

## 🔧 Chức năng

### Phân STM32 (thiết bị trung tâm):

* Đọc giá trị ADC từ cảm biến MQ-6
* Tính giá trị ppm
* Cảnh báo qua LED RGB, Buzzer, Relay
* Hiển thị LCD nồng độ khí và trạng thái hệ thống
* Giao tiếp UART với ESP32

### Phân ESP32 (kết nối Internet):

* Nhận dữ liệu UART từ STM32
* Gửi Email khi phát hiện rò rỉ khí nguy hiểm (state == 3)
* Logic chống spam: gửi ngay lần đầu, lặp lại sau 5 phút nếu nguy hiểm tiếp diễn

---

## 📂 Cấu trúc code STM32

* `adc.[c/h]`        → Đọc ADC từ MQ-6
* `gas_sensor.[c/h]` → Tính toán ppm từ ADC
* `lcd.[c/h]`         → I2C LCD 16x2 hiển thị
* `led.[c/h]`         → LED RGB theo mức gas
* `buzzer.[c/h]`      → Báo âm nguy hiểm
* `relay.[c/h]`       → Relay ngắt gas
* `button.[c/h]`      → Nút nhấn và EXTI
* `state_machine.[c/h]` → FSM 4 trạng thái: STOP, SAFE, LOW, HIGH, DANGER
* `uart.[c/h]`       → UART2 gửi JSON sang ESP32
* `timer.[c/h]`       → millis() và delay non-blocking

---

## 🛠️ Kết nối UART với ESP32

* Baudrate: 9600
* Format: `{"ppm":450,"state":3}\n`
* Chân STM32: TX = PB12 → RX ESP32 (GPIO16)

---

## 🔓 Cảnh báo Email qua ESP32

* Sử dụng `ESP_Mail_Client`
* Gửi SMTP Gmail
* Chỉ gửi khi `state == 3`
* Mỗi 5 phút lặp lại nếu chưa hết nguy hiểm

---

## 🔌 Nguồn tham khảo & tool

* STM32CubeIDE (STM32)
* Arduino IDE (ESP32)
* ArduinoJson
* ESP\_Mail\_Client

---

## 🚪 Bật/tắt hệ thống

* SW1 (ON/OFF): PC13, EXTI13
* SW2 (RESET): PB3, EXTI3
* BUZZ OFF: PB5, EXTI5
* LED POWER bật khi hệ thống chạy
