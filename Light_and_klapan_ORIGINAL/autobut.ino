void autoButfunc(){
/* algorithm :
 *  3- если нажата какая либо кнопка 
 *  5- нажата 1. Если еще и 3 то 60- (действия по удержанию двух кнопок)
 *  10- если нажата 100*15 раз кнопка 1 то 50- (отключение всего света) сюда попадают из любой из 4х кнопок
 *  аналогично для других кнопок, опишу альтернативные состояния
 *  кнопка 1 \2 \3 \4
 *  состояния 5- \6- \7- \8-
 *  состояния 10- \20- \30- \40-
 *  далее 
 *  50 - отключение всего света и на 99-
 *  60- если нажата 1 и 4, 5 раз по 100 мс, инвертим режим работы клапана(авто, ручной) и идем на 99-
 *  80- если нажата 2 и 3, 2 раза по 100 мс, то если режим клапана ручной, инвертим состояние работы клапана и на 99-
 *  99- ожидание отпускания всех кнопок , сюда попадаем из кучи состояний , типа завершающее состояние и идем на новый цикл
 */ 
switch(autoBut){
  case 0:
  // инициализация автомата
  butMs = ms;
  butcount = 0;
  autoBut = 3; // GO
  break;
  case 3:
  if((ms - butMs) > 10){
    butMs = ms;
    if(digitalRead(BUTTON1) == ACTIVE){
      autoBut = 5; //GO
    } else if(digitalRead(BUTTON2) == ACTIVE){
      autoBut = 6; //GO
    } else if(digitalRead(BUTTON3) == ACTIVE){
      autoBut = 7; //GO
    } else if(digitalRead(BUTTON4) == ACTIVE){
      autoBut = 8; //GO
    }//if any Button
  }//if ms
  break;
  case 5:
  // кнопка 1 нажата? Если да, то если нажата еще и кнопка 4, идем на их взаимную обработку
  // пока кнопка 1 нажата, если больше 30*50 мс, то нажатие длительное - отключаем весь свет
  // если кнопку отпустили раньше чем 30*50, нажатие короткое - меняем состояние света 
  if((ms - butMs) > 30){
    butMs = ms;
    if(digitalRead(BUTTON1) == ACTIVE){
      if(digitalRead(BUTTON4) == ACTIVE){
        // нажаты 1 и 4, идем на их взаимную обработку
        butcount = 0;
        autoBut = 60; //GO 
        #ifdef DEBUG
        Serial.println("1 & 4 but noticed");
        #endif
      }// 1 & 4
      if(butcount < 50){
        butcount++;
      } else { // зафиксировано длительное удержание кнопки 
        // выключаем весь свет
        #ifdef DEBUG
        Serial.println("long 1 fixed");
        #endif
        statelamp1 = statelamp2 = statelamp3 = statergbwstrip = 0;
        makelamps(); //включим лампы и подсветку в новое состояние 
        butcount = 0;
        autoBut = 99; // GO на ожидание отпускания кнопок
      }
    } else { //BUT 1 released
      if (butcount){
        #ifdef DEBUG
        Serial.println("short 1 fixed");
        #endif
        butcount = 0;
        statelamp1 = !statelamp1; // инвертируем состояние света
        makelamps(); //включим лампы и подсветку в новое состояние 
      } 
      autoBut = 99; // GO на ожидание отпускания кнопок 
    }// no buttons pressed
  }//if ms
  break;
  case 6:
  // кнопка 2 нажата? Если да, то если нажата еще и кнопка 3, идем на их взаимную обработку
  // пока кнопка 2 нажата, если больше 30*50 мс, то нажатие длительное - отключаем весь свет
  // если кнопку отпустили раньше чем 30*50, нажатие короткое - меняем состояние света 
  if((ms - butMs) > 30){
    butMs = ms;
    if(digitalRead(BUTTON2) == ACTIVE){
      if(digitalRead(BUTTON3) == ACTIVE){
        // нажаты 2 и 3, идем на их взаимную обработку
        butcount = 0;
        autoBut = 80; //GO на попытку ручного переключения клапана
        #ifdef DEBUG
        Serial.println("2 & 3 but noticed");
        #endif
      }// 2 & 3
      if(butcount < 50){
        butcount++;
      } else { // зафиксировано длительное удержание кнопки 
        // выключаем весь свет
        #ifdef DEBUG
        Serial.println("long 2 fixed");
        #endif
        statelamp1 = statelamp2 = statelamp3 = statergbwstrip = 0;
        makelamps(); //включим лампы и подсветку в новое состояние 
        butcount = 0;
        autoBut = 99; // GO на ожидание отпускания кнопок
      }
    } else { //BUT 2 released
      if (butcount){
        #ifdef DEBUG
        Serial.println("short 2 fixed");
        #endif
        butcount = 0;
        statelamp2 = !statelamp2; // инвертируем состояние света
        makelamps(); //включим лампы и подсветку в новое состояние 
      } 
      autoBut = 99; // GO на ожидание отпускания кнопок 
    }// no buttons pressed
  }//if ms
  break;
  case 7:
  // кнопка 3 нажата? Если да, то если нажата еще и кнопка 2, идем на их взаимную обработку
  // пока кнопка 2 нажата, если больше 30*50 мс, то нажатие длительное - отключаем весь свет
  // если кнопку отпустили раньше чем 30*50, нажатие короткое - меняем состояние света 
  if((ms - butMs) > 30){
    butMs = ms;
    if(digitalRead(BUTTON3) == ACTIVE){
      if(digitalRead(BUTTON2) == ACTIVE){
        // нажаты 3 и 2, идем на их взаимную обработку
        butcount = 0;
        autoBut = 80; //GO на попытку ручного переключения клапана
        #ifdef DEBUG
        Serial.println("3 & 2 but noticed");
        #endif
      }// 3 & 2
      if(butcount < 50){
        butcount++;
      } else { // зафиксировано длительное удержание кнопки 
        // выключаем весь свет
        #ifdef DEBUG
        Serial.println("long 3 fixed");
        #endif
        statelamp1 = statelamp2 = statelamp3 = statergbwstrip = 0;
        makelamps(); //включим лампы и подсветку в новое состояние 
        butcount = 0;
        autoBut = 99; // GO на ожидание отпускания кнопок
      }
    } else { //BUT 2 released
      if (butcount){
        #ifdef DEBUG
        Serial.println("short 3 fixed");
        #endif
        butcount = 0;
        statelamp3 = !statelamp3; // инвертируем состояние света
        makelamps(); //включим лампы и подсветку в новое состояние 
      } 
      autoBut = 99; // GO на ожидание отпускания кнопок 
    }// no buttons pressed
  }//if ms
  break;
  case 8:
  // кнопка 4 нажата? Если да, то если нажата еще и кнопка 1, идем на их взаимную обработку
  // пока кнопка 4 нажата, если больше 30*50 мс, то нажатие длительное - отключаем весь свет
  // если кнопку отпустили раньше чем 30*50, нажатие короткое - меняем состояние света 
  if((ms - butMs) > 30){
    butMs = ms;
    if(digitalRead(BUTTON4) == ACTIVE){
      if(digitalRead(BUTTON1) == ACTIVE){
        // нажаты 4 и 1, идем на их взаимную обработку
        butcount = 0;
        autoBut = 60; //GO 
        #ifdef DEBUG
        Serial.println("4 & 1 but noticed");
        #endif
      }// 4 & 1
      if(butcount < 50){
        butcount++;
      } else { // зафиксировано длительное удержание кнопки 
        // выключаем весь свет
        #ifdef DEBUG
        Serial.println("long 4 fixed");
        #endif
        statelamp1 = statelamp2 = statelamp3 = statergbwstrip = 0;
        makelamps(); //включим лампы и подсветку в новое состояние 
        butcount = 0;
        autoBut = 99; // GO на ожидание отпускания кнопок
      }
    } else { //BUT 1 released
      if (butcount){
        #ifdef DEBUG
        Serial.println("short 4 fixed");
        #endif
        butcount = 0;
        statergbwstrip = !statergbwstrip; // инвертируем состояние света
        makelamps(); //включим лампы и подсветку в новое состояние 
      } 
      autoBut = 99; // GO на ожидание отпускания кнопок 
    }// no buttons pressed
  }//if ms
  break;
  case 60:
  // одновременно нажаты 1 и 4, меняем klapanmode
  if((ms - butMs) > 100){
    butMs = ms;
    if((digitalRead(BUTTON1) == ACTIVE) && (digitalRead(BUTTON4) == ACTIVE)){
      if( butcount < 30){
        butcount ++;
      } else { // обе кнопки удерживались 3 секунды 
        butcount = 0;
        #ifdef DEBUG
        Serial.println("inverting klapanmode");
        #endif
        klapanmode = !klapanmode; // ИНВЕРТИРУЕМ РЕЖИМ РАБОТЫ КЛАПАНА
        autoBut = 99; //GO на ожидание опускания
      }//1 & 4 fixed
    } else { // недодержали обе кнопки
      butcount = 0;
      autoBut = 99; // GO на ожидание отпускания кнопок
    }
  }//if ms
  break; 
  
  case 80:
  // одновременно нажаты 2 и 3 =>  Если режим управления клапаном ручной, позволяем изменить состояние клапана
  if((ms - butMs) > 100){
    butMs = ms;
    if((digitalRead(BUTTON2) == ACTIVE) && (digitalRead(BUTTON3) == ACTIVE)){
      if( butcount < 5){
        butcount ++;
      } else { // обе кнопки удерживались 3 секунды 
        butcount = 0;
        // если режим клапана ручной, переключим состояние клапана? приходится костылить и напрямую управлять автоматом клапана чтобы красивая отрисовка была 
        if(!klapanmode){
          if(stateklapan){ // если клапан включен
            autoKlapan = 22; // ручное отключение клапана GO
            #ifdef DEBUG
            Serial.println("KLAPAN OFF manually");
            #endif
          } else { 
            autoKlapan = 24; // ручное включение клапана GO
            #ifdef DEBUG
            Serial.println("manually KLAPAN ON");
            #endif
          }
        } // if klapanmode = manual
        else {
          #ifdef DEBUG
          Serial.println("not allowed manually drive KLAPAN");
          #endif
          autoKlapan = 26; // отрисовка запрета на изменение состояния клапана
        }
        autoBut = 99; //GO на ожидание опускания
      }//2 & 3 fixed
    } else { // недодержали обе кнопки
      butcount = 0;
      autoBut = 99; // GO на ожидание отпускания кнопок
    }
  }//if ms
  break; 


   
  case 99:
  // ждем пока все кнопки будут отпущены
  if((ms - butMs) > 20){
    butMs = ms;
    if((digitalRead(BUTTON1) != ACTIVE) && (digitalRead(BUTTON2) != ACTIVE) && (digitalRead(BUTTON3) != ACTIVE) && (digitalRead(BUTTON4) != ACTIVE)){
      if(!butcount){
        butcount++;
      } else {
        butcount = 0;
        autoBut = 3; // GO
      }
    }//if no active buttons
  }//if ms
}//switch(autobut)

/*
#ifdef DEBUG
// отладка автомата кнопок
if(autoButprev != autoBut){
  autoButprev  = autoBut;
  Serial.print("autoBut = ");
  Serial.println(autoBut);
}
#endif
*/
}//void autoButfunc()


// функция переключения состояний ламп
void makelamps(){
  // включаем лампы как надо
  if(statelamp1) digitalWrite(LAMP1, RELAY_ON);
  else digitalWrite(LAMP1, RELAY_OFF);
  if(statelamp2) digitalWrite(LAMP2, RELAY_ON);
  else digitalWrite(LAMP2, RELAY_OFF);
  if(statelamp3) digitalWrite(LAMP3, RELAY_ON);
  else digitalWrite(LAMP3, RELAY_OFF);
  if(statergbwstrip) digitalWrite(RGBWSTRIP, RELAY_ON);
  else digitalWrite(RGBWSTRIP, RELAY_OFF);
        //включаем подсветку ламп как надо
        digitalWrite(LEDLAMP1, (!statelamp1));
        digitalWrite(LEDLAMP2, (!statelamp2));
        digitalWrite(LEDLAMP3, (!statelamp3));
        digitalWrite(LEDRGBWSTRIP, (!statergbwstrip));
}//void makelamps()

// для мигания подсветкой когда с клапаном что то делаем
void showKlapanState(byte i){
  analogWrite(LEDLAMP1, i);
  analogWrite(LEDLAMP2, i);
  analogWrite(LEDLAMP3, i);
  analogWrite(LEDRGBWSTRIP, i);

}
