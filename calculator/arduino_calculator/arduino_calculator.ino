#include <LiquidCrystal.h>
#include <Keypad.h>

// lcd
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] =
{
    {'1', '2', '3', '+'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', '*'},
    {'q', '0', '=', '/'}
};
byte rowPins[ROWS] = {52, 51, 48, 47}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {44, 43, 40, 39}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// global calculator variables
const unsigned int DISPLAY_SIZE = 15;
char display[DISPLAY_SIZE];
long long buffer;
char oper;
void show_display(void);
void clear_display(void);
void handle(char c);
long long display_to_number(void);
void buffer_to_display(void);




void setup()
{
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("calculator");

    Serial.begin(9600);

    oper = 'x';
    buffer = 0;

    clear_display();
    show_display();

}

void loop()
{


    char customKey = customKeypad.getKey();

    if (customKey)
    {
        Serial.println(customKey);
        handle(customKey);
    }

}



void show_display(void)
{
    for(int i = 0; i < DISPLAY_SIZE; i++)
    {
        lcd.setCursor(i, 0);
        // printf("%c", display[i]);
        lcd.print(display[i]);
    }
    // printf("(%c)", oper);
};

void clear_display(void)
{
    for(int i = 0; i < DISPLAY_SIZE; i++)
    {
        display[i] = ' ';
    }
};

void handle(char c)
{

    switch (c)
    {
    case '+':
        c = oper;
        oper = '+';
        break;
    case '-':
        c = oper;
        oper = '-';
        break;
    case '*':
        c = oper;
        oper = '*';
        break;
    case '/':
        c = oper;
        oper = '/';
        break;
    case '=':
        c = oper;
        oper = 'x';
        break;
    }

    switch (c)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        for(int i = 0; i < DISPLAY_SIZE - 1; i++)
        {
            display[i] = display[i + 1];
        }
        display[DISPLAY_SIZE - 1] = c;
        show_display();

        break;
    case 'x':
        buffer = display_to_number();
        clear_display();
        break;
    case '+':
        buffer += display_to_number();
        buffer_to_display();
        clear_display();
        break;
    case '-':
        buffer -= display_to_number();
        buffer_to_display();
        clear_display();
        break;
    case '*':
        buffer *= display_to_number();
        buffer_to_display();
        clear_display();
        break;
    case '/':
        if(display_to_number() != 0)
        {
            buffer /= display_to_number();
            buffer_to_display();
            clear_display();
        }
        break;
    case '=':
        buffer_to_display();
        buffer = 0;
        clear_display();
        break;
    default:
        show_display();
        break;
    }
};

long long display_to_number(void)
{
    long long ret = 0;
    long long multi = 1;
    for(int i = DISPLAY_SIZE - 1; i >= 0 ; i--, multi *= 10)
    {
        if( display[i] < '0' || display[i] > '9') continue;
        ret += multi * (display[i] - '0');
    }

    return ret;
};

void buffer_to_display(void)
{
    long long buff = buffer;
    for(int i = DISPLAY_SIZE - 1; i >= 0 ; i--)
    {
        display[i] = buff % 10 + '0';
        buff /= 10;
    }

    // clear the leading zeros
    for(int i = 0; i < DISPLAY_SIZE - 1; i++)
    {
        if(display[i] == '0')
            display[i] = ' ';
        else
            break;
    }

    show_display();
};
