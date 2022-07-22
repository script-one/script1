// source file: prog/lib/rnd.s1

export function rUnif(min=0,max=1)                 // (1) 
{                                                  // (1) 
    return (min+(random()*(max-min)));             // (2) 
}                                                  // (1) 
export function rInt(min,max)                      // (5) 
{                                                  // (5) 
    return floor(rUnif(min,max));                  // (6) 
}                                                  // (5) 
export function rChoose(a)                         // (9) 
{                                                  // (9) 
    return a[rInt(0,len(a))];                      // (10) 
}                                                  // (9) 

