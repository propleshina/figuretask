#include <windows.h>
#include <iostream>

typedef double (*CalculateAreaFunc) (double, double);
typedef double (*CalculatePerimeterFunc)(double, double);
typedef void (*GetDescriptionFunc) (char*, int);
typedef void (*SetColorFunc) (const char*);
typedef void (*IsFilledFunc) (bool);
int main() {
    HINSTANCE hLib = LoadLibrary("C:\\Users\\ogilk\\source\\repos\\source\\x64\\Debug\\source.dll"); 
    if (!hLib) {
        std::cerr << "Cannot load library" << std::endl;
        return -1;
    }
    CalculateAreaFunc CalculateArea = (CalculateAreaFunc)GetProcAddress(hLib, "CalculateArea");
    CalculatePerimeterFunc CalculatePerimeter = (CalculatePerimeterFunc)GetProcAddress(hLib, "CalculatePerimeter");
    GetDescriptionFunc GetDescription = (GetDescriptionFunc)GetProcAddress(hLib, "GetDescription");
    SetColorFunc SetColor = (SetColorFunc)GetProcAddress(hLib, "SetColor");
    IsFilledFunc IsFilled = (IsFilledFunc)GetProcAddress(hLib, "IsFilled");
    if (!CalculateArea  || !CalculatePerimeter || !GetDescription || !SetColor || !IsFilled) {
        std::cerr << "Failed to load one or more functions" << std::endl;
        FreeLibrary(hLib);
        return -2;
    }

    double width = 5.0;
    double height = 6.0;
    std::cout << "Area: " << CalculateArea(width, height) << std::endl;
    std::cout << "Perimeter: " << CalculatePerimeter(width, height) << std::endl;
    char description[50];
    GetDescription(description, 50);
    std::cout << "Description: " << description << std::endl;

    SetColor("Blue");
    IsFilled(true);
    FreeLibrary(hLib);
    return 0;
}