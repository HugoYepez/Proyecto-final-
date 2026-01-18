#ifndef NOTAS_H
#define NOTAS_H

#include <stdio.h>

#define MAX 500
#define STR 100

typedef struct
{
    char codMateria[16];
    char nombreMateria[STR];
    char carrera[STR];
    char codEstudiante[16];
    char nombreEstudiante[STR];
    float n1, n2, n3;
} Registro;

extern Registro registros[MAX];
extern int total;
extern float p1, p2, p3;
extern float umbral;

void cargarCSV();
void guardarCSV();
void registrarMateria();
void listarMaterias();
void actualizarDatos();
void eliminarMateria();
float calcularNotaFinal(Registro r);
void promedioPorEstudiante();
void promedioPorMateria();
void aprobadosReprobados();
void limpiarBuffer();
void recortarSalto(char *cad);

#endif
