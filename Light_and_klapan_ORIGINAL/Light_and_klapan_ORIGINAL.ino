#include "DHT.h"



// *************************************** Начало настроек *****************************
/*
 * Алгоритм работы 
    1)  Короткое нажатие на любую кнопку включает\выключает соответствующий свет
    2) Длительное нажатие на любую кнопку выключает все группы света
    3) Длительное (3 сек) одновременное нажатие на 1 и 4 кнопки включает \ отключает автоматический режим работы клапана обогрева
    о чем свидетельствует плавное включение, выключение сигнальных светодиодов
    4) нажатие на 2 и 3 кнопки на пол секунды включает \выключает клапан вручную в том случае, если авто режим работы отключен
*/
// к какому пину подключен сигнальный контакт датчика DHT
#define DHTPIN 2     
// максимальная температура на которой клапан будет отключаться в режиме авто
//важно ее указывать с точкой и двумя нулями после
#define MAXTEMPERATURE 26.00

// тип датчика температуры, раскомментировать нужную из трех строк
#define DHTTYPE DHT11   
//#define DHTTYPE DHT22   
//#define DHTTYPE DHT21   

// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// указываем, к каким пинам будут подключены кнопки
// не использовать пины А6, А7
//кнопка подключается одним концом к пину ардуино, другим к Gnd
#define BUTTON1 A1 // кнопка включения лампы №1
#define BUTTON2 A2 // кнопка включения лампы №2
#define BUTTON3 A3 // кнопка включения лампы №3
#define BUTTON4 A4 // кнопка включения светодиодной подсветки

//Добавляем новые кнопки

#define BUTTON5 A1 //Присвоить  ПИНЫ к новым кнопкам: Ночник для чтения 1
#define BUTTON6 A1 //Присвоить  ПИНЫ к новым кнопкам: Ночник для чтения 2
#define BUTTON7 A1 // Зона над подиумом 1 
#define BUTTON8 A1 // Зона над подиумом 2
#define BUTTON9 A1 // Зона над подиумом 1 
#define BUTTON10 A1
#define BUTTON11 A1
#define BUTTON12 A1

// в зависимости от типа кнопки, если это обычная механическая кнопка, 
//подключенная к GND, то устанавливаем ACTIVE 0 
// если электронная кнопка, возможно ACTIVE 1
#define ACTIVE 0

//указываем к каким пинам будут подключены реле для ламп
#define LAMP1 3
#define LAMP2 4
#define LAMP3 5
#define RGBWSTRIP 7



// тип управления реле
// если включается нулем, оставить как есть, если включается единицей, поменять 1 и 0 местами
// чтобы убедиться что эти параметры установлены правильно, при первом включении после перепрошивки
// все лампы должны быть выключены, а все подсветки включателей - светиться
#define RELAY_ON 0
#define RELAY_OFF 1 

// пин клапана воды
#define KLAPAN 8

//к каким пинам будут подключены светодиоды подсветки включаетелей
// к плате ардуино нано допустимо подключать только к пинам 3, 5, 6, 9, 10 и 11
// светодиод подключается одной ногой (анод) к пину ардуино, второй ногой (катод) через резистор 150-1000 Ом  к Gnd
#define LEDLAMP1 6
#define LEDLAMP2 9
#define LEDLAMP3 10
#define LEDRGBWSTRIP 11

//


// для вывода в консоль отладочных сообщений расскомментировать
//#define DEBUG
// *************************************** конец настроек *****************************

DHT dht(DHTPIN, DHTTYPE);

bool statelamp1 = 0;//Освещение 1
bool statelamp2 = 0;//Освещение 2
bool statelamp3 = 0;//Освещение периметра + карниз
bool statergbwstrip = 0;// светодиодная лента RGBW (периметр)

 
bool stateklapan = 0; // состояние клапан открыто \ закрыто
bool klapanmode = 0; // состояние режима работы клапана. 0 - ручной режим, 1 - авто режим от датчика температуры

//Новые приборы (с аналогичным алгоритмом работы с которые были ранее)
bool statenightlight1 = 0; // Ночник для чтения 1
bool statenightlight2 = 0; // Ночник для чтения 2


// Новые приборы (с только на вкл и выкл + наджатие любой кнопки из всех в проекте = выкл все!)
bool statecornice = 0; // освещение карниза
bool statetheatrelight1 = 0; // Зона над подиумом 1 
bool statetheatrelight2 = 0; // Зона над подиумом 2
bool statetheatrelight3 = 0; // Зона над подиумом 3
bool statetheatrelight4 = 0; // Зона над подиумом 4
bool stateuvlight =0; // Ультрафиолетовая лампа
bool statelightmusic = 0; //Светомузыка
bool statergbwstrip2 = 0;// светодиодная лента RGBW (подиум)
bool staterezerv = 0;// резерв

byte autoBut = 0; // автомат обработки всех 4  кнопок 
byte autoButprev  = 0; // для отладки
unsigned long ms =0, butMs = 0;
// счетчик верных нажатий ( отпусканий) той или иной кнопки
byte butcount = 0;

byte autoKlapan = 0; // автомат обработки клапона. управляется из автомата кнопок
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
makelamps(); // включим лампы и подсветку как надо
}//setup

void loop() {

ms = millis();
autoButfunc(); // опрос кнопок и работа света
autoKlapanfunc(); // работа клапана

}//loop