# GC_ESPTrade_H2T_38.2

## Description
We developed the Stock Trading Bot with ESP8266 to automate stock trading processes using an ESP8266 microcontroller. Our goal was to create a bot that connects to a server, fetches real-time stock data, performs technical analysis based on predefined conditions, and executes buying or selling orders accordingly. It uses candle stick pattern analysis to decide whether to buy, sell or hold. This bot simplifies the stock trading process by leveraging automation and real-time data analysis capabilities.

## Table of Contents
1. Features
2. Hardware Requirements
3. Software Requirements
4. Installation and Setup
5. Usage
6. Technical Details

## 1. Features
- Real-time stock data fetching
- Technical analysis based on candle stick patterns.
- Automated buying and selling orders execution
- HTTPS protocol for secure communication
- Account status checking and transaction history viewing

## 2. Hardware Requirements
- ESP8266 microcontroller
- Stable internet connection

## 3. Software Requirements
- Arduino IDE
- ArduinoJson library
- ESP8266WiFi library
- WiFiClientSecure library
## 4. Installation and Setup
### Hardware Setup
1. Connected the ESP8266 microcontroller to our development machine via USB.
2. Ensured proper power supply and connections.
### Software Setup
1. Installed the Arduino IDE from the official website.
2. Installed the required libraries:
 - ArduinoJson
 - ESP8266WiFi
 - WiFiClientSecure
### Code Configuration
1. Opened the `ESP_Trade_TeamID_38_2.ino` file in Arduino IDE.
2. Updated the following variables with our WiFi network credentials, teamid and api-key:
 char ssid[] = "YOUR_WIFI_SSID";
 char password[] = "YOUR_WIFI_PASSWORD";
 String teamid = "YOUR_TEAM_ID";
 String apikey = "YOUR_API_KEY";


### Uploading the Code
1. Connected the ESP8266 to our computer and selected the appropriate board and port in Arduino IDE.
2. Compiled and uploaded the code to our ESP8266 microcontroller.

## 5. Usage
Once the code is uploaded, the bot will automatically connect to our configured WiFi network. It will start fetching stock data from the server and analyze it based on the algorithm it was fedded. The bot will execute buying or selling orders as per the analysis. We can monitor the bot's actions and status via the Serial Monitor in Arduino IDE.



## 6. Technical Details
- We used the HTTPS protocol to securely communicate with the server.
- Stock data is fetched from the server's `/api/curr-stock-data` endpoint.
- Buying or selling orders are executed via server endpoints such as `/api/buy` and `/api/sell`.
- Additional functionalities include checking account status (`/api/mystatus`), viewing transaction history (`/api/transactions`), and receiving free stocks (`/api/faucet`).
