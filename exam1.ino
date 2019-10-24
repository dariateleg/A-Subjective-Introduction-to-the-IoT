#define V 30
#define DELAY 0.05
#define Kp 2

int left, right;
int u, err;

class track {
  public:
    void set_speed(int a, int b) { }
};
track TRACK;
class bus_hardware {
  public:
    static track init() {
      track tr;
      return tr;
    }
};

void setup() {
  Serial.begin(38400); // Default communication rate of the ESP module
  TRACK = bus_hardware::init();
}

void loop() {
  left = analogRead(A0); // Look for obstacles on the left
  right = analogRead(A1); // Look for obstacles on the right

  Serial.write(left / 4); // Dividing by 4 for converting from 0 - 1023 to 0 - 256, (1 byte) range
  Serial.write(left / 4);

  err = left - right;
  u = Kp * err;

  TRACK.set_speed(V - u, V + u); // Set velocities
  delay(DELAY);
}
