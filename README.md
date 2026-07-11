# ESP32 AI Terminal

> AI-powered web terminal hosted on an ESP32 using the OpenRouter API.

## Overview

ESP32 AI Terminal is an embedded AI project that hosts a browser-based chat interface directly from an ESP32. The microcontroller serves a web page over Wi-Fi, accepts user prompts, sends them to the OpenRouter API, parses the JSON response, and displays the AI's reply back in the browser.

This project demonstrates how modern Large Language Models can be integrated with resource-constrained embedded hardware using HTTP and REST APIs.

## Features

- Browser-based chat interface
- Hosted directly on ESP32
- Wi-Fi connectivity
- OpenRouter API integration
- JSON request/response parsing
- Lightweight HTML/CSS UI
- Embedded web server

## Hardware

- ESP32 Dev Module

## Software

- Arduino IDE
- WiFi Library
- WebServer Library
- HTTPClient Library
- ArduinoJson

## Project Structure

```
ESP32-AI-Terminal/
├── README.md
├── LICENSE
├── .gitignore
├── src/
│   └── Chatbotcode.ino
└── images/
```

## How It Works

1. ESP32 connects to Wi-Fi.
2. Starts a local web server.
3. User opens the ESP32 IP address in a browser.
4. Prompt is sent to the ESP32.
5. ESP32 forwards the request to the OpenRouter API.
6. JSON response is parsed.
7. AI response is displayed in the browser.

## Screenshots

Place the screenshots inside the `images/` folder using these names:

- terminal.png
- conversation.png
- arduino_ide.png

Then add them to this README if desired.

## Setup

Before uploading your code, replace any secrets with placeholders:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* apiKey = "YOUR_OPENROUTER_API_KEY";
const char* accessPassword = "YOUR_PASSWORD";
```

Users should then replace these with their own credentials.

## Future Improvements

- Conversation memory
- Streaming responses
- OLED display
- Voice input
- Local LLM integration
- Sensor support

## Author

**Aarya Gurudath**

Electronics and Communication Engineering
