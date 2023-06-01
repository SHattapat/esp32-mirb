
while true do
  puts "TEST"
  sleep 1
end

include ESP32::GPIO
led = GPIO_NUM_18
pinMode(led, OUTPUT)

loop {
  digitalWrite(led, HIGH)
  puts "High"
  sleep 1
  digitalWrite(led, LOW)
  puts "Low"
  sleep 1
}
pin = ESP32::GPIO::Pin.new(18,OUTPUT)

pin = ESP32::GPIO::Pin.new(18,:output)


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

pin.analog_read( ADC1_CHANNEL_6)
