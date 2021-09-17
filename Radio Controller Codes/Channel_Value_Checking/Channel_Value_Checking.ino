#define channel1 14
#define channel2 15
#define channel3 16
#define channel4 17
#define channel5 18
#define channel6 19

int channel1Value;
int channel2Value;
int channel3Value;
int channel4Value;
int channel5Value;
int channel6Value;

void setup() {
    pinMode(channel1 , INPUT);
    pinMode(channel2 , INPUT);
    pinMode(channel3 , INPUT);
    pinMode(channel4 , INPUT);
    pinMode(channel5 , INPUT);
    pinMode(channel6 , INPUT);
    Serial.begin(9600);
}

void loop() {
    channel1Value = (pulseIn (channel1, HIGH));
    channel2Value = (pulseIn (channel2, HIGH));
    channel3Value = (pulseIn (channel3, HIGH));
    channel4Value = (pulseIn (channel4, HIGH));
    channel5Value = (pulseIn (channel5, HIGH));
    channel6Value = (pulseIn (channel6, HIGH));

    Serial.print("Channel 1: ");
    Serial.print(channel1Value);
    Serial.print("    ");
    Serial.print("Channel 2: ");
    Serial.print(channel2Value);
    Serial.print("    ");
    Serial.print("Channel 3: ");
    Serial.print(channel3Value);
    Serial.print("    ");
    Serial.print("Channel 4: ");
    Serial.print(channel4Value);
    Serial.print("    ");
    Serial.print("Channel 5: ");
    Serial.print(channel5Value);
    Serial.print("    ");
    Serial.print("Channel 6: ");
    Serial.println(channel6Value);
}
