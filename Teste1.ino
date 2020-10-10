#include <LiquidCrystal.h>
#include <Keypad.h>

const byte qtdLinhas = 4;
const byte qtdColunas = 4;
char matriz_teclas[qtdLinhas][qtdColunas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte PinosqtdLinhas[qtdLinhas] = {3, 4, 5, 6};
byte PinosqtdColunas[qtdColunas] = {8, 9, 10, 11};

String opcao[3];
int n = 0;
int a = 0;
int p = 0;

bool isON = false;
bool Naoleu = true;
bool leu = false;

int pos = 0;
LiquidCrystal lcd(A5, 13, 12, 2, 1, 0);

Keypad meuteclado = Keypad( makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Bem-vindo!      ");
  opcao[0] = "<<LigIrrigador>>";
  opcao[1] = "<<AgendarIrrig>>";
  opcao[2] = "<< ZerarAgend >>";
  lcd.setCursor(0, 1);
  lcd.print(opcao[n]);
  pinMode(7, OUTPUT);
}

void loop() {
  Menu();
}

void Menu() {
  Naoleu = true;
  lcd.setCursor(0,0);
  lcd.print("Bem-vindo!      ");
  lcd.setCursor(0, 1);
  lcd.print(opcao[n]);

  while(Naoleu == true)
  {
    char tecla_pressionada = meuteclado.getKey();
  
    if(tecla_pressionada){
  
      if(tecla_pressionada == '#'){
        if(n == 2){
          n = -1;
        }
        n++;
        lcd.setCursor(0, 1);
        lcd.print(opcao[n]);
      }
      else if(tecla_pressionada == '*'){
        if(n == 0){
          n = 3;
        }
        n--;
        lcd.setCursor(0, 1);
        lcd.print(opcao[n]);
      }
      else if(tecla_pressionada == 'D'){
        if(n == 0){
          LigarIrrigador();
        }
        else if(n == 1){
          AgendarIrrigador();
        }
        else if(n == 2){
          ApagarAgendamento();
        }
      }
    }
  }
}
void LigarIrrigador(){
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);

  if(isON){
    digitalWrite(7, LOW);
    lcd.print(" Status: Deslig ");
    isON = false;
    delay(1000);
  }
  else{
    digitalWrite(7, HIGH);
    lcd.print(" Status: Ligado ");
    isON = true;
    delay(1000);
  }
  
  lcd.setCursor(0,1);
  lcd.print(opcao[0]);
  lcd.setCursor(0,0);
  lcd.print("Bem-vindo!      ");
}
void AgendarIrrigador(){
  SelecionarFrequencia();
  SelecionarDia();
  SelecionarHora();
}
void ApagarAgendamento(){
  
}
void SelecionarFrequencia(){
  String quantidade[7];
  
  quantidade[0] = "<<      1     >>";
  quantidade[1] = "<<      2     >>";
  quantidade[2] = "<<      3     >>";
  quantidade[3] = "<<      4     >>";
  quantidade[4] = "<<      5     >>";
  quantidade[5] = "<<      6     >>";
  quantidade[6] = "<<      7     >>";
    
  lcd.setCursor(0,0);
  lcd.print("Frequencia:     ");
  lcd.setCursor(0,1);
  lcd.print(quantidade[a]);
  
  while(leu == false)
  {
    char tecla_pressionada = meuteclado.getKey();  
    
    if(tecla_pressionada)   
    {
      if(tecla_pressionada == '#')
      { 
        if(a==6){ 
          a = -1;
        }
        a++;
        lcd.setCursor(0,1);
        lcd.print(quantidade[a]); 
      }
      else if(tecla_pressionada == '*')
      { if(a==0){ 
          a = 7;
        }
        a--;
        lcd.setCursor(0,1);
        lcd.print(quantidade[a]); 
      }
      if(tecla_pressionada == 'D'){
      leu = true;}
    }
  } 
}
void SelecionarDia(){
 
}
void SelecionarHora(){
  
}
