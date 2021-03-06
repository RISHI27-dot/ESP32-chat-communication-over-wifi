
# ESP32-chat-communication-over-wifi 
The aim of the project is to build a chat system using two esp32 development boards.  


<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Tech Stack](#tech-stack)
  * [File Structure](#file-structure)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Results and Demo](#results-and-demo)
* [Future Work](#future-work)
* [Troubleshooting](#troubleshooting)
* [Contributors](#contributors)
* [Acknowledgements and Resources](#acknowledgements-and-resources)
* [License](#license)


<!-- ABOUT THE PROJECT -->
## About The Project


* Aim of the project is to build a chat system between two ESP32 development boards.
* The chat system should be fast,secure and easy to use.
* Communication protocol used is ESP-NOW as
  * It overcomes the drawbacks of traditonal wifi connection.
  * The pairing between devices is needed prior to their communication. After the pairing is done, the connection is secure and peer-to-peer.
  * ESP NOW does not require a router for the connection,Thus this project can be used anywhere,at any remote places.
  * If suddenly one of the boards loses power or resets, when it restarts, it will automatically connect to its peers.

To read more about the project refer this [documentation](https://github.com/RISHI27-dot/ESP32-chat-communication-over-wifi/blob/testing1/docs/report.pdf)

### Tech Stack

* [FreeRTOS](https://www.freertos.org/openrtos.html)
* [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)


### File Structure
     .
    ├── Components              # Contains files of specific library of functions or Hardware used
    │    ├──esp_now             # Contains the code to setup connection using ESP-NOW. 
    │    ├──CMakeLists.txt      # To include this component in a esp-idf 
    ├── docs                    # Documentation files 
    │   ├── report.pdf          # Project report
    │   └── results             # Folder containing the video, gifs of the result
    ├── main                    # Source files of project
    │   ├──main.c               # Main Source code.
    │   ├──kconfig.projbuild    # Shows the menu of project configuration
    │   ├──CMakeLists.txt       # To include source code files in esp-idf.
    ├── CmakeLists.txt          # To include components and main folder while executing
    ├── LICENSE
    └── README.md 
    

<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

* **ESP-IDF v4.0 and above**

  You can visit the [ESP-IDF Programmming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html#installation-step-by-step) for the installation steps.

### Installation
Clone the repo
```sh
git clone https://github.com/RISHI27-dot/ESP32-chat-communication-over-wifi
```


<!-- USAGE EXAMPLES -->
## Usage
### Configuration

```
idf.py menuconfig
```
* `Chat history`
  * `Store command history in flash` - to store the chat history ans use previous chats.
  
* `ESP-NOW Configuration`
  * `Send len` - espnow packet lenght.

![**menuconfig image**](https://github.com/RISHI27-dot/ESP32-chat-communication-over-wifi/blob/testing1/assets/menuconfig.png) 

### Build
```
idf.py build
```
### Flash and Monitor
* Connect two esp32 through ports and run the following command on two seprate terminals.
* The terminals will act as user interface. 
```
idf.py -p /dev/ttyUSB0 flash monitor

```
```
idf.py -p /dev/ttyUSB1 flash monitor

```
<!-- CODE  -->
## Code
* The input of chat is taken from the user through the console.
* The chat data is sent to espnow and console task suspended,chat data is sent to other esp32 board.
* Console task is resumed to take the next chat.
* When the chat data is received by the other esp32 board it is printed to the console.


![**flowchart**](https://github.com/RISHI27-dot/ESP32-chat-communication-over-wifi/blob/testing1/assets/code_flow.png)
<!-- RESULTS AND DEMO -->
## Results and Demo
 
![**result gif**](https://github.com/RISHI27-dot/ESP32-chat-communication-over-wifi/blob/testing1/assets/result.gif)  

<!-- FUTURE WORK -->
## Future Work
- [ ] Add a http web server chat interface.
- [ ] Add encryption to the chat communication.




<!-- CONTRIBUTORS -->
## Contributors
* [Viraj Jagdale](https://github.com/Jviraj)
* [Rishikesh Donadkar](https://github.com/RISHI27-dot)


<!-- ACKNOWLEDGEMENTS AND REFERENCES -->
## Acknowledgements and Resources
* [SRA VJTI](http://sra.vjti.info/) Eklavya 2020
* Special thanks 
  * [Gautam Agrawal](https://github.com/gautam-dev-maker)
  * [Dhairya Shah](https://github.com/dhairyashah1)  
* Refered [FreeRTOS](https://www.freertos.org/) for FreeRTOS API.
* Refered [ESP_NOW](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html) for ESP-NOW API.



<!-- LICENSE -->
## License
Describe your [License](LICENSE) for your project. 