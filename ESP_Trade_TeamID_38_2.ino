#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

char ssid[] = "LAPTOP-F5S5B9MT 2147";
char password[] = "asdfghjkl";
String teamid = "38.2";
String apikey = "ptEMhrBr3Yu0bE2iMFZkgwQZAJprbcx2";
WiFiClientSecure client;
#define HOST "esptrade.gciitbbs.com"
bool check = false;

float currentOpen, currentHigh, currentLow, currentClose, currentVolume;
float previousOpen, previousHigh, previousLow, previousClose, previousVolume;
float nstocks, currbalance;

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  client.setInsecure();
  fetchstocksdata();
}

void fetchstocksdata(){
  if (!client.connect(HOST, 443)){
    Serial.println(F("Connection failed"));
    return;
  }
  Serial.println(client);
  yield();  
  
  client.print(F("GET "));  
  client.print("/api/curr-stock-data"); // after GET
  client.println(F(" HTTP/1.0")); //!very important

  //Headers (POSTMAN)
  client.print(F("Host: "));
  client.println(HOST);
  client.println(F("Cache-Control: no-cache"));
  client.println(F("teamid: 38.2"));
  client.println(F("api-key: ptEMhrBr3Yu0bE2iMFZkgwQZAJprbcx2"));

  if (client.println() == 0){
    Serial.println(F("Failed to send request"));
    return;
  }
  delay(100);
  Serial.println(client.println());
  
  // // Check HTTP status
  // char status[32] = {0};
  // client.readBytesUntil('\r', status, sizeof(status));  
  // // Check if it responded "OK" 
  // if (strcmp(status, "HTTP/1.0 200 OK") != 0 || strcmp(status, "HTTP/1.1 200 OK") != 0){
  //   Serial.print(F("Unexpected response: "));
  //   Serial.println(status);
  //   return;
  // }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)){
    Serial.println(F("Invalid response"));
    return;
  }
  // //While the client is still availble read each byte and print to the serial monitor  
  // String input ="";
  // while (client.available()){
  //   char c = 0;
  //   client.readBytes(&c, 1);
  //   input+=c;
  // } 
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, client);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  previousOpen = doc["open"].as<float>(); // "224.7"
  previousHigh = doc["high"].as<float>(); // "224.74"
  previousLow = doc["low"].as<float>(); // "224.4518"
  previousClose = doc["close"].as<float>(); // "224.4518"
  previousVolume = doc["volume"].as<float>(); // "5570"
  const char* time = doc["time"];
}

void buystocks(String amount){
  if (!client.connect(HOST, 443)){
    Serial.println(F("Connection failed"));
    return;
  }
  Serial.println(client);
  yield();  
  
  client.print(F("POST "));  
  client.print("/api/buy?amount="+amount); // after GET
  client.println(F(" HTTP/1.0")); //!very important

  //Headers (POSTMAN)
  client.print(F("Host: "));
  client.println(HOST);
  client.println(F("Cache-Control: no-cache"));
  client.println(F("teamid: 38.2"));
  client.println(F("api-key: ptEMhrBr3Yu0bE2iMFZkgwQZAJprbcx2"));
  

  if (client.println() == 0){
    Serial.println(F("Failed to send request"));
    return;
  }
  delay(100);
  Serial.println(client.println());
  
  // // Check HTTP status
  // char status[32] = {0};
  // client.readBytesUntil('\r', status, sizeof(status));  
  // // Check if it responded "OK" 
  // if (strcmp(status, "HTTP/1.0 200 OK") != 0 || strcmp(status, "HTTP/1.1 200 OK") != 0){
  //   Serial.print(F("Unexpected response: "));
  //   Serial.println(status);
  //   return;
  // }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)){
    Serial.println(F("Invalid response"));
    return;
  }

  //While the client is still availble read each byte and print to the serial monitor  
  while (client.available()){
    char c = 0;
    client.readBytes(&c, 1);
    Serial.print(c);
  }
}

void sellstocks(String amount){
  if (!client.connect(HOST, 443)){
    Serial.println(F("Connection failed"));
    return;
  }
  Serial.println(client);
  yield();  
  
  client.print(F("POST "));  
  client.print("/api/sell?amount="+amount); // after GET
  client.println(F(" HTTP/1.0")); //!very important

  //Headers (POSTMAN)
  client.print(F("Host: "));
  client.println(HOST);
  client.println(F("Cache-Control: no-cache"));
  client.println(F("teamid: 38.2"));
  client.println(F("api-key: ptEMhrBr3Yu0bE2iMFZkgwQZAJprbcx2"));
  

  if (client.println() == 0){
    Serial.println(F("Failed to send request"));
    return;
  }
  delay(100);
  Serial.println(client.println());
  
  // // Check HTTP status
  // char status[32] = {0};
  // client.readBytesUntil('\r', status, sizeof(status));  
  // // Check if it responded "OK" 
  // if (strcmp(status, "HTTP/1.0 200 OK") != 0 || strcmp(status, "HTTP/1.1 200 OK") != 0){
  //   Serial.print(F("Unexpected response: "));
  //   Serial.println(status);
  //   return;
  // }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)){
    Serial.println(F("Invalid response"));
    return;
  }

  //While the client is still availble read each byte and print to the serial monitor  
  while (client.available()){
    char c = 0;
    client.readBytes(&c, 1);
    Serial.print(c);
  }
}

void mystatus(){
  if (!client.connect(HOST, 443)){
    Serial.println(F("Connection failed"));
    return;
  }
  Serial.println(client);
  yield();  
  
  client.print(F("GET "));  
  client.print("/api/mystatus"); // after GET
  client.println(F(" HTTP/1.0")); //!very important

  //Headers (POSTMAN)
  client.print(F("Host: "));
  client.println(HOST);
  client.println(F("Cache-Control: no-cache"));
  client.println(F("teamid: 38.2"));
  client.println(F("api-key: ptEMhrBr3Yu0bE2iMFZkgwQZAJprbcx2"));

  if (client.println() == 0){
    Serial.println(F("Failed to send request"));
    return;
  }
  delay(100);
  Serial.println(client.println());
  
  // // Check HTTP status
  // char status[32] = {0};
  // client.readBytesUntil('\r', status, sizeof(status));  
  // // Check if it responded "OK" 
  // if (strcmp(status, "HTTP/1.0 200 OK") != 0 || strcmp(status, "HTTP/1.1 200 OK") != 0){
  //   Serial.print(F("Unexpected response: "));
  //   Serial.println(status);
  //   return;
  // }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)){
    Serial.println(F("Invalid response"));
    return;
  }

  //While the client is still availble read each byte and print to the serial monitor  
  while (client.available()){
    char c = 0;
    client.readBytes(&c, 1);
    Serial.print(c);
  } 
}

void mytransactions(){
  if (!client.connect(HOST, 443)){
    Serial.println(F("Connection failed"));
    return;
  }
  Serial.println(client);
  yield();  
  
  client.print(F("GET "));  
  client.print("/api/transactions"); // after GET
  client.println(F(" HTTP/1.0")); //!very important

  //Headers (POSTMAN)
  client.print(F("Host: "));
  client.println(HOST);
  client.println(F("Cache-Control: no-cache"));
  client.println(F("teamid: 38.2"));
  client.println(F("api-key: ptEMhrBr3Yu0bE2iMFZkgwQZAJprbcx2"));

  if (client.println() == 0){
    Serial.println(F("Failed to send request"));
    return;
  }
  delay(100);
  Serial.println(client.println());
  
  // // Check HTTP status
  // char status[32] = {0};
  // client.readBytesUntil('\r', status, sizeof(status));  
  // // Check if it responded "OK" 
  // if (strcmp(status, "HTTP/1.0 200 OK") != 0 || strcmp(status, "HTTP/1.1 200 OK") != 0){
  //   Serial.print(F("Unexpected response: "));
  //   Serial.println(status);
  //   return;
  // }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)){
    Serial.println(F("Invalid response"));
    return;
  }

  //While the client is still availble read each byte and print to the serial monitor  
  while (client.available()){
    char c = 0;
    client.readBytes(&c, 1);
    Serial.print(c);
  } 
}

void faucetstock(){
  if (!client.connect(HOST, 443)){
    Serial.println(F("Connection failed"));
    return;
  }
  Serial.println(client);
  yield();  
  
  client.print(F("POST "));  
  client.print("/api/faucet"); // after GET
  client.println(F(" HTTP/1.0")); //!very important

  //Headers (POSTMAN)
  client.print(F("Host: "));
  client.println(HOST);
  client.println(F("Cache-Control: no-cache"));
  client.println(F("teamid: 38.2"));
  client.println(F("api-key: ptEMhrBr3Yu0bE2iMFZkgwQZAJprbcx2"));
  

  if (client.println() == 0){
    Serial.println(F("Failed to send request"));
    return;
  }
  delay(100);
  Serial.println(client.println());
  
  // // Check HTTP status
  // char status[32] = {0};
  // client.readBytesUntil('\r', status, sizeof(status));  
  // // Check if it responded "OK" 
  // if (strcmp(status, "HTTP/1.0 200 OK") != 0 || strcmp(status, "HTTP/1.1 200 OK") != 0){
  //   Serial.print(F("Unexpected response: "));
  //   Serial.println(status);
  //   return;
  // }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)){
    Serial.println(F("Invalid response"));
    return;
  }

  //While the client is still availble read each byte and print to the serial monitor  
  while (client.available()){
    char c = 0;
    client.readBytes(&c, 1);
    Serial.print(c);
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  //fetchstocksdata();
  //buystocks("1");
  //sellstocks("31");
  //faucetstock();
  //mystatus();
  //mytransactions();

  if (!client.connect(HOST, 443)){
    Serial.println(F("Connection failed"));
    return;
  }
  Serial.println(client);
  yield();  
  
  client.print(F("GET "));  
  client.print("/api/curr-stock-data"); // after GET
  client.println(F(" HTTP/1.0")); //!very important

  //Headers (POSTMAN)
  client.print(F("Host: "));
  client.println(HOST);
  client.println(F("Cache-Control: no-cache"));
  client.println(F("teamid: 38.2"));
  client.println(F("api-key: ptEMhrBr3Yu0bE2iMFZkgwQZAJprbcx2"));

  if (client.println() == 0){
    Serial.println(F("Failed to send request"));
    return;
  }
  delay(100);
  Serial.println(client.println());
  
  // // Check HTTP status
  // char status[32] = {0};
  // client.readBytesUntil('\r', status, sizeof(status));  
  // // Check if it responded "OK" 
  // if (strcmp(status, "HTTP/1.0 200 OK") != 0 || strcmp(status, "HTTP/1.1 200 OK") != 0){
  //   Serial.print(F("Unexpected response: "));
  //   Serial.println(status);
  //   return;
  // }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)){
    Serial.println(F("Invalid response"));
    return;
  }
  // //While the client is still availble read each byte and print to the serial monitor  
  // String input ="";
  // while (client.available()){
  //   char c = 0;
  //   client.readBytes(&c, 1);
  //   input+=c;
  // } 
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, client);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  float open = doc["open"].as<float>(); // "224.7"
  float high = doc["high"].as<float>(); // "224.74"
  float low = doc["low"].as<float>(); // "224.4518"
  float close = doc["close"].as<float>(); // "224.4518"
  float volume = doc["volume"].as<float>(); // "5570"
  const char* time = doc["time"];
  Serial.print("Time : ");
  Serial.println(time);
  Serial.print("High : ");
  Serial.println(high);
  Serial.print("Low : ");
  Serial.println(low);
  Serial.print("Open : ");
  Serial.println(open);
  Serial.print("Close : ");
  Serial.println(close);
  Serial.print("Volume : ");
  Serial.println(volume);
  Serial.println("------------------");
  Serial.println();

  if(previousClose>previousOpen && close<open && previousLow>low && previousHigh<high){
    sellstocks("1"); //Bearish engulfing conditions
  }
  else if(close<open && high>open*2 && close-low<1){
    sellstocks("1"); //Bearish Shooting Star conditions
  }
  else if(close<open && open-close<=1 && high>open+(high-low)*(2/3) && low<open-2){
    sellstocks("1"); //Bearish Gravestone doji conditions
  }
  else if(open>close && high<open+(high-low)/2 && low<close-2*(open-close && (open-close)<=(high-low)/5)){
    sellstocks("1"); //Hanging Man Bearish conditions 
  }
  else if(open==low && close==high && close<open){
    sellstocks("1"); //Bearish Marubozu conditions
  }
  else if(previousClose>previousOpen && close<open && open>previousClose && close<(previousClose-((previousClose-previousOpen)/2))){
    sellstocks("1"); //Bearish Dark Cloud Cover conditions
  }
  else if(close < open && previousClose < previousOpen && high < previousLow){
    sellstocks("1"); //Bearish Falling Window conditions
  }
  if(previousClose < previousOpen && close > open && previousLow > open && previousHigh < close){
    buystocks("1"); //Bullish engulfing conditions
  }
  else if(previousClose < previousOpen && close > open && previousClose < open+1 && open < previousLow && close > previousHigh){
    buystocks("1"); //Bullish Piercing Line 
  }
  else if((close-open)<=(high-low)/5  &&  low<open-2*(high-low) && high<open+(high-low)/2){
    buystocks("1"); // Bullish Hammer conditions
  }
  else if(close>open && close-open<=1 && low<close-(high-low)/2  &&  high>=open && high>=close-1){
    buystocks("1"); // Bullish Dragonfly Doji Conditions
  }
  else if(open==low && close==high && close>open){
    buystocks("1"); //Bullish Marubozu conditions
  }
  else if(close>open && previousClose>previousOpen && low>previousHigh){
    buystocks("1"); //Bullish Rising Window conditions
  }
  
  previousOpen = open;
  previousHigh = high;
  previousLow = low;
  previousClose = close;
  previousVolume = volume;
  mystatus();
  delay(50000);
}
