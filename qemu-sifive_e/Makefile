PROGRAM = hello
RISCVGNU = riscv32-unknown-elf

AOPS = -march=rv32imac
COPS = -march=rv32imac -Wall -O0 -g -nostdlib -nostartfiles -ffreestanding
#COPS = -march=rv32imac -Wall -O2 -nostdlib -nostartfiles -ffreestanding

all : $(PROGRAM).hex

clean :
	rm -f *.o
	rm -f *.elf
	rm -f *.hex
	rm -f *.list
	rm -f *~

utils.o : utils.S
	$(RISCVGNU)-as $(AOPS) utils.S -o utils.o

main.o : main.c
	$(RISCVGNU)-gcc $(COPS) -c main.c -o main.o

$(PROGRAM).hex : linker.ld utils.o main.o
	$(RISCVGNU)-ld utils.o main.o -T linker.ld -o $(PROGRAM).elf
	$(RISCVGNU)-objdump -D $(PROGRAM).elf > $(PROGRAM).list
	$(RISCVGNU)-objcopy $(PROGRAM).elf -O ihex $(PROGRAM).hex

flash : $(PROGRAM).hex
	JLinkExe -device FE310 -speed 1000 -if JTAG -jtagconf -1,-1 -autoconnect 1 -CommanderScript "upload.jlink"

gdb : $(PROGRAM).hex
	jLinkGDBServer -device FE310 -endian little -speed 1000 & riscv32-unknown-elf-gdb $(PROGRAM).elf

