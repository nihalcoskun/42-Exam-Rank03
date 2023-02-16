/* Assignment name  : ft_printf
Expected files   : ft_printf.c
Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------

Write a function named `ft_printf` that will mimic the real printf but
it will manage only the following conversions: s,d and x.

Your function must be declared as follows:

int ft_printf(const char *, ... );

Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
To test your program compare your results with the true printf.

Exemples of the function output:

call: ft_printf("%s\n", "toto");
out: toto$

call: ft_printf("Magic %s is %d", "number", 42);
out: Magic number is 42%

call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
out: Hexadecimal for 42 is 2a$*/

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

int ft_putstr(char *str)
{
    int count = 0;

    if(!str)
    {
        count += write(1,"(null)",6);
        return (count);
    }
    while(*str)
    {
        count += write(1,str++,1);
    }
    return (count);
}

int ft_putnbr(long num, int base)
{
    int count = 0;
    if(num < 0)
    {
        num *= -1;
        count += write(1,"-",1);
    } 
    if(num > (base -1))
    {
        count += ft_putnbr((num / base), base);
    }
    count += write(1,&"0123456789abcdef"[num % base],1);
    return (count);
}



int ft_printf(const char *str, ... )
{
    int count = 0;
    va_list list;

    va_start(list,str);

    while(*str)
    {
        if(*str == '%')
        {
            str++;
            if(*str == 's')
            {
                count += ft_putstr(va_arg(list, char*));
            }
            else if(*str == 'd')
            {
                count += ft_putnbr(va_arg(list, int), 10);
            }
            else if(*str == 'x')
            {
                count += ft_putnbr(va_arg(list, unsigned int), 16);
            }
        }
        else
        {
            count += write(1,str,1);
        }
        str++;
    }
    return (count);
}

int main()
{
    ft_printf("%s\n", "toto");
    ft_printf("Magic %s is %d", "number", 42);
    ft_printf("Hexadecimal for %d is %x\n", 42, 42);
}