# Simple Serial Comms

Simple Serial Comms is a C++ 11 utility project which if included in a program, spawns a thread to read serial raw data and sends data via callback.
It also provides interface to transmit data

## Usage

Simply clone the respository as a submodule into your project.

'''
git submodule add https://github.com/hemantkapoor/simpleSerial.git
'''

It has its own CMakeLists.txt. To include in a main project, add following lines presuming that simpleSerial is present at "src/simpleSerial" driectory

'''
add_library(SimpleSerial "")
add_subdirectory(src/simpleSerial)
'''

## TEST

Simply clone the simpleSerialTest git repository and follow the instructions

'''
git clone https://github.com/hemantkapoor/simpleSerialTest.git
'''

## Upcoming changes

* <s>Ability to transmit data</s> - Implemented on 17-September-2019 
* Add version number
* Ability to have a callback on received message
* Serial Comms setting via config.txt
* Debug class to output messages based on levels


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)
