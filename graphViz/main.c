#include <stdio.h>
#include <stdlib.h>

int main()
{
    char* dotExePath = getenv("GRAPHVIZ_DOT");
    if (dotExePath == NULL)
    {
        dotExePath = "C:\\Program Files\\Graphviz\\bin\\dot.exe";  // Установка пути к dot.exe по умолчанию
    }

    int matrix[4][4] = { {0, 1, 0, 1}, {1, 0, 1, 0}, {0, 1, 0, 0}, {1, 0, 1, 0}};

    char graphDotName[] = "graph.dot";
    char graphPngName[] = "graph.png";
    FILE* file = fopen(graphDotName, "w");
    fprintf(file, "graph G {\n");
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = i; j < 4; ++j)
        {
            if (matrix[i][j] == 1)
            {
                fprintf(file, "%d -- %d;\n", i, j);
            }
        }
    }
    fprintf(file, "}\n");
    fclose(file);

    char command[100] = { 0 };
    sprintf(command, "\"%s\" -Tpng %s -o %s", dotExePath, graphDotName, graphPngName);
    system(command);

    char command2[100] = { 0 };
    sprintf(command, "start %s", graphPngName);
    system(command, graphPngName);

    return 0;
}
