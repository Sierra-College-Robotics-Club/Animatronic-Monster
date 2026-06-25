from enum import Enum
import time

# =====================================================
# CONFIGURATION
# =====================================================

STARTUP_POSITION = 0

OPEN_POSITION = 90
CLOSED_POSITION = 0

POS_LT_100 = 30
POS_101_250 = 60
POS_251_400 = 90

ACTIVE_WAIT = 4.0
REACTION_DELAY = 2.0
RETURN_DELAY = 0.75

# =====================================================
# STATES
# =====================================================

class State(Enum):
    IDLE = 0
    INITIALIZATION = 1
    ACTIVE = 2
    REACTION = 3
    FROZEN = 4

current_state = State.IDLE
previous_state = State.IDLE

# =====================================================
# HARDWARE PLACEHOLDERS
# =====================================================

def stepper_move_to(angle):
    print(f"Stepper -> {angle}°")

def servo_move_to(position):
    print(f"Servo -> Position {position}")

def play_sfx(name):
    print(f"Playing SFX: {name}")

def stop_sfx():
    print("Stop SFX")

def led_on():
    print("LEDs ON")

def led_off():
    print("LEDs OFF")

def flash_leds(duration=2):
    end_time = time.time() + duration

    while time.time() < end_time:
        led_on()
        time.sleep(0.2)
        led_off()
        time.sleep(0.2)

def bootup_led_animation():
    print("Bootup LEDs")
    flash_leds(1)

def led_init_animation():
    print("Init LED Pattern")

    led_on()
    time.sleep(0.2)
    led_off()
    time.sleep(0.2)

    led_on()
    time.sleep(0.2)
    led_off()
    time.sleep(0.2)

    print("Right LED")
    time.sleep(0.2)

    print("Left LED")
    time.sleep(0.2)

    led_on()

def safety_controller_ok():
    """
    I2C communication with safety controller.
    Return True if safety controller passes.
    """
    print("Checking Safety Controller")
    return True

def get_distance_cm():
    """
    Replace with actual sensor reading.
    """
    return None

# =====================================================
# BUTTON PLACEHOLDERS
# =====================================================

def start_button_pressed():
    return False

def freeze_button_pressed():
    return False

def rehome_button_pressed():
    return False

# =====================================================
# REHOME
# =====================================================

def rehome():
    print("Rehoming")
    stepper_move_to(STARTUP_POSITION)

# =====================================================
# INITIALIZATION
# =====================================================

def initialization_state():

    print("Initialization Started")

    if not safety_controller_ok():

        play_sfx("INIT_FAILED")

        while True:
            led_on()
            time.sleep(0.25)
            led_off()
            time.sleep(0.25)

    # Stepper test
    stepper_move_to(50)
    time.sleep(1)

    stepper_move_to(0)
    time.sleep(1)

    stepper_move_to(-50)
    time.sleep(1)

    stepper_move_to(0)
    time.sleep(1)

    # Jaw test
    servo_move_to(OPEN_POSITION)
    time.sleep(1)

    servo_move_to(CLOSED_POSITION)
    time.sleep(1)

    # LED test
    led_init_animation()

    print("Initialization Successful")

    return True

# =====================================================
# REACTIONS
# =====================================================

def run_reaction(position, sfx_name):

    flash_leds(0.5)

    servo_move_to(position)

    play_sfx(sfx_name)

    time.sleep(REACTION_DELAY)

    stop_sfx()

    servo_move_to(CLOSED_POSITION)

    time.sleep(RETURN_DELAY)

def reaction_state(distance):

    print(f"Reaction State Distance={distance} cm")

    if 0 <= distance <= 100:

        run_reaction(
            POS_LT_100,
            "LESS_THAN_100"
        )

    elif 101 <= distance <= 250:

        run_reaction(
            POS_101_250,
            "101_TO_250"
        )

    elif 251 <= distance <= 400:

        run_reaction(
            POS_251_400,
            "251_TO_400"
        )

# =====================================================
# ACTIVE MODE
# =====================================================

def active_cycle():

    # Right
    stepper_move_to(45)

    for _ in range(int(ACTIVE_WAIT * 10)):

        if freeze_button_pressed():
            return

        time.sleep(0.1)

    stepper_move_to(0)

    # Check sensor
    distance = get_distance_cm()

    if distance is not None and distance <= 400:
        reaction_state(distance)
        return

    # Left
    stepper_move_to(-45)

    for _ in range(int(ACTIVE_WAIT * 10)):

        if freeze_button_pressed():
            return

        time.sleep(0.1)

    stepper_move_to(0)

    distance = get_distance_cm()

    if distance is not None and distance <= 400:
        reaction_state(distance)

# =====================================================
# MAIN LOOP
# =====================================================

def main():

    global current_state
    global previous_state

    bootup_led_animation()

    while True:

        # ---------------------
        # REHOME BUTTON
        # ---------------------
        if rehome_button_pressed():
            rehome()

        # ---------------------
        # FREEZE BUTTON
        # ---------------------
        if freeze_button_pressed():

            if current_state != State.FROZEN:

                previous_state = current_state
                current_state = State.FROZEN

            print("FROZEN")

            while freeze_button_pressed():
                time.sleep(0.1)

            current_state = previous_state

        # ---------------------
        # IDLE
        # ---------------------
        if current_state == State.IDLE:

            if start_button_pressed():
                current_state = State.INITIALIZATION

        # ---------------------
        # INITIALIZATION
        # ---------------------
        elif current_state == State.INITIALIZATION:

            success = initialization_state()

            if success:
                current_state = State.ACTIVE

        # ---------------------
        # ACTIVE
        # ---------------------
        elif current_state == State.ACTIVE:

            active_cycle()

        time.sleep(0.05)

# =====================================================
# START
# =====================================================

if __name__ == "__main__":
    main()


