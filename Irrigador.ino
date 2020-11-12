#include <TimeLib.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

/**********Variaveis importantes para a automação**************/
int dias_selecionados[7]; //armazena valores dos dias selecionados: 1 = dom, 2 = seg, 3 = ter, etc
int qtd_dias;             //define a quantidade de dias que foram armazenados no array dias_selecionados
int hora;                 //armazena a hora definida
int minuto;               //armazena os minutos
/**************************************************************/
int qtd_dias_r;
int dias_selecionados_r[7];
int hora_r;
int minuto_r;
/**************************************************************/

bool volta_menu = false;
bool volta_freq = false;
bool volta_dia = false;

const byte qtdLinhas = 4;
const byte qtdColunas = 4;
char matriz_teclas[qtdLinhas][qtdColunas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte PinosqtdLinhas[qtdLinhas] = {3, 4, 5, 6};
byte PinosqtdColunas[qtdColunas] = {7, 8, 9, 10};

String selecao[7];
String opcao[3];

int n = 0; //variavel de manipulação do array de menu
int a = 0; //variavel de manipulação do array de frequencia
int x = 0; //variavel de manipulação do array de selecionar dia

bool isON = false;
bool Naoleu = true;
bool leu = false;
bool isONAuto = false;


String clock = "     --:--      ";

int pos = 0;
LiquidCrystal lcd(14, 13, 12, 2, 16, 17);

Keypad meuteclado = Keypad( makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas);

void teste()
{
  Serial.println(dias_selecionados[0]);
  Serial.println(dias_selecionados[1]);
  Serial.println(dias_selecionados[2]);
  Serial.println(dias_selecionados[3]);
  Serial.println(dias_selecionados[4]);
  Serial.println(dias_selecionados[5]);
  Serial.println(dias_selecionados[6]);
  Serial.println("");
  Serial.println(hora);
  Serial.println(minuto);
  Serial.println(qtd_dias);
  Serial.println("");
}

void setup() {
  Serial.begin(9600);
  //Aqui deve se ajeitar o horário atual antes de ligar o arduino
  //No formato setTime( hora, minuto, segundo, dia, mês, ano );
  setTime(17,42,0,10,11,2020);
  lcd.begin(16, 2);
  opcao[0] = "<<LigIrrigador>>";
  opcao[1] = "<<AgendarIrrig>>";
  opcao[2] = "<< ZerarAgend >>";
  pinMode(15, OUTPUT);
  digitalWrite(15, LOW);
  limpa_tela();
}
void mostra_relogio()
{
  lcd.setCursor(4,0);
  if(hour() < 10)
  {
    lcd.setCursor(4,0);
    lcd.print("0");
    lcd.setCursor(5,0);
  }
  else
  {
    lcd.setCursor(4,0);
  }
  lcd.print(hour());

  lcd.setCursor(6,0);
  lcd.print(":");

  if(minute() < 10)
  {
    lcd.setCursor(7,0);
    lcd.print("0");
    lcd.setCursor(8,0);
  }
  else
  {
    lcd.setCursor(7,0);
  }
  lcd.print(minute());

  lcd.setCursor(9,0);
  lcd.print(":");

  if(second() < 10)
  {
    lcd.setCursor(10,0);
    lcd.print("0");
    lcd.setCursor(11,0);
  }
  else
  {
    lcd.setCursor(10,0);
  }
  lcd.print(second());
  lcd.setCursor(12,0);
  lcd.print("         ");
}
void mostra_data()
{
  if(day() < 10)
  {
    lcd.setCursor(0,1);
    lcd.print("0");
    lcd.setCursor(1,1);   
  }
  else
  {
    lcd.setCursor(0,1);
  }
  lcd.print(day());

  lcd.setCursor(2,1);
  lcd.print("/");

  if(month() < 10)
  {
    lcd.setCursor(3,1);
    lcd.print("0");
    lcd.setCursor(4,1);   
  }
  else
  {
    lcd.setCursor(3,1);
  }
  lcd.print(month());

  lcd.setCursor(5,1);
  lcd.print("/");

  lcd.setCursor(6,1);
  lcd.print(year());

  lcd.setCursor(10,1);
  lcd.print(" ");

  lcd.setCursor(11,1);
  lcd.print(dayShortStr(weekday()));
}
void Liga_auto()
{
  if(!isONAuto)
  {
    digitalWrite(15, HIGH);
    isONAuto = true;
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Status: Ligado  ");
    delay(2000);
  }
}
void verifica()
{
  for(int i = 0; i < qtd_dias; i++)
  {
    if(dias_selecionados[i] == weekday() && hora == hour() && minuto == minute())
    {
      Liga_auto();
    }
    else if(dias_selecionados[i] == weekday() && hora == hour() && minuto + 2 >= minute() && isONAuto == true)
    {
      digitalWrite(15,LOW);
      isONAuto = false;
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Status: Deslig. ");
      delay(2000 );
    }
  }
}
void loop() {
  teste();
  mostra_relogio();
  mostra_data();
  verifica();
  if(volta_menu)
  {
    Menu();
    volta_menu = false;
  }
  else if(volta_freq)
  {
    SelecionarFrequencia();
    volta_freq = false;
  }
  else if(volta_dia)
  {
    SelecionarDia();
    volta_dia = false;
  }
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
    Serial.println(n);
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
          Naoleu = false;
        }
        else if(n == 1){
          AgendarIrrigador();
          Naoleu = false;
        }
        else if(n == 2){
          ApagarAgendamento();
          Naoleu = false;
        }
      }
      else if(tecla_pressionada == 'A'){
        Naoleu = false;
        lcd.clear();
      }
    }
  }
}
void LigarIrrigador(){
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);

  if(isON){
    digitalWrite(15, LOW);
    lcd.print(" Status: Deslig ");
    isON = false;
    delay(1000);
  }
  else{
    digitalWrite(15, HIGH);
    lcd.print(" Status: Ligado ");
    isON = true;
    delay(1000);
  }
  lcd.clear();
}
void AgendarIrrigador(){
  SelecionarFrequencia();
}
void ApagarAgendamento(){
  dias_selecionados[0] = 0;
  dias_selecionados[1] = 0;
  dias_selecionados[2] = 0;
  dias_selecionados[3] = 0;
  dias_selecionados[4] = 0;
  dias_selecionados[5] = 0;
  dias_selecionados[6] = 0;
  qtd_dias = -1;
  hora = -1;
  minuto = -1;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Agend. Zerado   ");
  delay(2000);
  lcd.clear();
}

void SelecionarFrequencia(){
  String quantidade[7];
  leu = false;
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
        qtd_dias_r = a + 1;
        SelecionarDia();
      }
      else if(tecla_pressionada == 'A'){
        leu = true;
        lcd.clear();
      }
      else if(tecla_pressionada == 'B'){
        leu = true;
        volta_menu = true;
        volta_dia = false;
        volta_freq = false;
        lcd.clear();
      }
    }
  }
}

void SelecionarDia() {
  bool deve_ler = true;
  int aux = 0;
  lcd.clear();
  String semana[7];
  semana[0] = " <<  SEGUNDA >> ";
  semana[1] = " <<  TERCA   >> ";
  semana[2] = " <<  QUARTA  >> ";
  semana[3] = " <<  QUINTA  >> ";
  semana[4] = " <<  SEXTA   >> ";
  semana[5] = " <<  SABADO  >> ";
  semana[6] = " <<  DOMINGO >> ";

  int limite = 6;
  int comeco = 0;
  
  if(qtd_dias_r == 7)
  {
    aux = qtd_dias_r;
    dias_selecionados_r[0] = 1;
    dias_selecionados_r[1] = 2;
    dias_selecionados_r[2] = 3;
    dias_selecionados_r[3] = 4;
    dias_selecionados_r[4] = 5;
    dias_selecionados_r[5] = 6;
    dias_selecionados_r[6] = 7;
  }

  while (aux != qtd_dias_r)
  {

    Serial.println(semana[0]);
    Serial.println(semana[1]);
    Serial.println(semana[2]);
    Serial.println(semana[3]);
    Serial.println(semana[4]);
    Serial.println(semana[5]);
    Serial.println(semana[6]);

    Serial.println(limite);
    Serial.println(comeco);
    Serial.println(x);
    
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
        if (x == limite) {
          x = -1;
        }
        x++;
        lcd.setCursor(0, 1);
        lcd.print(semana[x]);
      }
      else if (tecla_pressionada == '*') { //<--
        if (x == comeco) {
          x = limite + 1;
        }
        x--;
        lcd.setCursor(0, 1);
        lcd.print(semana[x]);
      }
      else if (tecla_pressionada == 'D') { //Confirma
        if (semana[x] == " <<  SEGUNDA >> ") {
          lcd.setCursor(0, 1);
          lcd.print("Segunda selec.  ");
          dias_selecionados_r[aux] = 2;
          aux++;
        }
        else if (semana[x] == " <<  TERCA   >> ") {
          lcd.setCursor(0, 1);
          lcd.print("Terca selec.    ");
          dias_selecionados_r[aux] = 3;
          aux++;
        }
        else if (semana[x] == " <<  QUARTA  >> ") {
          lcd.setCursor(0, 1);
          lcd.print("Quarta selec.   ");
          dias_selecionados_r[aux] = 4;
          aux++;
        }
        else if (semana[x] == " <<  QUINTA  >> ") {
          lcd.setCursor(0, 1);
          lcd.print("Quinta selec.   ");
          dias_selecionados_r[aux] = 5;
          aux++;
        }
        else if (semana[x] == " <<  SEXTA   >> ") {
          lcd.setCursor(0, 1);
          lcd.print("Sexta selec.    ");
          dias_selecionados_r[aux] = 6;
          aux++;
        }
        else if (semana[x] == " <<  SABADO  >> ") {
          lcd.setCursor(0, 1);
          lcd.print("Sabado selec.   ");
          dias_selecionados_r[aux] = 7;
          aux++;
        }
        else if (semana[x] == " <<  DOMINGO >> ") {
          lcd.setCursor(0, 1);
          lcd.print("Domingo selec.  ");
          dias_selecionados_r[aux] = 1;
          aux++;
        }
        for(int i = x; i < limite;i++)
        {
          semana[i] = semana[i+1];
        }
        limite--;
        x = 0;
        delay(1000);
      }
      else if(tecla_pressionada == 'A')
      {
        aux = qtd_dias_r;
        lcd.clear();
        loop();
        deve_ler = false;
      }
      else if(tecla_pressionada == 'B')
      {
        aux = qtd_dias_r;
        lcd.clear();
        volta_freq = true;
        volta_menu = false;
        volta_dia = false;
        loop();
        deve_ler = false;
      }
    }
  }
    if(deve_ler)
    {
       lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Todos selec.");
      delay(2000);
      SelecionarHora();
    }
}

void SelecionarHora(){  
  bool deve_ler = true;
    clock = "     --:--      ";
  MostraClock();
  int contador = 5;
  bool hora_certa = true;
    
    while(contador <= 10) {

        if(contador == 7) {
            contador++;
            continue;
        }   

        bool escreve_digito = false;
        
        int digito = meuteclado.waitForKey();

        if(digito - '0' >= 0 && digito - '0' <= 9){
            escreve_digito = true;
        }
        else if((contador == 9 || contador == 10) && digito == 'D')
        {
            contador++;
            escreve_digito = false;
        }
        else if(digito == 'C' && contador > 5)
        {
            contador --;
            if(contador == 7)
            {
                contador--;
            }
            clock[contador] = '-';
            MostraClock();
        }
        else if(digito == 'A')
        {
          escreve_digito = false;
          deve_ler = false;
          contador = 11;
          lcd.clear();
        }
        else if(digito == 'B')
        {
          escreve_digito = false;
          deve_ler = false;
          contador = 11;
          volta_dia = true;
          volta_menu = false;
          volta_freq = false;
          lcd.clear();
        }
        if(contador == 10)
        {
            escreve_digito = false;
        }
        
        if(escreve_digito){
            clock[contador] = digito;
            MostraClock();
            contador++;
        }           

    }
    if(deve_ler)
    {
      int x1 = clock[5] - '0';
      int x2 = clock[6] - '0';
      int y1 = clock[8] - '0';
      int y2 = clock[9] - '0';
  
      int horasclock = (x1 * 10) + x2;
      int minutosclock = (y1 * 10) + y2;
  
      if(horasclock >= 24 || minutosclock >= 60)
      {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Hora invalida!");
          delay(2000);
          lcd.clear();
          hora_certa  = false;
          SelecionarHora();
      }
  
      if(hora_certa)
      {
          hora_r = horasclock;
          minuto_r = minutosclock;
          MensagemHorario();
          Finaliza();
      } 
    }
}
// Funções de horário

 void MostraClock() {
  lcd.setCursor(0,0);
  lcd.print("Digite a hora!  ");
  lcd.setCursor(0,1);
  lcd.print(clock);
}

void MensagemHorario() {
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Agendado: ");
  lcd.setCursor(10,0);
  lcd.print(hora_r);
  lcd.setCursor(12,0);
  lcd.print(":");
  lcd.setCursor(13,0);
  lcd.print(minuto_r);
  delay(2000);
}

void Finaliza()
{
    hora = hora_r;
    minuto = minuto_r;
    qtd_dias = qtd_dias_r;

    for(int i = 0; i < qtd_dias; i++)
    {
        dias_selecionados[i] = dias_selecionados_r[i];
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Agendadado com");
    lcd.setCursor(0,1);
    lcd.print("sucesso!");
    volta_menu = false;
    volta_freq = false;
    volta_dia = false;
    delay(3000);
    lcd.clear();
}
