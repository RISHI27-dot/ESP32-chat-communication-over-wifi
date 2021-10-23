
# ESP32-chat-communication-over-wifi 
The aim of the project is to build chat system using two esp32 devlopment bords.  


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
[![Product Name Screen Shot][product-screenshot]](https://example.com)  

* Aim of the project is to build a chat system between two ESP32 devlopment bords.
* Communication protocol used is ESP-NOW.

Refer this [documentation](https://link/to/report/)

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
  * `Store command history in flash` - to store the chat history ans use previous chats
  
* `ESP-NOW Configuration`
  * `Send len` - espnow packet lenght

![**menuconfig image**](https://github.com/RISHI27-dot/ESP32-chat-communication-over-wifi/blob/testing1/assets/menuconfig.png) 

### Build
```
idf.py build
```
### Flash
```
idf.py -p (PORT) flash monitor

```


<!-- RESULTS AND DEMO -->
## Results and Demo
 
![**result gif**](https://github.com/RISHI27-dot/ESP32-chat-communication-over-wifi/blob/testing1/assets/result.gif)  

<!-- FUTURE WORK -->
## Future Work
- [ ] Add a http web server chat interface
- [ ] Add encryption to the chat communication



<!-- CONTRIBUTORS -->
## Contributors
* [Viraj Jagdale](https://github.com/Jviraj)
* [Rishikesh Donadkar](https://github.com/RISHI27-dot)


<!-- ACKNOWLEDGEMENTS AND REFERENCES -->
## Acknowledgements and Resources
* [SRA VJTI](http://sra.vjti.info/) Eklavya 2020
* Special thanks to [Gautam Agrawal](https://github.com/gautam-dev-maker)  
* Refered [FreeRTOS](https://www.freertos.org/) for FreeRTOS API
* Refered [ESP_NOW](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html) for ESP-NOW API



<!-- LICENSE -->
## License
Describe your [License](LICENSE) for your project. 