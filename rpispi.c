#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

const char *spiDevice = "/dev/spidev0.0";
uint8_t spiMode = 0;
uint8_t spiBits = 8;
uint32_t spiSpeed = 15000000;
uint16_t spiDelay = 1;
uint32_t spiMode2 = 0x00000000 | SPI_NO_CS;
int spiDevFilehandle;

int SpiWriteRead(unsigned char *data, unsigned int length) {
    struct spi_ioc_transfer spi;
    memset(&spi, 0, sizeof(spi));

    spi.tx_buf = (unsigned long) data;
    spi.rx_buf = (unsigned long) data;
    spi.len = length;
    spi.delay_usecs = spiDelay;
    spi.speed_hz = spiSpeed;
    spi.bits_per_word = spiBits;
    spi.cs_change = false;

    return ioctl(spiDevFilehandle, SPI_IOC_MESSAGE(1), &spi);
}

int initSpi(unsigned int speed) {
    int ret;
    printf("init SPI");

    spiSpeed = speed;

    /* Device oeffen */
    if ((spiDevFilehandle = open(spiDevice, O_RDWR)) < 0) {
        perror("Fehler Open Device");
        exit(1);
    }
    /* Mode setzen */
    ret = ioctl(spiDevFilehandle, SPI_IOC_WR_MODE, &spiMode);
    if (ret < 0) {
        perror("Fehler Set SPI-Modus");
        exit(1);
    }

    /* Mode abfragen */
    ret = ioctl(spiDevFilehandle, SPI_IOC_RD_MODE, &spiMode);
    if (ret < 0) {
        perror("Fehler Get SPI-Modus");
        exit(1);
    }

    /* Mode2 setzen */
    ret = ioctl(spiDevFilehandle, SPI_IOC_WR_MODE32, &spiMode2);
    if (ret < 0) {
        perror("Fehler Set SPI-Modus2");
        exit(1);
    }

    /* Mode2 abfragen */
    ret = ioctl(spiDevFilehandle, SPI_IOC_RD_MODE32, &spiMode2);
    if (ret < 0) {
        perror("Fehler Get SPI-Modus2");
        exit(1);
    }

    /* Wortlaenge setzen */
    ret = ioctl(spiDevFilehandle, SPI_IOC_WR_BITS_PER_WORD, &spiBits);
    if (ret < 0) {
        perror("Fehler Set Wortlaenge");
        exit(1);
    }

    /* Wortlaenge abfragen */
    ret = ioctl(spiDevFilehandle, SPI_IOC_RD_BITS_PER_WORD, &spiBits);
    if (ret < 0) {
        perror("Fehler Get Wortlaenge");
        exit(1);
    }

    /* Datenrate setzen */
    ret = ioctl(spiDevFilehandle, SPI_IOC_WR_MAX_SPEED_HZ, &spiSpeed);
    if (ret < 0) {
        perror("Fehler Set Speed");
        exit(1);
    }

    /* Datenrate abfragen */
    ret = ioctl(spiDevFilehandle, SPI_IOC_RD_MAX_SPEED_HZ, &spiSpeed);
    if (ret < 0) {
        perror("Fehler Get Speed");
        exit(1);
    }

    /* Kontrollausgabe */
    printf("SPI-Device.....: %s\n", spiDevice);
    printf("SPI-Mode.......: %d\n", spiMode);
    printf("SPI-Mode2......: %d\n", spiMode2);
    printf("Wortlaenge.....: %d\n", spiBits);
    printf("Geschwindigkeit: %d Hz (%d MHz)\n", spiSpeed, spiSpeed / 1000000);
}