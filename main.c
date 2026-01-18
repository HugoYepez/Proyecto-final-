#include "notas.h"

int main()
{
    int op;
    cargarCSV();

    do
    {
        printf("\n1. Registrar\n2. Listar\n3. Actualizar\n4. Eliminar\n5. Promedios\n6. Guardar\n0. Salir\n");
        scanf("%d", &op);
        limpiarBuffer();

        switch (op)
        {
        case 1:
            registrarMateria();
            break;
        case 2:
            listarMaterias();
            break;
        case 3:
            actualizarDatos();
            break;
        case 4:
            eliminarMateria();
            break;
        case 5:
            promedioPorEstudiante();
            promedioPorMateria();
            aprobadosReprobados();
            break;
        case 6:
            guardarCSV();
            break;
        }
    } while (op != 0);

    guardarCSV();
    return 0;
}