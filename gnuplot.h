#include <unistd.h>

void gnuplot(int size, int max_time, SortType type) {

    if (type == Heap) {
        if (!access("heap_time.txt", 0))
            printf("File Present");
        else {
            printf("File heap_time.txt not found\n");
            exit(EEXIST);
        }
    } else {
        if (!access("bubble_time.txt", 0))
            printf("File Present");
        else {
            printf("File heap_time.txt not found\n");
            exit(EEXIST);
        }
    }
    FILE *fp = fopen("gnuplot.plt", "w");
    if (fp == NULL) {
        exit(EEXIST);
    }

    double to_sec = (1000.0 / CLOCKS_PER_SEC);
    fputs("set terminal png size 1600,900\n", fp);

    fputs("set output \"gnuplot.png\"\n", fp);

    fprintf(fp, "set xrange  [0:%d]\n", size + size / 5);
    fprintf(fp, "set yrange  [0:%d]\n", max_time + max_time / 5);

    fputs("set multiplot\n", fp);

    if (type == Heap) {
        fprintf(fp, "set key at %d, %d\n", size/6, max_time - 4 * max_time / 25);
        fprintf(fp, "plot x * log (x) * %f title \"x log x\" w l  lc 'red'\n", to_sec);
        fputs("set nokey\n", fp);
        fputs("plot \"heap_time.txt\" using 1:2 with linespoints lw 2 lt rgb '0xAARRGGBB'\n", fp);
        fputs("set nokey\n", fp);
    } else {
        fprintf(fp, "set key at %d, %d\n", size/6, max_time - 3 * max_time / 25);
        fprintf(fp, "plot x*x* %f title \"x^2\" w l lc 'blue'\n", to_sec);
        fputs("set nokey\n", fp);
        fputs("plot \"bubble_time.txt\" using 1:2 with linespoints lw 2 lt rgb '0x00000000'\n", fp);
        fputs("set nokey\n", fp);
    }
    fputs("set nomultiplot\n", fp);

    fclose(fp);

    system("gnuplot gnuplot.plt ");
}