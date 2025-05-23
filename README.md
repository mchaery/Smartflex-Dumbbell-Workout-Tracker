# 🏋️‍♀️ Smartflex: Dumbbell Workout Tracker

A wearable wrist-strap device powered by Arduino that tracks your arm movements during dumbbell workouts in real-time.  
Users can set their own workout goals — including reps, sets, and motion range — and receive feedback via LED and serial display.

---

## Overview

Smartflex monitors arm curls using **MPU6050 gyroscope sensor data**, tracking motion angles to count each valid repetition.  
The system provides visual feedback using an LED and allows users to view progress and completion via the Arduino serial monitor.

Key features include:

- 🎯 Customizable rep, set, and motion range goals
- 🔁 Real-time motion tracking with gyroscope data
- 💡 LED feedback after each rep and set
- 📊 Serial display for workout progress and automatic goal reset

---

## How It Works

1. **Setup**: Users input their target reps, sets, and desired motion range (e.g., 30–50°, 50–70°, 70–90°).
2. **Motion Detection**: The device tracks arm curl motions using **X-axis acceleration**.
3. **Repetition Logic**: A rep is counted when the arm travels above and below the calibrated angle.
4. **Feedback**: After each rep and set, the LED blinks. Completion is displayed via the serial monitor.

---

## Tech Stack

- **Platform**: Arduino UNO / Nano  
- **Sensor**: MPU6050 gyroscope + accelerometer  
- **Language**: C/C++ (Arduino IDE)  
- **Libraries**: [`MPU6050_tockn`](https://github.com/tockn/MPU6050_tockn)

---

## Final Prototype
https://wp.nyu.edu/tandonschoolofengineering-kristie_lee/about-my-work/
