#ifndef DIFFDRIVE_ARDUINO_ARDUINO_COMMS_HPP
#define DIFFDRIVE_ARDUINO_ARDUINO_COMMS_HPP

#include <string>
#include <vector>
#include <memory>
#include <io_context/io_context.hpp>
#include <serial_driver/serial_driver.hpp>

class ArduinoComms {
public:
    ArduinoComms() : 
      io_context_(std::make_shared<drivers::common::IoContext>()),
      serial_driver_(std::make_shared<drivers::serial_driver::SerialDriver>(*io_context_)) 
    {}

    void setup(const std::string &device, int baud_rate, int /*timeout_ms*/) {

        drivers::serial_driver::SerialPortConfig config(
            baud_rate, 
            drivers::serial_driver::FlowControl::NONE, 
            drivers::serial_driver::Parity::NONE, 
            drivers::serial_driver::StopBits::ONE);

        serial_driver_->init_port(device, config);
        if (!serial_driver_->port()->is_open()) {
            serial_driver_->port()->open();
        }
    }

    void sendMsg(const std::string &msg) {
        if (serial_driver_->port() && serial_driver_->port()->is_open()) {
            std::vector<uint8_t> data(msg.begin(), msg.end());
            serial_driver_->port()->send(data);
        }
    }

    void readEncoderValues(int &val_1, int &val_2) { 
        val_1 = 0; 
        val_2 = 0; 
    }

private:
    std::shared_ptr<drivers::common::IoContext> io_context_;
    std::shared_ptr<drivers::serial_driver::SerialDriver> serial_driver_;
};

#endif