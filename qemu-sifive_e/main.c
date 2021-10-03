void put32(unsigned int, unsigned int);
unsigned int get32(unsigned int);

#define GPIOBASE        0x10012000
#define GPIO_OUTPUT_EN  (GPIOBASE+0x08)
#define GPIO_PORT       (GPIOBASE+0x0C)
#define GPIO_IOF_EN     (GPIOBASE+0x38)
#define GPIO_IOF_SEL    (GPIOBASE+0x3C)

#define IOF_UART0_RX    (1<<16)
#define IOF_UART0_TX    (1<<17)
#define IOF_UART1_RX    (1<<18)
#define IOF_UART1_TX    (1<<23)

#define UART0BASE       0x10013000
#define UART1BASE       0x10023000

#define UART_TXDATA     (0x00)
#define UART_TXCTRL     (0x08)
#define UART_DIV        (0x18)

#define TXCTRL_TXEN     (1)
#define TXCTRL_NSTOP    (1<<1)

#define HFCLK           (16000000) // HF clock is 16MHz
#define LFCLK           (32768)    // LF clock is 32KHz

unsigned int uart = 0;


int setup_uart(int port, int baudrate)
{
    unsigned int iof;
    switch (port) {
        case 0:
            uart = UART0BASE;
            iof = IOF_UART0_RX | IOF_UART0_TX;
            break;
        case 1:
            uart = UART1BASE;
            iof = IOF_UART1_RX | IOF_UART1_TX;
            break;
        default:
            return -1;
    }

    unsigned int ra;
    ra = get32(GPIO_IOF_SEL);
    ra &= ~iof;
    put32(GPIO_IOF_SEL, ra);

    ra = get32(GPIO_IOF_EN);
    ra |= iof;
    put32(GPIO_IOF_EN, ra);

    unsigned div = HFCLK/baudrate - 1;
    put32(uart + UART_DIV, div);

    put32(uart + UART_TXCTRL, TXCTRL_NSTOP | TXCTRL_TXEN);

    return 0;
}

void putc(char c)
{
    /* wait if queue is full. */
    while (1) {
        if ((get32(uart + UART_TXDATA) & 0x80000000) == 0)
            break;
    }
    put32(uart + UART_TXDATA, c);
}

void puts(const char* s)
{
    do {
        putc(*s++);
    } while (*s != '\0');
}

int main(int argc, char* argv[])
{
    setup_uart(0, 115200);
    puts("hello world !!\r\n");
    return 0;
}

