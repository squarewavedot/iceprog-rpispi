#ifndef ICEPROG_RPICSI_RPISPI_H
#define ICEPROG_RPICSI_RPISPI_H

int SpiWriteRead(unsigned char *data, unsigned int length);

int initSpi(unsigned int speed);

#endif //ICEPROG_RPICSI_RPISPI_H
