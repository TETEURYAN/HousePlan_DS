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

double Min(double a, double b)
{
    return (a <= b) ? a : b; 
}

double AreaCircle(double largura, double comprimento)
{
    double min = Min(largura, comprimento);
    

    if(min == 8.7) min *= 0.95;
    else if(min < 15) min *= 0.8;
    else if(min < 25) min *= 0.7;
    else min *= 0.6;

    min /= 2;

    return min;
}