import spidev
import time

# Function to initialize SPI
def init_spi():
    spi = spidev.SpiDev()
    spi.open(0, 0)  # Use CE0 (chip enable 0) on the Raspberry Pi
    spi.max_speed_hz = 1000000  # Set SPI speed to 1 MHz
    return spi

# Function to send and receive data over SPI
def transfer_spi(spi, data):
    return spi.xfer2(data)

# Main function
def main():
    try:
        spi = init_spi()

        while True:
            # Example: sending and receiving data
            print("Sending Data...")

            data_to_send = [0x49]  # Sending "I" in ASCII
            received_data = transfer_spi(spi, data_to_send)

            # Print received data
            print("Received data:", received_data)

            time.sleep(1)  # Wait for 1 second before the next transfer

    except KeyboardInterrupt:
        print("Program terminated by the user.")
    finally:
        spi.close()  # Close the SPI connection

if __name__ == "__main__":
    main()
