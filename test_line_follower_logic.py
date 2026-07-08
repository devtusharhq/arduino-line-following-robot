"""
Line Follower Logic Simulator
Tests decision logic without hardware
"""

def simulate_line_follower():
    """Simulate the line follower logic"""
    
    test_cases = [
        (0, 0, "FORWARD"),      # Both on black
        (0, 1, "TURN_LEFT"),    # Left on black, right on white
        (1, 0, "TURN_RIGHT"),   # Left on white, right on black
        (1, 1, "STOP"),         # Both on white
    ]
    
    print("=" * 50)
    print("LINE FOLLOWER LOGIC TEST")
    print("=" * 50)
    print("\nTest Cases:")
    print("L=0 (BLACK), R=0 (BLACK) -> FORWARD")
    print("L=0 (BLACK), R=1 (WHITE) -> TURN_LEFT")
    print("L=1 (WHITE), R=0 (BLACK) -> TURN_RIGHT")
    print("L=1 (WHITE), R=1 (WHITE) -> STOP")
    print("\n" + "=" * 50)
    
    all_pass = True
    
    for left, right, expected in test_cases:
        # Simulate sensor logic
        if left == 0 and right == 0:
            result = "FORWARD"
        elif left == 0 and right == 1:
            result = "TURN_LEFT"
        elif left == 1 and right == 0:
            result = "TURN_RIGHT"
        else:
            result = "STOP"
        
        status = "✓ PASS" if result == expected else "✗ FAIL"
        if result != expected:
            all_pass = False
        
        print(f"L={left} R={right} -> {result:12} [{status}]")
    
    print("\n" + "=" * 50)
    if all_pass:
        print("✓ ALL TESTS PASSED - Logic is correct")
    else:
        print("✗ SOME TESTS FAILED - Check code logic")
    print("=" * 50)

if __name__ == "__main__":
    simulate_line_follower()
