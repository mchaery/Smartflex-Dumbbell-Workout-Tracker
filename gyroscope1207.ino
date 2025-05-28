// Please download the MPU6050_tockn library before uploading this code.
// 1. Click on "Sketch" in the top menu, then navigate to "Include Library" > "Manage Libraries...".
// 2. In the Library Manager, search for "MPU6050_tockn" and click "Install" to download and install the library.
// 3. After installing the library, you can upload this code to your Arduino board.

#include <Wire.h>
#include <MPU6050_tockn.h>
#include <math.h>  // For atan2, sqrt, PI

MPU6050 mpu6050(Wire);

int goalReps;                 // User-defined goal reps
int goalSets;                 // User-defined goal sets
int reps = 0;                 // Variable to store the number of arm curl repetitions
int sets = 1;                 // Variable to store the number of arm curl sets
float thresholdAngle;         // Angle threshold to detect the arm curl motion
float MovementRange;          // Range of movement(motion)
bool motionDetected = false;  // Variable to track if the arm curl motion is detected
bool goalAchieved = false;    // Variable to track if the user has achieved the goal
int ledPin = 12;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  // Select calibrated range
  Serial.println("Select your desired motion range:");
  Serial.println("1. 30~50 degrees");
  Serial.println("2. 50~70 degrees");
  Serial.println("3. 70~90 degrees");

  int selectedRange;
  while (!Serial.available()) {}
  selectedRange = Serial.parseInt();

  // Set threshold angle based on the selected range
  switch (selectedRange) {
    case 1:
      thresholdAngle = 30.0;
      MovementRange = 15.0;
      break;
    case 2:
      thresholdAngle = 50.0;
      MovementRange = 15.0;
      break;
    case 3:
      thresholdAngle = 70.0;
      MovementRange = 15.0;
      break;
    default:
      thresholdAngle = 70.0; // Default to 70~90 degrees
      MovementRange = 15.0;
  }

  // Get user input for goal reps and sets
  Serial.println("Enter goal reps and sets (e.g., 10,3):");
  while (!Serial.available()) {}
  goalReps = Serial.parseInt();
  while (Serial.read() != ',') {}  // Read and discard the comma
  goalSets = Serial.parseInt();

  // Display user-entered goals
  Serial.println("Your goals:");
  Serial.print("Goal Reps: ");
  Serial.println(goalReps);
  Serial.print("Goal Sets: ");
  Serial.println(goalSets);

  Serial.println("Start your workout!");
}

void light() {
  digitalWrite(ledPin, HIGH);  // turn on the LED
  delay(700);  // wait for 0.7 sec
  digitalWrite(ledPin, LOW);  // turn off the LED
}

void loop() {
  // Read accelerometer and gyroscope values from the sensor
  mpu6050.update();
  float accX = mpu6050.getAccX();
  float accY = mpu6050.getAccY();
  float accZ = mpu6050.getAccZ();

  // Calculate pitch angle using accelerometer values (in degrees)
  float pitch = atan2(-accX, sqrt(accY * accY + accZ * accZ)) * 180.0 / PI;

  // Wait for goal sets input if not received yet
  while (goalSets == 0) {
    Serial.println("Enter goal sets:");
    while (!Serial.available()) {}
    goalSets = Serial.parseInt();
  }

  // Detect arm curl motion based on pitch angle
  if (pitch >= thresholdAngle && !motionDetected) {
    motionDetected = true;  // First event detected (arm going up)
  } else if (pitch <= thresholdAngle - MovementRange && motionDetected) {
    // Second event detected (arm going down)
    reps++;  // Increase the arm curl repetitions count
    light();

    Serial.print("Sets: ");
    Serial.print(sets);
    Serial.print(" Reps: ");
    Serial.println(reps);
    motionDetected = false;  // Reset for the next arm curl motion

    // Check for goal achievement
    if (reps == goalReps) {
      reps = 0;  // Reset reps count for the next set
      sets++;    // Increase the sets count
      light();
    }

    // Check for overall goal achievement
    if (sets == goalSets + 1) {
      goalAchieved = true;
      Serial.println("Congratulations! You've achieved your goal!");

      // Reset goals for a new workout
      Serial.println("Enter new goal reps and sets (e.g., 10,3):");
      while (!Serial.available()) {}
      goalReps = Serial.parseInt();
      while (Serial.read() != ',') {}  // Read and discard the comma
      goalSets = Serial.parseInt();

      // Display new goals
      Serial.println("Your new goals:");
      Serial.print("Goal Reps: ");
      Serial.println(goalReps);
      Serial.print("Goal Sets: ");
      Serial.println(goalSets);

      // Reset workout variables
      reps = 0;
      sets = 1;
      goalAchieved = false;
    }
  }
}
