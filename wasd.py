"""
WASD Manual Control for RC Car
Simple keyboard control
"""
import serial
import time
import msvcrt
import sys

# Configuration
COM_PORT = 'COM3'
BAUD_RATE = 9600

print("=" * 50)
print("RC CAR - WASD CONTROL")
print("=" * 50)

try:
    # Connect to Arduino
    arduino = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)
    print(f"✓ Connected to Arduino on {COM_PORT}\n")
    
    # Clear buffer
    arduino.reset_input_buffer()
    
    print("Controls:")
    print("  W - Forward")
    print("  S - Backward")
    print("  A - Left")
    print("  D - Right")
    print("  X - Stop")
    print("  Q - Quit")
    print("=" * 50)
    print("\nPress keys to control the car...")
    print("(Hold key for continuous movement)\n")
    
    last_command = None
    
    while True:
        if msvcrt.kbhit():
            key = msvcrt.getch().decode('utf-8').upper()
            
            if key == 'Q':
                print("\n⏹️  Stopping car...")
                arduino.write(b'X')
                time.sleep(0.1)
                break
            
            elif key in ['W', 'S', 'A', 'D', 'X']:
                # Send command to Arduino
                arduino.write(key.encode())
                
                # Show what we're doing
                actions = {
                    'W': '⬆️  FORWARD',
                    'S': '⬇️  BACKWARD',
                    'A': '⬅️  LEFT',
                    'D': '➡️  RIGHT',
                    'X': '⏹️  STOP'
                }
                
                if key != last_command:
                    print(f"{actions[key]}")
                    last_command = key
        
        # Read feedback from Arduino
        if arduino.in_waiting > 0:
            response = arduino.readline().decode('utf-8', errors='ignore').strip()
            if response and "Commands:" not in response:
                print(f"  {response}")
        
        time.sleep(0.05)
    
    # Cleanup
    arduino.close()
    print("✓ Disconnected")

except serial.SerialException as e:
    print(f"\n✗ ERROR: {e}")
    print("\nTroubleshooting:")
    print("- Make sure Arduino is connected")
    print("- Close Arduino IDE Serial Monitor")
    print("- Check if COM3 is the correct port")
    print("- Upload motor_only.ino to Arduino first")

except KeyboardInterrupt:
    print("\n\n⏹️  Stopping...")
    if 'arduino' in locals():
        arduino.write(b'X')
        time.sleep(0.1)
        arduino.close()
    print("✓ Disconnected")

except Exception as e:
    print(f"\n✗ Unexpected error: {e}")