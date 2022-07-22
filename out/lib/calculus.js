// source file: prog/lib/calculus.s1

export function df(f,x,h=0.001)                    // (3) 
{                                                  // (3) 
    let dy=(f((x+h))-f(x));                        // (4) 
    return (dy/h);                                 // (5) 
}                                                  // (3) 
export function integral(f,a,b,h=0.001)            // (9) 
{                                                  // (9) 
    let area=0.0;                                  // (10) 
    for (let x of range(a,b,h))                    // (11) 
    {                                              // (11) 
        area=(area+(f(x)*h));                      // (12) 
    };                                             // (11) 
                                                   // (11) 
    return area;                                   // (14) 
}                                                  // (9) 

