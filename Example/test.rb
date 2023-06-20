
while true do
  puts "TEST"
  sleep 1
end

include ESP32::GPIO

include ESP32::STANDARD
p = GPIO.new(18,OUT)
p.high_at?


include ESP32::STANDARD
led = GPIO_NUM_16
pinMode(led, INPUT)
digitalWrite(led, HIGH)

digitalRead(led)

loop {
  digitalWrite(led, HIGH)
  puts "High"
  sleep 1
  digitalWrite(led, LOW)
  puts "Low"
  sleep 1
}
pin = ESP32::GPIO::Pin.new(18,OUTPUT)
pin = ESP32::GPIO::Pin.new(6,INPUT)
pin1 = ESP32::GPIO::Pin.new(18,:output)


include ESP32::GPIO
pin = ADC1_CHANNEL_6

w = (w*3.3)/ 4096

T = (V - 0.5) /0.0195
loop {
  w = analogRead(pin)
  V = w * (3.3 / 4095)
  T = (V - 0.5) /0.0195
  puts "Temp : #{T}"
  sleep 1
}


pin = ESP32::GPIO::Pin.new(ADC1_CHANNEL_6,INPUT)
pin.analog_read( ADC1_CHANNEL_6)


loop {
  w = pin.read_at 6
  V = w * (3.3 / 4095)
  T = (V - 0.5) /0.0195
  puts "Temp : #{T}"
  sleep 1
}