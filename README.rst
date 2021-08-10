.. cSLIM nRF9160-DK Board Controller:

cSLIM nRF9160-DK Board Controller
###########

Overview
********

A board-controller for the cSLIM application, disabling DK LEDs and switches, and connecting the UART of nRF9160 through nRF52840.

Building and Running
********************

This application can be built and executed as follows:

west build -b nRF9160dk_nRF52840 -p

west flash

Remember to switch to programing the nRF52840.
