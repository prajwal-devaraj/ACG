#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *gp = popen("gnuplot -persistent", "w");
    if (gp == NULL) {
        printf("Error: Could not open gnuplot.\n");
        return 1;
    }

    // Set terminal to PNG (no GUI needed in Codespaces)
    fprintf(gp, "set terminal pngcairo size 1200,600 enhanced font 'Arial,12'\n");
    fprintf(gp, "set output 'frustum.png'\n");

    // Create two subplots
    fprintf(gp, "set multiplot layout 1,2 title 'Frustum Visualization'\n");

    // ---- Perspective Projection ----
    fprintf(gp, "set title 'Perspective Projection Frustum'\n");
    fprintf(gp, "unset key\n");
    fprintf(gp, "set xrange [-2:2]\n");
    fprintf(gp, "set yrange [-2:2]\n");
    fprintf(gp, "set zrange [0:5]\n");
    fprintf(gp, "set view 60,30\n");
    fprintf(gp, "set ticslevel 0\n");

    // Perspective frustum (trapezoid pyramid)
    fprintf(gp, "splot '-' with lines lw 2 lc rgb 'blue'\n");
    // Near plane square
    fprintf(gp, "-1 -1 1\n1 -1 1\n1 1 1\n-1 1 1\n-1 -1 1\n\n");
    // Far plane square (bigger)
    fprintf(gp, "-2 -2 4\n2 -2 4\n2 2 4\n-2 2 4\n-2 -2 4\n\n");
    // Connecting edges
    fprintf(gp, "-1 -1 1\n-2 -2 4\n\n");
    fprintf(gp, "1 -1 1\n2 -2 4\n\n");
    fprintf(gp, "1 1 1\n2 2 4\n\n");
    fprintf(gp, "-1 1 1\n-2 2 4\n\n");
    fprintf(gp, "e\n");

    // Labels
    fprintf(gp, "set label 'Near Plane' at 0,1,1.2 center\n");
    fprintf(gp, "set label 'Far Plane' at 0,2.5,4.2 center\n");

    // ---- Orthographic Projection ----
    fprintf(gp, "set title 'Orthographic Projection Frustum'\n");
    fprintf(gp, "unset key\n");
    fprintf(gp, "set xrange [-2:2]\n");
    fprintf(gp, "set yrange [-2:2]\n");
    fprintf(gp, "set zrange [0:5]\n");
    fprintf(gp, "set view 60,30\n");
    fprintf(gp, "set ticslevel 0\n");

    // Orthographic frustum (cube-like box)
    fprintf(gp, "splot '-' with lines lw 2 lc rgb 'red'\n");
    // Near plane square
    fprintf(gp, "-1 -1 1\n1 -1 1\n1 1 1\n-1 1 1\n-1 -1 1\n\n");
    // Far plane square (same size as near)
    fprintf(gp, "-1 -1 4\n1 -1 4\n1 1 4\n-1 1 4\n-1 -1 4\n\n");
    // Connecting edges
    fprintf(gp, "-1 -1 1\n-1 -1 4\n\n");
    fprintf(gp, "1 -1 1\n1 -1 4\n\n");
    fprintf(gp, "1 1 1\n1 1 4\n\n");
    fprintf(gp, "-1 1 1\n-1 1 4\n\n");
    fprintf(gp, "e\n");

    // Labels
    fprintf(gp, "set label 'Near Plane' at 0,1,1.2 center\n");
    fprintf(gp, "set label 'Far Plane' at 0,1,4.2 center\n");

    fprintf(gp, "unset multiplot\n");

    fflush(gp);
    pclose(gp);

    printf("Frustum diagram saved as frustum.png\n");
    return 0;
}
