
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

String selecao[7];
String opcao[3];

int n = 0; //variavel de manipulação do array de menu
int a = 0; //variavel de manipulação do array de frequencia
int x = 0; //variavel de manipulação do array de selecionar dia

int frequencia = 0;

bool isON = false;
bool Naoleu = true;
bool leu = false;
bool clockTravado = true;

String clock = "--:--           ";

int pos = 0;
LiquidCrystal lcd(A5, 13, 12, 2, 1, 0);

Keypad meuteclado = Keypad( makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas);

void setup() {
  lcd.begin(16, 2);
  opcao[0] = "<<LigIrrigador>>";
  opcao[1] = "<<AgendarIrrig>>";
  opcao[2] = "<< ZerarAgend >>";
  pinMode(7, OUTPUT);
}

void loop() {
  limpa_tela();
  lcd.print(millis()/1000);
  char tecla_pressionada = meuteclado.getKey();
  if(tecla_pressionada)
  {
    Naoleu = true;
    if(tecla_pressionada == 'A')
    {
      Menu();
    }
  }
}
void limpa_tela(){
  lcd.clear();
}   
void Menu() {
  Naoleu = true;
  lcd.setCursor(0,0);
  lcd.print("Bem-vindo!      ");
  lcd.setCursor(0, 1);
  lcd.print(opcao[n]);
  leu = false;

  while(Naoleu == true)
  {
    char tecla_pressionada = meuteclado.waitForKey();
  
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
      else if(tecla_pressionada == 'A'){
        Naoleu = false;
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
  Menu();
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
    char tecla_pressionada = meuteclado.waitForKey();  
    
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
      else if(tecla_pressionada == 'D'){
        leu = true;
        frequencia = a + 1;
      }
    }
  } 
}

void SelecionarDia() {
  int aux = 0;
  lcd.clear();
  String semana[6];
  semana[0] = " <<  SEGUNDA >> ";
  semana[1] = " <<  TERCA   >> ";
  semana[2] = " <<  QUARTA  >> ";
  semana[3] = " <<  QUINTA  >> ";
  semana[4] = " <<  SEXTA   >> ";
  semana[5] = " <<  SABADO  >> ";
  semana[6] = " <<  DOMINGO >> ";
  
  if(frequencia == 7)
  {
    aux = frequencia;
  }

  while (aux != frequencia)
  {
    lcd.setCursor(0,0);
    lcd.print("Selec. o dia ");
    lcd.setCursor(13,0);
    lcd.print(aux + 1);
    lcd.setCursor(14,0);
    lcd.print("   ");
    lcd.setCursor(0,1);
    lcd.print(semana[x]);
    char tecla_pressionada = meuteclado.waitForKey(); //Retorna o valor ASCII da tecla pressionada
    
    if (tecla_pressionada) {
      if (tecla_pressionada == '#') { //-->
        if (x == 6) {
          x = -1;
        }
        x++;
        lcd.setCursor(0, 1);
        lcd.print(semana[x]);
      }
      else if (tecla_pressionada == '*') { //<--
        if (x == 0) {
          x = 7;
        }
        x--;
        lcd.setCursor(0, 1);
        lcd.print(semana[x]);
      }
      else if (tecla_pressionada == 'D') { //Confirma
        if (x == 0) {
          lcd.setCursor(0, 1);
          lcd.print("Segunda selec.  ");
          aux++;
          selecao[aux] = "Segunda";
        }
        else if (x == 1) {
          lcd.setCursor(0, 1);
          lcd.print("Terca selec.    ");
          aux++;
          selecao[aux] = "Terça-Feira";
        }
        else if (x == 2) {
          lcd.setCursor(0, 1);
          lcd.print("Quarta selec.   ");
          aux++;
          selecao[aux] = "Quarta-Feira";
        }
        else if (x == 3) {
          lcd.setCursor(0, 1);
          lcd.print("Quinta selec.   ");
          aux++;
          selecao[aux] = "Quinta-Feira";
        }
        else if (x == 4) {
          lcd.setCursor(0, 1);
          lcd.print("Sexta selec.    ");
          aux++;
          selecao[aux] = "Sexta-Feira";
        }
        else if (x == 5) {
          lcd.setCursor(0, 1);
          lcd.print("Sabado selec.   ");
          aux++;
          selecao[aux] = "Sábado";
        }
        else if (x == 6) {
          lcd.setCursor(0, 1);
          lcd.print("Domingo selec.  ");
          aux++;
          selecao[aux] = "Domingo";
        }
        delay(1000);
      }
    }
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tudo selec.");
  delay(1000);
}

void SelecionarHora(){  
  MostraClock();
  
  int contador = 0;
  
  while(clockTravado) {
    
    while(contador <= 4) {
      if(contador == 2) {
        contador++;
        continue;
      }   
      bool escreve_digito = false;
      
      int digito = meuteclado.waitForKey();
      if( digito > 3){
        escreve_digito = true;
      }
      
      if(escreve_digito){
        clock[contador] = digito;
        MostraClock();
        contador++;
      }        
        

      char tecla_pressionada = meuteclado.getKey();
      if (tecla_pressionada){
        
      }
   }  
      clockTravado = false;
  }
  MensagemHorario();
  clock = "--:--           ";
  Menu();
}
// Funções de horário

 void MostraClock() {
  lcd.setCursor(0,0);
  lcd.print("Digite a hora!  ");
  lcd.setCursor(0,1);
  lcd.print(clock);
}

void MensagemHorario() {
  lcd.setCursor(0,0);
  lcd.print("Agendado: " + clock);
  lcd.setCursor(0,1);
  lcd.print("               ");
  delay(2000);
}
