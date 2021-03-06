/* TEST for Git (upd2) */

#include "DHT.h" //подключаем библ. датчка Т.



// *************************************** Начало настроек *****************************
/*
   Алгоритм работы
    1)  Короткое нажатие на любую кнопку включает\выключает соответствующий свет
    2) Длительное нажатие на любую кнопку выключает все группы света
    3) Длительное (3 сек) одновременное нажатие на 1 и 4 кнопки включает \ отключает автоматический режим работы клапана обогрева
    о чем свидетельствует плавное включение, выключение сигнальных светодиодов
    4) нажатие на 2 и 3 кнопки на пол секунды включает \выключает клапан вручную в том случае, если авто режим работы отключен
*/
// к какому пину подключен сигнальный контакт датчика DHT
#define DHTPIN 22       // Датчик температуры     
// максимальная температура на которой клапан будет отключаться в режиме авто
//важно ее указывать с точкой и двумя нулями после


#define MAXTEMPERATURE 22.00 // Возможно ли вывести значение температуры (без меню) на простейший однострочный дисплей 
//и добавить возможность корректировки MAXTEMPERATURE?

// тип датчика температуры, раскомментировать нужную из трех строк
#define DHTTYPE DHT22     // тип датчика.   
//#define DHTTYPE DHT22
//#define DHTTYPE DHT21

// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor


/*КНОПКИ. КНОПКИ. КНОПКИ.  КНОПКИ. КНОПКИ. КНОПКИ. КНОПКИ. КНОПКИ. КНОПКИ. КНОПКИ. КНОПКИ. КНОПКИ. КНОПКИ. КНОПКИ. КНОПКИ. КНОПКИ. КНОПКИ. КНОПКИ. КНОПКИ.*/

//кнопка подключается одним концом к пину ардуино, другим к Gnd
#define BUTTON1 22        /* кнопка включения лампы №1. Освещение 1 */
#define BUTTON2 24        /* кнопка включения лампы №2. Освещение 2 */
#define BUTTON3 26        /* кнопка включения лампы №3. Освещение периметра */
#define BUTTON4 28        /* кнопка включения светодиодной подсветки. Cветодиодная лента RGBW (периметр) */

/*Добавляем новые кнопки*/
#define BUTTON5 30        /* Кнопка: Ночник для чтения 1 */
#define BUTTON6 32        /* Кнопка: Ночник для чтения 2 */
#define BUTTON7 34        /* Кнопка: Зона над подиумом 1 */    
#define BUTTON8 36        /* Кнопка: Зона над подиумом 2 */
#define BUTTON9 38        /* Кнопка: Зона над подиумом 3 */
#define BUTTON10 40       /* Кнопка: Зона над подиумом 4 */
#define BUTTON11 42       /* Кнопка: Зона над подиумом 2 */
#define BUTTON12 44       /* Кнопка: Ультрафиолетовая лампа */
#define BUTTON13 46       /* Кнопка: Светомузыка */
#define BUTTON14 48       /* Кнопка: Cветодиодная лента RGBW (подиум) */
#define BUTTON15 50       /* Кнопка: Резерв - пока кнопка отключена */


// в зависимости от типа кнопки, если это обычная механическая кнопка,
//подключенная к GND, то устанавливаем ACTIVE 0
// если электронная кнопка, возможно ACTIVE 1
#define ACTIVE 0// Оставляем 0


/* РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ.РЕЛЕ. РЕЛЕ. */

//указываем к каким пинам будут подключены реле
#define LAMP1 23           /* Реле. Освещение 1*/
#define LAMP2 25           /* Реле. Освещение 2*/
#define LAMP3 27           /* Реле. Освещение периметра*/
#define RGBWSTRIP 29       /* Реле. Cветодиодная лента RGBW (периметр)*/

/* Новые реле:*/
#define nightlight1 31     /* Реле. Ночник для чтения 1 */
#define nightlight2 33     /* Реле. Ночник для чтения 2 */
#define cornice 35         /* Реле. Освещение карниза */
#define theatrelight1 37   /* Реле. Зона над подиумом 1 */ 
#define theatrelight2 39   /* Реле. Зона над подиумом 1 */
#define theatrelight3 41   /* Реле. Зона над подиумом 1 */
#define theatrelight4 43   /* Реле. Зона над подиумом 1 */
#define uvlight 45         /* Реле. Ультрафиолетовая лампа */
#define lightmusic 47      /* Реле. Светомузыка*/
#define rgbwstrip2 49      /* Реле. Cветодиодная лента RGBW (подиум) */
#define rezerv 51          /* Реле. Резерв */ 


// тип управления реле
// если включается нулем, оставить как есть, если включается единицей, поменять 1 и 0 местами
// чтобы убедиться что эти параметры установлены правильно, при первом включении после перепрошивки
// все лампы должны быть выключены, а все подсветки включателей - светиться

/*Наш вариант:*/
#define RELAY_ON 0
#define RELAY_OFF 1

/* КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. КЛАПАН. */

#define KLAPAN 22

/* СВЕТОДИОДЫ. СВЕТОДИОДЫ. СВЕТОДИОДЫ. СВЕТОДИОДЫ. СВЕТОДИОДЫ. СВЕТОДИОДЫ. СВЕТОДИОДЫ. СВЕТОДИОДЫ. СВЕТОДИОДЫ. СВЕТОДИОДЫ. СВЕТОДИОДЫ. СВЕТОДИОДЫ.*/

//к каким пинам будут подключены светодиоды подсветки включаетелей

// светодиод подключается одной ногой (анод) к пину ардуино, второй ногой (катод) через резистор 150-1000 Ом  к Gnd
#define LEDLAMP1 2         /* Светодиод состояния: Освещение 1 */
#define LEDLAMP2 3         /* Светодиод состояния: Освещение 2 */
#define LEDLAMP3 4         /* Светодиод состояния: Освещение периметра */
#define LEDRGBWSTRIP 5     /* Светодиод состояния: СостояниеCветодиодная лента RGBW (периметр) */

/* Новые светодиоды (состояния)*/

#define LEDKLAPAN 23

/* Новые светодиоды (состояния) - пока отключил из-за экономии пинов*/


/*#define LEDnightlight1 33  /* Светодиод состояния: Ночник для чтения 1
#define LEDnightlight2 35    // Светодиод состояния: Ночник для чтения 2
*/

/*#define LEDcornice 37        // Светодиод состояния: Освещение карниза

#define LEDtheatrelight1 39  // Светодиод состояния: Зона над подиумом 1 
#define LEDtheatrelight2 41  // Светодиод состояния: Зона над подиумом 2
#define LEDtheatrelight3 43  // Светодиод состояния: Зона над подиумом 3
#define LEDtheatrelight4 45  // Светодиод состояния: Зона над подиумом 4
#define LEDuvlight 47        // Светодиод состояния: Ультрафиолетовая лампа
#define LEDlightmusic 49     // Светодиод состояния: Светомузыка
#define LEDrgbwstrip2 51     // Светодиод состояния: Cветодиодная лента RGBW (подиум)
#define LEDrezerv 53         // Светодиод состояния: Резерв*/


// для вывода в консоль отладочных сообщений расскомментировать

/* убрать или поставить знаки комментариев, для начала отладки с выводом в порт. НЕ ЗАБЫТЬ УБАРТЬ (видимо чтобы не замедляло, уточнить)!!!*/

#define DEBUG
// *************************************** конец настроек *****************************

DHT dht(DHTPIN, DHTTYPE);

/* ПЕРЕМЕННАЯ СОСТОЯНИЯ РЕЛЕ. ПЕРЕМЕННАЯ СОСТОЯНИЯ РЕЛЕ. ПЕРЕМЕННАЯ СОСТОЯНИЯ РЕЛЕ. ПЕРЕМЕННАЯ СОСТОЯНИЯ РЕЛЕ. ПЕРЕМЕННАЯ СОСТОЯНИЯ РЕЛЕ.*/

bool statelamp1 = 0;         /* Состояние: Освещение 1*/
bool statelamp2 = 0;         /* Состояние: Освещение 2*/
bool statelamp3 = 0;         /* Состояние: Освещение периметра*/
bool statergbwstrip = 0;     /* Состояние: Cветодиодная лента RGBW (периметр)*/

bool stateklapan = 0;        /* Состояние: клапан открыто \ закрыто*/
bool klapanmode = 0;         /* Состояние режима работы клапана: 0 - ручной режим, 1 - авто режим от датчика температуры*/

//NEW. Состояние новых приборов (с аналогичным алгоритмом работы, как было ранее)
bool statenightlight1 = 0;   /* Состояние: Ночник для чтения 1*/
bool statenightlight2 = 0;   /* Состояние: Ночник для чтения 2*/

//NEW. Состояние новых приборов  (только на вкл и выкл + нажатие любой кнопки из всех в проекте = выкл все!)
bool statecornice = 0;       /* Состояние: Освещение карниза*/
bool statetheatrelight1 = 0; /* Состояние: Зона над подиумом 1*/
bool statetheatrelight2 = 0; /* Состояние: Зона над подиумом 2*/
bool statetheatrelight3 = 0; /* Состояние: Зона над подиумом 3*/
bool statetheatrelight4 = 0; /* Состояние: Зона над подиумом 4*/
bool stateuvlight = 0;       /* Ультрафиолетовая лампа*/
bool statelightmusic = 0;    /*Светомузыка*/
bool statergbwstrip2 = 0;    /* Cветодиодная лента RGBW (подиум)*/
bool staterezerv = 0;        /* Резерв*/



byte autoBut = 0;            // автомат обработки всех 4  кнопок
byte autoButprev  = 0;       // для отладки
unsigned long ms = 0, butMs = 0;
// счетчик верных нажатий ( отпусканий) той или иной кнопки
byte butcount = 0;

byte autoKlapan = 0; // автомат обработки клапана. управляется из автомата кнопок
unsigned long klapanMs = 0;

//SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP. SETUP.
void setup() {
  Serial.begin(115200);
  dht.begin();

  // РЕЖИМ РАБОТЫ ПИНОВ.РЕЖИМ РАБОТЫ ПИНОВ.РЕЖИМ РАБОТЫ ПИНОВ.РЕЖИМ РАБОТЫ ПИНОВ.РЕЖИМ РАБОТЫ ПИНОВ.РЕЖИМ РАБОТЫ ПИНОВ.РЕЖИМ РАБОТЫ ПИНОВ.РЕЖИМ РАБОТЫ ПИНОВ.

  // Кнопки:
  pinMode(BUTTON1, INPUT_PULLUP); /* Копка: Вход - Освещение 1 */
  pinMode(BUTTON2, INPUT_PULLUP); /* Копка: Вход  - Освещение 2 */
  pinMode(BUTTON3, INPUT_PULLUP); /* Копка: Вход  - Освещение периметра */
  pinMode(BUTTON4, INPUT_PULLUP); /* Копка: Вход  - Cветодиодная лента RGBW (периметр) */

  //Реле
  pinMode(LAMP1, OUTPUT);
  pinMode(LAMP2, OUTPUT);
  pinMode(LAMP3, OUTPUT);
  pinMode(RGBWSTRIP, OUTPUT);
  pinMode(LEDLAMP1, OUTPUT);
  pinMode(LEDLAMP2, OUTPUT);
  pinMode(LEDLAMP3, OUTPUT);
  pinMode(LEDRGBWSTRIP, OUTPUT);
  //Клапан
  pinMode(KLAPAN, OUTPUT);
  digitalWrite(KLAPAN , RELAY_OFF);

  // NEW. РЕЖИМ РАБОТЫ ПИНОВ.
  //Новые Кнопки:
  pinMode (BUTTON5, INPUT_PULLUP);    /* Копка: Вход - Ночник для чтения 1 */
  pinMode (BUTTON6, INPUT_PULLUP);    /* Копка: Вход - Ночник для чтения 2 */

  /* Тумблеры ВКЛ/ВЫКЛ. */

  pinMode (BUTTON7, INPUT);    /* Тумблер ВКЛ/ВЫКЛ: Вход - Зона над подиумом 1 */
  pinMode (BUTTON8, INPUT);    /* Тумблер ВКЛ/ВЫКЛ: Вход - Зона над подиумом 2 */
  pinMode (BUTTON9, INPUT);    /* Тумблер ВКЛ/ВЫКЛ: Вход - Зона над подиумом 3 */
  pinMode (BUTTON10, INPUT);   /* Тумблер ВКЛ/ВЫКЛ: Вход - Зона над подиумом 4 */
  pinMode (BUTTON11, INPUT);   /* Тумблер ВКЛ/ВЫКЛ: Вход - Зона над подиумом */
  pinMode (BUTTON12, INPUT);   /* Тумблер ВКЛ/ВЫКЛ: Вход - Ультрафиолетовая лампа */
  pinMode (BUTTON13, INPUT);   /* Тумблер ВКЛ/ВЫКЛ: Вход - Светомузыка */
  pinMode (BUTTON14, INPUT);   /* Тумблер ВКЛ/ВЫКЛ: Вход - Cветодиодная лента RGBW (подиум) */
  pinMode (BUTTON15, INPUT);   /* Тумблер ВКЛ/ВЫКЛ: Вход - Резерв */

  /*  Новые Реле:*/
  
  pinMode(nightlight1, OUTPUT);    /* Реле: Выход - Ночник для чтения 1 */
  pinMode(nightlight2, OUTPUT);    /* Реле: Выход - Ночник для чтения 2 */
  pinMode(cornice, OUTPUT);        /* Реле: Выход - Освещение карниза */
  pinMode(theatrelight1, OUTPUT);  /* Реле: Выход - Зона над подиумом 1 */
  pinMode(theatrelight2, OUTPUT);  /* Реле: Выход - Зона над подиумом 2 */
  pinMode(theatrelight3, OUTPUT);  /* Реле: Выход - Зона над подиумом 3 */
  pinMode(theatrelight4, OUTPUT);  /* Реле: Выход - Зона над подиумом 4 */
  pinMode(uvlight, OUTPUT);        /* Реле: Выход - Ультрафиолетовая лампа */
  pinMode(lightmusic, OUTPUT);     /* Реле: Выход - Светомузыка */
  pinMode(rgbwstrip2, OUTPUT);     /* Реле: Выход - Cветодиодная лента RGBW (подиум) */
  pinMode(rezerv, OUTPUT);         /* Реле: Выход - Резерв */


  makelamps(); /* Вызываем функцию makelamps (из последней вкладки, в самом низу */
 //включим лампы и подсветку как надо
}//setup

void loop() {

  ms = millis();
  autoButfunc(); // опрос кнопок и работа света
  autoKlapanfunc(); // работа клапана

}//loop
