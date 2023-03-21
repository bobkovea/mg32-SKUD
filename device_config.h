#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

/* Выбор адреса устройства в сети RS-485 */
#define DEVICE_ADDRESS_H 0x43
#define DEVICE_ADDRESS_L 0x10

/* Выбор cкорости USART (раскомментировать нужную) */
#define URT_BAUDRATE 19200UL
//#define URT_BAUDRATE 38400UL

#endif // DEVICE_CONFIG_H