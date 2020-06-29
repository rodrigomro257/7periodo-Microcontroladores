#include <xc.h>
#include <adc.h>
#include <p18f4550.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xlcd.h>
#include <delays.h>
#include <plib/usart.h>

#pragma CONFIG WDT=OFF
#define _XTAL_FREQ 12000000
#define TEMPO TMR0
#define HAB_INTERRUPCAO INTCONbits.TMR0IE
#define POLY 0x8408

void limpa();
void enviaByte(unsigned char);
void tx_data();
unsigned char rx_data(void);
unsigned char serial_data;
unsigned int i = 0;

#define IDLE 0
#define VERIFICACRC 1
#define COMRECEBIDO 2
#define ENVIARESPOSTA 3
#define ENVIAACK 4
#define ENVIANACK 5	

#define ALTERACAO '2'
#define LEITURA '1'

#define ACK 	0x05
#define NACK 	0x15

#define FREQ 12000000    // Frequency = 12MHz
#define baud 9600
#define spbrg_value (((FREQ/64)/baud)-1)    // Refer to the formula for Baud rate calculation in Description tab

unsigned char BUFFCOM[7], BUFFRESP[7];
char estado = IDLE;
char versao = 1;
char revisao = 2;

char buf1[8];
char buf2[8];
char buf3[8];
char buf4[8];

float voltage=0; 
unsigned int ADCResult = 0;
float voltage;

char estado_relogio = 1;
int hora = 23, minuto = 59, segundo = 40;
int dia = 28, mes = 2, ano = 18;
int tempo_1 = 53800;
int flag = 0;
char num_flag = 0;
unsigned int contador = 0;
int dias_ano[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int seg_desp = 0, min_desp = 0, hor_desp = 0;

/*
 void init_ADC(void)        //Configure ADC with 3 analog channels{
    OpenADC(ADC_FOSC_64 & ADC_RIGHT_JUST & ADC_12_TAD, ADC_CH0 & ADC_INT_OFF & ADC_REF_VDD_VSS,ADC_1ANA);   
}*/

unsigned short calculaCRCBUFFRESP(char *data_p, unsigned short length) {
    unsigned char f;
    unsigned int data;
    unsigned int crc = 0xffff;

    if (length == 0)return (~crc);

    do {
        for (f = 0, data = (unsigned int) 0xff & *data_p++;
                f < 8;
                f++, data >>= 1) {
            if ((crc & 0x0001) ^ (data & 0x0001))
                crc = (crc >> 1) ^ POLY;
            else crc >>= 1;
        }
    } while (--length);

    crc = ~crc;
    data = crc;
    
    estado = ENVIARESPOSTA;
    
    BUFFRESP[5] = crc >> 8;
    BUFFRESP[6] = crc & 0x00FF;
    
    return (crc);
}

int calculaCRCBUFFCOM(char *data_p, unsigned short length) {
    unsigned char f;
    unsigned int data;
    unsigned int crc = 0xffff;

    if (length == 0)return (~crc);

    do {
        for (f = 0, data = (unsigned int) 0xff & *data_p++;
                f < 8;
                f++, data >>= 1) {
            if ((crc & 0x0001) ^ (data & 0x0001))
                crc = (crc >> 1) ^ POLY;
            else crc >>= 1;
        }
    } while (--length);

    crc = ~crc;
    data = crc;

    if(BUFFCOM[5] == (crc >> 8) && BUFFCOM[6] == (crc & 0x00FF)) return 1;
    else return 0;
}


void interrupt low_priority pic_isr(void) {
    if (TMR0IF) {
        TEMPO = tempo_1;
        INTCONbits.TMR0IF = 0;
        flag = 1;
    }

    if (PIR1bits.RCIF == 1) {
        while (!RCIF); // Wait until RCIF gets low
        BUFFCOM[i] = RCREG; // Retrieve data from reception register
        i++;

        if (i > 6) {
            PIR1bits.RCIF = 0; // clear rx flag
            i = 0;
            estado = VERIFICACRC;
        }
    }
}

void trataComando() {
    //verifica se e comando de leitura ou alteracao	
    switch (BUFFCOM[0]) {
        case LEITURA:
            BUFFRESP[0] = BUFFCOM[0];
            BUFFRESP[1] = BUFFCOM[1];

            // verifica o que deve ser lido
            switch (BUFFCOM[1]) {
                    //leitura de versao e revisao
                case '0':
                    BUFFRESP[2] = versao;
                    BUFFRESP[3] = revisao;
                    BUFFRESP[4] = 0xFF;
                    break;

                case '1':
                    BUFFRESP[2] = hora;
                    BUFFRESP[3] = minuto;
                    BUFFRESP[4] = segundo;
                    break;

                case '2':
                    BUFFRESP[2] = dia;
                    BUFFRESP[3] = mes;
                    BUFFRESP[4] = ano;
                    break;

                case '3':
                    BUFFRESP[2] = hor_desp;
                    BUFFRESP[3] = min_desp;
                    BUFFRESP[4] = seg_desp;
                    break;

                default:
                    break;
            }
            break;

        case ALTERACAO:
            BUFFRESP[0] = BUFFCOM[0];
            BUFFRESP[1] = BUFFCOM[1];
            BUFFRESP[2] = BUFFCOM[2];
            BUFFRESP[3] = BUFFCOM[3];
            BUFFRESP[4] = BUFFCOM[4];

            switch (BUFFCOM[1]) {
                case '0':
                    limpa();
                    versao = BUFFCOM[2];
                    versao = versao - 48;
                    revisao = BUFFCOM[3];
                    revisao = revisao - 48;
                    break;

                case '1':
                    limpa();
                    hora = BUFFCOM[2];
                    hora = hora - 48;

                    minuto = BUFFCOM[3];
                    minuto = minuto - 48;

                    segundo = BUFFCOM[4];
                    segundo = segundo - 48;

                    break;

                case '2':
                    limpa();
                    dia = BUFFCOM[2];
                    dia = dia - 48;

                    mes = BUFFCOM[3];
                    mes = mes - 48;

                    ano = BUFFCOM[4];
                    ano = ano - 48;
                    break;

                case '3':
                    limpa();
                    hor_desp = BUFFCOM[2];
                    hor_desp = hor_desp - 48;

                    min_desp = BUFFCOM[3];
                    min_desp = min_desp - 48;

                    seg_desp = BUFFCOM[4];
                    seg_desp = seg_desp - 48;

                    break;

                default:
                    break;
            }
            break;
    }
    
    calculaCRCBUFFRESP(&BUFFRESP[0],5);
}

void verificaCRCBUFFCOM() {
    char CRC_OK;
    CRC_OK = calculaCRCBUFFCOM(&BUFFCOM[0],5); 
            
    if (CRC_OK == 1) {estado = ENVIAACK;}
    else {estado = ENVIANACK;}
}

void maquinaEstado() {
    switch (estado) {
        case VERIFICACRC:
            verificaCRCBUFFCOM();
            break;

        case COMRECEBIDO:
            trataComando();
            break;

        case ENVIARESPOSTA:
            tx_data();
            break;

        case ENVIAACK:
            enviaByte(ACK);
            break;

        case ENVIANACK:
            enviaByte(NACK);
            break;

        default:
            break;
    }
}

void init_XLCD(void) {
    OpenXLCD(FOUR_BIT & LINES_5X7);
    while (BusyXLCD());

    WriteCmdXLCD(0x06);
    WriteCmdXLCD(0x0C);
}

void limpa() {
    SetDDRamAddr(0x00);
    putrsXLCD("                ");
    SetDDRamAddr(0x40);
    putrsXLCD("                ");
}

void tela1() {
    SetDDRamAddr(0x03);
    putrsXLCD("Despertador");

    sprintf(buf4, "ver:%d  rev:%d", versao,revisao);

    SetDDRamAddr(0x40);
    putrsXLCD(buf4);
}

void tela2() {
    SetDDRamAddr(0x00);
    putrsXLCD("Hora: ");
    sprintf(buf1, "%d:%d:%d", hora, minuto, segundo);
    putrsXLCD(buf1);

    SetDDRamAddr(0x40);
    putrsXLCD("Data: ");
    sprintf(buf2, "%d/%d/%d", dia, mes, ano);
    putrsXLCD(buf2);
}

void tela3() {
    //limpa();
    SetDDRamAddr(0x05);
    putrsXLCD("Alarme");
    SetDDRamAddr(0x44);
    sprintf(buf3, "%d:%d:%d", hor_desp, min_desp, seg_desp);
    putrsXLCD(buf3);
}

void push_botton(int porta) {
    __delay_ms(170);
    while (1) {
        if (porta)break;
    }
}

void push_botton_alarme(int porta) {
    __delay_ms(255);
    while (1) {
        if (porta)break;
    }
}

void troca_tela() {
    if (estado_relogio > 3) {
        estado_relogio = 1;
    }
    switch (estado_relogio) {
        case 1:
            tela1();
            break;
        case 2:
            tela2();
            break;
        case 3:
            tela3();
            break;
        default:
            break;
    }

}

void adicionaHoras() {
    segundo++;
    if (segundo > 59) {
        segundo = 0;
        minuto++;

        if (minuto > 59) {
            limpa();
            minuto = 0;
            hora++;

            if (hora > 23) {
                hora = 0;
                dia++;

                if (mes == 2 && ano % 4 == 0 || ano % 400 == 0 && !ano % 100 == 100) {
                    dias_ano[mes - 1] = 29;
                }

                if (dia > dias_ano[mes - 1]) {
                    dia = 1;
                    mes++;
                }
                if (mes > 11) {
                    mes = 1;
                    ano++;
                    dia = 1;
                }
            }
        }
    }
}

void adicionaHoraDesp() {
    min_desp++;
    if (min_desp > 59) {
        min_desp = 0;
        hor_desp++;

        if (hor_desp > 23) {
            hor_desp = 0;
        }
    }
}

void verificaDespertador() {
    if (min_desp == minuto && hor_desp == hora) {
        PORTAbits.AN0 = 1;
    } else {
        PORTAbits.AN0 = 0;
    }
}

void main(void) {
    SPBRG = spbrg_value;

    TRISCbits.RC6 = 0; //TX pin set as output
    TRISCbits.RC7 = 1; //RX pin set as input

    ADCON1 = 15;
    TRISAbits.RA1 = 1;
    TRISA = 1; 
    PORTAbits.AN1 = 0; 
    
    
    RCSTA = 0b10010000; // 0x90 (SPEN RX9 SREN CREN ADEN FERR OERR RX9D)
    TXSTA = 0b00100000; // 0x20 (CSRC TX9 TXEN SYNC - BRGH TRMT TX9D)

    INTCONbits.GIEL = 1;
    INTCONbits.GIEH = 1;

    //compare with the table above
    RCIF = 0; //reset RX pin flag
    RCIP = 0; //Not high priority
    RCIE = 1; //Enable RX interrupt
    PEIE = 1; //Enable pheripheral interrupt (serial port is a pheripheral)

    TRISCbits.RC0 = 1;
    TRISCbits.RC1 = 1;
    init_XLCD();

    tela1();

    ADCON1 = 0x0F;
    TRISAbits.RA0 = 0;
    TRISB = 0x00;

    T0CONbits.TMR0ON = 0;

    HAB_INTERRUPCAO = 1;
    INTCONbits.TMR0IF = 0;

    T0CONbits.T08BIT = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS0 = 1;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS2 = 1;
    T0CONbits.T0CS = 0;

    TMR0 = 65532;

    T0CONbits.TMR0ON = 1;

    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;

    while (1) {
        maquinaEstado();
        if (PORTCbits.RC1) {
            adicionaHoraDesp();
            push_botton_alarme(PORTCbits.RC1);
        }

        if (flag) {
            adicionaHoras();
            flag = 0;
            verificaDespertador();
            troca_tela();
        }

        if (PORTCbits.RC0) {
            push_botton(PORTCbits.RC0);
            estado_relogio++;
            limpa();
            troca_tela();
        }

    }
    return;
}

void DelayFor18TCY(void) {
    Delay10TCYx(120);
}

void DelayPORXLCD(void) {
    Delay1KTCYx(180);
    return;
}

void DelayXLCD(void) {
    Delay1KTCYx(60);
    return;
}

void enviaByte(char BYTE) {
    while (!TXIF); // Wait until RCIF gets low
    TXREG = BYTE;

    if (BYTE == ACK)
        estado = COMRECEBIDO;
    else
        estado = IDLE;
}

void tx_data() {
    int cont;
    while (!TXIF);

    for (cont = 0; cont < 7; cont++) {
        while (!TXIF);
        TXREG = BUFFRESP[cont];
    }
    estado = IDLE;
}
