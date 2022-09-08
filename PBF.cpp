#include "PBF.hpp"
#include "NaivePBF.hpp"
#include "SinglePBF.hpp"
#include "PBF1.hpp"
#include "PBF2.hpp"
unsigned long h1(std::string s, unsigned long arrSize)
{
    unsigned long hash = 0;
    for (unsigned long i = 0; i < s.size(); i++)
    {
        hash += (unsigned long) s[i];
        hash %= arrSize;
    }
    return hash;
}
unsigned long h2(std::string s, unsigned long arrSize)
{
    unsigned long hash = 1;
    for (unsigned long i = 0; i < s.size(); i++)
    {
        hash += pow(19, i) * s[i];
        hash %= arrSize;
    }
    return hash;
}
unsigned long h3(std::string s, unsigned long arrSize)
{
    unsigned long hash = 7;
    for (unsigned long i = 0; i < s.size(); i++)
    {
        hash *= 31;
        hash += s[i];
        hash %= arrSize;
    }
    return hash;
}
unsigned long h4(std::string s, unsigned long arrSize)
{
    unsigned long hash = 3;
    for (unsigned long i = 0; i < s.size(); i++)
    {
        hash *= 8;
        hash += s[0] * pow(7, i);
        hash %= arrSize;
    }
    return hash;
}
void naivepbf()
{
    try
    {
        unsigned long n = 20; long double p = 0.05;
        NaivePBF<std::string> bloom(n, p, { h1, h2, h3, h4, });
        bloom.insert("hello");
        bloom.insert("test");
        bloom.insert("why");
        bloom.insert("therefore");
        std::cout << bloom.find("hello") << bloom.find("test") << bloom.find("why") << bloom.find("therefore") << std::endl;
        std::cout << bloom.find("watermelon") << std::endl;
        std::cout << bloom.find("hello", 0) << bloom.find("hello", 1) << bloom.find("hello", 2) << bloom.find("hello", 3) << bloom.find("hello", 4) << std::endl;
        std::cout << bloom.find("test", 0) << bloom.find("test", 1) << bloom.find("test", 2) << bloom.find("test", 3) << bloom.find("test", 4) << std::endl;
        std::cout << bloom.find("why", 0) << bloom.find("why", 1) << bloom.find("why", 2) << bloom.find("why", 3) << bloom.find("why", 4) << std::endl;
        std::cout << bloom.find("therefore", 0) << bloom.find("therefore", 1) << bloom.find("therefore", 2) << bloom.find("therefore", 3) << bloom.find("therefore", 4) << std::endl;
    }
    catch (std::invalid_argument e)
    {
        std::cerr << e.what() << std::endl;
    }
}
void pbf1()
{
    PBF1<std::string> pbfone(20, 0.05, 2, 8, { h1, h2, h3, h4, });
    pbfone.insert("hello", 3);
    std::cout << pbfone.query("hello", 2, 4) << std::endl;
    std::cout << pbfone.query("hello", 1, 4) << std::endl;
    std::cout << pbfone.query("hello", 4, 5) << std::endl;
    std::cout << pbfone.query("hello", 1, 6) << std::endl;
    std::cout << pbfone.query("different", 1, 6) << std::endl;
}
void pbf2()
{
    PBF2<std::string> pbftwo(20, 0.05, 8, { h1, h2, h3, h4, });
    pbftwo.insert("hello", 3);
    std::cout << pbftwo.query("hello", 2, 4) << std::endl;
    std::cout << pbftwo.query("hello", 1, 4) << std::endl;
    std::cout << pbftwo.query("hello", 4, 5) << std::endl;
    std::cout << pbftwo.query("hello", 1, 6) << std::endl;
    std::cout << pbftwo.query("different", 1, 6) << std::endl;
}
void pbf()
{
    char funcNames[][100] =
    {
        "NaivePBF",
        "PBF1",
        "PBF2"
    };
    void (*funcs[])() =
    {
        naivepbf,
        pbf1,
        pbf2
    };
    int choice;
    int maxFuncs = sizeof(funcs) / sizeof(funcs)[0];
    for (int i = 0; i < maxFuncs; i++)
    {
        printf("%d: %s:\n", i + 1, funcNames[i]);
    }
    while (true)
    {
        printf("Enter selection: ");
        scanf("%d", &choice);
        getchar();
        if (choice > maxFuncs || choice <= 0)
        {
            break;
        }
        printf("%s : Output below\n", funcNames[choice - 1]);
        funcs[choice - 1]();
        printf("\n");
    }
}