#include <string.h>
#include "notas.h"

Registro registros[MAX];
int total = 0;
float p1 = 30, p2 = 30, p3 = 40;
float umbral = 6.0;

void limpiarBuffer()
{
    while (getchar() != '\n')
        ;
}

void recortarSalto(char *cad)
{
    cad[strcspn(cad, "\n")] = '\0';
}

float calcularNotaFinal(Registro r)
{
    return (r.n1 * p1 + r.n2 * p2 + r.n3 * p3) / 100.0;
}

void cargarCSV()
{
    FILE *f = fopen("notas.csv", "r");
    char linea[300];

    if (!f)
        return;

    fgets(linea, sizeof(linea), f);
    total = 0;

    while (fgets(linea, sizeof(linea), f))
    {
        sscanf(linea, "%15[^,],%99[^,],%99[^,],%15[^,],%99[^,],%f,%f,%f",
               registros[total].codMateria,
               registros[total].nombreMateria,
               registros[total].carrera,
               registros[total].codEstudiante,
               registros[total].nombreEstudiante,
               &registros[total].n1,
               &registros[total].n2,
               &registros[total].n3);
        total++;
    }
    fclose(f);
}

void guardarCSV()
{
    FILE *f = fopen("notas.csv", "w");
    int i;
    if (!f)
        return;

    fprintf(f, "codigo_materia,nombre_materia,carrera,codigo_estudiante,nombre_estudiante,nota_p1,nota_p2,nota_p3\n");
    for (i = 0; i < total; i++)
    {
        fprintf(f, "%s,%s,%s,%s,%s,%.2f,%.2f,%.2f\n",
                registros[i].codMateria,
                registros[i].nombreMateria,
                registros[i].carrera,
                registros[i].codEstudiante,
                registros[i].nombreEstudiante,
                registros[i].n1,
                registros[i].n2,
                registros[i].n3);
    }
    fclose(f);
}

void registrarMateria()
{
    Registro r;
    int i;

    printf("Codigo materia: ");
    fgets(r.codMateria, 16, stdin);
    recortarSalto(r.codMateria);
    printf("Nombre materia: ");
    fgets(r.nombreMateria, STR, stdin);
    recortarSalto(r.nombreMateria);
    printf("Carrera: ");
    fgets(r.carrera, STR, stdin);
    recortarSalto(r.carrera);
    printf("Codigo estudiante: ");
    fgets(r.codEstudiante, 16, stdin);
    recortarSalto(r.codEstudiante);
    printf("Nombre estudiante: ");
    fgets(r.nombreEstudiante, STR, stdin);
    recortarSalto(r.nombreEstudiante);

    for (i = 0; i < total; i++)
    {
        if (strcmp(r.codMateria, registros[i].codMateria) == 0 &&
            strcmp(r.codEstudiante, registros[i].codEstudiante) == 0)
        {
            printf("Registro duplicado.\n");
            return;
        }
    }

    do
    {
        printf("Nota P1: ");
        scanf("%f", &r.n1);
    } while (r.n1 < 1 || r.n1 > 10);
    do
    {
        printf("Nota P2: ");
        scanf("%f", &r.n2);
    } while (r.n2 < 1 || r.n2 > 10);
    do
    {
        printf("Nota P3: ");
        scanf("%f", &r.n3);
    } while (r.n3 < 1 || r.n3 > 10);
    limpiarBuffer();

    registros[total++] = r;
}

void listarMaterias()
{
    int i;
    for (i = 0; i < total; i++)
    {
        printf("%s | %s | %s | %s | %s | %.2f | %.2f | %.2f | FINAL: %.2f\n",
               registros[i].codMateria,
               registros[i].nombreMateria,
               registros[i].carrera,
               registros[i].codEstudiante,
               registros[i].nombreEstudiante,
               registros[i].n1,
               registros[i].n2,
               registros[i].n3,
               calcularNotaFinal(registros[i]));
    }
}

void actualizarDatos()
{
    char cod[16];
    int i;
    printf("Codigo materia a actualizar: ");
    fgets(cod, 16, stdin);
    recortarSalto(cod);

    for (i = 0; i < total; i++)
    {
        if (strcmp(cod, registros[i].codMateria) == 0)
        {
            printf("Nuevo nombre materia: ");
            fgets(registros[i].nombreMateria, STR, stdin);
            recortarSalto(registros[i].nombreMateria);
            printf("Nueva nota P1: ");
            scanf("%f", &registros[i].n1);
            printf("Nueva nota P2: ");
            scanf("%f", &registros[i].n2);
            printf("Nueva nota P3: ");
            scanf("%f", &registros[i].n3);
            limpiarBuffer();
            return;
        }
    }
}

void eliminarMateria()
{
    char cod[16];
    int i, j;
    printf("Codigo materia a eliminar: ");
    fgets(cod, 16, stdin);
    recortarSalto(cod);

    for (i = 0; i < total; i++)
    {
        if (strcmp(cod, registros[i].codMateria) == 0)
        {
            printf("Confirmar borrado (s/n): ");
            if (getchar() == 's')
            {
                for (j = i; j < total - 1; j++)
                    registros[j] = registros[j + 1];
                total--;
            }
            limpiarBuffer();
            return;
        }
    }
}

void promedioPorEstudiante()
{
    int i;
    float suma = 0;
    for (i = 0; i < total; i++)
        suma += calcularNotaFinal(registros[i]);
    if (total > 0)
        printf("Promedio general estudiante: %.2f\n", suma / total);
}

void promedioPorMateria()
{
    int i;
    float suma = 0;
    for (i = 0; i < total; i++)
        suma += calcularNotaFinal(registros[i]);
    if (total > 0)
        printf("Promedio materia: %.2f\n", suma / total);
}

void aprobadosReprobados()
{
    int i;
    for (i = 0; i < total; i++)
    {
        printf("%s -> %s\n", registros[i].nombreEstudiante,
               calcularNotaFinal(registros[i]) >= umbral ? "APROBADO" : "REPROBADO");
    }
}
