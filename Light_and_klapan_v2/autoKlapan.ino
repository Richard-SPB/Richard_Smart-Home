/* тест синхронизации с Git */

void autoKlapanfunc() {
  switch (autoKlapan) {
    case 0:
      // init
      klapanMs = ms;
      autoKlapan = 10; //?
      break;

    case 5:
      // auto mode
      // если переключили в ручной режим, уходим
      if (!klapanmode) autoKlapan = 30; //GO
      if ((ms - klapanMs) > 5000) {
        klapanMs = ms;
        float t = dht.readTemperature();
        if (isnan(t)) return; // если ошибка чтения с датчика
        if (t > MAXTEMPERATURE) {
          digitalWrite(KLAPAN, RELAY_OFF);

          /* Добавил выкл. светодиод состояния*/
          digitalWrite(LEDKLAPAN, 0);

          stateklapan = 0;
#ifdef DEBUG
          Serial.print(" max is ");
          Serial.print(MAXTEMPERATURE);
          Serial.print(" *C. Now ");
          Serial.print(t);
          Serial.println(" *C. KLAPAN is off");
#endif
        } else if (t < MAXTEMPERATURE) {
          digitalWrite(KLAPAN, RELAY_ON);

          /* Добавил работающий светодиод состояния*/
          digitalWrite(LEDKLAPAN, 1);
          stateklapan = 1;
#ifdef DEBUG
          Serial.print(" max is ");
          Serial.print(MAXTEMPERATURE);
          Serial.print(" *C. Now ");
          Serial.print(t);
          Serial.println(" *C. KLAPAN is on");
#endif
        }
      }//if ms
      break;

    case 10:
      // manual mode
      if (klapanmode) autoKlapan = 40; // GO
      break;

    case 22:
      // отрисовка отключения клапана вручную
      //трижды мигаем, затухаем
      showKlapanState(255); //включаем подсветки
      delay(100);
      showKlapanState(0);
      delay(100);
      showKlapanState(255);
      delay(100);
      showKlapanState(0);
      delay(100);
      showKlapanState(255);
      delay(100);
      showKlapanState(0);
      delay(500);
      for (int i = 255; i > 0; i--) {
        showKlapanState(i);
        delay(3);
      }//for
      delay(200);
      makelamps();  // возвращаем подсветку на исходное
      stateklapan = 0;
      digitalWrite(KLAPAN, stateklapan);
      autoKlapan = 10; // GO
      break;

    case 24:
      // отрисовка ВКЛЮЧЕНИЯ клапана вручную
      showKlapanState(255); //включаем подсветки
      delay(100);
      showKlapanState(0);
      delay(100);
      showKlapanState(255);
      delay(100);
      showKlapanState(0);
      delay(100);
      showKlapanState(255);
      delay(100);
      showKlapanState(0);
      delay(500);
      for (int i = 0; i < 255; i++) {
        showKlapanState(i);
        delay(3);
      }//for
      delay(200);
      makelamps();  // возвращаем подсветку на исходное
      stateklapan = 1;
      digitalWrite(KLAPAN, stateklapan);
      autoKlapan = 10; // GO
      break;

    case 26:
      // отрисовка запрета на изм сост клапана
      showKlapanState(255); //включаем подсветки
      delay(300);
      showKlapanState(0);
      delay(100);
      showKlapanState(255);
      delay(100);
      showKlapanState(0);
      delay(100);
      makelamps();  // возвращаем подсветку на исходное
      autoKlapan = 5; // GO
      break;

    case 30:
      //transition from auto to manual
      showKlapanState(255); //включаем подсветки
      delay(500);
      for (int i = 255; i > 0; i--) {
        showKlapanState(i);
        delay(10);
      }//for
      delay(500);
      makelamps(); // вновь зажжем подсветку кнопок как должна быть
      autoKlapan = 10; //GO
#ifdef DEBUG
      Serial.println(" KLAPAN in manual mode");
#endif

      break;

    case 40:
      //transition from manual to auto
      // отрисовываем и меняем состояние
      showKlapanState(0); // тушим подсветки
      delay(500);
      for (int i = 0; i < 255; i++) {
        showKlapanState(i);
        delay(10);
      }//for
      delay(500);
      makelamps(); // вновь зажжем подсветку кнопок как должна быть
      autoKlapan = 5; //GO
#ifdef DEBUG
      Serial.println(" KLAPAN in auto mode");
#endif
      break;

  }//switch(autoKlapan){
}//void autoKlapanfunc()