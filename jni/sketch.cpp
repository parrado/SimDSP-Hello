// Archivo de cabecera de SimDSP
#include <simdsp.h>

// Frecuencia de muestreo
#define F_S 44100

// Tamaño del bloque de datos
#define N_DATA 512

// Señal de salida
short y[N_DATA];

// Rutina que simulará la ISR que se invoca una vez ha finalizado
// la transferencia por DMA, audio apunta a los datos que se procesarán
void process_data(short *x)
{

  // Para ciclo for
  int n;

  // Muestra anterior de filtro pasa-altos
  static double xn1 = 0.0;

  // Invoca captura por DMA nuevamente
  captureBlock(process_data);

  // Inicia procesamiento
  for (n = 0; n < N_DATA; n++)
  {
    // Salida igual a entrada
    y[n] = x[n];
    // Actualiza muestra anterior
    xn1 = x[n];
  }
  // Reproduce señal
  playBlock(y);
}

// Funcion de inicializacion
void dsp_setup()
{
  // Habilita sistema de audio del teléfono
  enableAudio(N_DATA, F_S);

  // Imprime tasa de muestreo actual
  println("Sampling frequency is %d Hz and buffer size is %d samples", F_S, N_DATA);

  // Inicia captura por DMA
  captureBlock(process_data);
}
