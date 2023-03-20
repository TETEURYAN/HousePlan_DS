#include <math.h>

double raio(double area)
{
    return sqrt(area/M_PI);
}

double area_coroa(double areaExterna, double areaInterna)
{
    return areaExterna - areaInterna;
}

double area_circunferencia(double raio)
{
    return pow(raio, 2) * M_PI;
}

double comprimemnto_circunferencia(double raio)
{
    return 2 * M_PI * raio;
}

double area_setor(double raio, double angulo)
{
    return (angulo * M_PI * pow(raio, 2)) / 360;
}

double coef(double x1, double x2, double y1, double y2)
{
    return ((y2 - y1)/(x2 - x1));
}

double reta(double coef, double Xpoint, double equacao)
{
    return ((coef * Xpoint) + equacao);
}
