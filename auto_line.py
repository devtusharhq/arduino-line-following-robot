"""
Automatic Line Follower - IR Sensor Based
Auto-detect COM port
"""
import serial
import serial.tools.list_ports
import time
import re
import sys

# Auto-detect Arduino COM port
def find_arduino_port():
    ports = serial.tools.list_ports.comports()
    print("Available COM ports:")
    for p in ports:
        print(f"  {p.device} - {p.description}")
    
    # Prefer COM3, then COM4, then first available
    for port in ['COM3', 'COM4', 'COM5', 'COM6']:
        for p in ports:
            if p.device == port:
                return port
    
    if ports:
        return ports[0].device
    return None

BAUD_RATE = 9600
COM_PORT = find_arduino_port()

print("=" * 50)
print("AUTOMATIC LINE FOLLOWER TEST")
print("=" * 50)

if not COM_PORT:
    print("✗ No Arduino found. Check connection.")
    sys.exit(1)

print(f"Using port: {COM_PORT}\n")

try:
    # Connect to Arduino
    arduino = serial.Serial(COM_PORT, BAUD_RATE, timeout=2)
    time.sleep(2)
    print(f"✓ Connected to Arduino on {COM_PORT}")

    # Clear buffer
    arduino.reset_input_buffer()
    time.sleep(1)
    
    # Read startup messages
    print("\nArduino startup messages:")
    for _ in range(10):
        if arduino.in_waiting > 0:
            line = arduino.readline().decode('utf-8', errors='ignore').strip()
            if line:
                print(f"  {line}")
        time.sleep(0.1)
    
    print("\n" + "=" * 50)
    print("MOTOR & SENSOR TEST RUNNING...")
    print("=" * 50)
    print("\nWatch your robot:")
    print("1. RIGHT motor should spin (3 sec)")
    print("2. LEFT motor should spin (3 sec)")
    print("3. Then sensors will be tested")
    print("\n")
    
    # Capture test output
    start_time = time.time()
    timeout = 30  # 30 second timeout
    output_lines = []
    
    while time.time() - start_time < timeout:
        if arduino.in_waiting > 0:
            try:
                line = arduino.readline().decode('utf-8', errors='ignore').strip()
                if line:
                    print(line)
                    output_lines.append(line)
            except:
                pass
        time.sleep(0.05)
    
    print("\n" + "=" * 50)
    print("TEST COMPLETE")
    print("=" * 50)
    
    # Check output
    right_motor_ok = any("RIGHT MOTOR" in line for line in output_lines)
    left_motor_ok = any("LEFT MOTOR" in line for line in output_lines)
    
    if right_motor_ok and left_motor_ok:
        print("\n✓ Motor test output detected")
    else:
        print("\n⚠ Check motor connections if not spinning")
    
    arduino.close()
    print("✓ Disconnected")
    
except serial.SerialException as e:
    print(f"\n✗ ERROR: {e}")
    print("\nTroubleshooting:")
    print("- Close Arduino IDE Serial Monitor")
    print("- Check USB cable connection")
    print("- Try a different USB port")
    
except KeyboardInterrupt:
    print("\nInterrupted")
    if 'arduino' in locals():
        arduino.close()
    
except Exception as e:
    print(f"\n✗ Error: {e}")
    if 'arduino' in locals():
        arduino.close()

    try:
        input("Press Enter when ready to start the sensor test...")

        # Step 1: WHITE paper
        print("\nStep 1 — Place the sensor on WHITE paper and press Enter")
        input("When ready, press Enter to sample WHITE (expect mostly 1/high)...")
        white_samples = read_samples(arduino, samples=20, timeout=8)
        if not white_samples:
            print("✗ No samples received for WHITE — check connection and serial monitor.")
            raise SystemExit

        # Step 2: BLACK line
        print("\nStep 2 — Place the sensor on BLACK line and press Enter")
        input("When ready, press Enter to sample BLACK (expect mostly 0/low)...")
        black_samples = read_samples(arduino, samples=20, timeout=8)
        if not black_samples:
            print("✗ No samples received for BLACK — check connection and serial monitor.")
            raise SystemExit

        # Analyze results
        white_ones = sum(1 for v in white_samples if v == 1)
        white_zeros = sum(1 for v in white_samples if v == 0)
        black_ones = sum(1 for v in black_samples if v == 1)
        black_zeros = sum(1 for v in black_samples if v == 0)

        print("\n=== TEST RESULTS ===")
        print(f"WHITE samples: {len(white_samples)}  -> ones: {white_ones}, zeros: {white_zeros}")
        print(f"BLACK samples: {len(black_samples)}  -> ones: {black_ones}, zeros: {black_zeros}")

        # Decision
        white_ok = white_ones >= max(1, len(white_samples) * 0.7)
        black_ok = black_zeros >= max(1, len(black_samples) * 0.7)

        if white_ok and black_ok:
            print("\n✓ SENSOR OK — shows HIGH on white and LOW on black")
        else:
            print("\n✗ SENSOR MAY BE FAULTY or MISPLACED")
            if not white_ok:
                print(" - WHITE reading did not show expected HIGH values")
            if not black_ok:
                print(" - BLACK reading did not show expected LOW values")
            print("\nSuggested checks:")
            print(" - Ensure sensor wiring to the correct pin (LEFT=pin7, RIGHT=pin6)")
            print(" - Clean sensor lens; keep ~1-2cm from surface")
            print(" - Verify sensor power and GND")
            print(" - Try swapping sensor to the other pin or test with a multimeter")

    except KeyboardInterrupt:
        print("\nInterrupted by user")
    finally:
        arduino.close()
        print("✓ Disconnected")

except serial.SerialException as e:
    print(f"\n✗ ERROR: {e}")
    print("\nTroubleshooting:")
    print("- Make sure Arduino is connected")
    print("- Close Arduino IDE Serial Monitor")
    print("- Check if COM7 is the correct port")
    
except KeyboardInterrupt:
    print("\n\n⏹️  Stopping...")
    arduino.close()
    print("✓ Disconnected")

except Exception as e:
    print(f"\n✗ Unexpected error: {e}")
    