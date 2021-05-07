#!/bin/bash

gdb-multiarch \
    -ex "set arc arm" \
	-ex "target remote :3333" \
	-ex "file out.elf" \
	-ex "load" \
	-ex "b USART2_IRQHandler" \
	-ex "continue" 


