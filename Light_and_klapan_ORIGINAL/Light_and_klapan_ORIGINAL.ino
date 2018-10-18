#include "DHT.h"



// *************************************** ������ �������� *****************************
/*
 * �������� ������ 
    1)  �������� ������� �� ����� ������ ��������\��������� ��������������� ����
    2) ���������� ������� �� ����� ������ ��������� ��� ������ �����
    3) ���������� (3 ���) ������������� ������� �� 1 � 4 ������ �������� \ ��������� �������������� ����� ������ ������� ��������
    � ��� ��������������� ������� ���������, ���������� ���������� �����������
    4) ������� �� 2 � 3 ������ �� ��� ������� �������� \��������� ������ ������� � ��� ������, ���� ���� ����� ������ ��������
*/
// � ������ ���� ��������� ���������� ������� ������� DHT
#define DHTPIN 2     
// ������������ ����������� �� ������� ������ ����� ����������� � ������ ����
//����� �� ��������� � ������ � ����� ������ �����
#define MAXTEMPERATURE 26.00

// ��� ������� �����������, ����������������� ������ �� ���� �����
#define DHTTYPE DHT11   
//#define DHTTYPE DHT22   
//#define DHTTYPE DHT21   

// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// ���������, � ����� ����� ����� ���������� ������
// �� ������������ ���� �6, �7
//������ ������������ ����� ������ � ���� �������, ������ � Gnd
#define BUTTON1 A1 // ������ ��������� ����� �1
#define BUTTON2 A2 // ������ ��������� ����� �2
#define BUTTON3 A3 // ������ ��������� ����� �3
#define BUTTON4 A4 // ������ ��������� ������������ ���������

//��������� ����� ������

#define BUTTON5 A1 //���������  ���� � ����� �������: ������ ��� ������ 1
#define BUTTON6 A1 //���������  ���� � ����� �������: ������ ��� ������ 2
#define BUTTON7 A1 // ���� ��� �������� 1 
#define BUTTON8 A1 // ���� ��� �������� 2
#define BUTTON9 A1 // ���� ��� �������� 1 
#define BUTTON10 A1
#define BUTTON11 A1
#define BUTTON12 A1

// � ����������� �� ���� ������, ���� ��� ������� ������������ ������, 
//������������ � GND, �� ������������� ACTIVE 0 
// ���� ����������� ������, �������� ACTIVE 1
#define ACTIVE 0

//��������� � ����� ����� ����� ���������� ���� ��� ����
#define LAMP1 3
#define LAMP2 4
#define LAMP3 5
#define RGBWSTRIP 7



// ��� ���������� ����
// ���� ���������� �����, �������� ��� ����, ���� ���������� ��������, �������� 1 � 0 �������
// ����� ��������� ��� ��� ��������� ����������� ���������, ��� ������ ��������� ����� ������������
// ��� ����� ������ ���� ���������, � ��� ��������� ����������� - ���������
#define RELAY_ON 0
#define RELAY_OFF 1 

// ��� ������� ����
#define KLAPAN 8

//� ����� ����� ����� ���������� ���������� ��������� ������������
// � ����� ������� ���� ��������� ���������� ������ � ����� 3, 5, 6, 9, 10 � 11
// ��������� ������������ ����� ����� (����) � ���� �������, ������ ����� (�����) ����� �������� 150-1000 ��  � Gnd
#define LEDLAMP1 6
#define LEDLAMP2 9
#define LEDLAMP3 10
#define LEDRGBWSTRIP 11

//


// ��� ������ � ������� ���������� ��������� ������������������
//#define DEBUG
// *************************************** ����� �������� *****************************

DHT dht(DHTPIN, DHTTYPE);

bool statelamp1 = 0;//��������� 1
bool statelamp2 = 0;//��������� 2
bool statelamp3 = 0;//��������� ��������� + ������
bool statergbwstrip = 0;// ������������ ����� RGBW (��������)

 
bool stateklapan = 0; // ��������� ������ ������� \ �������
bool klapanmode = 0; // ��������� ������ ������ �������. 0 - ������ �����, 1 - ���� ����� �� ������� �����������

//����� ������� (� ����������� ���������� ������ � ������� ���� �����)
bool statenightlight1 = 0; // ������ ��� ������ 1
bool statenightlight2 = 0; // ������ ��� ������ 2


// ����� ������� (� ������ �� ��� � ���� + �������� ����� ������ �� ���� � ������� = ���� ���!)
bool statecornice = 0; // ��������� �������
bool statetheatrelight1 = 0; // ���� ��� �������� 1 
bool statetheatrelight2 = 0; // ���� ��� �������� 2
bool statetheatrelight3 = 0; // ���� ��� �������� 3
bool statetheatrelight4 = 0; // ���� ��� �������� 4
bool stateuvlight =0; // ���������������� �����
bool statelightmusic = 0; //�����������
bool statergbwstrip2 = 0;// ������������ ����� RGBW (������)
bool staterezerv = 0;// ������

byte autoBut = 0; // ������� ��������� ���� 4  ������ 
byte autoButprev  = 0; // ��� �������
unsigned long ms =0, butMs = 0;
// ������� ������ ������� ( ����������) ��� ��� ���� ������
byte butcount = 0;

byte autoKlapan = 0; // ������� ��������� �������. ����������� �� �������� ������
unsigned long klapanMs = 0;
void setup() {
  Serial.begin(115200);
  dht.begin();
pinMode(BUTTON1, INPUT_PULLUP);
pinMode(BUTTON2, INPUT_PULLUP);
pinMode(BUTTON3, INPUT_PULLUP);
pinMode(BUTTON4, INPUT_PULLUP);
pinMode(LAMP1, OUTPUT);
pinMode(LAMP2, OUTPUT);
pinMode(LAMP3, OUTPUT);
pinMode(RGBWSTRIP, OUTPUT);
pinMode(LEDLAMP1, OUTPUT);
pinMode(LEDLAMP2, OUTPUT);
pinMode(LEDLAMP3, OUTPUT);
pinMode(LEDRGBWSTRIP, OUTPUT);
pinMode(KLAPAN, OUTPUT);
digitalWrite(KLAPAN , RELAY_OFF);
makelamps(); // ������� ����� � ��������� ��� ����
}//setup

void loop() {

ms = millis();
autoButfunc(); // ����� ������ � ������ �����
autoKlapanfunc(); // ������ �������

}//loop