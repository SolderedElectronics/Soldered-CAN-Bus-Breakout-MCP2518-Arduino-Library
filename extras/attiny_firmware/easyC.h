#ifndef __EASYC_FIRMWARE__
#define __EASYC_FIRMWARE__

// IO port bank A defines
#define PA0 11
#define PA1 8
#define PA2 9
#define PA3 10
#define PA4 0
#define PA5 1
#define PA6 2
#define PA7 3 // USED BY DEFAULT

// IO port bank B defines
#define PB0 7
#define PB1 6
#define PB2 5 // USED BY DEFAULT
#define PB3 4 // USED BY DEFAULT

// Pins always used for address
#define ADDRESS_PIN1 5
#define ADDRESS_PIN2 4
#define ADDRESS_PIN3 3

// Default address always used by easyC
#define DEFAULT_ADDRESS 0x30

void initDefault()
{
    // Initialize default pins
    pinMode(ADDRESS_PIN1, INPUT_PULLUP);
    pinMode(ADDRESS_PIN2, INPUT_PULLUP);
    pinMode(ADDRESS_PIN3, INPUT_PULLUP);
}

char getI2CAddress()
{
    // Inverted values cause hardware is setup that way
    char addrPin1 = !digitalRead(ADDRESS_PIN1);
    char addrPin2 = !digitalRead(ADDRESS_PIN2);
    char addrPin3 = !digitalRead(ADDRESS_PIN3);

    // Default address if all pins are on off position
    char address = DEFAULT_ADDRESS;
    address |= (addrPin1 << 0) | (addrPin2 << 1) | (addrPin3 << 2);

    return address;
}

#endif
