
//////////// LIBRERIAS PARA PANTALLA TFT LCD 3.5 (ILI9488) ////////////////
#include <Adafruit_GFX.h> 
//////////// LIBRERIAS PARA ARDUINO DUE Y PANTALLA ///////////////////////
#include <MCUFRIEND_kbv.h>


///////////ENTRADAS DE PUERTO A8 y A9 ///////////////////////////
#define LEFT_BUTTON 12
#define RIGHT_BUTTON 13

///////////PALETA DE COLORES PREDEFINIDOS ////////////////////
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY    0xD6BA

/////////// VARIABLE GLOBAL DE PANTALLA ///////////////
MCUFRIEND_kbv tft;

/////////// FUNCIONES ///////////////////
void dibujaPatalla();
void animacionSebas(uint8_t);
void animacionSebasFondo(uint8_t);

/////////// ARREGLO DEL BITMAP PERSONAJE PRINCIPAL/////////////////////
extern uint8_t sebastianQuieto[];
extern uint8_t sebastianCorriendo1[];
extern uint8_t sebastianCorriendo2[];
extern uint8_t sebastianCorriendo3[];
extern uint8_t sebastianCorriendo4[];
extern uint8_t sebastianCorriendo5[];
extern uint8_t sebastianCorriendo6[];
//extern uint8_t sebastianCorriendo7[];
//extern uint8_t sebastianCorriendo8[];
extern uint8_t sebastianCorriendo9[];
extern uint8_t sebastianCorriendo10[];
extern uint8_t sebastianCorriendo11[];
extern uint8_t sebastianCorriendo12[];
extern uint8_t sebastianCorriendo13[];

///////// POCISION INICIAL PERSONAJE /////////////// 
uint16_t player_x = 80-32;
const uint16_t PLAYER_Y = 0;

///////// COLOR PERSONAJE Y COLOR DEL FONDO
#define COLOR BLACK
#define FONDO GREY

  
void setup() {
  //////// INICALIZANDO BOTONES /////////////
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  
  //////// INICIALIZANDO PANTALLA ///////////
  //Serial.begin(9600);
  tft.begin(0x9486);
  tft.setRotation(3); // Dibuja la orientación de la pantalla
  tft.fillScreen(FONDO); // Dibuja fondo de pantalla

  //////// INICIALIZA PERSONAJE Y OBSTACULOS
  dibujaPatalla();
  creaHoyos(); // funcion que crea los obstáculos
}

void loop() 
{
  ///////// Definición milímetros /////////////////
  unsigned long time = millis();
  ///////// Define los botones inactivos, personaje inmovil //////   
  static bool left_state = false;
  static bool right_state = false;

  static uint8_t frame = 1; // Se define el frame uncial
  
  ////////////// Direction del botín de entrada
  left_state |= (digitalRead(LEFT_BUTTON) == LOW);
  right_state |= (digitalRead(RIGHT_BUTTON) == LOW);

  ////////////// Movimiento del personaje 32 PIXELES
  tft.drawRect(player_x+32,PLAYER_Y-32,64,128,FONDO); // Dibuja rectangle color del condo
  animacionSebasFondo(frame-1); // Ejecuta dibujo anterior del personaje principal

	////////// MOVIMIENTO IZQUIERDA O DERECHA DEL PERSONAJE ///////////
        if(left_state && player_x>80-32) {
            player_x -= 32;
        }
        if(right_state && player_x<336-32) {
            player_x += 32;
        }
	////////// DESACTIVA MOVIMIENTO DEL PERSONAJE ////////////////
        left_state = right_state = false;
  ///////// DIBUJA PERSONAJE CON LA POSICION ACTUAL ////////////
  tft.drawRect(player_x+32,PLAYER_Y-32,64,128,COLOR);
  ///////// ACTUALIZA FRAME DEL PERSONAJE
  animacionSebas(frame);
  ///////// AUMENTA UN FRAME MAS //////////////
  frame++; 
  /////////// SI EL FRAME ES MAYOR DE 11 REINICAL EL CICLO //////////
  if(frame > 11) 
  {
    frame = 1;
    animacionSebasFondo(11);
  }

}

//////// FUNCION QUE DIBUJA UN ARRAY DE BITMAP /////////////////////////
void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) 
{
   int16_t i, j, byteWidth = (w + 7) / 8;
   uint8_t byte;

   for(j=0; j<h; j++) 
   {
      for(i=0; i<w; i++) 
      {
         if(i & 7) 
            byte <<= 1;
         else      
            byte = pgm_read_byte(bitmap + j * byteWidth + i / 8);
         if(byte & 0x80) tft.drawPixel(x+i, y+j, color);
      }
   }
}

//////// FUNCION QUE DIBUJA UN RECTANGULO NEGRO EN CADA MITAD DE PANTALLA ///////////////
void dibujaPatalla() 
{
   ////// fondo negro izquierdo
   tft.fillRect(0, 0, 80, 320, BLACK);
   ////// fondo negro derechoS
   tft.fillRect(400, 0, 480, 320, BLACK);
}

/////// DUBUJA UN ELIPSE COLOR NEGRO //////////////////////////
void creaHoyos()
{
    //tft.fillRoundRect(82, 304, 64, 15, 16, COLOR);
    tft.fillRoundRect(80+random(0,320), 304, 64, 15, 16, COLOR);
}

//////// DIBUJA PERSONAJE COLOR NEGRO POR PARAMETROS ///////////////
void animacionSebas(uint8_t sprite)
{
  switch(sprite)
  {
    case 1:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo1, 128, 128,COLOR);
      delay(10);
      break;
    case 2:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo2, 128, 128,COLOR);
      delay(10);
      break;
    case 3:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo3, 128, 128,COLOR);
      delay(10);
      break; 
    case 4:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo4, 128, 128,COLOR);
      delay(10);
      break; 
    case 5:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo5, 128, 128,COLOR);
      delay(10);
      break; 
    case 6:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo6, 128, 128,COLOR);
      delay(10);
      break; 
    case 7:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo9, 128, 128,COLOR);
      delay(10);
      break; 
    case 8:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo10, 128, 128,COLOR);
      delay(10);
      break; 
    case 9:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo11, 128, 128,COLOR);
      delay(10);
      break; 
    case 10:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo12, 128, 128,COLOR);
      delay(10);
      break; 
    case 11:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo13, 128, 128,COLOR);
      delay(10);
      break;  
    default:
      delay(10);
      break;
  }
}

//////// DIBUJA PERSONAJE COLOR DEL FONDO CON PARAMETRO ESPECIFICO ///////////////
void animacionSebasFondo(uint8_t sprite)
{
  switch(sprite)
  {
    case 1:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo1, 128, 128,FONDO);
      delay(10);
      break;
    case 2:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo2, 128, 128,FONDO);
      delay(10);
      break;
    case 3:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo3, 128, 128,FONDO);
      delay(10);
      break; 
    case 4:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo4, 128, 128,FONDO);
      delay(10);
      break; 
    case 5:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo5, 128, 128,FONDO);
      delay(10);
      break; 
    case 6:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo6, 128, 128,FONDO);
      delay(10);
      break; 
    case 7:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo9, 128, 128,FONDO);
      delay(10);
      break; 
    case 8:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo10, 128, 128,FONDO);
      delay(10);
      break; 
    case 9:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo11, 128, 128,FONDO);
      delay(10);
      break; 
    case 10:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo12, 128, 128,FONDO);
      delay(10);
      break; 
    case 11:
      drawBitmap(player_x,PLAYER_Y, sebastianCorriendo13, 128, 128,FONDO);
      delay(10);
      break; 
    default:
      delay(10);
      break;
  }
}
