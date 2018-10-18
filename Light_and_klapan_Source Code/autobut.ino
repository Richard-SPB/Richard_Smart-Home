void autoButfunc(){
/* algorithm :
 *  3- ���� ������ ����� ���� ������ 
 *  5- ������ 1. ���� ��� � 3 �� 60- (�������� �� ��������� ���� ������)
 *  10- ���� ������ 100*15 ��� ������ 1 �� 50- (���������� ����� �����) ���� �������� �� ����� �� 4� ������
 *  ���������� ��� ������ ������, ����� �������������� ���������
 *  ������ 1 \2 \3 \4
 *  ��������� 5- \6- \7- \8-
 *  ��������� 10- \20- \30- \40-
 *  ����� 
 *  50 - ���������� ����� ����� � �� 99-
 *  60- ���� ������ 1 � 4, 5 ��� �� 100 ��, �������� ����� ������ �������(����, ������) � ���� �� 99-
 *  80- ���� ������ 2 � 3, 2 ���� �� 100 ��, �� ���� ����� ������� ������, �������� ��������� ������ ������� � �� 99-
 *  99- �������� ���������� ���� ������ , ���� �������� �� ���� ��������� , ���� ����������� ��������� � ���� �� ����� ����
 */ 
switch(autoBut){
  case 0:
  // ������������� ��������
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
  // ������ 1 ������? ���� ��, �� ���� ������ ��� � ������ 4, ���� �� �� �������� ���������
  // ���� ������ 1 ������, ���� ������ 30*50 ��, �� ������� ���������� - ��������� ���� ����
  // ���� ������ ��������� ������ ��� 30*50, ������� �������� - ������ ��������� ����� 
  if((ms - butMs) > 30){
    butMs = ms;
    if(digitalRead(BUTTON1) == ACTIVE){
      if(digitalRead(BUTTON4) == ACTIVE){
        // ������ 1 � 4, ���� �� �� �������� ���������
        butcount = 0;
        autoBut = 60; //GO 
        #ifdef DEBUG
        Serial.println("1 & 4 but noticed");
        #endif
      }// 1 & 4
      if(butcount < 50){
        butcount++;
      } else { // ������������� ���������� ��������� ������ 
        // ��������� ���� ����
        #ifdef DEBUG
        Serial.println("long 1 fixed");
        #endif
        statelamp1 = statelamp2 = statelamp3 = statergbwstrip = 0;
        makelamps(); //������� ����� � ��������� � ����� ��������� 
        butcount = 0;
        autoBut = 99; // GO �� �������� ���������� ������
      }
    } else { //BUT 1 released
      if (butcount){
        #ifdef DEBUG
        Serial.println("short 1 fixed");
        #endif
        butcount = 0;
        statelamp1 = !statelamp1; // ����������� ��������� �����
        makelamps(); //������� ����� � ��������� � ����� ��������� 
      } 
      autoBut = 99; // GO �� �������� ���������� ������ 
    }// no buttons pressed
  }//if ms
  break;
  case 6:
  // ������ 2 ������? ���� ��, �� ���� ������ ��� � ������ 3, ���� �� �� �������� ���������
  // ���� ������ 2 ������, ���� ������ 30*50 ��, �� ������� ���������� - ��������� ���� ����
  // ���� ������ ��������� ������ ��� 30*50, ������� �������� - ������ ��������� ����� 
  if((ms - butMs) > 30){
    butMs = ms;
    if(digitalRead(BUTTON2) == ACTIVE){
      if(digitalRead(BUTTON3) == ACTIVE){
        // ������ 2 � 3, ���� �� �� �������� ���������
        butcount = 0;
        autoBut = 80; //GO �� ������� ������� ������������ �������
        #ifdef DEBUG
        Serial.println("2 & 3 but noticed");
        #endif
      }// 2 & 3
      if(butcount < 50){
        butcount++;
      } else { // ������������� ���������� ��������� ������ 
        // ��������� ���� ����
        #ifdef DEBUG
        Serial.println("long 2 fixed");
        #endif
        statelamp1 = statelamp2 = statelamp3 = statergbwstrip = 0;
        makelamps(); //������� ����� � ��������� � ����� ��������� 
        butcount = 0;
        autoBut = 99; // GO �� �������� ���������� ������
      }
    } else { //BUT 2 released
      if (butcount){
        #ifdef DEBUG
        Serial.println("short 2 fixed");
        #endif
        butcount = 0;
        statelamp2 = !statelamp2; // ����������� ��������� �����
        makelamps(); //������� ����� � ��������� � ����� ��������� 
      } 
      autoBut = 99; // GO �� �������� ���������� ������ 
    }// no buttons pressed
  }//if ms
  break;
  case 7:
  // ������ 3 ������? ���� ��, �� ���� ������ ��� � ������ 2, ���� �� �� �������� ���������
  // ���� ������ 2 ������, ���� ������ 30*50 ��, �� ������� ���������� - ��������� ���� ����
  // ���� ������ ��������� ������ ��� 30*50, ������� �������� - ������ ��������� ����� 
  if((ms - butMs) > 30){
    butMs = ms;
    if(digitalRead(BUTTON3) == ACTIVE){
      if(digitalRead(BUTTON2) == ACTIVE){
        // ������ 3 � 2, ���� �� �� �������� ���������
        butcount = 0;
        autoBut = 80; //GO �� ������� ������� ������������ �������
        #ifdef DEBUG
        Serial.println("3 & 2 but noticed");
        #endif
      }// 3 & 2
      if(butcount < 50){
        butcount++;
      } else { // ������������� ���������� ��������� ������ 
        // ��������� ���� ����
        #ifdef DEBUG
        Serial.println("long 3 fixed");
        #endif
        statelamp1 = statelamp2 = statelamp3 = statergbwstrip = 0;
        makelamps(); //������� ����� � ��������� � ����� ��������� 
        butcount = 0;
        autoBut = 99; // GO �� �������� ���������� ������
      }
    } else { //BUT 2 released
      if (butcount){
        #ifdef DEBUG
        Serial.println("short 3 fixed");
        #endif
        butcount = 0;
        statelamp3 = !statelamp3; // ����������� ��������� �����
        makelamps(); //������� ����� � ��������� � ����� ��������� 
      } 
      autoBut = 99; // GO �� �������� ���������� ������ 
    }// no buttons pressed
  }//if ms
  break;
  case 8:
  // ������ 4 ������? ���� ��, �� ���� ������ ��� � ������ 1, ���� �� �� �������� ���������
  // ���� ������ 4 ������, ���� ������ 30*50 ��, �� ������� ���������� - ��������� ���� ����
  // ���� ������ ��������� ������ ��� 30*50, ������� �������� - ������ ��������� ����� 
  if((ms - butMs) > 30){
    butMs = ms;
    if(digitalRead(BUTTON4) == ACTIVE){
      if(digitalRead(BUTTON1) == ACTIVE){
        // ������ 4 � 1, ���� �� �� �������� ���������
        butcount = 0;
        autoBut = 60; //GO 
        #ifdef DEBUG
        Serial.println("4 & 1 but noticed");
        #endif
      }// 4 & 1
      if(butcount < 50){
        butcount++;
      } else { // ������������� ���������� ��������� ������ 
        // ��������� ���� ����
        #ifdef DEBUG
        Serial.println("long 4 fixed");
        #endif
        statelamp1 = statelamp2 = statelamp3 = statergbwstrip = 0;
        makelamps(); //������� ����� � ��������� � ����� ��������� 
        butcount = 0;
        autoBut = 99; // GO �� �������� ���������� ������
      }
    } else { //BUT 1 released
      if (butcount){
        #ifdef DEBUG
        Serial.println("short 4 fixed");
        #endif
        butcount = 0;
        statergbwstrip = !statergbwstrip; // ����������� ��������� �����
        makelamps(); //������� ����� � ��������� � ����� ��������� 
      } 
      autoBut = 99; // GO �� �������� ���������� ������ 
    }// no buttons pressed
  }//if ms
  break;
  case 60:
  // ������������ ������ 1 � 4, ������ klapanmode
  if((ms - butMs) > 100){
    butMs = ms;
    if((digitalRead(BUTTON1) == ACTIVE) && (digitalRead(BUTTON4) == ACTIVE)){
      if( butcount < 30){
        butcount ++;
      } else { // ��� ������ ������������ 3 ������� 
        butcount = 0;
        #ifdef DEBUG
        Serial.println("inverting klapanmode");
        #endif
        klapanmode = !klapanmode; // ����������� ����� ������ �������
        autoBut = 99; //GO �� �������� ���������
      }//1 & 4 fixed
    } else { // ����������� ��� ������
      butcount = 0;
      autoBut = 99; // GO �� �������� ���������� ������
    }
  }//if ms
  break; 
  
  case 80:
  // ������������ ������ 2 � 3 =>  ���� ����� ���������� �������� ������, ��������� �������� ��������� �������
  if((ms - butMs) > 100){
    butMs = ms;
    if((digitalRead(BUTTON2) == ACTIVE) && (digitalRead(BUTTON3) == ACTIVE)){
      if( butcount < 5){
        butcount ++;
      } else { // ��� ������ ������������ 3 ������� 
        butcount = 0;
        // ���� ����� ������� ������, ���������� ��������� �������? ���������� ��������� � �������� ��������� ��������� ������� ����� �������� ��������� ���� 
        if(!klapanmode){
          if(stateklapan){ // ���� ������ �������
            autoKlapan = 22; // ������ ���������� ������� GO
            #ifdef DEBUG
            Serial.println("KLAPAN OFF manually");
            #endif
          } else { 
            autoKlapan = 24; // ������ ��������� ������� GO
            #ifdef DEBUG
            Serial.println("manually KLAPAN ON");
            #endif
          }
        } // if klapanmode = manual
        else {
          #ifdef DEBUG
          Serial.println("not allowed manually drive KLAPAN");
          #endif
          autoKlapan = 26; // ��������� ������� �� ��������� ��������� �������
        }
        autoBut = 99; //GO �� �������� ���������
      }//2 & 3 fixed
    } else { // ����������� ��� ������
      butcount = 0;
      autoBut = 99; // GO �� �������� ���������� ������
    }
  }//if ms
  break; 


   
  case 99:
  // ���� ���� ��� ������ ����� ��������
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
// ������� �������� ������
if(autoButprev != autoBut){
  autoButprev  = autoBut;
  Serial.print("autoBut = ");
  Serial.println(autoBut);
}
#endif
*/
}//void autoButfunc()


// ������� ������������ ��������� ����
void makelamps(){
  // �������� ����� ��� ����
  if(statelamp1) digitalWrite(LAMP1, RELAY_ON);
  else digitalWrite(LAMP1, RELAY_OFF);
  if(statelamp2) digitalWrite(LAMP2, RELAY_ON);
  else digitalWrite(LAMP2, RELAY_OFF);
  if(statelamp3) digitalWrite(LAMP3, RELAY_ON);
  else digitalWrite(LAMP3, RELAY_OFF);
  if(statergbwstrip) digitalWrite(RGBWSTRIP, RELAY_ON);
  else digitalWrite(RGBWSTRIP, RELAY_OFF);
        //�������� ��������� ���� ��� ����
        digitalWrite(LEDLAMP1, (!statelamp1));
        digitalWrite(LEDLAMP2, (!statelamp2));
        digitalWrite(LEDLAMP3, (!statelamp3));
        digitalWrite(LEDRGBWSTRIP, (!statergbwstrip));
}//void makelamps()

// ��� ������� ���������� ����� � �������� ��� �� ������
void showKlapanState(byte i){
  analogWrite(LEDLAMP1, i);
  analogWrite(LEDLAMP2, i);
  analogWrite(LEDLAMP3, i);
  analogWrite(LEDRGBWSTRIP, i);

}
