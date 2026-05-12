#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define trig_pin 13
#define echo_pin 12
#define ph_pin 34
#define flow_pin 35
#define buzzer_pin 25
#define relay_pin 26

const char* ssid = "wifi_name";
const char* password = "Password";

#define BOTtoken "paste_tocken_id"
#define CHAT_ID "paste_chat_id"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

float prev_distance = 0;

bool emptyAlertSent = false;
bool leakAlertSent = false;
bool phAlertSent = false;
bool flowAlertSent = false;

void sendTelegram(String message)
{
  Serial.println("Sending Telegram Message...");

  bool sent = bot.sendMessage(CHAT_ID, message, "");

  if(sent)
  {
    Serial.println("Telegram Message Sent");
  }
  else
  {
    Serial.println("Telegram Failed");
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  pinMode(buzzer_pin, OUTPUT);
  pinMode(relay_pin, OUTPUT);

  digitalWrite(relay_pin, LOW);
  digitalWrite(buzzer_pin, LOW);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  client.setInsecure();

  sendTelegram("SMART WATER DISTRIBUTION MONITORING SYSTEM STARTED");
}

void loop()
{
//ultra
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig_pin, LOW);

  long duration = pulseIn(echo_pin, HIGH);

  float distance = duration * 0.034 / 2;

//ph

  int ph_value = analogRead(ph_pin);

  float voltage = ph_value * (3.3 / 4095.0);

  float ph = 7 + ((2.5 - voltage) / 0.18);

//flow 
  int flow_value = analogRead(flow_pin);

  int flow = map(flow_value, 0, 4095, 0, 40);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("Raw pH Value: ");
  Serial.println(ph_value);

  Serial.print("Voltage: ");
  Serial.println(voltage);

  Serial.print("pH Value: ");
  Serial.println(ph);

  Serial.print("Flow Rate: ");
  Serial.print(flow);
  Serial.println(" L/min");

  String message = "SMART WATER SYSTEM STATUS\n\n";

  message += "Water Level: ";
  message += String(distance);
  message += " cm\n";

  message += "pH Value: ";
  message += String(ph, 2);
  message += "\n";

  message += "Flow Rate: ";
  message += String(flow);
  message += " L/min\n\n";
=
//tank altert on telegram
  if(distance > 200)
  {
    message += "Tank Status: EMPTY\n";

    digitalWrite(relay_pin, HIGH);

    tone(buzzer_pin, 500);

    if(!emptyAlertSent)
    {
      sendTelegram("ALERT: WATER TANK IS EMPTY");
      emptyAlertSent = true;
    }
  }
  else if(distance < 50)
  {
    message += "Tank Status: FULL\n";

    digitalWrite(relay_pin, LOW);

    noTone(buzzer_pin);

    emptyAlertSent = false;
  }
  else
  {
    message += "Tank Status: NORMAL\n";

    noTone(buzzer_pin);

    emptyAlertSent = false;
  }

//ph altert on telegram

  if(ph < 6.5)
  {
    message += "Water Quality: ACIDIC / UNSAFE\n";

    if(!phAlertSent)
    {
      sendTelegram("WARNING: WATER IS ACIDIC AND UNSAFE");
      phAlertSent = true;
    }
  }
  else if(ph > 8.5)
  {
    message += "Water Quality: ALKALINE / UNSAFE\n";

    if(!phAlertSent)
    {
      sendTelegram("WARNING: WATER IS ALKALINE AND UNSAFE");
      phAlertSent = true;
    }
  }
  else
  {
    message += "Water Quality: SAFE\n";
    phAlertSent = false;
  }
  //flow altert on telegram

  if(flow < 5)
  {
    message += "Flow Status: LOW FLOW\n";
  }
  else if(flow > 25)
  {
    message += "Flow Status: HIGH FLOW\n";

    if(!flowAlertSent)
    {
      sendTelegram("WARNING: HIGH WATER FLOW DETECTED");
      flowAlertSent = true;
    }
  }
  else
  {
    message += "Flow Status: NORMAL FLOW\n";
    flowAlertSent = false;
  }

//leak alert on telegram

  if(distance > prev_distance + 1.0 && flow < 5)
  {
    message += "Leak Status: POSSIBLE LEAK DETECTED\n";
    digitalWrite(relay_pin, HIGH);
    tone(buzzer_pin, 1000);

    if(!leakAlertSent)
    {
      sendTelegram("LEAK ALERT: WATER LEVEL DROPPING BUT NO FLOW DETECTED");
      leakAlertSent = true;
    }
  }
  else
  {
    message += "Leak Status: NORMAL\n";
    leakAlertSent = false;
  }

  prev_distance = distance;

  sendTelegram(message);
  delay(15000);
}