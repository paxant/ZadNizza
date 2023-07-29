#!/bin/bash
ls -l /sys/class/tty/*/device/driver | grep -v "platform/drivers/serial8250" | awk '{print $9}' | awk -F'/' '{print "/dev/" $5}' | tee ~/STM32_PC_realis/COM_PORTS.ZadNizza

